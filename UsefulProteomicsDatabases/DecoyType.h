/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "../Proteomics/ProteolyticDigestion/ProteinDigestion.h"
using namespace Proteomics::ProteolyticDigestion;

#include <string>

namespace UsefulProteomicsDatabases
{
    enum class DecoyType
    {
        /// <summary>
        /// Generate no decoy
        /// </summary>
        None,

        /// <summary>
        /// Reverse the protein sequence, possibly keeping the initiating methionine in place
        /// </summary>
        Reverse,

        /// <summary>
        /// No clue...
        /// </summary>
        Slide,

        /// <summary>
        /// Generate decoy by:
        /// 1. simulating proteolytic digesiton (if any)
        /// 2. shuffling the resulting peptides, keeping the cleavage site and possibly initiating methionine in place,
        /// 3. concatenating them back together into
        /// </summary>
        Shuffle,

        /// <summary>
        /// No clue... not implemented
        /// </summary>
        Random
    };

    static std::string DecoyTypeToString( DecoyType &t ) {
        std::string s;

        if ( t == DecoyType::None ) 
            s = "None";
        else if ( t == DecoyType::Reverse ) 
            s = "Reverse";
        else if ( t == DecoyType::Slide ) 
            s = "Slide";
        else if ( t == DecoyType::Shuffle )
            s = "Shuffle";
        else if (t == DecoyType::Random )
            s = "Random";

        return s;
    }

    static DecoyType DecoyTypeFromString( std::string &s ) {
        DecoyType t;

        if ( s == "None" ) {
            t = DecoyType::None;           
        }
        else if (  s == "Reverse") {
            t = DecoyType::Reverse;
        }
        else if (  s == "Slide") {
            t = DecoyType::Slide;
        }
        else if (  s == "Shuffle") {
            t = DecoyType::Shuffle;
        }
        else if (  s == "Random") {
            t = DecoyType::Random;
        }
        return t;
    }

}
