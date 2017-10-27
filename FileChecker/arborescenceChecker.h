#pragma once

#ifndef DEF_ARBORESCENCECHECKER
#define DEF_ARBORESCENCECHECKER

#include "settings.h"
#include "Status.h"

class ArborescenceChecker
{
	static ArborescenceChecker* s_arborescenceChkr;

public:
	static void Start(Settings& settings);
	static void Stop();
	static ArborescenceChecker* GetInstance() { return s_arborescenceChkr; }

private:
	ArborescenceChecker();
	~ArborescenceChecker();
	void Run(Settings& settings);
	
	APP_Status m_status;
};

#endif
