#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::vector<nameValueType*> peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::getparameter() const {
            return this->parameterField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::setparameter(const std::vector<nameValueType*> &value) {
            this->parameterField = value;
        }

        model_dis_type peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::gettype() const {
            return this->typeField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::settype(model_dis_type value) {
            this->typeField = value;
        }

        bool peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::gettypeSpecified() const {
            return this->typeFieldSpecified;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution::settypeSpecified(bool value) {
            this->typeFieldSpecified = value;
        }
    }
}
