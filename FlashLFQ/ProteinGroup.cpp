#include "ProteinGroup.h"
#include "SpectraFileInfo.h"
#include "stringhelper.h"


namespace FlashLFQ
{

    ProteinGroup::ProteinGroup(const std::string &proteinGroupName, const std::string &geneName, const std::string &organism) : ProteinGroupName(proteinGroupName), GeneName(geneName), Organism(organism)
    {
        intensities = std::unordered_map<SpectraFileInfo*, double>();
    }

    double ProteinGroup::GetIntensity(SpectraFileInfo *fileInfo)
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

    void ProteinGroup::SetIntensity(SpectraFileInfo *fileInfo, double intensity)
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

    std::string ProteinGroup::TabSeparatedHeader(std::vector<SpectraFileInfo*> &rawFiles)
    {
        auto sb = new StringBuilder();
        sb->append(std::string("Protein Groups") + "\t");
        sb->append(std::string("Gene Name") + "\t");
        sb->append(std::string("Organism") + "\t");

        for (auto rawfile : rawFiles)
        {
            sb->append("Intensity_" + rawfile->FilenameWithoutExtension + "\t");
        }

        delete sb;
        return sb->toString();
    }

    std::string ProteinGroup::ToString(std::vector<SpectraFileInfo*> &rawFiles)
    {
        StringBuilder *str = new StringBuilder();
        str->append(ProteinGroupName + "\t");
        str->append(GeneName + "\t");
        str->append(Organism + "\t");

        for (auto file : rawFiles)
        {
            double intensity;
            std::unordered_map<SpectraFileInfo*, double>::const_iterator intensities_iterator = intensities.find(file);
            if (intensities_iterator != intensities.end())
            {
                intensity = intensities_iterator->second;
                str->append(std::to_string(intensity) + "\t");
            }
            else
            {
                intensity = intensities_iterator->second;
                str->append(std::to_string(0) + "\t");
            }
        }

        delete str;
        return str->toString();
    }

    bool ProteinGroup::Equals(std::any obj)
    {
        return (std::any_cast<ProteinGroup*>(obj))->ProteinGroupName == this->ProteinGroupName;
    }

    int ProteinGroup::GetHashCode()
    {
        return StringHelper::GetHashCode(ProteinGroupName);
    }
}
