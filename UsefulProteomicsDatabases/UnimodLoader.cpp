#include "UnimodLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/PeriodicTable.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../MassSpectrometry/Enums/DissociationType.h"

#include <iostream>
#include <fstream>
#include <string>

namespace UsefulProteomicsDatabases
{

    std::unordered_map<std::string, std::string> UnimodLoader::DictOfElements =
    {
        {"2H", "H{2}"},
        {"13C", "C{13}"},
        {"18O", "O{18}"},
        {"15N", "N{15}"}
    };

#ifdef ORIG
    //EDGAR: seems to be unused, but causes compilation problems. Deactivating for now.
    std::unordered_map<position_t, ModLocationOnPeptideOrProtein> UnimodLoader::positionDict =
    {
        {position_t::Any_C_term, ModLocationOnPeptideOrProtein::PepC},
        {position_t::Protein_C_term, ModLocationOnPeptideOrProtein::ProtC},
        {position_t::Anywhere, ModLocationOnPeptideOrProtein::Any},
        {position_t::Any_N_term, ModLocationOnPeptideOrProtein::NPep},
        {position_t::Protein_N_term, ModLocationOnPeptideOrProtein::NProt}
    };
#endif
    
    std::vector<Modification*> UnimodLoader::ReadMods(const std::string &unimodLocation)
    {
        std::vector<Modification*> retvec;

#ifdef ORIG
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto unimodSerializer = new XmlSerializer(typeof(unimod_t));
        FileStream tempVar(unimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        auto deserialized = dynamic_cast<unimod_t*>(unimodSerializer->Deserialize(&tempVar));
#endif
        std::ifstream fs (unimodLocation);
        auto deserialized = unimod(fs, xml_schema::flags::dont_validate );

        std::unordered_map<std::string, std::string> positionConversion =
        {
            {"Anywhere", "Anywhere."},
            {"AnyNterm", "Peptide N-terminal."},
            {"AnyCterm", "Peptide C-terminal."},
            {"ProteinNterm", "N-terminal."},
            {"ProteinCterm", "C-terminal."}
        };
        int ii=0;
        for (auto mod : deserialized->modifications().get().mod())
        {
            auto id = mod.title();
            auto ac = mod.record_id();
            ChemicalFormula *cf = new ChemicalFormula();
            for (auto el : mod.delta().element())
            {
                auto elem = PeriodicTable::GetElement(el.symbol());
                if (elem != nullptr ) {
                    cf->Add(elem, el.number());
                }
                else 
                {
                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el.symbol()]);
                    tempCF->Multiply(el.number() );
                    cf->Add(tempCF);                        
                }
            }

            //TODO Add "on motif" to the ID field
            for (auto target : mod.specificity())
            {
                auto tg = target.site();
                if (tg.length() > 1)
                {
                    tg = "X"; //I think that we should allow motifs here using the trygetmotif
                }
                ModificationMotif* motif;
                ModificationMotif::TryGetMotif(tg, &motif);

                std::string pos;
                std::unordered_map<std::string, std::string>::const_iterator positionConversion_iterator = positionConversion.find(target.position() );
                if (positionConversion_iterator != positionConversion.end())
                {
                    pos = positionConversion_iterator->second;
                    //do nothing, the new string value should be there
                }

                std::string s = std::to_string(ac.get());
                std::vector<std::string> svec = {s};
                std::unordered_map<std::string, std::vector<std::string>> dblinks;
                dblinks.emplace("Unimod", svec);

                if (target.NeutralLoss().empty())
                {
#ifdef ORIG
                    yield return new Modification(id, "", "Unimod", "", motif, pos, cf, std::nullopt, dblinks,
                                                  std::unordered_map<std::string, std::vector<std::string>>(),
                                                  std::vector<std::string>(),
                                                  std::unordered_map<DissociationType, std::vector<double>>(),
                                                  std::unordered_map<DissociationType, std::vector<double>>(), "");
#endif
                    auto tmp =  new Modification(id, "", "Unimod", "", motif, pos, cf, std::nullopt, dblinks,
                                                 std::unordered_map<std::string, std::vector<std::string>>(),
                                                 std::vector<std::string>(),
                                                 std::unordered_map<DissociationType, std::vector<double>>(),
                                                 std::unordered_map<DissociationType, std::vector<double>>(), "");
                    retvec.push_back(tmp);
                }
                else
                {
                    std::unordered_map<MassSpectrometry::DissociationType, std::vector<double>> neutralLosses;
                    for (auto nl : target.NeutralLoss())
                    {
                        ChemicalFormula *cfnl = new ChemicalFormula();
                        if (nl.mono_mass() == 0)
                        {
                            if (neutralLosses.empty())
                            {
                                neutralLosses = std::unordered_map<MassSpectrometry::DissociationType, std::vector<double>>
                                {
                                    {
                                        MassSpectrometry::DissociationType::AnyActivationType, {0}
                                    }
                                };
                            }
                            else
                            {
                                if (neutralLosses.find(MassSpectrometry::DissociationType::AnyActivationType) != neutralLosses.end())
                                {
                                    auto shortcut = neutralLosses[MassSpectrometry::DissociationType::AnyActivationType];
                                    if ( std::find(shortcut.begin(), shortcut.end(), 0) == shortcut.end())
                                    {
                                        neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].push_back(0);
                                    }
                                } //we don't need an else cuz it's already there
                            }
                        }
                        else
                        {
                            for (auto el : nl.element())
                            {
                                auto elem = PeriodicTable::GetElement(el.symbol());
                                if ( elem != nullptr ) {
                                    cfnl->Add(elem, el.number() );
                                }
                                else
                                {
                                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el.symbol()]);
                                    tempCF->Multiply( el.number() );
                                    cfnl->Add(tempCF);
                                }
                            }

                            if (neutralLosses.empty())
                            {
                                neutralLosses = std::unordered_map<MassSpectrometry::DissociationType, std::vector<double>>
                                {
                                    {
                                        MassSpectrometry::DissociationType::AnyActivationType, {cfnl->getMonoisotopicMass()}
                                    }
                                };
                            }
                            else
                            {
                                if (neutralLosses.find(MassSpectrometry::DissociationType::AnyActivationType) != neutralLosses.end())
                                {
                                    auto shortcut =neutralLosses[MassSpectrometry::DissociationType::AnyActivationType]; 
                                    if (std::find(shortcut.begin(), shortcut.end(), cfnl->getMonoisotopicMass()) == shortcut.end())
                                    {
                                        neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].push_back(cfnl->getMonoisotopicMass());
                                    }
                                } //we don't need an else cuz it's already there
                            }
                        }

                        delete cfnl;
                    }
#ifdef ORIG
                    yield return new Modification(id, "", "Unimod", "", motif, "Anywhere.", cf, std::nullopt, dblinks,
                                                  std::unordered_map<std::string, std::vector<std::string>>(),
                                                  std::vector<std::string>(), neutralLosses,
                                                  std::unordered_map<DissociationType, std::vector<double>>(), "");
#endif
                    auto tmp2 = new Modification(id, "", "Unimod", "", motif, "Anywhere.", cf, std::nullopt, dblinks,
                                                 std::unordered_map<std::string, std::vector<std::string>>(),
                                                 std::vector<std::string>(), neutralLosses,
                                                 std::unordered_map<DissociationType, std::vector<double>>(), "");
                    retvec.push_back(tmp2);
                }
            }
        }

        //delete unimodSerializer;
        return retvec;
    }
}
