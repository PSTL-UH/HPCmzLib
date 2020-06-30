/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "DecoyType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
#include "stringhelper.h"
#include "stringbuilder.h"

#include "FastaHeaderFieldRegex.h"
#include "../Proteomics/Proteomics.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

    // Having a std::tuple as the key of a std::unordered_map is not directly allowed
    // in C++.
    // See https://stackoverflow.com/questions/11408934/using-a-stdtuple-as-key-for-stdunordered-map
    // for how to handle this.

    typedef std::tuple<std::string, std::string, bool, bool> ProteinDbTuple;

    struct ProteinDbTuple_hash: public std::unary_function<ProteinDbTuple, std::size_t>{
        std::size_t operator() (const ProteinDbTuple& k ) const
        {
            size_t h1= std::hash<std::string>{}(std::get<0>(k));
            size_t h2= std::hash<std::string>{}(std::get<1>(k));
            size_t h3= std::hash<bool>{}(std::get<2>(k));
            size_t h4= std::hash<bool>{}(std::get<3>(k));
            return h1 ^ (h2 << 1) ^ (h3 << 2 ) ^ (h4 << 3);
        }
    };

    struct ProteinDbTuple_equal: public std::binary_function<ProteinDbTuple, ProteinDbTuple, bool>{
        bool operator() (const ProteinDbTuple& lhs, const ProteinDbTuple& rhs) const
        {
            return std::get<0>(lhs) == std::get<0>(rhs) &&
                std::get<1>(lhs) == std::get<1>(rhs) && 
                std::get<2>(lhs) == std::get<2>(rhs) && 
                std::get<3>(lhs) == std::get<3>(rhs) ;
        }
    };

    class ProteinDbLoader final
    {
    public:
        static FastaHeaderFieldRegex *const UniprotAccessionRegex;
        static FastaHeaderFieldRegex *const UniprotFullNameRegex;
        static FastaHeaderFieldRegex *const UniprotNameRegex;
        static FastaHeaderFieldRegex *const UniprotGeneNameRegex;
        static FastaHeaderFieldRegex *const UniprotOrganismRegex;

        static FastaHeaderFieldRegex *const EnsemblAccessionRegex;
        static FastaHeaderFieldRegex *const EnsemblFullNameRegex;
        static FastaHeaderFieldRegex *const EnsemblGeneNameRegex;

        static std::unordered_map<std::string, std::vector<Modification*>> IdToPossibleMods;
        static std::unordered_map<std::string, Modification*> IdWithMotifToMod;

        /// <summary>
        /// Stores the last database file path.
        /// </summary>
    private:
        static std::string last_database_location;

        /// <summary>
        /// Stores the modification list read during LoadProteinXML
        /// </summary>
        static std::vector<Modification*> protein_xml_modlist_general;

        /// <summary>
        /// Load a mzLibProteinDb or UniProt XML file. Protein modifications may be specified before
        /// the protein entries (mzLibProteinDb format).
        /// If so, this modification list can be acquired with GetPtmListFromProteinXml after using this method.
        /// They may also be read in separately from a ptmlist text file, and then input as allKnownModifications.
        /// If protein modifications are specified both in the mzLibProteinDb XML file and in
        /// allKnownModifications, they are collapsed into a HashSet of Modifications before generating
        /// Protein entries.
        /// </summary>
    public:
        static std::vector<Protein*> LoadProteinXML(const std::string &proteinDbLocation,
                                          bool generateTargets, DecoyType decoyType,
                                          std::vector<Modification*> &allKnownModifications,
                                          bool isContaminant,
                                          std::vector<std::string> &modTypesToExclude,
                                          std::unordered_map<std::string, Modification*> &unknownModifications,
                                          int maxThreads = -1,
                                          int maxHeterozygousVariants = 4,
                                          int minAlleleDepth = 1);

        /// <summary>
        /// Get the modification entries specified in a mzLibProteinDb XML file (.xml or .xml.gz).
        /// </summary>
        static std::vector<Modification*> GetPtmListFromProteinXml(const std::string &proteinDbLocation);

        /// <summary>
        /// Load a protein fasta database, using regular expressions to get various aspects of the headers.
        /// The first regex capture group is used as each field.
        /// </summary>
        static std::vector<Protein*> LoadProteinFasta(const std::string &proteinDbLocation,
                                                      bool generateTargets,
                                                      DecoyType decoyType,
                                                      bool isContaminant,
                                                      FastaHeaderFieldRegex *accessionRegex,
                                                      FastaHeaderFieldRegex *fullNameRegex,
                                                      FastaHeaderFieldRegex *nameRegex,
                                                      FastaHeaderFieldRegex *geneNameRegex,
                                                      FastaHeaderFieldRegex *organismRegex,
                                                      std::vector<std::string> &errors,
                                                      int maxThreads = -1);

        /// <summary>
        /// Merge proteins that have the same accession, sequence, and contaminant designation.
        /// </summary>
        static std::vector<Protein*> MergeProteins(std::vector<Protein*> &mergeThese);

    private:
        static std::string ApplyRegex(FastaHeaderFieldRegex *regex, const std::string &line);

        static std::unordered_map<std::string, std::vector<Modification*>> GetModificationDict(std::vector<Modification*> &mods);

        static std::unordered_map<std::string, Modification*> GetModificationDictWithMotifs(std::vector<Modification*> &mods);
    };
}
