#pragma once

#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#include <vector>
#include <string>
#include <rapidjson\document.h>
//namespace fs = std::experimental::filesystem;

class Settings
{
private:
	

public:
	struct FileValidationConfig
	{
		bool checkByNomenclature;
		bool checkByExtension;
	};

	struct DirectoryConfig
	{
		std::string name;
		bool excludeFromNomenclatureCheck;
		bool excludeFromExtensionCheck;
		std::vector<std::string> nomenclatureRestricts;
		std::vector<std::string> extensionRestricts;
		std::vector<DirectoryConfig> subDirectories;
	};

	struct NomenclatureConfig
	{
		std::vector<std::string> nomenclature;
		char separator;
		std::vector<std::vector<std::string>> definitions;
	};

	Settings(const std::string& filePath);
	~Settings();

	std::vector<DirectoryConfig>* GetDirectoriesArborescence() { return &m_directoriesArborescence; }

	NomenclatureConfig* GetNomenclatureConfig() { return &m_nomenclatureConfig; }
	FileValidationConfig* GetFileValidationConfig() { return &m_fileValidationConfig; }
	std::string GetMoveDirectoryPath() { return m_moveDirectoryPath; }
	std::string GetArborescenceStartPath() { return m_arborescenceStartPath; }
	std::vector<DirectoryConfig>* GetDirectoryArborescence() { return &m_directoriesArborescence; }

private:
	void LoadSettings(const std::string& filePath);
	DirectoryConfig CreateDirectoryConfig(const rapidjson::Value& value);
	//void SaveSetting(const std::string& filePath); when there is an interface

	std::vector<DirectoryConfig> m_directoriesArborescence;
	std::string m_arborescenceStartPath;
	NomenclatureConfig m_nomenclatureConfig;
	FileValidationConfig m_fileValidationConfig;
	std::string m_moveDirectoryPath;
};

#endif
