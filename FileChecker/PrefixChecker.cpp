#include <direct.h>
#include <iostream>
#include <string>
#include "prefixChecker.h"
#include "fileManipulator.h"
#include <set>

//using namespace std;

PrefixChecker::PrefixChecker() : m_status(0) {}

PrefixChecker::~PrefixChecker() {}

PrefixChecker* PrefixChecker::s_prefixChkr = nullptr;


bool PrefixChecker::Start()
{
	if (s_prefixChkr == nullptr)
	{
		s_prefixChkr = new PrefixChecker;
		s_prefixChkr->Run();
		return true;
	}
	return false;
}

void PrefixChecker::Stop()
{
	delete s_prefixChkr;
	s_prefixChkr = nullptr;
}

void PrefixChecker::Run()
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

bool PrefixChecker::CheckPrefix(const std::string &fileName)
{
	return (fileName.find(prefix) == 0 );
}

bool PrefixChecker::ChangePrefix(fs::path &file)
{
	std::string newName(prefix);
	newName.append(file.filename().string());
	return FileManipulator::RenameFile( file, newName );
}