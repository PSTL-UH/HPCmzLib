#include "IO.MzML.Generated.PrecursorType.h"
#include "IO.MzML.Generated.ParamGroupType.h"
#include "IO.MzML.Generated.SelectedIonListType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            ParamGroupType *PrecursorType::getisolationWindow() const
            {
                return this->isolationWindowField;
            }

            void PrecursorType::setisolationWindow(ParamGroupType *value)
            {
                this->isolationWindowField = value;
            }

            SelectedIonListType *PrecursorType::getselectedIonList() const
            {
                return this->selectedIonListField;
            }

            void PrecursorType::setselectedIonList(SelectedIonListType *value)
            {
                this->selectedIonListField = value;
            }

            ParamGroupType *PrecursorType::getactivation() const
            {
                return this->activationField;
            }

            void PrecursorType::setactivation(ParamGroupType *value)
            {
                this->activationField = value;
            }

            std::string PrecursorType::getspectrumRef() const
            {
                return this->spectrumRefField;
            }

            void PrecursorType::setspectrumRef(const std::string &value)
            {
                this->spectrumRefField = value;
            }

            std::string PrecursorType::getsourceFileRef() const
            {
                return this->sourceFileRefField;
            }

            void PrecursorType::setsourceFileRef(const std::string &value)
            {
                this->sourceFileRefField = value;
            }

            std::string PrecursorType::getexternalSpectrumID() const
            {
                return this->externalSpectrumIDField;
            }

            void PrecursorType::setexternalSpectrumID(const std::string &value)
            {
                this->externalSpectrumIDField = value;
            }
        }
    }
}
