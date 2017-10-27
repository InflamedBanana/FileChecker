#include "arborescenceChecker.h"

ArborescenceChecker::ArborescenceChecker(): m_status(APP_Status::S_STARTED){}
ArborescenceChecker::~ArborescenceChecker(){}

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

}
