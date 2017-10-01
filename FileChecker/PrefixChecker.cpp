#include <direct.h>
#include <iostream>
#include <string>
#include "prefixChecker.h"

using namespace std;

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
	string wesh("./");
	for (const auto& file : FileManipulator::GetAllFilesInRecursiveDirectory(wesh))
		std::cout << file << std::endl;

	system("PAUSE");
	Stop();
}