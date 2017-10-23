#include <iostream>
#include "application.h"
#include "fileManipulator.h"
#include "JsonParser.h"
#include <rapidjson\document.h>

using namespace std;

int main()
{
	if (!JSON_Parser::ConfigFileExists(CONFIG_FILE_PATH))
	{
		JSON_Parser::GenerateConfigFile(CONFIG_FILE_PATH);

		cout << "-------------------" << endl;
		cout << "Config File created" << endl;
		cout << "-------------------" << endl << endl;
	}

	const rapidjson::Document* doc = JSON_Parser::ParseFile(CONFIG_FILE_PATH);

	assert(!doc->HasParseError());
	assert(doc->HasMember("FileChecker configs"));
	assert(doc->HasMember("Arborescence"));

	system("PAUSE");
	/*if ( !Application::Start() )
	{
		std::cout << "Start Application Failed...";
		system("PAUSE");
		return -1;
	}*/

	return 0;
}