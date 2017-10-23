#include "settings.h"
#include <fstream>

using namespace std;
using namespace rapidjson;

Settings* Settings::s_instance = nullptr;

Settings::Settings()
{
	if (s_instance != nullptr)
		return;

	s_instance = this;
	s_instance->LoadSettings();
}

Settings::~Settings()
{
	delete s_instance;
	s_instance = nullptr;
}

void Settings::LoadSettings()
{
	// create directories with jsonparser;
}

const DirectoryConfig* Settings::GetDirectoryConfig( const fs::path &directoryPath)
{
	for (vector<DirectoryConfig>::iterator it = m_directoriesConfigs.begin(); it != m_directoriesConfigs.end(); it++)
		if (it->GetPath() == directoryPath)
			return &(*it);

	return nullptr;
}

// ---- DIRECTORY CONFIG -------

DirectoryConfig::DirectoryConfig( const bool excludeFromPrefixChkr, const bool excludeFromExtChkr, const fs::path &dirPath, const vector<fs::path> &subDirectories)
	:m_excludeFromPrefixChkr( excludeFromPrefixChkr ),m_excludeFromExtChkr( excludeFromExtChkr )
	, m_directoryPath( dirPath ),m_subDirectories( subDirectories )
{}

DirectoryConfig::~DirectoryConfig() {};
