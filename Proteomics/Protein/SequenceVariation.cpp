#include "SequenceVariation.h"
#include "stringhelper.h"
#include "Assert.h"

namespace Proteomics {

    SequenceVariation::SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications)
    {
        privateOneBasedBeginPosition = OneBasedBeginPosition;
        privateOneBasedEndPosition = OneBasedEndPosition;
        privateOriginalSequence = OriginalSequence;
        privateVariantSequence =VariantSequence;
        privateDescription = new SequenceVariantDescription(Description);
        privateOneBasedModifications = oneBasedModifications;
    }

    SequenceVariation::SequenceVariation(int OneBasedPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications) : SequenceVariation(OneBasedPosition, OneBasedPosition, OriginalSequence, VariantSequence, Description, oneBasedModifications) {
    }

    int SequenceVariation::getOneBasedBeginPosition() const {
        return privateOneBasedBeginPosition;
    }

    int SequenceVariation::getOneBasedEndPosition() const {
        return privateOneBasedEndPosition;
    }

    std::string SequenceVariation::getOriginalSequence() const {
        return privateOriginalSequence;
    }

    std::string SequenceVariation::getVariantSequence() const {
        return privateVariantSequence;
    }

     SequenceVariantDescription* SequenceVariation::getDescription() const {
        return privateDescription;
    }

    std::unordered_map<int, std::vector<Modification*>> SequenceVariation::getOneBasedModifications() const
    {
        return privateOneBasedModifications;
    }


    bool SequenceVariation::Equals(SequenceVariation *s ) {
//        SequenceVariation *s = dynamic_cast<SequenceVariation*>(obj);
#ifdef ORIG
        return s != nullptr &&
            getOneBasedBeginPosition() == s->getOneBasedBeginPosition()    &&
            getOneBasedEndPosition() == s->getOneBasedEndPosition()        &&
            (s->getOriginalSequence() == "" && getOriginalSequence() == "" ||
             getOriginalSequence() == s->getOriginalSequence())            &&
            (s->getVariantSequence() == "" && getVariantSequence() == ""   ||
             getVariantSequence() == s->getVariantSequence())              &&
            (s->getDescription() == nullptr && getDescription() == nullptr ||
             getDescription()->Equals(s->getDescription()))                &&
            (s->getOneBasedModifications().empty() &&
             getOneBasedModifications().empty() || s->getOneBasedModifications().Keys->ToList()->SequenceEqual(getOneBasedModifications().Keys->ToList()) &&
             s->getOneBasedModifications().Values->SelectMany([&] (std::any m)
        {
            return m;
        }).ToList()->SequenceEqual(getOneBasedModifications().Values->SelectMany([&] (std::any m)
        {
            return m;
        }).ToList()));
#endif
        
        std::unordered_map<int, std::vector<Modification*>> a1 = getOneBasedModifications();
        std::unordered_map<int, std::vector<Modification*>> a2 = s->getOneBasedModifications();
        std::vector<int> arr1, arr2;
        std::vector<Modification*> arr3, arr4;
        for ( auto a =a1.begin(); a != a1.end(); a++ ) {
            arr1.push_back(a->first);
            for ( auto aa: a->second ) {
                arr3.push_back(aa);
            }
        }
        for ( auto a =a2.begin(); a != a2.end(); a++ ) {
            arr2.push_back(a->first);
            for ( auto aa: a->second ) {
                arr4.push_back(aa);
            }
        }
            
        bool sequenceequal = Assert::SequenceEqual(arr1, arr2) && Assert::SequenceEqual(arr3, arr4);
      
        return s != nullptr                                                   &&
            getOneBasedBeginPosition() == s->getOneBasedBeginPosition()       &&
            getOneBasedEndPosition() == s->getOneBasedEndPosition()           &&
            ( (s->getOriginalSequence() == "" && getOriginalSequence() == "") ||
              getOriginalSequence() == s->getOriginalSequence() )             &&
            ((s->getVariantSequence() == "" && getVariantSequence() == "")    ||
             getVariantSequence() == s->getVariantSequence())                 &&
            ((s->getDescription() == nullptr && getDescription() == nullptr)  ||
             getDescription()->Equals(s->getDescription()))                &&
            ( (s->getOneBasedModifications().empty() && getOneBasedModifications().empty()) ||
              sequenceequal );
    }

    int SequenceVariation::GetHashCode() {
        return StringHelper::GetHashCode(std::to_string(getOneBasedBeginPosition())) ^
            StringHelper::GetHashCode(std::to_string(getOneBasedEndPosition())) ^
            StringHelper::GetHashCode(getOriginalSequence()) ^
            StringHelper::GetHashCode(getVariantSequence()) ^
            getDescription()->GetHashCode();
    }

    std::string SequenceVariation::SimpleString()
    {
        return getOriginalSequence() + std::to_string(getOneBasedBeginPosition()) + getVariantSequence();
    }
    
    bool SequenceVariation::Intersects(SequenceVariation *segment)
    {
        return segment->getOneBasedEndPosition() >= getOneBasedBeginPosition() &&
            segment->getOneBasedBeginPosition() <= getOneBasedEndPosition();
    }

    bool SequenceVariation::Intersects(ProteolysisProduct *segment)
    {
        //C# TO C++ CONVERTER TODO TASK: Comparisons involving nullable type instances will need to be
        // rewritten since comparison rules are different between C++ optional and System.Nullable:
        return segment->getOneBasedEndPosition().value() >= getOneBasedBeginPosition() &&
            segment->getOneBasedBeginPosition().value() <= getOneBasedEndPosition();
    }

    bool SequenceVariation::Intersects(int pos)
    {
        return getOneBasedBeginPosition() <= pos && pos <= getOneBasedEndPosition();
    }

    bool SequenceVariation::Includes(SequenceVariation *segment)
    {
        return getOneBasedBeginPosition() <= segment->getOneBasedBeginPosition() &&
            getOneBasedEndPosition() >= segment->getOneBasedEndPosition();
    }

    bool SequenceVariation::Includes(ProteolysisProduct *segment)
    {
        //C# TO C++ CONVERTER TODO TASK: Comparisons involving nullable type instances will need to be
        // rewritten since comparison rules are different between C++ optional and System.Nullable:
        return getOneBasedBeginPosition() <= segment->getOneBasedBeginPosition().value() &&
            getOneBasedEndPosition() >= segment->getOneBasedEndPosition().value();
    }

bool SequenceVariation::Includes(int pos)
    {
        return getOneBasedBeginPosition() <= pos && pos <= getOneBasedEndPosition();
    }
}
