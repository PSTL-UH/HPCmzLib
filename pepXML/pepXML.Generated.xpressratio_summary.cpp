#include "pepXML.Generated.xpressratio_summary.h"

namespace pepXML {
    namespace Generated {

        std::wstring xpressratio_summary::getversion() const {
            return this->versionField;
        }

        void xpressratio_summary::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        std::wstring xpressratio_summary::getauthor() const {
            return this->authorField;
        }

        void xpressratio_summary::setauthor(const std::wstring &value) {
            this->authorField = value;
        }

        std::wstring xpressratio_summary::getsame_scan_range() const {
            return this->same_scan_rangeField;
        }

        void xpressratio_summary::setsame_scan_range(const std::wstring &value) {
            this->same_scan_rangeField = value;
        }

        std::wstring xpressratio_summary::getlabeled_residues() const {
            return this->labeled_residuesField;
        }

        void xpressratio_summary::setlabeled_residues(const std::wstring &value) {
            this->labeled_residuesField = value;
        }

        unsigned int xpressratio_summary::getxpress_light() const {
            return this->xpress_lightField;
        }

        void xpressratio_summary::setxpress_light(unsigned int value) {
            this->xpress_lightField = value;
        }

        std::wstring xpressratio_summary::getmassdiff() const {
            return this->massdiffField;
        }

        void xpressratio_summary::setmassdiff(const std::wstring &value) {
            this->massdiffField = value;
        }

        float xpressratio_summary::getmasstol() const {
            return this->masstolField;
        }

        void xpressratio_summary::setmasstol(float value) {
            this->masstolField = value;
        }

        std::wstring xpressratio_summary::getppmtol() const {
            return this->ppmtolField;
        }

        void xpressratio_summary::setppmtol(const std::wstring &value) {
            this->ppmtolField = value;
        }

        std::wstring xpressratio_summary::getmin_num_chromatogram_points() const {
            return this->min_num_chromatogram_pointsField;
        }

        void xpressratio_summary::setmin_num_chromatogram_points(const std::wstring &value) {
            this->min_num_chromatogram_pointsField = value;
        }

        std::wstring xpressratio_summary::getmin_num_isotope_peaks() const {
            return this->min_num_isotope_peaksField;
        }

        void xpressratio_summary::setmin_num_isotope_peaks(const std::wstring &value) {
            this->min_num_isotope_peaksField = value;
        }
    }
}
