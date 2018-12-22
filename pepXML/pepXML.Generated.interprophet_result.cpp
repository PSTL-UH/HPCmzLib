#include "pepXML.Generated.interprophet_result.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::vector<nameValueType*> interprophet_result::getsearch_score_summary() const {
            return this->search_score_summaryField;
        }

        void interprophet_result::setsearch_score_summary(const std::vector<nameValueType*> &value) {
            this->search_score_summaryField = value;
        }

        float interprophet_result::getprobability() const {
            return this->probabilityField;
        }

        void interprophet_result::setprobability(float value) {
            this->probabilityField = value;
        }

        std::wstring interprophet_result::getall_ntt_prob() const {
            return this->all_ntt_probField;
        }

        void interprophet_result::setall_ntt_prob(const std::wstring &value) {
            this->all_ntt_probField = value;
        }
    }
}
