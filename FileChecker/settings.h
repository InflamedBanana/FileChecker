#pragma once

/*#ifndef DEF_DIRECTORYCONF
#define DEF_DIRECTORYCONF

#include <experimental\filesystem>

namespace fs = std::experimental::filesystem;

class DirectoryConfig
{
public:
	DirectoryConfig( const bool excludeFromPrefixChkr, const bool excludeFromExtChkr
		,const fs::path &dirPath, const std::vector<fs::path> &subDirectories);
	~DirectoryConfig();

	bool ExcludeFromPrefixChecker() const { return m_excludeFromPrefixChkr; };
	bool ExcludeFromExtensionChecker() const { return m_excludeFromExtChkr; };
	std::vector<fs::path> GetSubDirectories() const { return m_subDirectories; };
	fs::path GetPath() const { return m_directoryPath; };

private:
	bool m_excludeFromPrefixChkr;
	bool m_excludeFromExtChkr;
	std::vector<fs::path> m_subDirectories;
	fs::path m_directoryPath;
};

#endif // !DEF_DIRECTORYCONF*/

#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <rapidjson\document.h>

//namespace fs = std::experimental::filesystem;

class Settings
{
	//static Settings* s_instance;

public:
	Settings(const std::string& filePath);
	~Settings();

	const rapidjson::Document* GetSettings() { return m_settings; };

	//static Settings* GetInstance() { return s_instance; };
	//const DirectoryConfig* GetDirectoryConfig( const fs::path &directoryPath);

private:
	void LoadSettings(const std::string& filePath);
	const rapidjson::Document* m_settings;
	//DirectoryConfig& CreateDirectoryConfig();

	//std::vector<DirectoryConfig> m_directoriesConfigs; // DirectorySettings
};

#endif
