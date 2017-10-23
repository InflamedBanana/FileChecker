#include "application.h"
#include "nomenclatureChecker.h"
#include <iostream>

using namespace std;

Application* Application::s_app = nullptr;
Settings* Application::s_settings = nullptr;

Application::Application(): m_menuChoice(MenuItem::MENU_NULL),m_isQuitting(false){}

Application::~Application()
{
	delete s_settings;
	s_settings = nullptr;
	/*delete s_app;
	s_app = nullptr;*/
}


bool Application::Start()
{
	// look if this should be in constructor instead...
	if (s_app == nullptr)
	{
		s_settings = new Settings(CONFIG_FILE_PATH);
		s_app = new Application;
		s_app->Menu();
		return true;
	}
	return false;
}

void Application::Menu()
{
	m_menuChoice = Application::ChooseAction();
	
	cout << "You chose : " << (int)m_menuChoice << endl;
	switch (m_menuChoice)
	{

	case MenuItem::MENU_QUIT: Quit();
		break;
	case MenuItem::MENU_NOMENCLATURE_CHECKER:
		if ( !NomenclatureChecker::Start() ) cout << "Couldn't Run Prefix Checker..." << endl << endl;

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
	cout << "4. Quit" << endl;

	char input;

	while (true)
	{
		cin >> input;
		 
		switch (input)
		{
		case '1': return MenuItem::MENU_NOMENCLATURE_CHECKER;
		case '2': return MenuItem::MENU_EXTENSION_CHECKER;
		case '3': return MenuItem::MENU_RUN_ALL;
		case '4': return MenuItem::MENU_QUIT;
		
		default : cout << "Unknown command : " << input << endl;
		}
	}
}

void Application::Quit()
{
	delete s_app;
	s_app = nullptr;
}

