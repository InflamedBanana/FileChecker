#pragma once
#ifndef DEF_NOMENCLATURECHECK
#define DEF_NOMENCLATURECHECK

#define PREFIXCHKR_PREFIX "DyD_"

#include <string>
#include "fileManipulator.h"
#include "settings.h"
#include "Status.h"

class NomenclatureChecker
{
	static NomenclatureChecker* s_nomenclatureChkr;

public:
	NomenclatureChecker();
	~NomenclatureChecker();

	static bool Start(Settings& settings);
	static void Stop();
	static NomenclatureChecker* GetInstance() { return s_nomenclatureChkr; }

	APP_Status GetStatus() { return m_status; }

private:
	void Run(Settings& settings);
	
	void CheckDirectory(fs::path path,Settings::DirectoryConfig& directory, Settings& settings);
	bool CompareNomenclature(const fs::path &file, Settings &settings);
	std::vector<std::string> SplitFileName(const fs::path &file, Settings &settings);

	APP_Status m_status;
	int m_nbOfFilesChecked;
	int m_nbOfWrongFiles;
};

#endif