#include "Peptide.h"
#include "SpectraFileInfo.h"
#include "ProteinGroup.h"


namespace FlashLFQ
{

    Peptide::Peptide(const std::string &sequence, bool useForProteinQuant) : Sequence(sequence), UseForProteinQuant(useForProteinQuant)
    {
        intensities = std::unordered_map<SpectraFileInfo*, double>();
        detectionTypes = std::unordered_map<SpectraFileInfo*, DetectionType>();
        proteinGroups = std::unordered_set<ProteinGroup*>();
    }

    std::string Peptide::TabSeparatedHeader(std::vector<SpectraFileInfo*> &rawFiles)
    {
        auto sb = new StringBuilder();
        sb->append(std::string("Sequence") + "\t");
        sb->append(std::string("Protein Groups") + "\t");
        sb->append(std::string("Gene Names") + "\t");
        sb->append(std::string("Organism") + "\t");
        for (auto rawfile : rawFiles)
        {
            sb->append("Intensity_" + rawfile->FilenameWithoutExtension + "\t");
        }
        for (auto rawfile : rawFiles)
        {
            sb->append("Detection Type_" + rawfile->FilenameWithoutExtension + "\t");
        }

        delete sb;
        return sb->toString();
    }

    double Peptide::GetIntensity(SpectraFileInfo *fileInfo)
    {
        double intensity;
        std::unordered_map<SpectraFileInfo*, double>::const_iterator intensities_iterator = intensities.find(fileInfo);
        if (intensities_iterator != intensities.end())
        {
            intensity = intensities_iterator->second;
            return intensity;
        }
        else
        {
            intensity = intensities_iterator->second;
            return 0;
        }
    }

    void Peptide::SetIntensity(SpectraFileInfo *fileInfo, double intensity)
    {
        if (intensities.find(fileInfo) != intensities.end())
        {
            intensities[fileInfo] = intensity;
        }
        else
        {
            intensities.emplace(fileInfo, intensity);
        }
    }

    DetectionType Peptide::GetDetectionType(SpectraFileInfo *fileInfo)
    {
        DetectionType detectionType;
        std::unordered_map<SpectraFileInfo*, DetectionType>::const_iterator detectionTypes_iterator = detectionTypes.find(fileInfo);
        if (detectionTypes_iterator != detectionTypes.end())
        {
            detectionType = detectionTypes_iterator->second;
            return detectionType;
        }
        else
        {
            detectionType = detectionTypes_iterator->second;
            return DetectionType::NotDetected;
        }
    }

    void Peptide::SetDetectionType(SpectraFileInfo *fileInfo, DetectionType detectionType)
    {
        if (detectionTypes.find(fileInfo) != detectionTypes.end())
        {
            detectionTypes[fileInfo] = detectionType;
        }
        else
        {
            detectionTypes.emplace(fileInfo, detectionType);
        }
    }

    std::string Peptide::ToString(std::vector<SpectraFileInfo*> &rawFiles)
    {
        StringBuilder *str = new StringBuilder();
        str->append(Sequence + "\t");
        str->append(std::string::Join(";", proteinGroups.Select([&] (std::any p)
        {
            p::ProteinGroupName;
        }).Distinct()) + "\t");
        str->append(std::string::Join(";", proteinGroups.Select([&] (std::any p)
        {
            p::GeneName;
        }).Distinct()) + "\t");
        str->append(std::string::Join(";", proteinGroups.Select([&] (std::any p)
        {
            p::Organism;
        }).Distinct()) + "\t");

        for (auto file : rawFiles)
        {
            str->append(std::to_string(GetIntensity(file)) + "\t");
        }
        for (auto file : rawFiles)
        {
            str->append(GetDetectionType(file) + "\t");
        }

        delete str;
        return str->toString();
    }

    bool Peptide::Equals(std::any obj)
    {
        return (std::any_cast<Peptide*>(obj))->Sequence == this->Sequence;
    }

    int Peptide::GetHashCode()
    {
        return Sequence.GetHashCode();
    }
}
