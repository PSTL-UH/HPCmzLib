#include "ModificationMotif.h"
#include "stringhelper.h"
#include <regex>
#include <locale>

namespace Proteomics {

//Regex *const ModificationMotif::ModificationMotifRegex = new Regex(LR"(^[A-Za-z]+$)", RegexOptions::Compiled);

    ModificationMotif::ModificationMotif(const std::string &motif) : motifString(motif) {
    }

    bool ModificationMotif::TryGetMotif(const std::string &motifString, ModificationMotif **motif) {
        std::regex ModificationMotifRegex(R"(^[A-Za-z]+$)");
        std::locale loc;
        *motif = nullptr;
#ifdef ORIG
        if (ModificationMotifRegex->IsMatch(motifString) && motifString.Count([&] (std::any b) {
            std::isupper(b);
                }) == 1) {
            motif = new ModificationMotif(motifString);
            return true;
        }
#endif
        if ( std::regex_match(motifString, ModificationMotifRegex) ) {
            int count=0;
            for ( long unsigned int i=0; i < motifString.length(); i++ ) {
                char c = motifString[i];
                if ( std::isupper(c, loc) ){
                    count++;
                }
            }
            if ( count == 1 ) {
                ModificationMotif *m = new ModificationMotif(motifString);
                *motif = m;
                return true;
            }                  
        }

        return false;
    }

    bool ModificationMotif::Equals(ModificationMotif *&m) {
//        ModificationMotif *m = dynamic_cast<ModificationMotif*>(o);
        return m != nullptr && m->motifString == motifString;
    }

    int ModificationMotif::GetHashCode() {
        int c= StringHelper::GetHashCode(motifString);
        return c;
    }

    std::string ModificationMotif::ToString() {
        return motifString;
    }
}
