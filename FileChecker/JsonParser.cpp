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
		"				\"Name\" : [\"\"]\n"
		"			}\n"
		"		},\n"
		"\n"
		"		\"ArborescenceConfig\":\n"
		"		{\n"
		"			\"CheckByNomenclature\": true,\n"
		"			\"CheckByExtension\":true\n"
		"		},\n"
		"\n"
		"		\"MoveDirectory\":\n"
		"		{\n"
		"			\"Path\" : \"../Bin/\"\n"
		"		}\n"
		"	},\n"
		"\n"
		"	\"Arborescence\":\n"
		"	{\n"
		"		\"StartPath\":\"../\",\n"
		"		\"Directories\":\n"
		"		[\n"
		"			{\n"
		"				\"Name\":\"FileChecker\",\n"
		"				\"ExcludeFromNomenclatureCheck\" : true,\n"
		"				\"ExcludeFromExtensionCheck\" : true,\n"
		"				\"ExcludeRecursiveChecks\" : true,"
		"				\"NomenclatureRestrict\" :\n"
		"				[\n"
		"				],\n"
		"				\"ExtensionRestrict\" :\n"
		"				[\n"
		"				],\n"
		"				\"Directories\" : []\n"
		"			},\n"
		"\n"
		"			{\n"
		"				\"Name\":\"Bin\",\n"
		"				\"ExcludeFromNomenclatureCheck\" : true,\n"
		"				\"ExcludeFromExtensionCheck\" : true, \n"
		"				\"ExcludeRecursiveChecks\" : true,"
		"				\"NomenclatureRestrict\" :\n"
		"				[\n"
		"				],\n"
		"				\"ExtensionRestrict\" :\n"
		"				[\n"
		"				],\n"
		"				\"Directories\" : []\n"
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
