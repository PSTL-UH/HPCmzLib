#include "SourceFile.h"


namespace MassSpectrometry {

    SourceFile::SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, const std::wstring &id) {
        NativeIdFormat = nativeIdFormat;
        MassSpectrometerFileFormat = massSpectrometerFileFormat;
        CheckSum = checkSum;
        FileChecksumType = fileChecksumType;
        Id = id;
    }

    SourceFile::SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, const std::wstring &filePath, const std::wstring &id) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {
        getUri() result;
        getUri()->TryCreate(Directory::GetParent(filePath)->FullName, UriKind::Absolute, result);
        this->Uri = result;
        this->FileName = FileSystem::getFileName(filePath);
    }

    SourceFile::SourceFile(const std::wstring &nativeIdFormat, const std::wstring &massSpectrometerFileFormat, const std::wstring &checkSum, const std::wstring &fileChecksumType, System::Uri *uri, const std::wstring &id, const std::wstring &fileName) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {
        this->Uri = uri;
        this->FileName = fileName;
    }

    std::wstring SourceFile::getNativeIdFormat() const {
        return privateNativeIdFormat;
    }

    std::wstring SourceFile::getMassSpectrometerFileFormat() const {
        return privateMassSpectrometerFileFormat;
    }

    std::wstring SourceFile::getCheckSum() const {
        return privateCheckSum;
    }

    std::wstring SourceFile::getFileChecksumType() const {
        return privateFileChecksumType;
    }

    System::Uri *SourceFile::getUri() const {
        return privateUri;
    }

    std::wstring SourceFile::getFileName() const {
        return privateFileName;
    }

    std::wstring SourceFile::getId() const {
        return privateId;
    }
}
