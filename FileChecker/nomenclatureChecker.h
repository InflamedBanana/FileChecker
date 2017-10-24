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

	static bool Start( Settings* settings);
	static void Stop();
	static NomenclatureChecker* GetInstance() { return s_nomenclatureChkr; }

	APP_Status GetStatus() { return m_status; }

private:
	void Run(Settings* settings);
	/*bool CheckPrefix(const std::string &fileName);
	bool ChangePrefix(fs::path &file);*/

	APP_Status m_status;
	//std::string prefix = PREFIXCHKR_PREFIX;//Change variables with config file
	//bool doChangePrefix = true;//Change variables with config file
};

#endif