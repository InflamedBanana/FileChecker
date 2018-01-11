#pragma once
#ifndef DEF_NOMENCLATURECHECK
#define DEF_NOMENCLATURECHECK

#include <string>
#include "settings.h"
#include <vector>

namespace Nomenclature
{
	void CheckNomenclature( const std::string& _path, const Settings::NomenclatureConfig& _nomenclatureConfig, std::vector<std::string>& _badFiles );
}

namespace Arborescence
{
	void CheckArborescence( const std::string& _path, const Settings::DirectoryConfig& _directory, std::vector<std::string>& _badFiles );
}

namespace Extension
{
	void CheckFilesExtensions( const std::string& _path, const Settings::DirectoryConfig& _dirConfig, std::vector<std::string>& _badFiles );
}

//
//
//class NomenclatureChecker
//{
//	static NomenclatureChecker* s_nomenclatureChkr;
//
//public:
//	static void Start(Settings& settings);
//	static void Stop();
//	static NomenclatureChecker* GetInstance() { return s_nomenclatureChkr; }
//
//	APP_Status GetStatus() { return m_status; }
//
//private:
//	NomenclatureChecker();
//	~NomenclatureChecker();
//	void Run(Settings& settings);
//	
//	void CheckDirectory(fs::path path,Settings::DirectoryConfig& directory, Settings& settings);
//	bool CompareNomenclature(const fs::path &file, Settings &settings);
//
//	APP_Status m_status;
//	int m_nbOfFilesChecked;
//	int m_nbOfWrongFiles;
//};

#endif