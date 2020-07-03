#pragma once

#include "DecoyType.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <mutex>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Protein/SequenceVariation.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
    class DecoyProteinGenerator final
    {
        /// <summary>
        /// Generates decoys for a list of proteins
        /// </summary>
        /// <param name="proteins"></param>
        /// <param name="decoyType"></param>
        /// <param name="digestionParams"></param>
        /// <param name="randomSeed">Used when decoy type is shuffle for shuffling the peptides</param>
        /// <returns></returns>
    public:
        static std::vector<Protein*> GenerateDecoys(std::vector<Protein*> &proteins, DecoyType decoyType,
                                                    int maxThreads = -1);

        /// <summary>
        /// Generates a reverse decoy sequence
        /// </summary>
        /// <param name="protein"></param>
        /// <returns></returns>
    private:
        static std::vector<Protein*> GenerateReverseDecoys(std::vector<Protein*> &proteins, int maxThreads = -1);

        static std::vector<SequenceVariation*> ReverseSequenceVariations(std::vector<SequenceVariation*> &forwardVariants, Protein *protein, const std::string &reversedSequence);

        /// <summary>
        /// Generates a "slided" decoy sequence
        /// </summary>
        /// <param name="protein"></param>
        /// <returns></returns>
        static std::vector<Protein*> GenerateSlideDecoys(std::vector<Protein*> &proteins, int maxThreads = -1);

        /// <summary>
        /// Not sure...
        /// </summary>
        /// <param name="i"></param>
        /// <param name="numSlides"></param>
        /// <param name="sequenceLength"></param>
        /// <param name="methioninePresent"></param>
        /// <returns></returns>
        static int GetOldShuffleIndex(int i, int numSlides, int sequenceLength, bool methioninePresent);
    };
}
