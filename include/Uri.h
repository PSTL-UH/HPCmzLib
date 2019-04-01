#pragma once

// This code is loosely based  on the stackoverlow post
// https://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform

// Note: the Uri class is used sparingly, only in MassSpectrometry/ and MzML/
// but since it is unclear what its purpose really is (they don't seem to
// actually use it for anything) I will just provide a minimalistic implementation
// and fix it later in case it is required for something that I am overlooking
// right now.

#include <string>
#include <algorithm>    

class Uri {
public:
    std::string QueryString, Path, Protocol, Host, Port;
    
    Uri (std::string path) {
        Path = path;
    }
    Uri ( Uri* uri ) {
        Path = uri->Path;
    }
    
    std::string getFileName() {
        return Path;
    }
};

