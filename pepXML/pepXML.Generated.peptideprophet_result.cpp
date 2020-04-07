#include "pepXML.Generated.peptideprophet_result.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<nameValueType*> peptideprophet_result::getsearch_score_summary() const
        {
            return this->search_score_summaryField;
        }

        void peptideprophet_result::setsearch_score_summary(const std::vector<nameValueType*> &value)
        {
            this->search_score_summaryField = value;
        }

        float peptideprophet_result::getprobability() const
        {
            return this->probabilityField;
        }

        void peptideprophet_result::setprobability(float value)
        {
            this->probabilityField = value;
        }

        std::string peptideprophet_result::getall_ntt_prob() const
        {
            return this->all_ntt_probField;
        }

        void peptideprophet_result::setall_ntt_prob(const std::string &value)
        {
            this->all_ntt_probField = value;
        }

        std::string peptideprophet_result::getanalysis() const
        {
            return this->analysisField;
        }

        void peptideprophet_result::setanalysis(const std::string &value)
        {
            this->analysisField = value;
        }
    }
}
