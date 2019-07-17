#include "PeptideWithSetModifications.h"
#include "../Modifications/Modification.h"
#include "DigestionParams.h"
#include "../Protein/Protein.h"
#include "../../MzLibUtil/MzLibException.h"
#include "../../Chemistry/ClassExtensions.h"
#include "../Fragmentation/TerminusSpecificProductTypes.h"
#include "../Fragmentation/DissociationTypeCollection.h"

#include "stringhelper.h"

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

        const double PeptideWithSetModifications::WaterMonoisotopicMass = PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() * 2 +
            PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass();


        PeptideWithSetModifications::PeptideWithSetModifications(Proteomics::Protein *protein, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, CleavageSpecificity cleavageSpecificity, const std::string &peptideDescription, int missedCleavages, std::unordered_map<int, Modification*> &allModsOneIsNterminus, int numFixedMods) : ProteolyticPeptide(protein, oneBasedStartResidueInProtein, oneBasedEndResidueInProtein, missedCleavages, cleavageSpecificity, peptideDescription), NumFixedMods(numFixedMods), DigestionParamString(digestionParams->ToString()), ProteinAccession(protein->getAccession())
        {
            _allModsOneIsNterminus = allModsOneIsNterminus;
            _digestionParams = digestionParams;
            DetermineFullSequence();
            UpdateCleavageSpecificity();
        }

        PeptideWithSetModifications::PeptideWithSetModifications(const std::string &sequence, std::unordered_map<std::string, Modification*> &allKnownMods, int numFixedMods, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, Proteomics::Protein *p, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, int missedCleavages, CleavageSpecificity cleavageSpecificity, const std::string &peptideDescription) : ProteolyticPeptide(p, oneBasedStartResidueInProtein, oneBasedEndResidueInProtein, missedCleavages, cleavageSpecificity, peptideDescription), NumFixedMods(numFixedMods)
        {
            if (sequence.find("|") != std::string::npos)
            {
                throw MzLibUtil::MzLibException("Ambiguous peptide cannot be parsed from string: " + sequence);
            }

            setFullSequence(sequence);
            GetModsAfterDeserialization(allKnownMods, _baseSequence);
            _digestionParams = digestionParams;

            if (p != nullptr)
            {
                ProteinAccession = p->getAccession();
            }
            if (digestionParams != nullptr)
            {
                DigestionParamString = digestionParams->ToString();
            }
        }

        Proteomics::ProteolyticDigestion::DigestionParams *PeptideWithSetModifications::getDigestionParams() const
        {
            return _digestionParams;
        }

        std::unordered_map<int, Modification*> PeptideWithSetModifications::getAllModsOneIsNterminus() const
        {
            return _allModsOneIsNterminus;
        }

        int PeptideWithSetModifications::getNumMods() const
        {
            return getAllModsOneIsNterminus().size();
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
                std::unordered_map<int, Modification*> mods = getAllModsOneIsNterminus();
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
                    monoMass += Residue::ResidueMonoisotopicMass[b];
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
                if (AllModsOneIsNterminus_iterator != getAllModsOneIsNterminus().end())
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
                else
                {
                    pep_n_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                }

                for (int r = 0; r < getLength(); r++)
                {
                    subsequence->append(this->operator[](r));
                    // variable modification on this residue
                    Modification *residue_variable_mod;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus2_iterator = _allModsOneIsNterminus.find(r + 2);
                    if (AllModsOneIsNterminus2_iterator != getAllModsOneIsNterminus().end())
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
                    else
                    {
                        residue_variable_mod = AllModsOneIsNterminus2_iterator->second;
                    }
                }

                // variable modification on peptide C-terminus
                Modification *pep_c_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus3_iterator = _allModsOneIsNterminus.find(getLength() + 2);
                if (AllModsOneIsNterminus3_iterator != getAllModsOneIsNterminus().end())
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
                else
                {
                    pep_c_term_variable_mod = AllModsOneIsNterminus3_iterator->second;
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

             std::vector<ProductType> vInter;
             std::vector<ProductType> v1 = TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus[fragmentationTerminus];
             std::vector<ProductType> v2 = DissociationTypeCollection::ProductsFromDissociationType[dissociationType];
             std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vInter.begin());
             std::unordered_map<FragmentationTerminus, std::vector<ProductType>> productCollection = {{fragmentationTerminus, vInter}};
             
            //std::vector<std::tuple<ProductType, int>*> skippers;
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
                    skippers.AddRange(GetProlineZIonIndicies());
                    break;
            }

            for (auto productType : productCollection)
            {
                // we're separating the N and C terminal masses and computing a separate compact peptide for each one
                // this speeds calculations up without producing unnecessary terminus fragment info
                FragmentationTerminus temporaryFragmentationTerminus = TerminusSpecificProductTypes::ProductTypeToFragmentationTerminus[productType];
                CompactPeptide tempVar(this, temporaryFragmentationTerminus);
                std::vector<NeutralTerminusFragment*> terminalMasses = (&tempVar)->TerminalMasses;

                for (int f = 0; f < terminalMasses.size(); f++)
                {
                    // fragments with neutral loss
                    Modification mod;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(terminalMasses[f].AminoAcidPosition + 1);
                    std::vector<double> neutralLosses;
                    if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end() && mod::NeutralLosses != nullptr && mod::NeutralLosses::TryGetValue(dissociationType, neutralLosses))
                    {
                        mod = AllModsOneIsNterminus_iterator->second;
                        for (double neutralLoss : neutralLosses)
                        {
                            if (neutralLoss == 0)
                            {
                                continue;
                            }

                            for (int n = f; n < terminalMasses.size(); n++)
                            {
                                if (!std::find(skippers.begin(), skippers.end(), (productType, terminalMasses[n]->FragmentNumber)) != skippers.end()))
                                {
                                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                    //yield return new Product(productType, terminalMasses[n], neutralLoss);
                                     Product * pp = new Product(productType, terminalMasses[n], neutralLoss);
                                     v.push_back(pp);
                                }
                            }
                        }
                    }
                    else
                    {
                        mod = AllModsOneIsNterminus_iterator->second;
                    }

                    // "normal" fragment without neutral loss
                    if (!std::find(skippers.begin(), skippers.end(), (productType, terminalMasses[f]->FragmentNumber)) != skippers.end()))
                    {
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        //yield return new Product(productType, terminalMasses[f], 0);
                        Product *pp = new Product(productType, terminalMasses[f], 0);
                        v.push_back( pp);
                    }
                }
            }

            if (!getAllModsOneIsNterminus().empty())
            {
                std::unordered_set<Product*> diagnosticIons;

                for (auto mod : getAllModsOneIsNterminus())
                {
                    // molecular ion minus neutral losses
                    //List<double> losses;
                    std::vector<double> losses;
                    if (mod->second.NeutralLosses != nullptr && mod->second.NeutralLosses.TryGetValue(dissociationType, losses))
                    {
                        for (double neutralLoss : losses)
                        {
                            if (neutralLoss != 0)
                            {
                                NeutralTerminusFragment tempVar2(FragmentationTerminus::Both, getMonoisotopicMass(), 0, 0);
                                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                                //yield return new Product(ProductType::M, &tempVar2, neutralLoss);
                                Product *pp = new Product(ProductType::M, &tempVar2, neutralLoss);
                                v.push_back( pp);
                            }
                        }
                    }

                    // diagnostic ions
                    //List<double> diagIonsForThisModAndDissociationType;
                    std::vector<double> diagIonsForThisModAndDissociationType;
                    if ( mod->second.DiagnosticIons != nullptr &&
                         mod->second.DiagnosticIons.TryGetValue(dissociationType, diagIonsForThisModAndDissociationType))
                    {
                        for (double diagnosticIon : diagIonsForThisModAndDissociationType)
                        {
                            int diagnosticIonLabel = static_cast<int>(std::round(Chemistry::ClassExtensions::ToMz(diagnosticIon, 1) * std::pow(10, 0))) / std::pow(10, 0);

                            // the diagnostic ion is assumed to be annotated in the mod info as the *neutral mass* of the diagnostic ion, not the ionized species
                            Product tempVar3(ProductType::D, new NeutralTerminusFragment(FragmentationTerminus::Both, diagnosticIon, diagnosticIonLabel, 0), 0);
                            diagnosticIons.insert(&tempVar3);
                        }
                    }
                }

                for (auto diagnosticIon : diagnosticIons)
                {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    //yield return diagnosticIon;
                    v.push_back(diagnosticIon);
                }
            }
            return v;
        }

        std::string PeptideWithSetModifications::EssentialSequence(IReadOnlyDictionary<std::string, int> *modstoWritePruned)
        {
            std::string essentialSequence = getBaseSequence();
            if (modstoWritePruned != nullptr)
            {
                auto sbsequence = new StringBuilder();

                // variable modification on peptide N-terminus
                Modification pep_n_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(1);
                if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
                {
                    pep_n_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                    if (modstoWritePruned->ContainsKey(pep_n_term_variable_mod::ModificationType))
                    {
                        sbsequence->append('[' + pep_n_term_variable_mod::ModificationType + ":" + pep_n_term_variable_mod::IdWithMotif + ']');
                    }
                }
                else
                {
                    pep_n_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                }
                for (int r = 0; r < getLength(); r++)
                {
                    sbsequence->append(this->operator[](r));
                    // variable modification on this residue
                    Modification residue_variable_mod;
                    std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(r + 2);
                    if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
                    {
                        residue_variable_mod = AllModsOneIsNterminus_iterator->second;
                        if (modstoWritePruned->ContainsKey(residue_variable_mod::ModificationType))
                        {
                            sbsequence->append('[' + residue_variable_mod::ModificationType + ":" + residue_variable_mod::IdWithMotif + ']');
                        }
                    }
                    else
                    {
                        residue_variable_mod = AllModsOneIsNterminus_iterator->second;
                    }
                }

                // variable modification on peptide C-terminus
                Modification pep_c_term_variable_mod;
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(Length + 2);
                if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
                {
                    pep_c_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                    if (modstoWritePruned->ContainsKey(pep_c_term_variable_mod::ModificationType))
                    {
                        sbsequence->append('[' + pep_c_term_variable_mod::ModificationType + ":" + pep_c_term_variable_mod::IdWithMotif + ']');
                    }
                }
                else
                {
                    pep_c_term_variable_mod = AllModsOneIsNterminus_iterator->second;
                }

                essentialSequence = sbsequence->toString();

                delete sbsequence;
            }
            return essentialSequence;
        }

        PeptideWithSetModifications *PeptideWithSetModifications::Localize(int j, double massToLocalize)
        {
            auto dictWithLocalizedMass = std::unordered_map<int, Modification*>(getAllModsOneIsNterminus());
            double massOfExistingMod = 0;
            Modification modToReplace;
            std::unordered_map<int, Modification*>::const_iterator dictWithLocalizedMass_iterator = dictWithLocalizedMass.find(j + 2);
            if (dictWithLocalizedMass_iterator != dictWithLocalizedMass.end())
            {
                modToReplace = dictWithLocalizedMass_iterator->second;
                massOfExistingMod = static_cast<double>(modToReplace::MonoisotopicMass);
                dictWithLocalizedMass.erase(j + 2);
            }
            else
            {
                modToReplace = dictWithLocalizedMass_iterator->second;
            }

            Modification tempVar("", "", "", "", nullptr, "Anywhere.", nullptr, std::make_optional(massToLocalize + massOfExistingMod), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
            dictWithLocalizedMass.emplace(j + 2, &tempVar);

            auto peptideWithLocalizedMass = new PeptideWithSetModifications(getProtein(), _digestionParams, getOneBasedStartResidueInProtein(), getOneBasedEndResidueInProtein(), getCleavageSpecificityForFdrCategory(), getPeptideDescription(), getMissedCleavages(), dictWithLocalizedMass, NumFixedMods);

            //C# TO C++ CONVERTER TODO TASK: A 'delete peptideWithLocalizedMass' statement was not added
            //since peptideWithLocalizedMass was used in a 'return' or 'throw' statement.
            return peptideWithLocalizedMass;
        }

        std::string PeptideWithSetModifications::ToString()
        {
#ifdef ORIF
            return getFullSequence() + std::string::Join("\t", getAllModsOneIsNterminus().Select([&] (std::any m)
            {
                m.ToString();
            }));
#endif
            StringBuilder *sb = new StringBuilder();
            sb->appendLine(getFullSequence);
            for (auto m : getAllModsOneIsNterminus() ) {
                sb->appendLine(m->ToString() );
            }
            return sb->toString();
        }

        bool PeptideWithSetModifications::Equals(PeptideWithSetModifications* q)
        {
            if (getProtein() == nullptr && q->getProtein() == nullptr)
            {
                return q->getFullSequence() == this->getFullSequence();
            }

            return q != nullptr && q->getFullSequence() == this->getFullSequence() && q->getOneBasedStartResidueInProtein() == this->getOneBasedStartResidueInProtein() && (q->getProtein()->getAccession() == "" && this->getProtein()->getAccession() == "" || q->getProtein()->getAccession() == this->getProtein()->getAccession()) && q->getDigestionParams()->getProtease() == this->getDigestionParams()->getProtease();
        }

        int PeptideWithSetModifications::GetHashCode()
        {
#ifdef ORIG
            return getFullSequence().GetHashCode() + getDigestionParams()->getProtease()->GetHashCode();
#endif
            return StringHelper::GetHashCode(getFullSequence()) + StringHelper::GetHashCode(getDigestionParams()->getProtease());
        }

        void PeptideWithSetModifications::SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*> &idToMod, std::unordered_map<std::string, Proteomics::Protein*> &accessionToProtein)
        {
            std::string baseSequence;
            GetModsAfterDeserialization(idToMod, baseSequence);
            GetProteinAfterDeserialization(accessionToProtein);
            GetDigestionParamsAfterDeserialization();
        }

        void PeptideWithSetModifications::GetDigestionParamsAfterDeserialization()
        {
            if (DigestionParamString != "")
            {
                _digestionParams = getDigestionParams()->FromString(DigestionParamString);
            }
        }

        void PeptideWithSetModifications::GetModsAfterDeserialization(std::unordered_map<std::string, Modification*> &idToMod, std::string &baseSequence)
        {
            _allModsOneIsNterminus = std::unordered_map<int, Modification*>();
            StringBuilder *baseSequenceSb = new StringBuilder();
            StringBuilder *currentModification = new StringBuilder();
            int currentModificationLocation = 1;
            bool currentlyReadingMod = false;
            int bracketCount = 0;

            for (int r = 0; r < getFullSequence().length(); r++)
            {
                char c = getFullSequence()[r];

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
                                throw MzLibUtil::MzLibException("Error while trying to parse string into peptide: " + e.what());
                            }

                            Modification mod;
                            std::unordered_map<std::string, Modification*>::const_iterator idToMod_iterator = idToMod.find(modId);
                            if (idToMod_iterator == idToMod.end())
                            {
                                mod = idToMod_iterator->second;

                                delete currentModification;
                                delete baseSequenceSb;
                                throw MzLibUtil::MzLibException("Could not find modification while reading string: " + getFullSequence());
                            }
                            else
                            {
                                mod = idToMod_iterator->second;
                            }

                            if (mod::LocationRestriction->Contains("C-terminal.") && r == getFullSequence().length() - 1)
                            {
                                currentModificationLocation = baseSequenceSb->length() + 2;
                            }

                            getAllModsOneIsNterminus().emplace(currentModificationLocation, mod);
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
                protein = idToProtein_iterator->second;
                throw MzLibUtil::MzLibException("Could not find protein accession after deserialization! " + ProteinAccession);
            }
            else
            {
                protein = idToProtein_iterator->second;
            }

            setProtein(protein);
        }

        void PeptideWithSetModifications::DetermineFullSequence()
        {
            auto subsequence = new StringBuilder();

            // modification on peptide N-terminus
            Modification mod;
            std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(1);
            if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
            {
                mod = AllModsOneIsNterminus_iterator->second;
                subsequence->append('[' + mod::ModificationType + ":" + mod::IdWithMotif + ']');
            }
            else
            {
                mod = AllModsOneIsNterminus_iterator->second;
            }

            for (int r = 0; r < getLength(); r++)
            {
                subsequence->append(this->operator[](r));

                // modification on this residue
                std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(r + 2);
                if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
                {
                    mod = AllModsOneIsNterminus_iterator->second;
                    subsequence->append('[' + mod::ModificationType + ":" + mod::IdWithMotif + ']');
                }
                else
                {
                    mod = AllModsOneIsNterminus_iterator->second;
                }
            }

            // modification on peptide C-terminus
            std::unordered_map<int, Modification*>::const_iterator AllModsOneIsNterminus_iterator = AllModsOneIsNterminus.find(Length + 2);
            if (getAllModsOneIsNterminus()_iterator != getAllModsOneIsNterminus().end())
            {
                mod = AllModsOneIsNterminus_iterator->second;
                subsequence->append('[' + mod::ModificationType + ":" + mod::IdWithMotif + ']');
            }
            else
            {
                mod = AllModsOneIsNterminus_iterator->second;
            }

            setFullSequence(subsequence->toString());

            delete subsequence;
        }

        void PeptideWithSetModifications::UpdateCleavageSpecificity()
        {
            if (getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Unknown)
            {
                setCleavageSpecificityForFdrCategory(getDigestionParams()->getSpecificProtease()->GetCleavageSpecificity(getProtein()->getBaseSequence(), getOneBasedStartResidueInProtein(), getOneBasedEndResidueInProtein()));
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                setPeptideDescription(getCleavageSpecificityForFdrCategory().ToString());
            }
        }
    }
}
