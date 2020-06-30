/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <any>
#include <tuple>

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

    // Having a std::tuple as the key of a std::unordered_map is not directly allowed
    // in C++.
    // See https://stackoverflow.com/questions/11408934/using-a-stdtuple-as-key-for-stdunordered-map
    // for how to handle this.
    typedef std::tuple<int, Modification*> ModDbTuple;
    struct ModDbTuple_hash: public std::unary_function<ModDbTuple, std::size_t>{
        std::size_t operator() (const ModDbTuple& k ) const
        {
            size_t h1= std::hash<int>{}(std::get<0>(k));
            size_t h2= std::hash<void*>{}(std::get<1>(k));
            return h1 ^ (h2 << 1);
        }
    };

    struct ModDbTuple_equal: public std::binary_function<ModDbTuple, ModDbTuple, bool>{
        bool operator() (const ModDbTuple& lhs, const ModDbTuple& rhs) const
        {
            return std::get<0>(lhs) == std::get<0>(rhs) &&
                std::get<1>(lhs) == std::get<1>(rhs); 
        }
    };
    typedef std::unordered_set<ModDbTuple, ModDbTuple_hash, ModDbTuple_equal> ModDbTuple_set;
    
    class ProteinDbWriter
    {
        /// <summary>
        /// Writes a protein database in mzLibProteinDb format, with additional modifications from the AdditionalModsToAddToProteins list.
        /// </summary>
        /// <param name="additionalModsToAddToProteins"></param>
        /// <param name="proteinList"></param>
        /// <param name="outputFileName"></param>
        /// <returns>The new "modified residue" entries that are added due to being in the Mods dictionary</returns>
    public:
        static std::unordered_map<std::string, int> WriteXmlDatabase(std::unordered_map<std::string,ModDbTuple_set> &additionalModsToAddToProteins,
                                                           std::vector<Protein*> &proteinList,
                                                           const std::string &outputFileName);

        static void WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::string &outputFileName,
                                       const std::string &delimeter);

    private:
        static std::unordered_map<int, std::unordered_set<std::string>> GetModsForThisProtein(
            Protein *protein, SequenceVariation *seqvar,
            //std::unordered_map<std::string, std::unordered_set<ModDbTuple, ModDbTuple_hash, ModDbTuple_equal>> &additionalModsToAddToProteins,
            std::unordered_map<std::string, ModDbTuple_set> &additionalModsToAddToProteins,
            std::unordered_map<std::string, int> &newModResEntries);
    };
}
