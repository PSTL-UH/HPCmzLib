#include "UnimodLoader.h"
#include "../Proteomics/ModificationWithLocation.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/ModificationWithMassAndCf.h"

using namespace Chemistry;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases {

const std::unordered_map<std::string, std::string> UnimodLoader::DictOfElements = std::unordered_map<std::string, std::string> {
    {"2H", "H{2}"}, {
    {"18O", "O{18}"}, {
    };
const std::unordered_map<position_t, TerminusLocalization> UnimodLoader::positionDict = std::unordered_map<position_t, TerminusLocalization> {
    {position_t::AnyCterm, TerminusLocalization::PepC}, {
    {position_t::Anywhere, TerminusLocalization::Any}, {
    {position_t::ProteinNterm, TerminusLocalization::NProt}
    };

    std::vector<ModificationWithLocation*> UnimodLoader::ReadMods(const std::string &unimodLocation) {
        auto unimodSerializer = new XmlSerializer(unimod_t::typeid);
        FileStream tempVar(unimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        auto deserialized = dynamic_cast<unimod_t*>(unimodSerializer->Deserialize(&tempVar));

        for (auto cool : deserialized->getmodifications()) {
            auto id = cool->gettitle();
            auto ac = cool->getrecord_id();
            ChemicalFormula *cf = new ChemicalFormula();
            for (auto el : cool->getdelta()->getelement()) {
                try {
                    cf->Add(el->getsymbol(), std::stoi(el->getnumber()));
                }
                catch (...) {
                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el->getsymbol()]);
                    tempCF->Multiply(std::stoi(el->getnumber()));
                    cf->Add(tempCF);
                }
            }

            for (auto nice : cool->getspecificity()) {
                auto tg = nice->getsite();
                if (tg.length() > 1) {
                    tg = "X";
                }
                ModificationMotif motif;
                ModificationMotif::TryGetMotif(tg, motif);
                auto pos = nice->getposition();
                std::unordered_map<std::string, std::vector<std::string>> dblinks = {
                {
                        "Unimod", {std::to_string(ac)}
                }
                };

                if (nice->getNeutralLoss().empty()) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new ModificationWithMassAndCf(id + " on " + motif + " at " + positionDict[pos], "Unimod", motif, positionDict[pos], cf, , dblinks);
                }
                else {
                    std::vector<double> neutralLosses;
                    for (auto nl : nice->getNeutralLoss()) {
                        ChemicalFormula *cfnl = new ChemicalFormula();
                        if (nl->getmono_mass() == 0) {
                            neutralLosses.push_back(0);
                        }
                        else {
                            for (auto el : nl->getelement()) {
                                try {
                                    cfnl->Add(el->getsymbol(), std::stoi(el->getnumber()));
                                }
                                catch (...) {
                                    auto tempCF = ChemicalFormula::ParseFormula(DictOfElements[el->getsymbol()]);
                                    tempCF->Multiply(std::stoi(el->getnumber()));
                                    cfnl->Add(tempCF);
                                }
                            }
                        }
                        neutralLosses.push_back(cfnl->getMonoisotopicMass());

                        delete cfnl;
                    }

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return new ModificationWithMassAndCf(id + " on " + motif + " at " + positionDict[pos], "Unimod", motif, positionDict[pos], cf, , dblinks, , neutralLosses);
                }
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete cf' statement was not added since cf was passed to a method or constructor. Handle memory management manually.
        }

        delete unimodSerializer;
    }
}
