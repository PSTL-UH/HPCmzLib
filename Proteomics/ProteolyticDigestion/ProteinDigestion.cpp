#include "ProteinDigestion.h"
#include "Protease.h"
#include "DigestionParams.h"
#include "../Modifications/Modification.h"
#include "../Protein/Protein.h"
#include "PeptideWithSetModifications.h"
#include "ProteolyticPeptide.h"
#include "CleavageSpecificity.h"

using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        ProteinDigestion::ProteinDigestion(Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, std::vector<Modification*> &allKnownFixedModifications, std::vector<Modification*> &variableModifications)
        {
            setDigestionParams(digestionParams);
            setProtease(digestionParams->getProtease());
            setMaximumMissedCleavages(digestionParams->getMaxMissedCleavages());
            setInitiatorMethionineBehavior(digestionParams->getInitiatorMethionineBehavior());
            setMinPeptideLength(digestionParams->getMinPeptideLength());
            setMaxPeptideLength(digestionParams->getMaxPeptideLength());
            setAllKnownFixedModifications(allKnownFixedModifications );
            setVariableModifications(variableModifications );
        }

        Proteomics::ProteolyticDigestion::Protease *ProteinDigestion::getProtease() const
        {
            return privateProtease;
        }

        void ProteinDigestion::setProtease(Proteomics::ProteolyticDigestion::Protease *value)
        {
            privateProtease = value;
        }

        int ProteinDigestion::getMaximumMissedCleavages() const
        {
            return privateMaximumMissedCleavages;
        }

        void ProteinDigestion::setMaximumMissedCleavages(int value)
        {
            privateMaximumMissedCleavages = value;
        }

        Proteomics::ProteolyticDigestion::DigestionParams *ProteinDigestion::getDigestionParams() const
        {
            return privateDigestionParams;
        }

        void ProteinDigestion::setDigestionParams(Proteomics::ProteolyticDigestion::DigestionParams *value)
        {
            privateDigestionParams = value;
        }

        Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior ProteinDigestion::getInitiatorMethionineBehavior() const
        {
            return privateInitiatorMethionineBehavior;
        }

        void ProteinDigestion::setInitiatorMethionineBehavior(Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior value)
        {
            privateInitiatorMethionineBehavior = value;
        }

        int ProteinDigestion::getMinPeptideLength() const
        {
            return privateMinPeptideLength;
        }

        void ProteinDigestion::setMinPeptideLength(int value)
        {
            privateMinPeptideLength = value;
        }

        int ProteinDigestion::getMaxPeptideLength() const
        {
            return privateMaxPeptideLength;
        }

        void ProteinDigestion::setMaxPeptideLength(int value)
        {
            privateMaxPeptideLength = value;
        }

        std::vector<Modification*> ProteinDigestion::getAllKnownFixedModifications() const
        {
            return privateAllKnownFixedModifications;
        }

        void ProteinDigestion::setAllKnownFixedModifications(const std::vector<Modification*> &value)
        {
            privateAllKnownFixedModifications = value;
        }

        std::vector<Modification*> ProteinDigestion::getVariableModifications() const
        {
            return privateVariableModifications;
        }

        void ProteinDigestion::setVariableModifications(const std::vector<Modification*> &value)
        {
            privateVariableModifications = value;
        }

        std::vector<PeptideWithSetModifications*> ProteinDigestion::SpeedySemiSpecificDigestion(Protein *protein)
        {
            std::vector<ProteolyticPeptide*> peptides;
            std::vector<int> oneBasedIndicesToCleaveAfter = privateProtease->GetDigestionSiteIndices(protein->getBaseSequence());
            //get peptide bonds to cleave SPECIFICALLY (termini included)

            //it's possible not to go through this loop (maxMissedCleavages+1>number of indexes), and that's okay.
            //It will get digested in the next loops (finish C/N termini)
            for (int i = 0; i < (int)oneBasedIndicesToCleaveAfter.size() - getMaximumMissedCleavages() - 1; i++)
            {
                bool retain = privateProtease->Retain(i, getInitiatorMethionineBehavior(), protein->getBaseSequence()[0]);
                if (retain) 
                {
                    //it's okay to use i instead of oneBasedIndicesToCleaveAfter[i], because the index of zero is zero and
                    //it only checks if it's the N-terminus or not
                    int peptideLength = oneBasedIndicesToCleaveAfter[i + getMaximumMissedCleavages() + 1] - oneBasedIndicesToCleaveAfter[i];
                    if (peptideLength >= getMinPeptideLength()) //if bigger than min
                    {
                        if (peptideLength <= getMaxPeptideLength()) //if an acceptable length (bigger than min, smaller than max), add it
                        {
                            auto tempVar = new ProteolyticPeptide (protein, oneBasedIndicesToCleaveAfter[i] + 1,
                                                                   oneBasedIndicesToCleaveAfter[i + privateMaximumMissedCleavages + 1],
                                                                   privateMaximumMissedCleavages,
                                                                   CleavageSpecificity::Full, "full");
                            peptides.push_back(tempVar);
                        }
                        else if (privateDigestionParams->getFragmentationTerminus() == FragmentationTerminus::N) 
                        {
                            //make something with the maximum length and fixed N
                            int tempIndex = oneBasedIndicesToCleaveAfter[i] + 1;
                            auto tempVar2 = new ProteolyticPeptide (protein, tempIndex,
                                                                    tempIndex + privateMaxPeptideLength,
                                                                    privateMaximumMissedCleavages,
                                                                    CleavageSpecificity::Semi, "semi");
                            peptides.push_back(tempVar2);
                        }
                        else //It has to be FragmentationTerminus.C //make something with the maximum length and fixed C
                        {
                            int tempIndex = oneBasedIndicesToCleaveAfter[i + privateMaximumMissedCleavages + 1];
                            auto tempVar3 = new ProteolyticPeptide(protein, tempIndex - privateMaxPeptideLength, tempIndex,
                                                                   privateMaximumMissedCleavages,
                                                                   CleavageSpecificity::Semi, "semi");
                            peptides.push_back(tempVar3);
                        }
                    }
                }

                if (privateProtease->Cleave(i, privateInitiatorMethionineBehavior, protein->getBaseSequence()[0]) &&
                    (privateDigestionParams->getFragmentationTerminus() == FragmentationTerminus::N || !retain)) 
                {
                    //it's okay to use i instead of oneBasedIndicesToCleaveAfter[i], because the index of zero is
                    // zero and it only checks if it's the N-terminus or not
                    int peptideLength = oneBasedIndicesToCleaveAfter[i + privateMaximumMissedCleavages + 1] - 1;
                    if (peptideLength >= privateMinPeptideLength )
                    {
                        if (peptideLength <= privateMaxPeptideLength )
                        {
                            auto tempVar4 = new ProteolyticPeptide(protein, 2,
                                                                   oneBasedIndicesToCleaveAfter[i + privateMaximumMissedCleavages + 1],
                                                                   privateMaximumMissedCleavages,
                                                                   CleavageSpecificity::Full, "full:M cleaved");
                            peptides.push_back(tempVar4);
                        }
                        else if (privateDigestionParams->getFragmentationTerminus() == FragmentationTerminus::N)
                        {
                            auto tempVar5 = new ProteolyticPeptide (protein, 2, 2 + privateMaxPeptideLength,
                                                                    privateMaximumMissedCleavages,
                                                                    CleavageSpecificity::Semi, "semi");
                            peptides.push_back(tempVar5);
                        }
                        else //It has to be FragmentationTerminus.C //make something with the maximum length and fixed C
                        {
                            //kinda tricky, because we'll be creating a duplication if cleavage is variable
                            if (!privateProtease->Retain(i, privateInitiatorMethionineBehavior, protein->getBaseSequence()[0])) 
                            {
                                //only if cleave, because then not made earlier during retain
                                int tempIndex = oneBasedIndicesToCleaveAfter[i + privateMaximumMissedCleavages + 1];
                                auto tempVar6 = new ProteolyticPeptide(protein, tempIndex - privateMaxPeptideLength,
                                                                       tempIndex, privateMaximumMissedCleavages,
                                                                       CleavageSpecificity::Semi, "semi");
                                peptides.push_back(tempVar6);
                            }
                        }
                    }
                }
            }

            //wrap up the termini that weren't hit earlier
            int lastIndex = oneBasedIndicesToCleaveAfter.size() - 1; //last cleavage index (the c-terminus)
            int maxIndexDifference = privateMaximumMissedCleavages < lastIndex ? privateMaximumMissedCleavages : lastIndex; //the number of index differences allowed.
            //If the protein has fewer cleavage sites than allowed missed cleavages, just use the number of cleavage sites (lastIndex)
            bool nTerminusFragmentation = privateDigestionParams->getFragmentationTerminus() == FragmentationTerminus::N;
            for (int i = 1; i <= maxIndexDifference; i++) 
            {
                //i is the difference (in indexes) between indexes (cleavages), so it needs to start at 1,
                //or the peptide would have length = 0
                int startIndex = nTerminusFragmentation ? oneBasedIndicesToCleaveAfter[lastIndex - i] : oneBasedIndicesToCleaveAfter[0];
                int endIndex = nTerminusFragmentation ? oneBasedIndicesToCleaveAfter[lastIndex] : oneBasedIndicesToCleaveAfter[i];

                int peptideLength = endIndex - startIndex;
                if (peptideLength >= privateMinPeptideLength )
                {
                    if (peptideLength <= privateMaxPeptideLength ) //if okay length, add it up to the terminus
                    {
                        auto  tempVar7 = new ProteolyticPeptide(protein, startIndex + 1, endIndex, i - 1,
                                                                CleavageSpecificity::Full, "full");
                        peptides.push_back(tempVar7);
                    }
                    else //update so that not the end of terminus
                    {
                        if (nTerminusFragmentation)
                        {
                            endIndex = startIndex + privateMaxPeptideLength;
                        }
                        else
                        {
                            startIndex = endIndex - privateMaxPeptideLength;
                        }
                        auto  tempVar8 = new ProteolyticPeptide(protein, startIndex + 1, endIndex, i - 1,
                                                                CleavageSpecificity::Semi, "semi");
                        peptides.push_back(tempVar8);
                    }
                }
            }

            // Also digest using the proteolysis product start/end indices
#ifdef ORIG
            peptides.AddRange(protein->getProteolysisProducts().Where([&] (std::any proteolysisProduct)
            {
                return proteolysisProduct::OneBasedEndPosition.HasValue &&
                    proteolysisProduct::OneBasedBeginPosition.HasValue &&
                    (proteolysisProduct::OneBasedBeginPosition != 1 ||
                     proteolysisProduct::OneBasedEndPosition != protein->getLength());
            })->Select([&] (std::any proteolysisProduct)
            {
                new ProteolyticPeptide(protein, proteolysisProduct::OneBasedBeginPosition->Value,
                                       proteolysisProduct::OneBasedEndPosition->Value, 0,
                                       CleavageSpecificity::Full, proteolysisProduct::Type + " start");
            }));
#endif
            for ( auto proteolysisProduct : protein->getProteolysisProducts() ){
                if ( proteolysisProduct->getOneBasedEndPosition().has_value()     &&
                     proteolysisProduct->getOneBasedBeginPosition().has_value()   &&
                     (proteolysisProduct->getOneBasedBeginPosition().value() != 1 ||
                      proteolysisProduct->getOneBasedEndPosition().value()   != protein->getLength() ) ){
                    ProteolyticPeptide *p = new ProteolyticPeptide(protein,
                                                   proteolysisProduct->getOneBasedBeginPosition().value(),
                                                   proteolysisProduct->getOneBasedEndPosition().value(), 0,
                                                   CleavageSpecificity::Full,
                                                   proteolysisProduct->getType() + " start");
                    peptides.push_back(p);
                }
            }

            std::vector<PeptideWithSetModifications*> temppeptides;
            
            for ( auto peptide : peptides ) {
                std::vector<PeptideWithSetModifications*> ts = peptide->GetModifiedPeptides(privateAllKnownFixedModifications,
                                                                                            privateDigestionParams,
                                                                                            privateVariableModifications);
                for ( auto t : ts ) {
                    temppeptides.push_back (t);
                }
            }
            return temppeptides;
        }

        std::vector<PeptideWithSetModifications*> ProteinDigestion::Digestion(Protein *protein)
        {
            auto unmodifiedPeptides = getProtease()->GetUnmodifiedPeptides(protein, privateMaximumMissedCleavages,
                                                                           privateInitiatorMethionineBehavior,
                                                                           privateMinPeptideLength,
                                                                           privateMaxPeptideLength);
            std::vector<PeptideWithSetModifications*> tmp;
            for ( auto peptide : unmodifiedPeptides ) {
                std::vector<PeptideWithSetModifications*> ps = peptide->GetModifiedPeptides(privateAllKnownFixedModifications,
                                                                                            privateDigestionParams,
                                                                                            privateVariableModifications);
                for ( auto p : ps ) {
                    tmp.push_back(p);
                }
            }
            return tmp;
        }
    }
}
