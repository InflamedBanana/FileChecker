#define CONFIG_FILE_PATH "./CheckerConfig.json"
#pragma once

#ifndef DEF_JSONPARSER
#define DEF_JSONPARSER

#include<string>
#include<rapidjson\document.h>
//#include<rapidjson\document.h>
//#include<filesystem>



namespace JSON_Parser
{
	void GenerateConfigFile(const std::string& filePath);
	bool ConfigFileExists(const std::string& filePath);
	const rapidjson::Document* ParseFile(const std::string &filePath);
}

namespace JP = JSON_Parser;

#endif
