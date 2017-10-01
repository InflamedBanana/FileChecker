#pragma once
#ifndef DEF_PREFIXCHECK
#define DEF_PREFIXCHECK

#define PREFIXCHKR_PREFIX "DyD_"

#include <string>
#include "fileManipulator.h"

class PrefixChecker
{
	static PrefixChecker* s_prefixChkr;

public:
	PrefixChecker();
	~PrefixChecker();

	static bool Start();
	static void Stop();
	static PrefixChecker* GetInstance() { return s_prefixChkr; }

	int Status() { return m_status; }

private:

	void Run();
	bool CheckPrefix(const std::string &file);
	void ChangePrefix(std::string &file);

	int m_status;
};

#endif // !DEF_PREFIXCHECK