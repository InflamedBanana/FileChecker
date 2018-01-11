//#pragma once
#ifndef DEF_APPLICATION
#define DEF_APPLICATION

#include "Status.h"
#include "settings.h"
#define CONFIG_FILE_PATH "./CheckerConfig.json"
#define APPLICATION_PATH "../FileChecker"

class Application
{
	static Application* s_application;
	//static Settings* s_settings;

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
		/*	MENU_NOMENCLATURE_CHECKER,
			MENU_ARBORESCENCE_CHECKER,*/
		MENU_SETTINGS,
		MENU_RUN_ALL,
		MENU_QUIT,
	};


	void Menu();
	MenuItem ChooseAction();
	void ShowSettings();

	void NavigateThroughDirectories();
	void CheckDirectory( std::string& _path, const Settings::DirectoryConfig& _directory, std::vector<std::string>& _badFiles );
	void SendToBin( const std::vector<std::string>& _file );
	void LogFilesSent( const std::vector<std::string>& _files );

	Settings   m_settings;
	MenuItem   m_menuChoice;
	APP_Status m_status;
};

#endif // !DEF_APPLICATION
