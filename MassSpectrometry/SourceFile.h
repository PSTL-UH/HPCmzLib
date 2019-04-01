#pragma once

#include <string>
#include "tangible_filesystem.h"
#include "Uri.h"

// Copyright 2017 Stefan Solntsev
//
// This file (SourceFile.cs) is part of MassSpectrometry.
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
    class SourceFile {
    private:
        std::string privateNativeIdFormat;
        std::string privateMassSpectrometerFileFormat;
        std::string privateCheckSum;
        std::string privateFileChecksumType;
        Uri *privateUri;
        std::string privateFileName;
        std::string privateId;


    public:
        SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &id);

        SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &filePath, const std::string &id);

        SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, Uri *uri, const std::string &id, const std::string &fileName);


        std::string getNativeIdFormat() const;
        std::string getMassSpectrometerFileFormat() const;
        std::string getCheckSum() const;
        std::string getFileChecksumType() const;
        Uri *getUri() const;

        std::string getFileName() const;
        std::string getId() const;

    };
}
