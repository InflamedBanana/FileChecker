#include "settings.h"
#include <fstream>
#include "JsonParser.h"
#include <iostream>

//using namespace std;
using namespace rapidjson;

//Settings* Settings::s_instance = nullptr;

Settings::Settings(const std::string& filePath)
{
	/*if (s_instance != nullptr)
		return;

	s_instance = this;
	s_instance->LoadSettings(filePath);*/
}

Settings::~Settings()
{
	/*delete s_instance;
	s_instance = nullptr;*/
	delete m_settings;
	m_settings = nullptr;
}

void Settings::LoadSettings(const std::string& filePath)
{
	// create directories with jsonparser;
	if (!JSON_Parser::ConfigFileExists(filePath))
	{
		JSON_Parser::GenerateConfigFile(filePath);

		std::cout << "-------------------" << std::endl;
		std::cout << "Config File created" << std::endl;
		std::cout << "-------------------" << std::endl << std::endl;
	}

	m_settings = JSON_Parser::ParseFile(filePath);
}

/*const DirectoryConfig* Settings::GetDirectoryConfig( const fs::path &directoryPath)
{
	for (vector<DirectoryConfig>::iterator it = m_directoriesConfigs.begin(); it != m_directoriesConfigs.end(); it++)
		if (it->GetPath() == directoryPath)
			return &(*it);

	return nullptr;
}*/

// ---- DIRECTORY CONFIG -------

/*DirectoryConfig::DirectoryConfig( const bool excludeFromPrefixChkr, const bool excludeFromExtChkr, const fs::path &dirPath, const vector<fs::path> &subDirectories)
	:m_excludeFromPrefixChkr( excludeFromPrefixChkr ),m_excludeFromExtChkr( excludeFromExtChkr )
	, m_directoryPath( dirPath ),m_subDirectories( subDirectories )
{}

DirectoryConfig::~DirectoryConfig() {};*/
