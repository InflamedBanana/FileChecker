//#pragma once
#ifndef DEF_APPLICATION
#define DEF_APPLICATION

class Application
{
	static Application* s_app;

public:
	Application();
	~Application();

	static bool Start();
	static void Quit();
	static Application* GetInstance(void) { return s_app; };


private:
	enum MenuItem
	{
		MENU_NULL,
		MENU_PREFIX_CHECKER,
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
