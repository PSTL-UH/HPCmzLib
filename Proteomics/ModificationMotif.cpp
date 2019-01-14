#include "ModificationMotif.h"
#include "stringhelper.h"
#include <regex>

namespace Proteomics {

//Regex *const ModificationMotif::ModificationMotifRegex = new Regex(LR"(^[A-Za-z]+$)", RegexOptions::Compiled);

    ModificationMotif::ModificationMotif(const std::string &motif) : motifString(motif) {
    }

    bool ModificationMotif::TryGetMotif(const std::string &motifString, ModificationMotif *&motif) {
        std::regex ModificationMotifRegex("(^[A-Za-z]+$)");
        
        motif = nullptr;
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
            for ( int i; i< motifString.length(); i++ ) {
                if ( isupper(motifString[i] ) ){
                        count++;
                    }
            }
            if ( count == 1 ) {
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
        return StringHelper::GetHashCode(motifString);
    }

    std::string ModificationMotif::ToString() {
        return motifString;
    }
}
