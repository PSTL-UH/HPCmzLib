#pragma once
#include "toml.h"
#include <iostream>

class Toml {

public:
    toml::Value tomlReadFile(std::string FilePath) {
        std::ifstream ifs(FilePath);
	toml::ParseResult parsed_toml = toml::parse(ifs);
        
	// check if parsed toml is valid
	if (!parsed_toml.valid()) {
            std::cout << parsed_toml.errorReason << std::endl;
	}
        
	// parsed_toml.value is the parsed value.  We will use the parsed value to look up
	// table names and/or value keys
	toml::Value& toml_value = parsed_toml.value;
        
	return toml_value;
    }

    toml::Value* getValue(toml::Value& toml_value, std::string ValueName) {
	toml::Value* found_toml_value = toml_value.find(ValueName);
        return found_toml_value;
    }

    toml::Value tomlSetValue(std::string FilePath, std::string key, toml::Value val, toml::Value new_val) {
	std::ofstream ofs(FilePath);

	//updating value.  call toml value.set(string key, value) and then write value to file
	val.set(key, new_val);

	ofs << val;
	ofs.close();
	return val;
    }

    toml::Value tomlEraseValue(std::string FilePath, std::string key, toml::Value val) {
	std::ofstream ofs(FilePath);
	val.erase(key);

	ofs << val;
	ofs.close();
	return val;
    }

    void tomlWriteNewFile(std::string FilePath, toml::Value val) {
	std::ofstream ofs(FilePath);
	ofs << val;
	ofs.close();
    }
};

