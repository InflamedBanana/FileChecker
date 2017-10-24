//#pragma once
#ifndef DEF_APPLICATION
#define DEF_APPLICATION

#include "Status.h"
#include "settings.h"
#define CONFIG_FILE_PATH "./CheckerConfig.json"

class Application
{
	static Application* s_application;
	static Settings* s_settings;

public:
	Application();
	~Application();

	static bool Start();
	static void Quit();
	static Application* GetInstance() { return s_application; }
	static Settings* GetSettings() { return s_settings; }
	APP_Status GetStatus() { return m_status; }

private:
	enum MenuItem
	{
		MENU_NULL,
		MENU_NOMENCLATURE_CHECKER,
		MENU_EXTENSION_CHECKER,
		MENU_SETTINGS,
		MENU_RUN_ALL,
		MENU_QUIT,
	};

	void Menu();
	MenuItem ChooseAction();
	void ShowSettings();

	MenuItem m_menuChoice;
	APP_Status m_status;
};

#endif // !DEF_APPLICATION
