#include "UsefulProteomicsDatabases.Generated.mod_t.h"
#include "UsefulProteomicsDatabases.Generated.specificity_t.h"
#include "UsefulProteomicsDatabases.Generated.composition_t.h"
#include "UsefulProteomicsDatabases.Generated.xref_t.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::vector<specificity_t*> mod_t::getspecificity() const
        {
            return this->specificityField;
        }

        void mod_t::setspecificity(const std::vector<specificity_t*> &value)
        {
            this->specificityField = value;
        }

        composition_t *mod_t::getdelta() const
        {
            return this->deltaField;
        }

        void mod_t::setdelta(composition_t *value)
        {
            this->deltaField = value;
        }

        std::vector<composition_t*> mod_t::getIgnore() const
        {
            return this->ignoreField;
        }

        void mod_t::setIgnore(const std::vector<composition_t*> &value)
        {
            this->ignoreField = value;
        }

        std::vector<std::string> mod_t::getalt_name() const
        {
            return this->alt_nameField;
        }

        void mod_t::setalt_name(const std::vector<std::string> &value)
        {
            this->alt_nameField = value;
        }

        std::vector<xref_t*> mod_t::getxref() const
        {
            return this->xrefField;
        }

        void mod_t::setxref(const std::vector<xref_t*> &value)
        {
            this->xrefField = value;
        }

        std::string mod_t::getmisc_notes() const
        {
            return this->misc_notesField;
        }

        void mod_t::setmisc_notes(const std::string &value)
        {
            this->misc_notesField = value;
        }

        std::string mod_t::gettitle() const
        {
            return this->titleField;
        }

        void mod_t::settitle(const std::string &value)
        {
            this->titleField = value;
        }

        std::string mod_t::getfull_name() const
        {
            return this->full_nameField;
        }

        void mod_t::setfull_name(const std::string &value)
        {
            this->full_nameField = value;
        }

        std::string mod_t::getusername_of_poster() const
        {
            return this->username_of_posterField;
        }

        void mod_t::setusername_of_poster(const std::string &value)
        {
            this->username_of_posterField = value;
        }

        std::string mod_t::getgroup_of_poster() const
        {
            return this->group_of_posterField;
        }

        void mod_t::setgroup_of_poster(const std::string &value)
        {
            this->group_of_posterField = value;
        }

        std::string mod_t::getdate_time_posted() const
        {
            return this->date_time_postedField;
        }

        void mod_t::setdate_time_posted(const std::string &value)
        {
            this->date_time_postedField = value;
        }

        std::string mod_t::getdate_time_modified() const
        {
            return this->date_time_modifiedField;
        }

        void mod_t::setdate_time_modified(const std::string &value)
        {
            this->date_time_modifiedField = value;
        }

        bool mod_t::getapproved() const
        {
            return this->approvedField;
        }

        void mod_t::setapproved(bool value)
        {
            this->approvedField = value;
        }

        bool mod_t::getapprovedSpecified() const
        {
            return this->approvedFieldSpecified;
        }

        void mod_t::setapprovedSpecified(bool value)
        {
            this->approvedFieldSpecified = value;
        }

        std::string mod_t::getex_code_name() const
        {
            return this->ex_code_nameField;
        }

        void mod_t::setex_code_name(const std::string &value)
        {
            this->ex_code_nameField = value;
        }

        long long mod_t::getrecord_id() const
        {
            return this->record_idField;
        }

        void mod_t::setrecord_id(long long value)
        {
            this->record_idField = value;
        }

        bool mod_t::getrecord_idSpecified() const
        {
            return this->record_idFieldSpecified;
        }

        void mod_t::setrecord_idSpecified(bool value)
        {
            this->record_idFieldSpecified = value;
        }
    }
}
