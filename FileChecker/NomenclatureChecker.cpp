#include <iostream>
#include <string>
#include "nomenclatureChecker.h"
#include "fileManipulator.h"
#include <vector>

NomenclatureChecker::NomenclatureChecker() : m_status(APP_Status::S_STARTED) {}

NomenclatureChecker::~NomenclatureChecker() {}

NomenclatureChecker* NomenclatureChecker::s_nomenclatureChkr = nullptr;


bool NomenclatureChecker::Start( Settings* settings)
{
	if (settings == nullptr) return false;

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

void NomenclatureChecker::Run( Settings* settings)
{
	m_status = APP_Status::S_RUNNING;

	Stop();
	/* nbOfFiles(0), nbOfWrongFileName(0), nbOfRenamedFiles(0);

	for (auto file : FileManipulator::GetAllFilesInRecursiveDirectory("./"))
	{
		std::cout << file << std::endl;
		++nbOfFiles;

		if ( !CheckPrefix(file.filename().string() ) )
		{
			++nbOfWrongFileName;
			if (doChangePrefix)
			{
				++nbOfRenamedFiles;
				ChangePrefix(file);
			}
		}
	}

	std::cout << std::endl << "-- Nb of files checked : " << nbOfFiles << " --" << std::endl;
	std::cout << std::endl << "-- Nb of wrong file names : " << nbOfWrongFileName << " --" << std::endl;
	std::cout << std::endl << "-- Nb of renamed files : " << nbOfRenamedFiles << " --" << std::endl;

	system("PAUSE");
	Stop();*/
}

/*bool NomenclatureChecker::CheckPrefix(const std::string &fileName)
{
	return (fileName.find(prefix) == 0 );
}

bool NomenclatureChecker::ChangePrefix(fs::path &file)
{
	std::string newName(prefix);
	newName.append(file.filename().string());
	return FileManipulator::RenameFile( file, newName );
}*/