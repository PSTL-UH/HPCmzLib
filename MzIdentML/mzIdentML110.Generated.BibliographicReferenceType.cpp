#include "mzIdentML110.Generated.BibliographicReferenceType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::wstring BibliographicReferenceType::getauthors() const {
            return this->authorsField;
        }

        void BibliographicReferenceType::setauthors(const std::wstring &value) {
            this->authorsField = value;
        }

        std::wstring BibliographicReferenceType::getpublication() const {
            return this->publicationField;
        }

        void BibliographicReferenceType::setpublication(const std::wstring &value) {
            this->publicationField = value;
        }

        std::wstring BibliographicReferenceType::getpublisher() const {
            return this->publisherField;
        }

        void BibliographicReferenceType::setpublisher(const std::wstring &value) {
            this->publisherField = value;
        }

        std::wstring BibliographicReferenceType::geteditor() const {
            return this->editorField;
        }

        void BibliographicReferenceType::seteditor(const std::wstring &value) {
            this->editorField = value;
        }

        int BibliographicReferenceType::getyear() const {
            return this->yearField;
        }

        void BibliographicReferenceType::setyear(int value) {
            this->yearField = value;
        }

        bool BibliographicReferenceType::getyearSpecified() const {
            return this->yearFieldSpecified;
        }

        void BibliographicReferenceType::setyearSpecified(bool value) {
            this->yearFieldSpecified = value;
        }

        std::wstring BibliographicReferenceType::getvolume() const {
            return this->volumeField;
        }

        void BibliographicReferenceType::setvolume(const std::wstring &value) {
            this->volumeField = value;
        }

        std::wstring BibliographicReferenceType::getissue() const {
            return this->issueField;
        }

        void BibliographicReferenceType::setissue(const std::wstring &value) {
            this->issueField = value;
        }

        std::wstring BibliographicReferenceType::getpages() const {
            return this->pagesField;
        }

        void BibliographicReferenceType::setpages(const std::wstring &value) {
            this->pagesField = value;
        }

        std::wstring BibliographicReferenceType::gettitle() const {
            return this->titleField;
        }

        void BibliographicReferenceType::settitle(const std::wstring &value) {
            this->titleField = value;
        }

        std::wstring BibliographicReferenceType::getdoi() const {
            return this->doiField;
        }

        void BibliographicReferenceType::setdoi(const std::wstring &value) {
            this->doiField = value;
        }
    }
}
