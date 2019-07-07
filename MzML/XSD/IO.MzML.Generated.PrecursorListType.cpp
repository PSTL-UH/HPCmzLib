#include "IO.MzML.Generated.PrecursorListType.h"
#include "IO.MzML.Generated.PrecursorType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<PrecursorType*> PrecursorListType::getprecursor() const
            {
                return this->precursorField;
            }

            void PrecursorListType::setprecursor(const std::vector<PrecursorType*> &value)
            {
                this->precursorField = value;
            }

            std::string PrecursorListType::getcount() const
            {
                return this->countField;
            }

            void PrecursorListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
