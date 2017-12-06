#pragma once

#ifndef DEF_ARBORESCENCECHECKER
#define DEF_ARBORESCENCECHECKER

#include "settings.h"
#include "Status.h"
#include "fileManipulator.h"

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
	
	void CheckDirectory( fs::path _path, const Settings::DirectoryConfig& _directory, const Settings& _settings);
	void CheckFilesExtensionInDirectory(const fs::path _directory, const std::vector<std::string>& _extensions, Settings& _settings);
	bool CheckFileExtension(const fs::path _file, const std::vector<std::string>& _extensions);


	APP_Status m_status;
};

#endif
