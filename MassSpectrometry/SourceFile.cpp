#include "SourceFile.h"


namespace MassSpectrometry {

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &id) {
        privateNativeIdFormat = nativeIdFormat;
        privateMassSpectrometerFileFormat = massSpectrometerFileFormat;
        privateCheckSum = checkSum;
        privateFileChecksumType = fileChecksumType;
        privateId = id;
    }

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, const std::string &filePath, const std::string &id) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {

#ifdef ORIG
        Uri.TryCreate(Directory.GetParent(filePath).FullName, UriKind.Absolute, out Uri result);
        this.Uri = result;
        this.FileName = Path.GetFileName(filePath);
#endif        
        this->privateUri = new Uri(filePath);
        this->privateFileName = privateUri->getFileName();
    }

    SourceFile::SourceFile(const std::string &nativeIdFormat, const std::string &massSpectrometerFileFormat, const std::string &checkSum, const std::string &fileChecksumType, Uri *uri, const std::string &id, const std::string &fileName) : SourceFile(nativeIdFormat, massSpectrometerFileFormat, checkSum, fileChecksumType, id) {
        this->privateUri = uri;
        this->privateFileName = fileName;
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

    Uri *SourceFile::getUri() const {
        return privateUri;
    }

    std::string SourceFile::getFileName() const {
        return privateFileName;
    }

    std::string SourceFile::getId() const {
        return privateId;
    }
}
