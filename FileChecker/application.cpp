#include "application.h"
#include "nomenclatureChecker.h"
#include <iostream>

using namespace std;

Application* Application::s_application = nullptr;
Settings* Application::s_settings = nullptr;

Application::Application(): m_menuChoice(MenuItem::MENU_NULL),m_status(APP_Status::S_STARTED){}

Application::~Application()
{
	delete s_settings;
	s_settings = nullptr;
}

bool Application::Start()
{
	if (s_application == nullptr)
	{
		s_settings = new Settings(CONFIG_FILE_PATH);
		s_application = new Application;
		s_application->Menu();
		return true;
	}
	return false;
}

void Application::Menu()
{
	m_status = APP_Status::S_RUNNING;

	m_menuChoice = Application::ChooseAction();
	
	cout << "You chose : " << ((int)m_menuChoice +1 ) << endl;
	switch (m_menuChoice)
	{

	case MenuItem::MENU_QUIT: Quit();
		break;
	case MenuItem::MENU_NOMENCLATURE_CHECKER:
		if (!NomenclatureChecker::Start(s_settings))
			cout << "Couldn't Run Prefix Checker..." << endl << endl;
	case MenuItem::MENU_SETTINGS:
		ShowSettings();
	case MenuItem::MENU_EXTENSION_CHECKER:
	case MenuItem::MENU_RUN_ALL:
	default :
		Menu();
		break;
	}
}

Application::MenuItem Application::ChooseAction()
{
	cout << endl << "======== MENU =======" << endl << endl;
	cout << "1. Prefix Checker" << endl;
	cout << "2. Extension Checker" << endl;
	cout << "3. Run All" << endl;
	cout << "4. Settings" << endl;
	cout << "5. Quit" << endl;

	char input;

	while (true)
	{
		cin >> input;
		 
		switch (input)
		{
		case '1': return MenuItem::MENU_NOMENCLATURE_CHECKER;
		case '2': return MenuItem::MENU_EXTENSION_CHECKER;
		case '3': return MenuItem::MENU_RUN_ALL;
		case '4': return MenuItem::MENU_SETTINGS;
		case '5': return MenuItem::MENU_QUIT;
		
		default : cout << "Unknown command : " << input << endl;
		}
	}
}

void Application::Quit()
{
	s_application->m_status = APP_Status::S_STOPPED;
	delete s_application;
	s_application = nullptr;
}

void Application::ShowSettings()
{
	cout << endl << "======== SETTINGS =======" << endl << endl;

	string nomenclature;

	for (vector<string>::iterator itr = s_settings->GetNomenclatureConfig()->nomenclature.begin();
		itr != s_settings->GetNomenclatureConfig()->nomenclature.end(); ++itr)
	{
		nomenclature.append((*itr).begin(), (*itr).end());
		nomenclature.push_back(s_settings->GetNomenclatureConfig()->separator);
	}

	cout << "Nomenclature : " << nomenclature << endl;
	
	{
		int i(1);

		for (vector<vector<string>>::iterator itr = s_settings->GetNomenclatureConfig()->definitions.begin();
			itr != s_settings->GetNomenclatureConfig()->definitions.end(); ++itr)
		{
			cout << "Definition " << i << " : " ;
			for (vector<string>::iterator sitr = itr->begin(); sitr != itr->end(); ++sitr)
				cout << *sitr << ", " ;
			cout << endl;
			++i;
		}
	}

	cout << endl << "Check by nomenclature : " << s_settings->GetFileValidationConfig()->checkByNomenclature << endl;
	cout << "Check by extension : " << s_settings->GetFileValidationConfig()->checkByExtension << endl;

	cout << "Move Directory Path : " << s_settings->GetMoveDirectoryPath() << endl;
	cout << endl << "Arborescence Start Path : " << s_settings->GetArborescenceStartPath() << endl;
	cout << "nb of directories " << s_settings->GetDirectoryArborescence()->size() << endl;
	for (vector<Settings::DirectoryConfig>::iterator it = s_settings->GetDirectoryArborescence()->begin();
		it != s_settings->GetDirectoryArborescence()->end(); ++it)
		cout << "Directory : " << it->name << endl;
}
