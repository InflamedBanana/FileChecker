#include "JsonParser.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace rapidjson;

void JSON_Parser::GenerateConfigFile(const string& filePath)
{
	std::ofstream configFile(filePath);

	configFile <<
		"{\n"
		"	\"FileChecker configs\":\n"
		"	{\n"
		"		\"Nomenclature\":\n"
		"		{\n"
		"			\"Separator\" : \"_\",\n"
		"			\"Definitions\":\n"
		"			{\n"
		"				\"Prefix\": [\"\"],\n"
		"				\"Type\" : [\"\"],\n"
		"				\"Name\" : []\n"
		"			}\n"
		"		},\n"
		"\n"
		"		\"MoveDirectory\":\n"
		"		{\n"
		"			\"Path\" : \"../Bin/\",\n"
		"			\"Move_Associated_Files\" : []\n"
		"		}\n"
		"	},\n"
		"\n"
		"	\"Arborescence\":\n"
		"	{\n"
		"		\"Directories\":\n"
		"		[\n"
		"			{\n"
		"				\"Name\":\"../\",\n"
		"				\"Exclude_Nomenclature_Check\" : false,\n"
		"				\"Exclude_Extension_Check\" : false,\n"
		"				\"Exclude_Recursive_Checks\" : false,\n"
		"				\"ExtensionRestrict\" :\n"
		"				[\n"
		"				],\n"
		"				\"Directories\" : \n"
		"				[\n"
		"					{\n"
		"						\"Name\":\"FileChecker\",\n"
		"						\"Exclude_Nomenclature_Check\" : true,\n"
		"						\"Exclude_Extension_Check\" : true,\n"
		"						\"Exclude_Recursive_Checks\" : true,\n"
		"						\"ExtensionRestrict\" :\n"
		"						[\n"
		"						],\n"
		"						\"Directories\" : []\n"
		"					},\n"
		"\n"
		"					{\n"
		"						\"Name\":\"Bin\",\n"
		"						\"Exclude_Nomenclature_Check\" : true,\n"
		"						\"Exclude_Extension_Check\" : true,\n"
		"						\"Exclude_Recursive_Checks\" : true,\n"
		"						\"ExtensionRestrict\" :\n"
		"						[\n"
		"						],\n"
		"						\"Directories\" : []\n"
		"					}\n"
		"				]\n"
		"			}\n"
		"		]\n"
		"	}\n"
		"}" << endl;

	configFile.close();
}

bool JSON_Parser::ConfigFileExists(const string& filePath)
{
	std::experimental::filesystem::path configFilePath( filePath );
	return std::experimental::filesystem::exists(configFilePath);
}

Document JSON_Parser::ParseFile(const std::string &filePath)
{
	if ( !ConfigFileExists( filePath ) ) // in case it's been deleted during
		GenerateConfigFile( filePath );

	fstream file( filePath );

	if (!file) return nullptr;

	string json;
	
	{
		string temp;
		while (getline(file, temp) )
			json.append(temp);
	}
	
	Document doc;
	doc.Parse(json.c_str());
	return doc;
}
