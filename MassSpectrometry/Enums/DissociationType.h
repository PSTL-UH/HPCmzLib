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
#include <cctype>
#include <algorithm>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (DissociationType.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

namespace MassSpectrometry {
    enum class DissociationType {
        Unknown = -1,

        // The values below are identical to thermo names
        CID = 0, // MS:1000133 collision-induced dissociation

        IRMPD = 1, // MS:1000435 photodissociation
        ECD = 2, // MS:1000250 electron capture dissociation
        PQD = 3, // MS:1000599 pulsed q dissociation
        ETD = 4, // MS:1000598 electron transfer dissociation
        HCD = 5, // MS:1002481 higher energy beam-type collision-induced dissociation

        AnyActivationType = 6,

        EThcD = 7, // MS:1002631 Electron-Transfer/Higher-Energy Collision Dissociation (EThcD)
        Custom = 8,

        ISCID = 9,
        //NPTR = 10,
        // The values above are identical to thermo names

        //ISCID = 11
    };

    class GetDissocationType{
    public:
        static DissociationType GetDissocationTypeFromString(std::string &dissociation) {
            std::transform(dissociation.begin(), dissociation.end(), dissociation.begin(), [] (unsigned char c) {return toupper(c); } );
            if (dissociation.find("CID") != std::string::npos){
                return DissociationType::CID;
            }
            else if (dissociation.find("IRMPD") != std::string::npos){
                return DissociationType::IRMPD;
            }
            else if (dissociation.find("ECD") != std::string::npos){
                return DissociationType::ECD;
            }
            else if (dissociation.find("PQD") != std::string::npos){
                return DissociationType::PQD;
            }
            else if (dissociation.find("ETD") != std::string::npos){
                return DissociationType::ETD;
            }
            else if (dissociation.find("HCD") != std::string::npos){
                return DissociationType::HCD;
            }
            else if (dissociation.find("AnyActivationType") != std::string::npos){
                return DissociationType::AnyActivationType;
            }
            else if (dissociation.find("EThcD") != std::string::npos){
                return DissociationType::EThcD;
            }
            else if (dissociation.find("Custom") != std::string::npos){
                return DissociationType::Custom;
            }
            else if (dissociation.find("ISCID") != std::string::npos){
                return DissociationType::ISCID;
            }
            return DissociationType::Unknown;
        }

        static std::string GetDissocationTypeAsString(DissociationType dissociation) {
            if (dissociation == DissociationType::CID){
                return "CID";
            }
            else if (dissociation == DissociationType::IRMPD){
                return "IRMPD";
            }
            else if (dissociation == DissociationType::ECD){
                return "ECD";
            }
            else if (dissociation == DissociationType::PQD){
                return "PQD";
            }
            else if (dissociation == DissociationType::ETD){
                return "ETD";
            }
            else if (dissociation == DissociationType::HCD){
                return "HCD";
            }
            else if (dissociation == DissociationType::AnyActivationType){
                return "AnyActivationType";
            }
            else if (dissociation == DissociationType::EThcD){
                return "EThcD";
            }
            else if (dissociation == DissociationType::Custom){
                return "Custom";
            }
            else if (dissociation == DissociationType::ISCID){
                return "ISCID";
            }
            return "Unknown";
        }
    };
}
