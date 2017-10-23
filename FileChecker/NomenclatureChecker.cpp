#include <iostream>
#include <string>
#include "nomenclatureChecker.h"
#include "fileManipulator.h"

NomenclatureChecker::NomenclatureChecker() : m_status(0) {}

NomenclatureChecker::~NomenclatureChecker() {}

NomenclatureChecker* NomenclatureChecker::s_prefixChkr = nullptr;


bool NomenclatureChecker::Start()
{
	if (s_prefixChkr == nullptr)
	{
		s_prefixChkr = new NomenclatureChecker;
		s_prefixChkr->Run();
		return true;
	}
	return false;
}

void NomenclatureChecker::Stop()
{
	delete s_prefixChkr;
	s_prefixChkr = nullptr;
}

void NomenclatureChecker::Run()
{
	int nbOfFiles(0), nbOfWrongFileName(0), nbOfRenamedFiles(0);

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
	Stop();
}

bool NomenclatureChecker::CheckPrefix(const std::string &fileName)
{
	return (fileName.find(prefix) == 0 );
}

bool NomenclatureChecker::ChangePrefix(fs::path &file)
{
	std::string newName(prefix);
	newName.append(file.filename().string());
	return FileManipulator::RenameFile( file, newName );
}