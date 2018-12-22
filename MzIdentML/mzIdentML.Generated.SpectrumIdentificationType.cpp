#include "mzIdentML.Generated.SpectrumIdentificationType.h"
#include "mzIdentML.Generated.InputSpectraType.h"
#include "mzIdentML.Generated.SearchDatabaseRefType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<InputSpectraType*> SpectrumIdentificationType::getInputSpectra() const {
            return this->inputSpectraField;
        }

        void SpectrumIdentificationType::setInputSpectra(const std::vector<InputSpectraType*> &value) {
            this->inputSpectraField = value;
        }

        std::vector<SearchDatabaseRefType*> SpectrumIdentificationType::getSearchDatabaseRef() const {
            return this->searchDatabaseRefField;
        }

        void SpectrumIdentificationType::setSearchDatabaseRef(const std::vector<SearchDatabaseRefType*> &value) {
            this->searchDatabaseRefField = value;
        }

        std::wstring SpectrumIdentificationType::getspectrumIdentificationProtocol_ref() const {
            return this->spectrumIdentificationProtocol_refField;
        }

        void SpectrumIdentificationType::setspectrumIdentificationProtocol_ref(const std::wstring &value) {
            this->spectrumIdentificationProtocol_refField = value;
        }

        std::wstring SpectrumIdentificationType::getspectrumIdentificationList_ref() const {
            return this->spectrumIdentificationList_refField;
        }

        void SpectrumIdentificationType::setspectrumIdentificationList_ref(const std::wstring &value) {
            this->spectrumIdentificationList_refField = value;
        }
    }
}
