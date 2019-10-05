#pragma once
#include "toml.h"

class Toml {

public:
	toml::Value tomlReadFile(std::string FilePath);

	toml::Value* getValue(toml::Value& toml_value, std::string ValueName);

	toml::Value tomlSetValue(std::string FilePath, std::string key, toml::Value val, toml::Value new_val);

	toml::Value tomlEraseValue(std::string FilePath, std::string key, toml::Value val);
};

