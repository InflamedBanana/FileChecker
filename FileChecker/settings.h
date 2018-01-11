#pragma once

#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <vector>
#include <string>
#include <rapidjson\document.h>

class Settings
{
private:


public:

	struct DirectoryConfig
	{
		enum DirectoryFlags
		{
			None = 0,
			Exclude_Nomenclature_Check = 1 << 0,
			Exclude_Extension_Check = 1 << 1,
			Exclude_Recursive_Check = 1 << 2,
			Has_Been_Visited = 1 << 3
		};

		DirectoryConfig() : name( "" ), flags( 0 ) {}
		DirectoryConfig( std::string _name ) : name( _name ), flags( 0 ) {}

		std::string name;
		int flags;
		//std::vector<std::string> nomenclatureRestricts;
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

	std::vector<DirectoryConfig> GetDirectoriesArborescence() const { return m_directoriesArborescence; }

	NomenclatureConfig GetNomenclatureConfig() const { return m_nomenclatureConfig; }
	std::string GetMoveDirectoryPath() const { return m_moveDirectoryPath; }
	std::string GetArborescenceStartPath() const { return m_arborescenceStartPath; }
	std::vector<std::string> GetAssociatedFiles() const { return m_associatedFiles; }

private:
	bool LoadSettings( const std::string& filePath );
	DirectoryConfig CreateDirectoryConfig( const rapidjson::Value& value );
	//void SaveSetting(const std::string& filePath); when there is an interface

	std::vector<DirectoryConfig> m_directoriesArborescence;
	std::string m_arborescenceStartPath;
	NomenclatureConfig m_nomenclatureConfig;
	std::string m_moveDirectoryPath;
	std::vector<std::string> m_associatedFiles;

};

#endif
