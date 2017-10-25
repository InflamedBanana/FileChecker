#pragma once

#ifndef DEF_JSONPARSER
#define DEF_JSONPARSER

#include<string>
#include<rapidjson\document.h>
#include<memory>

namespace JSON_Parser
{
	void GenerateConfigFile(const std::string& filePath);
	bool ConfigFileExists(const std::string& filePath);
	rapidjson::Document ParseFile(const std::string &filePath);
}

#endif
