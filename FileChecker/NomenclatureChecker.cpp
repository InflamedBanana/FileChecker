#include <iostream>
#include <string>
#include <sstream>
#include "nomenclatureChecker.h"
#include "fileManipulator.h"
#include <vector>

using namespace std;

NomenclatureChecker::NomenclatureChecker() : m_status(APP_Status::S_STARTED), m_nbOfFilesChecked(0),
											m_nbOfWrongFiles(0){}

NomenclatureChecker::~NomenclatureChecker() {}

NomenclatureChecker* NomenclatureChecker::s_nomenclatureChkr = nullptr;

bool NomenclatureChecker::Start( Settings& settings)
{
	if (s_nomenclatureChkr == nullptr)
	{
		s_nomenclatureChkr = new NomenclatureChecker;
		s_nomenclatureChkr->Run( settings );
		return true;
	}
	return false;
}

void NomenclatureChecker::Stop()
{
	s_nomenclatureChkr->m_status = APP_Status::S_STOPPED;
	delete s_nomenclatureChkr;
	s_nomenclatureChkr = nullptr;
}

void NomenclatureChecker::Run( Settings& settings)
{
	m_status = APP_Status::S_RUNNING;
	
	for (auto& directory : *(settings.GetDirectoriesArborescence())) //every root directories
		CheckDirectory(settings.GetArborescenceStartPath(), directory, settings);

	cout << endl << "Number of files checked : " << m_nbOfFilesChecked << '.' << endl;
	cout << "Number of wrong files : " << m_nbOfWrongFiles << '.' << endl;

	Stop();
}

void NomenclatureChecker::CheckDirectory(fs::path path, Settings::DirectoryConfig& directory, Settings& settings)
{
	path / directory.name / "/";

	if (!directory.excludeFromNomenclatureCheck)
	{
		for (auto& file : FileManipulator::GetFilesInDirectory(path.string()))
		{
			if (!CompareNomenclature(file, settings))
			{
				FileManipulator::MoveFile(file, fs::path(settings.GetMoveDirectoryPath()) / file.filename());
				++m_nbOfWrongFiles;
			}
			
			cout << file.string() << endl;
			++m_nbOfFilesChecked;
		}
	}

	for (auto& subDirectory : directory.subDirectories)
		CheckDirectory(path, subDirectory, settings);
}

bool NomenclatureChecker::CompareNomenclature(const fs::path &file, Settings &settings)
{
	vector<string> fileName(SplitFileName(file, settings));

	for (int i = 0; i < settings.GetNomenclatureConfig()->nomenclature.size(); ++i)
	{
		if (i >= fileName.size()) return false;
		if (settings.GetNomenclatureConfig()->definitions[i].size() == 0) return true;

		bool isBadlyNamed(true);

		for (const auto& nDef : settings.GetNomenclatureConfig()->definitions[i])
			if (fileName[i].compare(nDef) == 0) isBadlyNamed = false;

		if (isBadlyNamed) return false;
	}
	return true;
}

vector<string> NomenclatureChecker::SplitFileName(const fs::path &file, Settings &settings)
{
	vector<string> fileNameParts;
	istringstream iss(file.filename().string());
	string temp;

	while (getline(iss, temp, settings.GetNomenclatureConfig()->separator))
		fileNameParts.push_back(temp);

	return fileNameParts;
}
