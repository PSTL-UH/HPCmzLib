/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "../MassSpectrometry/Enums/DissociationType.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <tuple>
#include "stringhelper.h"

#include "../Proteomics/Modifications/Modification.h"
#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
    class PtmListLoader final
    {
    private:
        static std::unordered_map<std::string, char> AminoAcidCodes;

    public:
        static void InitAminoAcidCodes();

        /// <summary>
        /// Read a list of modifications from a text file.
        /// </summary>
        /// <param name="ptmListLocation"></param>
        /// <returns></returns>


        static std::vector<Modification*> ReadModsFromFile(const std::string &ptmListLocation,
               std::vector<std::tuple<Modification *, std::string>> &filteredModsWithWarnings);

        /// <summary>
        /// Reads a list of modifications from a text file.
        /// </summary>
        /// <param name="ptmListLocation"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromFile(const std::string &ptmListLocation,
                                std::unordered_map<std::string, int> &formalChargesDictionary,
                std::vector<std::tuple<Modification*, std::string>> &filteredModsWithWarnings);

        /// <summary>
        /// Reads a list of modifications from a string representation of a ptmlist text file.
        /// </summary>
        /// <param name="storedModifications"></param>
        /// <returns></returns>
        static std::vector<Modification*> ReadModsFromString(const std::string &storedModifications,
                                                             std::vector<std::tuple<Modification*, std::string>> &filteredModificationsWithWarnings);

        /// <summary>
        /// Parse modification from string representation
        /// </summary>
        /// <param name="ptmListLocation"></param>
        /// <param name="specification"></param>
        /// <param name="formalChargesDictionary"></param>
        /// <returns></returns>
    private:
        static std::vector<Modification*> ReadMod(const std::string &ptmListLocation, std::vector<std::string> &specification,
                                                  std::unordered_map<std::string, int> &formalChargesDictionary);

        template<typename T, typename U>
        static bool IsNullOrEmpty(std::unordered_map<T, U> &Dictionary)
        {
            return (Dictionary.empty() || Dictionary.size() < 1);
        }

        /// <summary>
        /// Subtract the mass of a proton for every formal charge on a modification.
        /// </summary>
        /// <param name="_monoisotopicMass"></param>
        /// <param name="_chemicalFormula"></param>
        /// <param name="_databaseReference"></param>
        /// <param name="formalChargesDictionary"></param>
        /// <returns></returns>
        static double AdjustMonoIsotopicMassForFormalCharge(std::optional<double> &_monoisotopicMass,
                                                            ChemicalFormula *_chemicalFormula,
                                                            std::unordered_map<std::string, std::vector<std::string>> &_databaseReference,
                                                            std::unordered_map<std::string, int> &formalChargesDictionary);

        /// <summary>
        /// Parse dissociation type string
        /// </summary>
        /// <param name="modType"></param>
        /// <returns></returns>
        static DissociationType ModDissociationType(std::string modType);
        
        /// <summary>
        /// Parse diagnostic ion and neutral loss strings
        /// </summary>
        /// <param name="oneEntry"></param>
        /// <returns></returns>
        static std::unordered_map<DissociationType, std::vector<double>> DiagnosticIonsAndNeutralLosses(const std::string &oneEntry,
                                                         std::unordered_map<DissociationType, std::vector<double>> &dAndNDictionary);
    };
}
