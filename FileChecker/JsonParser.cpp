#include "JsonParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include "fileManipulator.h"

using namespace std;
using namespace rapidjson;

void JSON_Parser::GenerateConfigFile( const string& filePath )
{
	std::ofstream configFile( filePath );

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
		"		\"Log_Options\":\n"
		"		{\n"
		//"			\"Path\" : \"../Bin/\",\n"
		"			\"Associated_Files\" : []\n"
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
		"						\"Name\":\"Template\",\n"
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

bool JSON_Parser::ParseFile( const std::string& _filePath, Document* _doc )
{
	assert( _doc != nullptr );
	if( !FileManipulator::PathExists( _filePath ) )
		GenerateConfigFile( _filePath );

	fstream file( _filePath );

	if( !file ) return nullptr;

	string json;

	{
		string temp;
		while( getline( file, temp ) )
			json.append( temp );
	}
	
	_doc->Parse( json.c_str() );

	return !_doc->IsNull();
}

bool JSON_Parser::CheckBoolValue( const rapidjson::Value & _value, const char* _name )
{
	return _value.HasMember(_name) && _value[_name].GetBool();
}
