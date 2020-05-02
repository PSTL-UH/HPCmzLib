#include "Peptide.h"
#include "SpectraFileInfo.h"
#include "ProteinGroup.h"

#include "stringhelper.h"

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
#ifdef ORIG
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
#endif
        std::vector<std::string> pgroupvec, genevec, orgvec;
        for ( auto p : proteinGroups ) {
            auto found = false;
            for ( auto v: pgroupvec ) {
                if ( v == p->ProteinGroupName ) {
                    found = true;
                }
            }
            if ( !found ) {
                pgroupvec.push_back (p->ProteinGroupName +"\t");
            }

            found = false;
            for ( auto v: genevec ) {
                if ( v == p->GeneName ) {
                    found = true;
                }
            }
            if ( !found ) {
                genevec.push_back (p->GeneName + "\t" );
            }

            found = false;
            for ( auto v: orgvec ) {
                if ( v == p->Organism ) {
                    found = true;
                }
            }
            if ( !found ) {
                orgvec.push_back (p->Organism +"\t");
            }
        }
        str->append(StringHelper::join (pgroupvec, ';' ) );
        str->append(StringHelper::join (genevec, ';' ) );
        str->append(StringHelper::join (orgvec, ';' ) );
        
        for (auto file : rawFiles)
        {
            str->append(std::to_string(GetIntensity(file)) + "\t");
        }
        for (auto file : rawFiles)
        {
            auto t = GetDetectionType(file);
            std::string tmpstring;
            if (t == DetectionType::MSMS ) {
                tmpstring = "MSMS";
            }
            else if (t == DetectionType::MBR) {
                tmpstring = "MBR";
            }
            else if (t == DetectionType::NotDetected) {
                tmpstring = "NotDetected";
            }
            else if (t == DetectionType::MSMSAmbiguousPeakfinding) {
                tmpstring = "MSMSAmbiguousPeakfinding";
            }
            else if (t == DetectionType::MSMSIdentifiedButNotQuantified) {
                tmpstring = "MSMSIdentifiedButNotQuantified";
            }
            else if (t == DetectionType::Imputed ) {
                tmpstring = "Imputed";
            }
                   
            str->append(tmpstring + "\t");
        }

        std::string s = str->toString();
        delete str;
        return s;
    }

    bool Peptide::Equals(std::any obj)
    {
        return (std::any_cast<Peptide*>(obj))->Sequence == this->Sequence;
    }

    int Peptide::GetHashCode()
    {
        return StringHelper::GetHashCode(Sequence);
    }
}
