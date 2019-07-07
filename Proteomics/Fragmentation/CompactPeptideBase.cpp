#include "CompactPeptideBase.h"
#include "NeutralTerminusFragment.h"
#include "../Modifications/Modification.h"

using namespace Chemistry;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::ProteolyticDigestion;
namespace Proteomics
{
    namespace Fragmentation
    {

        std::vector<NeutralTerminusFragment*> CompactPeptideBase::getTerminalMasses() const
        {
            return privateTerminalMasses;
        }

        void CompactPeptideBase::setTerminalMasses(const std::vector<NeutralTerminusFragment*> &value)
        {
            privateTerminalMasses = value;
        }

        double CompactPeptideBase::getMonoisotopicMassIncludingFixedMods() const
        {
            return privateMonoisotopicMassIncludingFixedMods;
        }

        void CompactPeptideBase::setMonoisotopicMassIncludingFixedMods(double value)
        {
            privateMonoisotopicMassIncludingFixedMods = value;
        }

        bool CompactPeptideBase::Equals(std::any obj)
        {
            auto cp = dynamic_cast<CompactPeptideBase*>(obj);
            return cp != nullptr && Equals(cp);
        }

        int CompactPeptideBase::GetHashCode()
        {
//            unchecked
                auto result = 0;
                if (!getTerminalMasses().empty())
                {
                    for (auto mass : getTerminalMasses())
                    {
                        result += (result * 31) ^ mass->GetHashCode();
                    }
                }
                return result;
//C# TO C++ CONVERTER TODO TASK: End of the original C# 'unchecked' block.
        }

        bool CompactPeptideBase::Equals(CompactPeptideBase *cp)
        {
            if (!getTerminalMasses().empty() && !cp->getTerminalMasses().empty()) //neither series is nulll
            {
                return getTerminalMasses().SequenceEqual(cp->getTerminalMasses());
            }
            else //Cannot compare
            {
                return false;
            }
        }

        std::vector<NeutralTerminusFragment*> CompactPeptideBase::ComputeNeutralTerminusFragments(PeptideWithSetModifications *peptide, FragmentationTerminus fragmentationTerminus)
        {
            double mass = 0;

            if (fragmentationTerminus == FragmentationTerminus::N || fragmentationTerminus == FragmentationTerminus::Both)
            {
                for (int r = 0; r <= peptide->getLength() - 1; r++) //This is a zero based indexed for residues. The index of the first amino acid in the peptide is 0.
                {
                    mass += Residue::ResidueMonoisotopicMass[peptide[r]]; //This is a zero based indexed for residues. The index of the first amino acid in the peptide is 0.

                    // side-chain mod
                    Modification currentModification;
                    std::unordered_map<int, Modification*>::const_iterator peptide.AllModsOneIsNterminus_iterator = peptide.AllModsOneIsNterminus.find(r + 2);
                    if (peptide->getAllModsOneIsNterminus()_iterator != peptide->getAllModsOneIsNterminus().end()) //This is a one based index. The index of the fragment from the first amino acid is 1.
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification::MonoisotopicMass);
                    }
                    else
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                    }

                    // N-terminal mod
                    std::unordered_map<int, Modification*>::const_iterator peptide.AllModsOneIsNterminus_iterator = peptide.AllModsOneIsNterminus.find(1);
                    if (r == 0 && peptide->getAllModsOneIsNterminus()_iterator != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification::MonoisotopicMass);
                    }
                    else
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                    }

                    if (r != peptide->getLength() - 1)
                    {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return new NeutralTerminusFragment(FragmentationTerminus::N, mass, r + 1, r + 1); //This is a one based index. The index of the fragment from the first amino acid is 1.
                    }
                }
            }

            if (fragmentationTerminus == FragmentationTerminus::C || fragmentationTerminus == FragmentationTerminus::Both)
            {
                mass = 0;

                for (int r = peptide->getLength() - 1; r >= 0; r--)
                {
                    mass += Residue::ResidueMonoisotopicMass[peptide[r]];

                    // side-chain mod
                    Modification currentModification;
                    std::unordered_map<int, Modification*>::const_iterator peptide.AllModsOneIsNterminus_iterator = peptide.AllModsOneIsNterminus.find(r + 2);
                    if (peptide->getAllModsOneIsNterminus()_iterator != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification::MonoisotopicMass);
                    }
                    else
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                    }

                    // C-terminal mod
                    std::unordered_map<int, Modification*>::const_iterator peptide.AllModsOneIsNterminus_iterator = peptide.AllModsOneIsNterminus.find(peptide.Length + 2);
                    if (r == peptide->getLength() - 1 && peptide->getAllModsOneIsNterminus()_iterator != peptide->getAllModsOneIsNterminus().end())
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                        mass += static_cast<double>(currentModification::MonoisotopicMass);
                    }
                    else
                    {
                        currentModification = peptide->AllModsOneIsNterminus_iterator->second;
                    }

                    if (r != -1)
                    {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        yield return new NeutralTerminusFragment(FragmentationTerminus::C, mass, peptide->getLength() - r, r + 1);
                    }
                }
            }
        }
    }
}
