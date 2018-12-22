#include "IO.MzML.Generated.SpectrumType.h"
#include "IO.MzML.Generated.ScanListType.h"
#include "IO.MzML.Generated.PrecursorListType.h"
#include "IO.MzML.Generated.ProductListType.h"
#include "IO.MzML.Generated.BinaryDataArrayListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            ScanListType *SpectrumType::getscanList() const {
                return this->scanListField;
            }

            void SpectrumType::setscanList(ScanListType *value) {
                this->scanListField = value;
            }

            PrecursorListType *SpectrumType::getprecursorList() const {
                return this->precursorListField;
            }

            void SpectrumType::setprecursorList(PrecursorListType *value) {
                this->precursorListField = value;
            }

            ProductListType *SpectrumType::getproductList() const {
                return this->productListField;
            }

            void SpectrumType::setproductList(ProductListType *value) {
                this->productListField = value;
            }

            BinaryDataArrayListType *SpectrumType::getbinaryDataArrayList() const {
                return this->binaryDataArrayListField;
            }

            void SpectrumType::setbinaryDataArrayList(BinaryDataArrayListType *value) {
                this->binaryDataArrayListField = value;
            }

            std::wstring SpectrumType::getid() const {
                return this->idField;
            }

            void SpectrumType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring SpectrumType::getspotID() const {
                return this->spotIDField;
            }

            void SpectrumType::setspotID(const std::wstring &value) {
                this->spotIDField = value;
            }

            std::wstring SpectrumType::getindex() const {
                return this->indexField;
            }

            void SpectrumType::setindex(const std::wstring &value) {
                this->indexField = value;
            }

            int SpectrumType::getdefaultArrayLength() const {
                return this->defaultArrayLengthField;
            }

            void SpectrumType::setdefaultArrayLength(int value) {
                this->defaultArrayLengthField = value;
            }

            std::wstring SpectrumType::getdataProcessingRef() const {
                return this->dataProcessingRefField;
            }

            void SpectrumType::setdataProcessingRef(const std::wstring &value) {
                this->dataProcessingRefField = value;
            }

            std::wstring SpectrumType::getsourceFileRef() const {
                return this->sourceFileRefField;
            }

            void SpectrumType::setsourceFileRef(const std::wstring &value) {
                this->sourceFileRefField = value;
            }
        }
    }
}
