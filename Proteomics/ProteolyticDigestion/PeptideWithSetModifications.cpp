#include "PeptideWithSetModifications.h"
#include "../Modifications/Modification.h"
#include "DigestionParams.h"
#include "../Protein/Protein.h"
#include "../../MzLibUtil/MzLibException.h"
#include "../../Chemistry/ClassExtensions.h"
#include "../Fragmentation/TerminusSpecificProductTypes.h"
#include "../Fragmentation/DissociationTypeCollection.h"
#include "../Fragmentation/CompactPeptide.h"
#include <algorithm>
#include <filesystem>

#include "BinaryPack.h"
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        std::string PeptideWithSetModifications::getFullSequence() const
        {
            return privateFullSequence;
        }

        void PeptideWithSetModifications::setFullSequence(const std::string &value)
        {
            privateFullSequence = value;
        }

        std::string PeptideWithSetModifications::getDigestionParamString() const
        {
            return DigestionParamString;
        }

        std::string PeptideWithSetModifications::getProteinAccession() const
        {
            return ProteinAccession;
        }

        void PeptideWithSetModifications::setProteinAccession(std::string accession)
        {
            ProteinAccession = accession;
        }

        const double PeptideWithSetModifications::WaterMonoisotopicMass = PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() * 2 +
            PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass();


        PeptideWithSetModifications::PeptideWithSetModifications(Proteomics::Protein *protein,
                                                                 Proteomics::ProteolyticDigestion::DigestionParams *digestionParams,
                                                                 int oneBasedStartResidueInProtein,
                                                                 int oneBasedEndResidueInProtein,
                                                                 CleavageSpecificity cleavageSpecificity,
                                                                 const std::string &peptideDescription,
                                                                 int missedCleavages,
                                                                 std::unordered_map<int, Modification*> &allModsOneIsNterminus,
                                                                 int numFixedMods) :
            ProteolyticPeptide(protein, oneBasedStartResidueInProtein,
                               oneBasedEndResidueInProtein, missedCleavages,
                               cleavageSpecificity, peptideDescription),
            NumFixedMods(numFixedMods),
            ProteinAccession(protein->getAccession())
        {
            _allModsOneIsNterminus = allModsOneIsNterminus;
            if (digestionParams != nullptr)
            {
                DigestionParamString = digestionParams->ToString();
                _digestionParams =  DigestionParams::FromString(DigestionParamString);
            }
            DetermineFullSequence();
            UpdateCleavageSpecificity();
        }

        PeptideWithSetModifications::PeptideWithSetModifications(const std::string &sequence,
                                                                 std::unordered_map<std::string, Modification*> &allKnownMods,
                                                                 int numFixedMods,
                                                                 Proteomics::ProteolyticDigestion::DigestionParams *digestionParams,
                                                                 Proteomics::Protein *p,
                                                                 int oneBasedStartResidueInProtein,
                                                                 int oneBasedEndResidueInProtein,
                                                                 int missedCleavages,
                                                                 CleavageSpecificity cleavageSpecificity,
                                                                 const std::string &peptideDescription) :
            ProteolyticPeptide(p, oneBasedStartResidueInProtein, oneBasedEndResidueInProtein, missedCleavages,
                               cleavageSpecificity, peptideDescription),
            NumFixedMods(numFixedMods)
        {
            if (sequence.find("|") != std::string::npos)
            {
                throw MzLibUtil::MzLibException("Ambiguous peptide cannot be parsed from string: " + sequence);
            }

            setFullSequence(sequence);
            GetModsAfterDeserialization(allKnownMods, _baseSequence);

            if (p != nullptr)
            {
                ProteinAccession = p->getAccession();
            }
            if (digestionParams != nullptr)
            {
                DigestionParamString = digestionParams->ToString();
                _digestionParams =  DigestionParams::FromString(DigestionParamString);
            }
        }

        Proteomics::ProteolyticDigestion::DigestionParams *PeptideWithSetModifications::getDigestionParams() const
        {
            return _digestionParams;
        }

        std::unordered_map<int, Modification*> &PeptideWithSetModifications::getAllModsOneIsNterminus() 
        {
            return _allModsOneIsNterminus;
        }

        int PeptideWithSetModifications::getNumMods() const
        {
            return _allModsOneIsNterminus.size();
        }

        int PeptideWithSetModifications::getNumVariableMods() const
        {
            return getNumMods() - NumFixedMods;
        }

        double PeptideWithSetModifications::getMonoisotopicMass()
        {
            if (!_monoisotopicMass)
            {
                double monoMass = WaterMonoisotopicMass;
                std::unordered_map<int, Modification*> mods = _allModsOneIsNterminus;
                for ( auto mod=mods.begin(); mod != mods.end(); mod++  )
                {
                    //monoMass += mod->second.MonoisotopicMass->Value;
                    monoMass += mod->second->getMonoisotopicMass().value();
                }
#ifdef ORIG
                monoMass += getBaseSequence().Select([&] (std::any b)
                {
                    Residue::ResidueMonoisotopicMass[b];
                }).Sum();
#endif
                for ( auto b: getBaseSequence() ) {
                    if ( Residue::ResidueMonoisotopicMass.size() == 0 ) {
                        // this should trigger the static constructor
                        monoMass += Residue::GetResidue(b)->getMonoisotopicMass();
                    }
                    else {
                        monoMass += Residue::ResidueMonoisotopicMass[b];
                    }
                }
                _monoisotopicMass = std::make_optional(monoMass);
            }
            return Chemistry::ClassExtensions::RoundedDouble(_monoisotopicMass).value();
        }

        std::string PeptideWithSetModifications::getSequenceWithChemicalFormulas()
        {
            if (!_hasChemicalFormulas)
            {
                bool b=true;
                _hasChemicalFormulas = std::make_optional(b);
                auto subsequence = new StringBuilder();

                // variable modification on peptide N-terminus
                Modification *pep_n_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = _allModsOneIsNterminus.find(1);
                if (AllModsOneIsNterminus_iterator != _allModsOneIsNterminus.end())
                {
                    pep_n_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                    Modification *jj = dynamic_cast<Modification*>(pep_n_term_variable_mod);
                    if (jj != nullptr)
                    {
                        subsequence->append(StringHelper::toString('[') + jj->getChemicalFormula()->getFormula() + StringHelper::toString(']'));
                    }
                    else
                    {
                        delete subsequence;
                        return "";
                    }
                }

                for (int r = 0; r < getLength(); r++)
                {
                    subsequence->append(this->operator[](r));
                    // variable modification on this residue
                    Modification *residue_variable_mod;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus2_iterator = _allModsOneIsNterminus.find(r + 2);
                    if (AllModsOneIsNterminus2_iterator != _allModsOneIsNterminus.end())
                    {
                        residue_variable_mod = AllModsOneIsNterminus2_iterator->second;
                        Modification *jj = dynamic_cast<Modification*>(residue_variable_mod);
                        if (jj != nullptr)
                        {
                            subsequence->append(StringHelper::toString('[') + jj->getChemicalFormula()->getFormula() + StringHelper::toString(']'));
                        }
                        else
                        {
                            delete subsequence;
                            return "";
                        }
                    }
                }

                // variable modification on peptide C-terminus
                Modification *pep_c_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus3_iterator = _allModsOneIsNterminus.find(getLength() + 2);
                if (AllModsOneIsNterminus3_iterator != _allModsOneIsNterminus.end())
                {
                    pep_c_term_variable_mod = AllModsOneIsNterminus3_iterator->second;
                    Modification *jj = dynamic_cast<Modification*>(pep_c_term_variable_mod);
                    if (jj != nullptr)
                    {
                        subsequence->append(StringHelper::toString('[') + jj->getChemicalFormula()->getFormula() + StringHelper::toString(']'));
                    }
                    else
                    {
                        delete subsequence;
                        return "";
                    }
                }

                _sequenceWithChemicalFormulas = subsequence->toString();

                delete subsequence;
            }
            return _sequenceWithChemicalFormulas;
        }

        std::vector<Product*> PeptideWithSetModifications::Fragment(DissociationType dissociationType,
                                                                    FragmentationTerminus fragmentationTerminus)
        {
            // molecular ion
            //yield return new Product(ProductType.M, new NeutralTerminusFragment(FragmentationTerminus.None,
            //this.MonoisotopicMass, Length, Length), 0);
            std::vector<Product*> v;

#if ORIG
             std::unordered_map<FragmentationTerminus, std::vector<ProductType>> productCollection =
                 TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus[fragmentationTerminus].Intersect(
                     DissociationTypeCollection::ProductsFromDissociationType[dissociationType]);
#endif
             
             std::vector<ProductType> &v1 = TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus[fragmentationTerminus];
             std::vector<ProductType> &v2 = DissociationTypeCollection::ProductsFromDissociationType[dissociationType];
             std::vector<ProductType> vInter;
             for ( auto p: v1 )  {
                 for ( auto q: v2 ) {
                     if ( p == q ) {
                         vInter.push_back(p);
                     }
                 }
             }
             std::unordered_map<FragmentationTerminus, std::vector<ProductType>> productCollection = {{fragmentationTerminus, vInter}};
             
             std::vector<std::tuple<ProductType, int>> skippers;
#ifdef ORIG
            for (auto product : productCollection->Where([&] (std::any f)
            {
                return f != ProductType::zDot;
            }))
            {
                skippers.push_back((product, getBaseSequence().length()));
            }
#endif
            for (auto product=productCollection.begin(); product != productCollection.end(); product++ ) {
                for ( auto type = product->second.begin(); type != product->second.end(); type ++ ) {
                    if ( *type != ProductType::zDot ) {
                        int len = getBaseSequence().length();
                        skippers.push_back(std::make_tuple(*type, len));
                    }
                }
            }
            
            switch (dissociationType)
            {
                case DissociationType::CID:
                    skippers.push_back(std::make_tuple(ProductType::b, 1));
                    break;

                case DissociationType::ETD:
                case DissociationType::ECD:
                case DissociationType::EThcD:
                {
                    // skippers.AddRange(GetProlineZIonIndicies());
                    std::vector<std::tuple<ProductType, int>> zv = GetProlineZIonIndicies();
                    for ( auto zve = zv.begin(); zve != zv.end(); zve++ ) {
                        skippers.push_back(*zve);
                    }
                    break;
                }
                default:
                    break;
            }

            for (auto k :  productCollection) {
                for (auto productType : std::get<1>(k) )  {
                    // we're separating the N and C terminal masses and computing a separate
                    // compact peptide for each one. This speeds 
                    // calculations up without producing unnecessary terminus fragment info
                    FragmentationTerminus temporaryFragmentationTerminus = TerminusSpecificProductTypes::ProductTypeToFragmentationTerminus[productType];
                    CompactPeptide tempVar(this, temporaryFragmentationTerminus);
                    std::vector<NeutralTerminusFragment*> terminalMasses = tempVar.getTerminalMasses();

                    for (int f = 0; f < (int)terminalMasses.size(); f++)
                    {
                        // fragments with neutral loss
                        Modification* mod;
                        std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = _allModsOneIsNterminus.find(terminalMasses[f]->AminoAcidPosition + 1);
                        std::vector<double> neutralLosses;
                        if (AllModsOneIsNterminus_iterator != _allModsOneIsNterminus.end() ){
                            mod = AllModsOneIsNterminus_iterator->second;
                            auto modNeutralLosses = mod->getNeutralLosses();
                            if ( !modNeutralLosses.empty()   &&
                                 modNeutralLosses.find(dissociationType) != modNeutralLosses.end() ) {
                                neutralLosses = modNeutralLosses[dissociationType];
                                for (double neutralLoss : neutralLosses)
                                {
                                    if (neutralLoss == 0)
                                    {
                                        continue;
                                    }
                                    
                                    for (int n = f; n < (int)terminalMasses.size(); n++)
                                    {
                                        if (std::find(skippers.begin(), skippers.end(),
                                                      std::make_tuple(productType, terminalMasses[n]->FragmentNumber)) == skippers.end())
                                        {
                                            //yield return new Product(productType, terminalMasses[n], neutralLoss);
                                            Product * pp = new Product(productType, terminalMasses[n], neutralLoss);
                                            v.push_back(pp);
                                        }
                                    }
                                }
                            }
                        }
                        
                        // "normal" fragment without neutral loss
                        if (std::find(skippers.begin(), skippers.end(),
                                      std::make_tuple(productType, terminalMasses[f]->FragmentNumber)) == skippers.end())
                        {
                            //yield return new Product(productType, terminalMasses[f], 0);
                            Product *pp = new Product(productType, terminalMasses[f], 0);
                            v.push_back( pp);
                        }
                    }
                }
            }

            if (!_allModsOneIsNterminus.empty())
            {
                std::unordered_set<Product*> diagnosticIons;

                for (auto mod : _allModsOneIsNterminus)
                {
                    // molecular ion minus neutral losses
                    //List<double> losses;
                    std::vector<double> losses;
                    auto modNeutralLosses = std::get<1>(mod)->getNeutralLosses();                    
                    if ( !modNeutralLosses.empty() &&
                         modNeutralLosses.find(dissociationType) != modNeutralLosses.end() )
                    {
                        losses = modNeutralLosses[dissociationType];
                        for (double neutralLoss : losses)
                        {
                            if (neutralLoss != 0)
                            {
                                auto  tempVar2 = new NeutralTerminusFragment (FragmentationTerminus::Both, getMonoisotopicMass(), 0, 0);
                                //yield return new Product(ProductType::M, &tempVar2, neutralLoss);
                                Product *pp = new Product(ProductType::M, tempVar2, neutralLoss);
                                v.push_back( pp);
                            }
                        }
                    }

                    // diagnostic ions
                    // List<double> diagIonsForThisModAndDissociationType;
                    std::vector<double> diagIonsForThisModAndDissociationType;
                    auto modDiagnosticIons = std::get<1>(mod)->getDiagnosticIons();
                    if ( !modDiagnosticIons.empty() &&
                         modDiagnosticIons.find(dissociationType)!= modDiagnosticIons.end() )
                    {
                        diagIonsForThisModAndDissociationType = modDiagnosticIons[dissociationType];
                        for (double diagnosticIon : diagIonsForThisModAndDissociationType)
                        {
                            int diagnosticIonLabel = static_cast<int>(std::round(Chemistry::ClassExtensions::ToMz(diagnosticIon, 1) *
                                                                                 std::pow(10, 0))) / std::pow(10, 0);

                            // the diagnostic ion is assumed to be annotated in the mod info as the *neutral mass* of the
                            // diagnostic ion, not the ionized species
                            auto tempVar3 = new Product (ProductType::D, new NeutralTerminusFragment(FragmentationTerminus::Both, diagnosticIon,
                                                                                                     diagnosticIonLabel, 0), 0);
                            diagnosticIons.insert(tempVar3);
                        }
                    }
                }

                for (auto diagnosticIon : diagnosticIons)
                {
                    //yield return diagnosticIon;
                    v.push_back(diagnosticIon);
                }
            }
            return v;
        }

        std::string PeptideWithSetModifications::EssentialSequence(std::unordered_map<std::string, int> *modstoWritePruned)
        {
            std::string essentialSequence = getBaseSequence();
            if (modstoWritePruned != nullptr)
            {
                auto sbsequence = new StringBuilder();

                // variable modification on peptide N-terminus
                Modification *pep_n_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = _allModsOneIsNterminus.find(1);
                if ( AllModsOneIsNterminus_iterator != _allModsOneIsNterminus.end())
                {
                    pep_n_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                    if ( modstoWritePruned->find(pep_n_term_variable_mod->getModificationType()) != modstoWritePruned->end() )
                    {
                        sbsequence->append('[' + pep_n_term_variable_mod->getModificationType() + ":" + pep_n_term_variable_mod->getIdWithMotif() + ']');
                    }
                }

                for (int r = 0; r < getLength(); r++)
                {
                    sbsequence->append(this->operator[](r));
                    // variable modification on this residue
                    Modification *residue_variable_mod;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = _allModsOneIsNterminus.find(r + 2);
                    if (AllModsOneIsNterminus_iterator != _allModsOneIsNterminus.end())
                    {
                        residue_variable_mod = AllModsOneIsNterminus_iterator->second;
                        if (modstoWritePruned->find(residue_variable_mod->getModificationType()) != modstoWritePruned->end() )
                        {
                            sbsequence->append('[' + residue_variable_mod->getModificationType() + ":" + residue_variable_mod->getIdWithMotif() + ']');
                        }
                    }
                }

                // variable modification on peptide C-terminus
                Modification *pep_c_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator2 = _allModsOneIsNterminus.find(getLength() + 2);
                if ( AllModsOneIsNterminus_iterator2 != _allModsOneIsNterminus.end())
                {
                    pep_c_term_variable_mod = AllModsOneIsNterminus_iterator2->second;
                    if (modstoWritePruned->find(pep_c_term_variable_mod->getModificationType()) != modstoWritePruned->end() )
                    {
                        sbsequence->append('[' + pep_c_term_variable_mod->getModificationType() + ":" + pep_c_term_variable_mod->getIdWithMotif() + ']');
                    }
                }

                essentialSequence = sbsequence->toString();
                delete sbsequence;
            }

            return essentialSequence;
        }

        PeptideWithSetModifications *PeptideWithSetModifications::Localize(int j, double massToLocalize)
        {
            auto dictWithLocalizedMass = std::unordered_map<int, Modification*>(_allModsOneIsNterminus);
            double massOfExistingMod = 0;
            Modification* modToReplace;
            std::unordered_map<int, Modification*>::const_iterator dictWithLocalizedMass_iterator = dictWithLocalizedMass.find(j + 2);
            if (dictWithLocalizedMass_iterator != dictWithLocalizedMass.end())
            {
                modToReplace = dictWithLocalizedMass_iterator->second;
                massOfExistingMod = modToReplace->getMonoisotopicMass().value();
                dictWithLocalizedMass.erase(j + 2);
            }

            auto tempVar = new Modification ("", "", "", "", nullptr, "Anywhere.", nullptr, std::make_optional(massToLocalize + massOfExistingMod),
                                 std::unordered_map<std::string, std::vector<std::string>>(),
                                 std::unordered_map<std::string, std::vector<std::string>>(),
                                 std::vector<std::string>(), std::unordered_map<DissociationType,
                                 std::vector<double>>(),
                                 std::unordered_map<DissociationType, std::vector<double>>(), "");
            dictWithLocalizedMass.emplace(j + 2, tempVar);

            auto peptideWithLocalizedMass = new PeptideWithSetModifications(getProtein(), _digestionParams,
                                                                            getOneBasedStartResidueInProtein(),
                                                                            getOneBasedEndResidueInProtein(),
                                                                            getCleavageSpecificityForFdrCategory(),
                                                                            getPeptideDescription(), getMissedCleavages(),
                                                                            dictWithLocalizedMass, NumFixedMods);

            //C# TO C++ CONVERTER TODO TASK: A 'delete peptideWithLocalizedMass' statement was not added
            //since peptideWithLocalizedMass was used in a 'return' or 'throw' statement.
            return peptideWithLocalizedMass;
        }

        std::string PeptideWithSetModifications::ToString()
        {
#ifdef ORIF
            return getFullSequence() + std::string::Join("\t", _allModsOneIsNterminus.Select([&] (std::any m)
            {
                m.ToString();
            }));
#endif
            std::string sb = privateFullSequence;
            if ( _allModsOneIsNterminus.size() > 0 ) {
                for (auto m : _allModsOneIsNterminus ) {
                    sb += "[" + std::to_string(static_cast<int>(std::get<0>(m))) + ", " + std::get<1>(m)->ToString() + "]\t";
                }
            }
            return sb;
        }

        bool PeptideWithSetModifications::Equals(PeptideWithSetModifications* q)
        {
            if (getProtein() == nullptr && q->getProtein() == nullptr)
            {
                return q->getFullSequence() == this->privateFullSequence;
            }

            return q != nullptr                                                                          &&
                q->getFullSequence() == this->privateFullSequence                                          &&
                q->getOneBasedStartResidueInProtein() == this->getOneBasedStartResidueInProtein()        &&
                (( q->getProtein()->getAccession() == ""  && this->getProtein()->getAccession() == "" )  ||
                ( q->getProtein()->getAccession() == this->getProtein()->getAccession() ))               &&
                q->getDigestionParams()->getProtease() == this->getDigestionParams()->getProtease();
        }

        int PeptideWithSetModifications::GetHashCode()
        {
#ifdef ORIG
            return getFullSequence().GetHashCode() + getDigestionParams()->getProtease()->GetHashCode();
#endif
            return StringHelper::GetHashCode(privateFullSequence) + getDigestionParams()->getProtease()->GetHashCode();
        }

        void PeptideWithSetModifications::SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*> &idToMod,
                                                                      std::unordered_map<std::string, Proteomics::Protein*> &accessionToProtein)
        {
            GetModsAfterDeserialization(idToMod, _baseSequence);
            GetProteinAfterDeserialization(accessionToProtein);
            // In C++ version the DigestionParams are already correctly determined before constructing the new
            // PeptideWithSetModifications object, so need to call it here again.
            //GetDigestionParamsAfterDeserialization(); 
        }

        void PeptideWithSetModifications::SetNonSerializedPeptideInfo(const std::vector<Proteomics::Protein*> &proteinList)
        {
            std::string accession = getProteinAccession();
            Proteomics::Protein *prot=nullptr;
            for ( auto p : proteinList ) {
                if ( p->getAccession() == accession ) {
                    prot = p;
                    break;
                }
            }            
            setProtein(prot);

            //only used to reconstruct _baseSequence 
            std::unordered_map<std::string, Modification*> idToMod;       
            GetModsAfterDeserialization(idToMod, _baseSequence);
        }
        
        
        void PeptideWithSetModifications::GetDigestionParamsAfterDeserialization()
        {
            if (DigestionParamString != "")
            {
                _digestionParams = getDigestionParams()->FromString(DigestionParamString);
            }
        }

        void PeptideWithSetModifications::GetModsAfterDeserialization(std::unordered_map<std::string, Modification*> &idToMod,
                                                                      std::string &baseSequence)
        {
            _allModsOneIsNterminus = std::unordered_map<int, Modification*>();
            StringBuilder *baseSequenceSb = new StringBuilder();
            StringBuilder *currentModification = new StringBuilder();
            int currentModificationLocation = 1;
            bool currentlyReadingMod = false;
            int bracketCount = 0;

            for (int r = 0; r < (int)privateFullSequence.length(); r++)
            {
                char c = privateFullSequence[r];

                switch (c)
                {
                    case '[':
                        currentlyReadingMod = true;

                        if (bracketCount > 0)
                        {
                            currentModification->append(c);
                        }

                        bracketCount++;

                        break;

                    case ']':
                    {
                        std::string modId = "";
                        bracketCount--;

                        if ( idToMod.size() == 0 ) {
                            if ( bracketCount == 0 ) {
                                currentlyReadingMod = false;
                            }
                            // not meant to identify mods, just called form the constructor
                            // without a valid Mods table. Just use to construct the base sequence.
                            break;
                        }
                        
                        if (bracketCount == 0)
                        {
                            try
                            {
                                std::string modString = currentModification->toString();
                                int splitIndex = (int)modString.find(':');
                                std::string modType = modString.substr(0, splitIndex);
                                modId = modString.substr(splitIndex + 1, modString.length() - splitIndex - 1);
                            }
                            catch (const std::runtime_error &e)
                            {
                                delete currentModification;
                                delete baseSequenceSb;
                                std::string message = {"Error while trying to parse string into peptide: "};
                                throw MzLibUtil::MzLibException(message + e.what());
                            }

                            Modification *mod;
                            std::unordered_map<std::string, Modification*>::const_iterator idToMod_iterator = idToMod.find(modId);
                            if (idToMod_iterator == idToMod.end() )
                            {
                                //mod = idToMod_iterator->second;
                                delete currentModification;
                                delete baseSequenceSb;
                                throw MzLibUtil::MzLibException("Could not find modification while reading string: " + privateFullSequence);
                            }
                            else  {
                                mod = idToMod_iterator->second;
                            }
                            
                            if ( (mod->getLocationRestriction().find("C-terminal.") != std::string::npos) &&
                                 (r == ((int)privateFullSequence.length() - 1))    ) 
                            {
                                currentModificationLocation = baseSequenceSb->length() + 2;
                            }

                            _allModsOneIsNterminus.emplace(currentModificationLocation, mod);
                            currentlyReadingMod = false;
                            currentModification = new StringBuilder();
                        }
                        else
                        {
                            currentModification->append(c);
                        }

                        break;

                    }
                    default:
                        if (currentlyReadingMod)
                        {
                            currentModification->append(c);
                        }
                        else
                        {
                            currentModificationLocation++;
                            baseSequenceSb->append(c);
                        }
                        break;
                }
            }

            baseSequence = baseSequenceSb->toString();

            delete currentModification;
            delete baseSequenceSb;
        }

        void PeptideWithSetModifications::GetProteinAfterDeserialization(std::unordered_map<std::string, Proteomics::Protein*> &idToProtein)
        {
            Proteomics::Protein *protein = nullptr;

            std::unordered_map<std::string, Proteomics::Protein*>::const_iterator idToProtein_iterator = idToProtein.find(ProteinAccession);
            if (ProteinAccession != "" && idToProtein_iterator == idToProtein.end())
            {
                 throw MzLibUtil::MzLibException("Could not find protein accession after deserialization! " + ProteinAccession);
            }
            else if (ProteinAccession != "" && idToProtein_iterator != idToProtein.end() ){
                protein = idToProtein_iterator->second;
            }
            setProtein(protein);
        }

        void PeptideWithSetModifications::DetermineFullSequence()
        {
            auto subsequence = new StringBuilder();

            // modification on peptide N-terminus
            Modification *mod;
            auto allMods = _allModsOneIsNterminus;
            std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = allMods.find(1);
            if (AllModsOneIsNterminus_iterator != allMods.end())
            {
                mod = AllModsOneIsNterminus_iterator->second;
                if ( mod == nullptr ) std::cout << "HELLO This shouldnt happen\n";
                subsequence->append('[' + mod->getModificationType() + ":" + mod->getIdWithMotif() + ']');
            }

            for (int r = 0; r < getLength(); r++)
            {
                subsequence->append(this->operator[](r));

                // modification on this residue
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = allMods.find(r + 2);
                if ( AllModsOneIsNterminus_iterator != allMods.end())
                {
                    mod = AllModsOneIsNterminus_iterator->second;
                    subsequence->append('[' + mod->getModificationType() + ":" + mod->getIdWithMotif() + ']');
                }
            }

            // modification on peptide C-terminus
            std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator2 = allMods.find(getLength() + 2);
            if (AllModsOneIsNterminus_iterator2 != allMods.end())
            {
                mod = AllModsOneIsNterminus_iterator2->second;
                subsequence->append('[' + mod->getModificationType() + ":" + mod->getIdWithMotif() + ']');
            }

            setFullSequence(subsequence->toString());

            delete subsequence;
        }

        void PeptideWithSetModifications::UpdateCleavageSpecificity()
        {
            if (getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Unknown)
            {
                setCleavageSpecificityForFdrCategory(getDigestionParams()->getSpecificProtease()->GetCleavageSpecificity(
                                                         getProtein()->getBaseSequence(),
                                                         getOneBasedStartResidueInProtein(),
                                                         getOneBasedEndResidueInProtein()));
                setPeptideDescription(std::to_string(static_cast<int>(getCleavageSpecificityForFdrCategory())) );
            }
        }


        // buf has to be preallocated, and size indicates the input size of the buffer.
        // both values might change however if the buffer is too small, in which case we
        // return error -1 and size will point to the required size;
        // The code does not realloc the buffer itself, since it might
        // be part of a larger buffer used to Serialize a vector of pep's
        int PeptideWithSetModifications::Pack (char *buf, size_t &buf_len,
                                               const std::vector<PeptideWithSetModifications *> &pepVec )            
        {
            size_t pos = 0;
            int ret;

            for ( auto pep: pepVec ) {
                size_t len = buf_len - pos;
                ret = PeptideWithSetModifications::Pack(buf+pos, len, pep);
                if ( ret == -1 ) {
                    buf_len = pos + len;
                    return ret;
                }
                pos += len;
            }
            buf_len = pos;
            return pos;
        }

        int PeptideWithSetModifications::Pack (char *buf, size_t &size, PeptideWithSetModifications *pep )
        {
            int retlen;
            char tmpbuf[256];

            // leave space for the length of the line
            size_t pos=sizeof(int);
            
            size_t bufpos = 0; // Since we store multiple lines, we need to keep track of the buf position as well.
            
            retlen = BinaryPack::PackInt( tmpbuf+pos, pep->getOneBasedStartResidueInProtein() );
            pos += retlen;
            retlen = BinaryPack::PackInt( tmpbuf+pos, pep->getOneBasedEndResidueInProtein() );
            pos += retlen;
            retlen = BinaryPack::PackInt( tmpbuf+pos, pep->getMissedCleavages() );
            pos += retlen;
            retlen = BinaryPack::PackString( tmpbuf+pos, pep->getPeptideDescription() );
            pos += retlen;
            retlen = BinaryPack::PackInt( tmpbuf+pos, pep->NumFixedMods );
            pos += retlen;
            retlen = BinaryPack::PackString( tmpbuf+pos, CleavageSpecificityExtension::GetCleavageSpecificityAsString( pep->getCleavageSpecificityForFdrCategory()));
            pos += retlen;

            //now save the length of this line at the beginning of the file.
            retlen = BinaryPack::PackInt(tmpbuf, (int)pos);
            if ( (pos + bufpos) > size ) {
                size = pos+bufpos;
                return -1;
            }
            
            memcpy (buf+bufpos, tmpbuf, pos);
            bufpos += pos;

            // line 2: FullSequence
            pos = sizeof(int);
            memset (tmpbuf, 0, 256);

            retlen = BinaryPack::PackString(tmpbuf+pos,pep->getFullSequence() );
            pos += retlen;

            //now save the length of this line at the beginning of the file.
            retlen = BinaryPack::PackInt(tmpbuf, (int)pos);
            if ( (pos + bufpos) > size ) {
                size = pos+bufpos;
                return -1;
            }
            memcpy (buf+bufpos, tmpbuf, pos);
            bufpos += pos;
            
            // line 3: DigestionParams
            pos = sizeof(int);
            memset (tmpbuf, 0, 256);

            retlen = BinaryPack::PackString(tmpbuf+pos,pep->getDigestionParamString() );
            pos += retlen;
            
            //now save the length of this line at the beginning of the file.
            retlen = BinaryPack::PackInt(tmpbuf, (int)pos);
            if ( (pos + bufpos) > size ) {
                size = pos+bufpos;
                return -1;
            }

            memcpy (buf+bufpos, tmpbuf, pos);
            bufpos += pos;

            // line4: ProteinAccession
            pos = sizeof(int);
            memset (tmpbuf, 0, 256);

            std::string accession = pep->getProteinAccession();
            if ( accession == "" )  {
                accession = "-";
            }
            retlen = BinaryPack::PackString(tmpbuf+pos, accession );
            pos += retlen;

            //now save the length of this line at the beginning of the file.
            retlen = BinaryPack::PackInt(tmpbuf, (int)pos);
            if ( (pos + bufpos) > size ) {
                size = pos+bufpos;
                return -1;
            }
            memcpy (buf+bufpos, tmpbuf, pos);
            bufpos += pos;
            size = bufpos;
            
            return bufpos;
        }

        void PeptideWithSetModifications::Serialize (std::string &filename, PeptideWithSetModifications* &pep )
        {
            std::vector<PeptideWithSetModifications *> pVec;
            pVec.push_back (pep);
            PeptideWithSetModifications::Serialize (filename, pVec );
        }
        
        void PeptideWithSetModifications::Serialize (std::string &filename,
                                                     std::vector<PeptideWithSetModifications *> &pVec )
        {

            int fp = open (filename.c_str(),  O_CREAT|O_TRUNC|O_WRONLY, S_IRWXU);
            if ( fp > 0 ) {
                size_t orig_size = PepWithSetModsDefaultSize;
                size_t size;
                char *buf = (char*) calloc ( 1, PepWithSetModsDefaultSize );
                if ( NULL == buf ) {
                    std::cout << "PeptideWithSetModifications::Serialize : Could not allocate memory\n";
                    return;
                }
                
                size = orig_size;
                int ret = -1;
                while ( ret < 0 ) { 
                    ret = PeptideWithSetModifications::Pack( buf, size, pVec );
                    if ( ret == -1 ) {
                        // buffer was not large enough
                        free ( buf ) ;
                        buf = (char*) calloc (1,  size );
                        orig_size = size;
                        if ( NULL == buf ) {
                            std::cout << "PeptideWithSetModifications::Serialize : Could not allocate memory\n";
                            return;
                        }
                    }
                }
                
                write (fp, buf, size );
                close(fp);
                free (buf);
            }
            else {
                std::cout <<"PeptideWithSetModifications::Serialize : Could not create file " << filename << std::endl;
            }
        }

        void PeptideWithSetModifications::Unpack (char *buf, size_t buf_len, size_t &len,
                                                  std::vector<PeptideWithSetModifications*> &pepVec,
                                                  int count )
        {
            std::vector<char *> lines = BinaryPack::SplitLines(buf, buf_len);
            
            size_t total_len=0;
            int counter=0;
            for (auto  i=0; i < lines.size(); i+=4 ) {                
                size_t tmp;
                PeptideWithSetModifications *pep;
                PeptideWithSetModifications::Unpack(lines, i, tmp, &pep);
                total_len += tmp;
                pepVec.push_back(pep);
                counter ++;
                if ( counter == count ) break;
            }
            len = total_len;
        }

        
        void PeptideWithSetModifications::Unpack (char *buf, size_t buf_len, size_t &len,
                                                  PeptideWithSetModifications** pep )
        {
            std::vector<char *> lines = BinaryPack::SplitLines(buf, buf_len);
            if ( lines.size() < 4 ) {
                std::cout << "PeptideWithSetModifications::Unpack : input does not contains enough information to " <<
                    "reconstruct the PeptideWithSetModifications. " << std::endl;
                return;
            }
            PeptideWithSetModifications::Unpack ( lines, 0, len, pep );
        }

        void PeptideWithSetModifications::Unpack (std::vector<char*> &input, int index, size_t &len,
                                                  PeptideWithSetModifications** pep )
        {
            size_t total_len=0;
            int retlen;
            
            // Processing line 1
            size_t pos = 0;
            int line_len=0;
            char *buf = input[index];

            retlen = BinaryPack::UnpackInt(buf+pos, line_len );
            pos += retlen;
            total_len += line_len;
            
            int onebasedstart, onebasedend, missedcleavages, numfixedMods;
            retlen = BinaryPack::UnpackInt(buf+pos, onebasedstart );
            pos += retlen;
            retlen = BinaryPack::UnpackInt(buf+pos, onebasedend );
            pos += retlen;
            retlen = BinaryPack::UnpackInt(buf+pos, missedcleavages );
            pos += retlen;
            
            std::string description;
            retlen = BinaryPack::UnpackString(buf+pos, description );
            pos += retlen;
            retlen = BinaryPack::UnpackInt(buf+pos, numfixedMods );
            pos += retlen;

            std::string cleavagestring;
            retlen = BinaryPack::UnpackString(buf+pos, cleavagestring );
            pos += retlen;
            
            CleavageSpecificity cvs = CleavageSpecificityExtension::ParseString(cleavagestring);
            
            // Processing line 2
            pos = 0;
            buf = input[index+1];

            retlen = BinaryPack::UnpackInt(buf+pos, line_len );
            pos += retlen;
            total_len += line_len;

            std::string fullsequence;
            retlen = BinaryPack::UnpackString(buf+pos, fullsequence );
            pos += retlen;       
            
            // Processing line 3
            pos = 0;
            buf = input[index+2];
            retlen = BinaryPack::UnpackInt(buf+pos, line_len );
            pos += retlen;
            total_len += line_len;

            std::string digestparamstring;
            retlen = BinaryPack::UnpackString(buf+pos, digestparamstring );
            pos += retlen;       

            DigestionParams *dp = nullptr;
            if ( digestparamstring != "" ) {
                dp = DigestionParams::FromString(digestparamstring);
            }
            
            // Processing line 4
            pos = 0;
            buf = input[index+3];
            retlen = BinaryPack::UnpackInt(buf+pos, line_len );
            pos += retlen;
            total_len += line_len;

            std::string accessionstring;
            retlen = BinaryPack::UnpackString(buf+pos, accessionstring );
            pos += retlen;       

            std::unordered_map<std::string, Modification*> umsM;
            auto newpep = new PeptideWithSetModifications(fullsequence, 
                                                          umsM,                
                                                          numfixedMods,
                                                          dp,                  
                                                          nullptr,  // Protein set in GetProteinAfterDeserialization 
                                                          onebasedstart,
                                                          onebasedend,
                                                          missedcleavages,
                                                          cvs,
                                                          description );
            if ( accessionstring != "-" ) {
                newpep->setProteinAccession ( accessionstring );
            }
            
            *pep = newpep;
            len = total_len;

            return ;
        }

        void PeptideWithSetModifications::Deserialize (std::string &filename, PeptideWithSetModifications* &pep )
        {
            std::vector<PeptideWithSetModifications *> pVec;
            PeptideWithSetModifications::Deserialize(filename, pVec );
            if ( pVec.size() > 0 ) {
                pep = pVec[0];
            }
        }
        
        void PeptideWithSetModifications::Deserialize (std::string &filename, std::vector<PeptideWithSetModifications *> &pVec )
        {
            std::filesystem::path p = filename;
            size_t buf_len = std::filesystem::file_size(p);
            
            int fp = open ( filename.c_str(), O_RDONLY );
            if ( fp > 0 ) {
                char *buf = (char*) malloc ( buf_len+1);
                if (buf == NULL ) {
                    std::cout << "PeptideWithSetModifications::Deserialize : Could not allocate buffer of size " << buf_len << std::endl;
                    return;
                }
                size_t tmp_len=0;
                read (fp, buf, buf_len);
                PeptideWithSetModifications::Unpack(buf, buf_len, tmp_len, pVec);

                free (buf);
                close(fp);
            }
            else {
                std::cout << "PeptideWithSetModifications::Deserialize : Could not open file " << filename << std::endl;
            }
        }       
    }
}
