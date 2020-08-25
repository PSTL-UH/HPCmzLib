#include "DigestionParams.h"
#include "Protease.h"
#include "ProteaseDictionary.h"

//using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        DigestionParams::DigestionParams() : DigestionParams("trypsin")
        {
        }

        DigestionParams::DigestionParams(const std::string &protease, int maxMissedCleavages, int minPeptideLength, int maxPeptideLength, int maxModificationIsoforms, Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior initiatorMethionineBehavior, int maxModsForPeptides, CleavageSpecificity searchModeType, FragmentationTerminus fragmentationTerminus)
        {
            setProtease(ProteaseDictionary::getDictionary()[protease]);
            setMaxMissedCleavages(maxMissedCleavages);
            setMinPeptideLength(minPeptideLength);
            setMaxPeptideLength(maxPeptideLength);
            setMaxModificationIsoforms(maxModificationIsoforms);
            setInitiatorMethionineBehavior(initiatorMethionineBehavior);
            setMaxModsForPeptide(maxModsForPeptides);
            setSearchModeType(searchModeType);
            setFragmentationTerminus(fragmentationTerminus);
            RecordSpecificProtease();
        }

        int DigestionParams::getMaxMissedCleavages() const
        {
            return privateMaxMissedCleavages;
        }

        void DigestionParams::setMaxMissedCleavages(int value)
        {
            privateMaxMissedCleavages = value;
        }

        Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior DigestionParams::getInitiatorMethionineBehavior() const
        {
            return privateInitiatorMethionineBehavior;
        }

        void DigestionParams::setInitiatorMethionineBehavior(Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior value)
        {
            privateInitiatorMethionineBehavior = value;
        }

        int DigestionParams::getMinPeptideLength() const
        {
            return privateMinPeptideLength;
        }

        void DigestionParams::setMinPeptideLength(int value)
        {
            privateMinPeptideLength = value;
        }

        int DigestionParams::getMaxPeptideLength() const
        {
            return privateMaxPeptideLength;
        }

        void DigestionParams::setMaxPeptideLength(int value)
        {
            privateMaxPeptideLength = value;
        }

        int DigestionParams::getMaxModificationIsoforms() const
        {
            return privateMaxModificationIsoforms;
        }

        void DigestionParams::setMaxModificationIsoforms(int value)
        {
            privateMaxModificationIsoforms = value;
        }

        int DigestionParams::getMaxModsForPeptide() const
        {
            return privateMaxModsForPeptide;
        }

        void DigestionParams::setMaxModsForPeptide(int value)
        {
            privateMaxModsForPeptide = value;
        }

        Proteomics::ProteolyticDigestion::Protease *DigestionParams::getProtease() const
        {
            return privateProtease;
        }

        void DigestionParams::setProtease(Proteomics::ProteolyticDigestion::Protease *value)
        {
            privateProtease = value;
        }

        CleavageSpecificity DigestionParams::getSearchModeType() const
        {
            return privateSearchModeType;
        }

        void DigestionParams::setSearchModeType(CleavageSpecificity value)
        {
            privateSearchModeType = value;
        }

        FragmentationTerminus DigestionParams::getFragmentationTerminus() const
        {
            return privateFragmentationTerminus;
        }

        void DigestionParams::setFragmentationTerminus(FragmentationTerminus value)
        {
            privateFragmentationTerminus = value;
        }

        Proteomics::ProteolyticDigestion::Protease *DigestionParams::getSpecificProtease() const
        {
            return privateSpecificProtease;
        }

        void DigestionParams::setSpecificProtease(Proteomics::ProteolyticDigestion::Protease *value)
        {
            privateSpecificProtease = value;
        }

        bool DigestionParams::Equals(DigestionParams *a)
        {

            return a != nullptr &&
                getMaxMissedCleavages() == a->getMaxMissedCleavages()      &&
                getMinPeptideLength()   == a->getMinPeptideLength()        &&
                getMaxPeptideLength()   == a->getMaxPeptideLength()        &&
                getInitiatorMethionineBehavior()== a->getInitiatorMethionineBehavior() &&
                getMaxModificationIsoforms() == a->getMaxModificationIsoforms()              &&
                getMaxModsForPeptide()  == a->getMaxModsForPeptide()       &&
                getProtease()->Equals(a->getProtease())                    &&
                getSearchModeType()    == a->getSearchModeType()           &&
                getFragmentationTerminus() == a->getFragmentationTerminus();
        }

        int DigestionParams::GetHashCode()
        {
            return StringHelper::GetHashCode(std::to_string(getMaxMissedCleavages()))                         ^
                StringHelper::GetHashCode(std::to_string(static_cast<int>(getInitiatorMethionineBehavior()))) ^
                StringHelper::GetHashCode(std::to_string(getMaxModificationIsoforms()))                       ^
                StringHelper::GetHashCode(std::to_string(getMaxModsForPeptide()));
        }

        std::string DigestionParams::ToString()
        {
            return std::to_string(getMaxMissedCleavages()) + "," +
                std::to_string(static_cast<int>(getInitiatorMethionineBehavior())) + "," +
                std::to_string(getMinPeptideLength()) + "," +
                std::to_string(getMaxPeptideLength()) + "," +
                std::to_string(getMaxModificationIsoforms()) + "," +
                std::to_string(getMaxModsForPeptide()) + "," +
                getProtease()->getName() + "," +
                CleavageSpecificityExtension::GetCleavageSpecificityAsString(getSearchModeType()) + "," +
                FragmentationTerminusToString(getFragmentationTerminus() );
        }

        DigestionParams *DigestionParams::FromString(const std::string &str)
        {
            std::vector<std::string> split = StringHelper::split(str, ',');
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
#ifdef ORIG
            return new DigestionParams(split[6], std::stoi(split[0]), std::stoi(split[2]), std::stoi(split[3]),
                     std::stoi(split[4]),
                     std::any_cast<Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior>(Enum::Parse(typeof(InitiatorMethionineBehavior),split[1])),
                     std::stoi(split[5]),
                     std::any_cast<CleavageSpecificity>(Enum::Parse(typeof(CleavageSpecificity), split[7])),
                     std::any_cast<FragmentationTerminus>(Enum::Parse(typeof(FragmentationTerminus), split[8])));
#endif
            return new DigestionParams(split[6], std::stoi(split[0]), std::stoi(split[2]), std::stoi(split[3]),
                                       std::stoi(split[4]),
                                       static_cast<Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior>(std::stoi(split[1])),
                                       std::stoi(split[5]),
                                       CleavageSpecificityExtension::ParseString(split[7]),
                                       FragmentationTerminusFromString(split[8]) );
        }

        void DigestionParams::RecordSpecificProtease()
        {
            setSpecificProtease(getProtease());
            
            if (getSearchModeType() == CleavageSpecificity::None)
            {
                //nonspecific searches, which might have a specific protease
                setProtease( getFragmentationTerminus() == FragmentationTerminus::N ?
                            ProteaseDictionary::getDictionary()["singleN"] :
                            ProteaseDictionary::getDictionary()["singleC"]);
            }
        }
    }
}
