//#pragma once
#ifndef DEF_APPLICATION
#define DEF_APPLICATION

#include "settings.h"
#define CONFIG_FILE_PATH "./CheckerConfig.json"

class Application
{
	static Application* s_app;
	static Settings* s_settings;

public:
	Application();
	~Application();

	static bool Start();
	static void Quit();
	static Application* GetInstance(void) { return s_app; };
	static Settings* GetSettings() { return s_settings; }

private:
	enum MenuItem
	{
		MENU_NULL,
		MENU_NOMENCLATURE_CHECKER,
		MENU_EXTENSION_CHECKER,
		MENU_RUN_ALL,
		MENU_QUIT,
	};

	void Menu();
	MenuItem ChooseAction();

	bool m_isQuitting;
	MenuItem m_menuChoice;
};

#endif // !DEF_APPLICATION
