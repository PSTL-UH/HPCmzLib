#include "SourceFile.h"


namespace MassSpectrometry {

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &id) {
        NativeIdFormat = nativeIdFormat;
        MassSpectrometerFileFormat = massSpectrometerFileFormat;
        CheckSum = checkSum;
        FileChecksumType = fileChecksumType;
        Id = id;
    }

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &filePath, const std::string &id) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {
        getUri() result;
        getUri()->TryCreate(Directory::GetParent(filePath)->FullName, UriKind::Absolute, result);
        this->Uri = result;
        this->FileName = FileSystem::getFileName(filePath);
    }

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, System::Uri *uri, const std::string &id, const std::string &fileName) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {
        this->Uri = uri;
        this->FileName = fileName;
    }

    std::string SourceFile::getNativeIdFormat() const {
        return privateNativeIdFormat;
    }

    std::string SourceFile::getMassSpectrometerFileFormat() const {
        return privateMassSpectrometerFileFormat;
    }

    std::string SourceFile::getCheckSum() const {
        return privateCheckSum;
    }

    std::string SourceFile::getFileChecksumType() const {
        return privateFileChecksumType;
    }

    System::Uri *SourceFile::getUri() const {
        return privateUri;
    }

    std::string SourceFile::getFileName() const {
        return privateFileName;
    }

    std::string SourceFile::getId() const {
        return privateId;
    }
}
