#pragma once

#ifndef DEF_JSONPARSER
#define DEF_JSONPARSER

#include<string>
#include<rapidjson\document.h>

namespace JSON_Parser
{
	void GenerateConfigFile(const std::string& filePath);
	bool ParseFile(const std::string &filePath, rapidjson::Document* _doc);

	bool CheckBoolValue( const rapidjson::Value& _value, const char* _name );
}

#endif
