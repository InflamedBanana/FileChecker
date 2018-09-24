#pragma once

#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <vector>
#include <string>
#include <rapidjson\document.h>
#include <unordered_set>

#define DIRFLAG_EXCL_NOMENCLATURE 1 << 0
#define DIRFLAG_EXCL_EXTENSION 1 << 1
#define DIRFLAG_EXCL_RECURSIVE 1 << 2



class Settings
{
public:

	struct DirectoryConfig
	{
		enum DirectoryFlags
		{
			None = 0,
			Exclude_Nomenclature_Check = 1 << 0,
			Exclude_Extension_Check = 1 << 1,
			Exclude_Recursive_Check = 1 << 2
		};

		DirectoryConfig() : name( "" ), flags( 0 ) {}
		DirectoryConfig( std::string _name ) : name( _name ), flags( 0 ) {}

		std::string name;
		int flags;
		std::vector<std::string> extensionRestricts;
		std::vector<DirectoryConfig> subDirectories;
	};

	struct NomenclatureConfig
	{
		std::vector<std::string> nomenclature;
		char separator;
		std::vector<std::vector<std::string>> definitions;
	};

	Settings( const std::string& filePath );
	~Settings();

	DirectoryConfig GetArborescenceRootDirectory() const { return m_arborescenceRootDirectory; }

	NomenclatureConfig GetNomenclatureConfig() const { return m_nomenclatureConfig; }
	std::string GetMoveDirectoryPath() const { return m_moveDirectoryPath; }
	std::vector<std::string> GetAssociatedFiles() const { return m_associatedFiles; }
	std::vector<std::string> GetDirectoriesExceptions() const { return m_directoriesExceptions; }

	//void MoveToBin( const std::unordered_set<std::string>& _files, const bool _logFiles = true);
	void WriteLogs( const std::unordered_set<std::string>& _files, const bool _logFiles = true );

private:
	bool LoadSettings( const std::string& filePath );
	DirectoryConfig CreateDirectoryConfig( const rapidjson::Value& value );
	//void CreateBinDirectory();
	void LogFilesSentToBin( const std::unordered_set<std::string>& _files );
	//void SaveSetting(const std::string& filePath); when there is an interface

	DirectoryConfig m_arborescenceRootDirectory;
	NomenclatureConfig m_nomenclatureConfig;
	std::string m_moveDirectoryPath;
	std::vector<std::string> m_associatedFiles;
	std::vector<std::string> m_directoriesExceptions;
};

#endif
