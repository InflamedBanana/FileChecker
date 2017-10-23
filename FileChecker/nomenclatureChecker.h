#pragma once
#ifndef DEF_PREFIXCHECK
#define DEF_PREFIXCHECK

#define PREFIXCHKR_PREFIX "DyD_"

#include <string>
#include "fileManipulator.h"

class NomenclatureChecker
{
	static NomenclatureChecker* s_prefixChkr;

public:
	NomenclatureChecker();
	~NomenclatureChecker();

	static bool Start();
	static void Stop();
	static NomenclatureChecker* GetInstance() { return s_prefixChkr; }

	//int Status() { return m_status; }

private:
	void Run();
	bool CheckPrefix(const std::string &fileName);
	bool ChangePrefix(fs::path &file);

	int m_status;
	std::string prefix = PREFIXCHKR_PREFIX;//Change variables with config file
	bool doChangePrefix = true;//Change variables with config file
};

#endif // !DEF_PREFIXCHECK