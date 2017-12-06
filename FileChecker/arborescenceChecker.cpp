#include "arborescenceChecker.h"
#include <algorithm>

ArborescenceChecker::ArborescenceChecker(): m_status(APP_Status::S_STARTED){}
ArborescenceChecker::~ArborescenceChecker(){}

ArborescenceChecker* ArborescenceChecker::s_arborescenceChkr = nullptr;

void ArborescenceChecker::Start(Settings& settings)
{
	if (s_arborescenceChkr != nullptr) return;

	s_arborescenceChkr = new ArborescenceChecker;
	s_arborescenceChkr->Run(settings);
}

void ArborescenceChecker::Stop()
{
	delete s_arborescenceChkr;
	s_arborescenceChkr = nullptr;
}

void ArborescenceChecker::Run(Settings& settings)
{
	// Check For All Root Directories ( from settings.GetStartPath() )

}

void ArborescenceChecker::CheckDirectory( fs::path _path, const Settings::DirectoryConfig& _directory, const Settings& _settings)
{
	_path.append(_directory.name) / "/";

	//Check each directories & Recursive directories, see if they exist. If not create it. If a directory exist and it shouldn't, move it to bin
}

void ArborescenceChecker::CheckFilesExtensionInDirectory(const fs::path _directory, const std::vector<std::string>& _extensions, Settings& _settings)
{
	//Check directory files extensions to match directory settings
	for (auto& file : FileManipulator::GetFilesInDirectory(_directory.string()))
		if (!CheckFileExtension(file, _extensions))
			FileManipulator::MoveFile(file, _settings.GetMoveDirectoryPath());
}

bool CheckFileExtension(const fs::path _file, const std::vector<std::string>& _extension)
{
	if (!_file.has_extension) return false;

	//return std::any_of(_extension.begin()), _extension.end(), [](std::string& _str) {return _str.compare(_file.extension().string(); })

	bool hasWrongExtension(true);

	for (const auto& ext : _extension)
		if (ext.compare(_file.extension().string()) == 0 )
				hasWrongExtension = false;
}
