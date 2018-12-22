#pragma once

#include <string>
#include "tangible_filesystem.h"

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
        std::wstring privateNativeIdFormat;
        std::wstring privateMassSpectrometerFileFormat;
        std::wstring privateCheckSum;
        std::wstring privateFileChecksumType;
        System::Uri *privateUri;
        std::wstring privateFileName;
        std::wstring privateId;

//        #region Public Constructors

    public:
        SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, const std::wstring &id);

        SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, const std::wstring &filePath, const std::wstring &id);

        SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, System::Uri *uri, const std::wstring &id, const std::wstring &fileName);

//        #endregion Public Constructors

//        #region Public Properties

        std::wstring getNativeIdFormat() const;
        std::wstring getMassSpectrometerFileFormat() const;
        std::wstring getCheckSum() const;
        std::wstring getFileChecksumType() const;
        System::Uri *getUri() const;

        std::wstring getFileName() const;
        std::wstring getId() const;

//        #endregion Public Properties
    };
}
