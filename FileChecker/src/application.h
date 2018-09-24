//#pragma once
#ifndef DEF_APPLICATION
#define DEF_APPLICATION

#include "Status.h"
#include "settings.h"
#include <unordered_set>

class Application
{
	static Application* s_application;

public:
	Application();
	~Application();

	APP_Status GetStatus() { return m_status; }
	Settings& GetSettings() { return m_settings; }

	static bool Start();
	static void Quit();
	static Application* GetInstance() { return s_application; }

private:
	enum MenuItem
	{
		MENU_NULL,
		MENU_SETTINGS,
		MENU_RUN_ALL,
		MENU_QUIT,
	};


	void Menu();
	MenuItem ChooseAction();
	void ShowSettings();

	void NavigateThroughDirectories();
	void CheckDirectory( std::string _path, const Settings::DirectoryConfig& _directory, std::unordered_set<std::string>& _badFiles );

	Settings   m_settings;
	MenuItem   m_menuChoice;
	APP_Status m_status;
};

#endif // !DEF_APPLICATION
