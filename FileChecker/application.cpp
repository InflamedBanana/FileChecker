#include "application.h"
#include "fileChecks.h"
#include "fileManipulator.h"
#include <iostream>

using namespace std;

typedef Settings::DirectoryConfig::DirectoryFlags DirectoryFlags;

Application* Application::s_application = nullptr;

Application::Application() : m_menuChoice( MenuItem::MENU_NULL ), m_status( APP_Status::S_STARTED )
, m_settings( CONFIG_FILE_PATH ) {}

Application::~Application()
{}

bool Application::Start()
{
	if( s_application == nullptr )
	{
		s_application = new Application;
		s_application->Menu();
		return true;
	}
	return false;
}

void Application::Menu()
{
	m_status = APP_Status::S_MENU;

	m_menuChoice = Application::ChooseAction();

	switch( m_menuChoice )
	{
		case MenuItem::MENU_QUIT:
			Quit();
			break;
		case MenuItem::MENU_SETTINGS:
			ShowSettings();
			Menu();
			break;
		case MenuItem::MENU_RUN_ALL:
			NavigateThroughDirectories();
			Menu();
			break;
		default:
			cout << "Didn't find menu entry." << endl;
			Menu();
			break;
	}
}

Application::MenuItem Application::ChooseAction()
{
	cout << endl << "======== MENU =======" << endl << endl;
	cout << "1. Run File Checker" << endl;
	cout << "2. Settings" << endl;
	cout << "3. Quit" << endl;

	char input;

	while( true )
	{
		cin >> input;

		switch( input )
		{
			case '1': return MenuItem::MENU_RUN_ALL;
			case '2': return MenuItem::MENU_SETTINGS;
			case '3': return MenuItem::MENU_QUIT;

			default: cout << "Unknown command : " << input << endl;
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

	Settings::NomenclatureConfig nomenclatureSettings( m_settings.GetNomenclatureConfig() );

	for( vector<string>::iterator itr = nomenclatureSettings.nomenclature.begin();
		 itr != nomenclatureSettings.nomenclature.end(); ++itr )
	{
		nomenclature.append( ( *itr ).begin(), ( *itr ).end() );
		nomenclature.push_back( nomenclatureSettings.separator );
	}

	cout << "Nomenclature : " << nomenclature << endl;

	{
		int i( 1 );

		for( vector<vector<string>>::iterator itr = nomenclatureSettings.definitions.begin();
			 itr != nomenclatureSettings.definitions.end(); ++itr )
		{
			cout << "Definition " << i << " : ";
			for( vector<string>::iterator sitr = itr->begin(); sitr != itr->end(); ++sitr )
				cout << *sitr << ", ";
			cout << endl;
			++i;
		}
	}

	cout << "Move Directory Path : " << m_settings.GetMoveDirectoryPath() << endl;
}

void Application::NavigateThroughDirectories()
{
	m_status = APP_Status::S_RUNNING;

	unordered_set<string> badFiles;

	string startPath( "" );
	CheckDirectory( startPath, m_settings.GetArborescenceRootDirectory(), badFiles );

	SendToBin( badFiles );
	LogFilesSent( badFiles );
}

void Application::CheckDirectory( string& _path, const Settings::DirectoryConfig& _directory, unordered_set<string>& _badFiles )
{
	if( _directory.name == "Bin" || _directory.name == "FileChecker" ) // replace by DirectoryConfig of StartPath
		return;

	_path.append( _directory.name + "/" );
	
	Arborescence::CheckArborescence( _path, _directory, _badFiles, m_settings.GetAssociatedFiles() );
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Nomenclature_Check ) == 0 )
		Nomenclature::CheckNomenclature( _path, m_settings.GetNomenclatureConfig(), _badFiles, m_settings.GetAssociatedFiles() );
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Extension_Check ) == 0 )
		Extension::CheckFilesExtensions( _path, _directory, _badFiles, m_settings.GetAssociatedFiles() );
	
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Recursive_Check ) == (int)DirectoryFlags::Exclude_Recursive_Check )
		return;

	for( const auto& subDir : _directory.subDirectories )
		CheckDirectory( _path, subDir, _badFiles );
}

void Application::SendToBin( const unordered_set<string>& _files )
{
	for( const auto& file : _files )
		FileManipulator::MoveFile( file, m_settings.GetMoveDirectoryPath() );
}

void Application::LogFilesSent( const unordered_set<string>& _files )
{
	cout << "------------ Check Report ------------" <<endl;
	for( const auto& file : _files )
		cout << file << endl;

	cout << "Number of files sent to bin : " << _files.size() << endl;
}
