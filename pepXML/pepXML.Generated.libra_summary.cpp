#include "pepXML.Generated.libra_summary.h"
#include "pepXML.Generated.libra_summaryFragment_masses.h"
#include "pepXML.Generated.libra_summaryContributing_channel.h"

namespace pepXML {
    namespace Generated {

        std::vector<libra_summaryFragment_masses*> libra_summary::getfragment_masses() const {
            return this->fragment_massesField;
        }

        void libra_summary::setfragment_masses(const std::vector<libra_summaryFragment_masses*> &value) {
            this->fragment_massesField = value;
        }

        std::vector<libra_summaryContributing_channel*> libra_summary::getisotopic_contributions() const {
            return this->isotopic_contributionsField;
        }

        void libra_summary::setisotopic_contributions(const std::vector<libra_summaryContributing_channel*> &value) {
            this->isotopic_contributionsField = value;
        }

        float libra_summary::getmass_tolerance() const {
            return this->mass_toleranceField;
        }

        void libra_summary::setmass_tolerance(float value) {
            this->mass_toleranceField = value;
        }

        int libra_summary::getcentroiding_preference() const {
            return this->centroiding_preferenceField;
        }

        void libra_summary::setcentroiding_preference(int value) {
            this->centroiding_preferenceField = value;
        }

        int libra_summary::getnormalization() const {
            return this->normalizationField;
        }

        void libra_summary::setnormalization(int value) {
            this->normalizationField = value;
        }

        int libra_summary::getoutput_type() const {
            return this->output_typeField;
        }

        void libra_summary::setoutput_type(int value) {
            this->output_typeField = value;
        }

        std::wstring libra_summary::getchannel_code() const {
            return this->channel_codeField;
        }

        void libra_summary::setchannel_code(const std::wstring &value) {
            this->channel_codeField = value;
        }
    }
}
