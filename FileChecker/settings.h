#pragma once

#ifndef DEF_DIRECTORYCONF
#define DEF_DIRECTORYCONF

#include <experimental\filesystem>
#include <rapidjson\document.h>

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

#endif // !DEF_DIRECTORYCONF

#ifndef DEF_SETTINGS
#define DEF_SETTINGS

namespace fs = std::experimental::filesystem;

class Settings
{
	static Settings* s_instance;

public:
	Settings();
	~Settings();

	static Settings* GetInstance() { return s_instance; };
	const DirectoryConfig* GetDirectoryConfig( const fs::path &directoryPath);//filesettings
	//faut un const pointer
private:
	void LoadSettings();
	DirectoryConfig& CreateDirectoryConfig();

	std::vector<DirectoryConfig> m_directoriesConfigs; // DirectorySettings
};

#endif

