#include "UsefulProteomicsDatabases.Generated.unimod_t.h"
#include "UsefulProteomicsDatabases.Generated.elem_t.h"
#include "UsefulProteomicsDatabases.Generated.mod_t.h"
#include "UsefulProteomicsDatabases.Generated.aa_t.h"
#include "UsefulProteomicsDatabases.Generated.brick_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        unimod_t::unimod_t() {
            this->majorVersionField = (static_cast<unsigned short>(2));
        }

        std::vector<elem_t*> unimod_t::getelements() const {
            return this->elementsField;
        }

        void unimod_t::setelements(const std::vector<elem_t*> &value) {
            this->elementsField = value;
        }

        std::vector<mod_t*> unimod_t::getmodifications() const {
            return this->modificationsField;
        }

        void unimod_t::setmodifications(const std::vector<mod_t*> &value) {
            this->modificationsField = value;
        }

        std::vector<aa_t*> unimod_t::getamino_acids() const {
            return this->amino_acidsField;
        }

        void unimod_t::setamino_acids(const std::vector<aa_t*> &value) {
            this->amino_acidsField = value;
        }

        std::vector<brick_t*> unimod_t::getmod_bricks() const {
            return this->mod_bricksField;
        }

        void unimod_t::setmod_bricks(const std::vector<brick_t*> &value) {
            this->mod_bricksField = value;
        }

        unsigned short unimod_t::getmajorVersion() const {
            return this->majorVersionField;
        }

        void unimod_t::setmajorVersion(unsigned short value) {
            this->majorVersionField = value;
        }

        unsigned short unimod_t::getminorVersion() const {
            return this->minorVersionField;
        }

        void unimod_t::setminorVersion(unsigned short value) {
            this->minorVersionField = value;
        }
    }
}
