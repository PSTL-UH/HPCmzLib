#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodel.h"
#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodelPoint.h"

namespace pepXML {
    namespace Generated {

        std::vector<peptideprophet_summaryMixture_modelMixturemodelPoint*> peptideprophet_summaryMixture_modelMixturemodel::getpoint() const {
            return this->pointField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel::setpoint(const std::vector<peptideprophet_summaryMixture_modelMixturemodelPoint*> &value) {
            this->pointField = value;
        }

        std::wstring peptideprophet_summaryMixture_modelMixturemodel::getname() const {
            return this->nameField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel::setname(const std::wstring &value) {
            this->nameField = value;
        }

        float peptideprophet_summaryMixture_modelMixturemodel::getpos_bandwidth() const {
            return this->pos_bandwidthField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel::setpos_bandwidth(float value) {
            this->pos_bandwidthField = value;
        }

        float peptideprophet_summaryMixture_modelMixturemodel::getneg_bandwidth() const {
            return this->neg_bandwidthField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel::setneg_bandwidth(float value) {
            this->neg_bandwidthField = value;
        }
    }
}
