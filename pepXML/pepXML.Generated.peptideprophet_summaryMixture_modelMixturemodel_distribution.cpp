#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodel_distribution.h"
#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodel_distributionPosmodel_distribution.h"
#include "pepXML.Generated.peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution.h"

namespace pepXML {
    namespace Generated {

        peptideprophet_summaryMixture_modelMixturemodel_distributionPosmodel_distribution *peptideprophet_summaryMixture_modelMixturemodel_distribution::getposmodel_distribution() const {
            return this->posmodel_distributionField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distribution::setposmodel_distribution(peptideprophet_summaryMixture_modelMixturemodel_distributionPosmodel_distribution *value) {
            this->posmodel_distributionField = value;
        }

        peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution *peptideprophet_summaryMixture_modelMixturemodel_distribution::getnegmodel_distribution() const {
            return this->negmodel_distributionField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distribution::setnegmodel_distribution(peptideprophet_summaryMixture_modelMixturemodel_distributionNegmodel_distribution *value) {
            this->negmodel_distributionField = value;
        }

        std::wstring peptideprophet_summaryMixture_modelMixturemodel_distribution::getname() const {
            return this->nameField;
        }

        void peptideprophet_summaryMixture_modelMixturemodel_distribution::setname(const std::wstring &value) {
            this->nameField = value;
        }
    }
}
