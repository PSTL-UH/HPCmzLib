#include "UnimodLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../MassSpectrometry/Enums/DissociationType.h"

using namespace Chemistry;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases
{

    std::unordered_map<std::string, std::string> UnimodLoader::DictOfElements =
    {
        {"2H", "H{2}"},
        {"13C", "C{13}"},
        {"18O", "O{18}"},
        {"15N", "N{15}"}
    };
    
    std::unordered_map<position_t, ModLocationOnPeptideOrProtein> UnimodLoader::positionDict =
    {
        {position_t::AnyCterm, ModLocationOnPeptideOrProtein::PepC},
        {position_t::ProteinCterm, ModLocationOnPeptideOrProtein::ProtC},
        {position_t::Anywhere, ModLocationOnPeptideOrProtein::Any},
        {position_t::AnyNterm, ModLocationOnPeptideOrProtein::NPep},
        {position_t::ProteinNterm, ModLocationOnPeptideOrProtein::NProt}
    };
    
    std::vector<Modification*> UnimodLoader::ReadMods(const std::string &unimodLocation)
    {
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto unimodSerializer = new XmlSerializer(typeof(unimod_t));
        FileStream tempVar(unimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        auto deserialized = dynamic_cast<unimod_t*>(unimodSerializer->Deserialize(&tempVar));

        std::unordered_map<std::string, std::string> positionConversion =
        {
            {"Anywhere", "Anywhere."},
            {"AnyNterm", "Peptide N-terminal."},
            {"AnyCterm", "Peptide C-terminal."},
            {"ProteinNterm", "N-terminal."},
            {"ProteinCterm", "C-terminal."}
        };

        for (auto mod : deserialized->getmodifications())
        {
            auto id = mod->gettitle();
            auto ac = mod->getrecord_id();
            ChemicalFormula *cf = new ChemicalFormula();
            for (auto el : mod->getdelta()->getelement())
            {
                try
                {
                    cf->Add(el->getsymbol(), std::stoi(el->getnumber()));
                }
                catch (...)
                {
                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el->getsymbol()]);
                    tempCF->Multiply(std::stoi(el->getnumber()));
                    cf->Add(tempCF);
                }
            }

            //TODO Add "on motif" to the ID field
            for (auto target : mod->getspecificity())
            {
                auto tg = target->getsite();
                if (tg.length() > 1)
                {
                    tg = "X"; //I think that we should allow motifs here using the trygetmotif
                }
                ModificationMotif motif;
                ModificationMotif::TryGetMotif(tg, motif);

                string pos;
                std::unordered_map<std::string, std::string>::const_iterator positionConversion_iterator = positionConversion.find(target.position.ToString());
                if (positionConversion_iterator != positionConversion.end())
                {
                    pos = positionConversion_iterator->second;
                    //do nothing, the new string value should be there
                }
                else
                {
                    pos = positionConversion_iterator->second;
                    pos = nullptr;
                }

                std::unordered_map<std::string, std::vector<std::string>> dblinks =
                {
                    {
                        "Unimod", {std::to_string(ac)}
                    }
                };

                if (target->getNeutralLoss().empty())
                {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new Modification(id, "", "Unimod", "", motif, pos, cf, std::nullopt, dblinks, std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
                }
                else
                {
                    std::unordered_map<MassSpectrometry::DissociationType, std::vector<double>> neutralLosses;
                    for (auto nl : target->getNeutralLoss())
                    {
                        ChemicalFormula *cfnl = new ChemicalFormula();
                        if (nl->getmono_mass() == 0)
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
                                    if (!std::find(neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].begin(), neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].end(), 0) != neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].end())
                                    {
                                        neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].push_back(0);
                                    }
                                } //we don't need an else cuz it's already there
                            }
                        }
                        else
                        {
                            for (auto el : nl->getelement())
                            {
                                try
                                {
                                    cfnl->Add(el->getsymbol(), std::stoi(el->getnumber()));
                                }
                                catch (...)
                                {
                                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el->getsymbol()]);
                                    tempCF->Multiply(std::stoi(el->getnumber()));
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
                                    if (!std::find(neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].begin(), neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].end(), cfnl->getMonoisotopicMass()) != neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].end())
                                    {
                                        neutralLosses[MassSpectrometry::DissociationType::AnyActivationType].push_back(cfnl->getMonoisotopicMass());
                                    }
                                } //we don't need an else cuz it's already there
                            }
                        }

                        delete cfnl;
                    }
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new Modification(id, "", "Unimod", "", motif, "Anywhere.", cf, std::nullopt, dblinks, std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), neutralLosses, std::unordered_map<DissociationType, std::vector<double>>(), "");
                }
            }

            delete cf;
        }

        delete unimodSerializer;
    }
}
