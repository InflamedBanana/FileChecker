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
			//case MenuItem::MENU_NOMENCLATURE_CHECKER:
			//	NomenclatureChecker::Start( m_settings );
			//	Menu();
			//	break;
			//case MenuItem::MENU_ARBORESCENCE_CHECKER:
			//	ArborescenceChecker::Start( m_settings ); Menu(); 
			//	break;
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
	//cout << "1. Nomenclature Check" << endl;
	//cout << "2. Arborescence Check" << endl;
	cout << "1. Run File Checker" << endl;
	cout << "2. Settings" << endl;
	cout << "3. Quit" << endl;

	char input;

	while( true )
	{
		cin >> input;

		switch( input )
		{
			/*case '1': return MenuItem::MENU_NOMENCLATURE_CHECKER;
			case '2': return MenuItem::MENU_ARBORESCENCE_CHECKER;*/
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
	vector<Settings::DirectoryConfig> directoriesArborescence( m_settings.GetDirectoriesArborescence() );

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

	cout << endl << "Check by nomenclature : " << m_settings.GetFileValidationConfig().checkByNomenclature << endl;
	cout << "Check by extension : " << m_settings.GetFileValidationConfig().checkByExtension << endl;

	cout << "Move Directory Path : " << m_settings.GetMoveDirectoryPath() << endl;
	cout << endl << "Arborescence Start Path : " << m_settings.GetArborescenceStartPath() << endl;
	cout << "nb of directories " << m_settings.GetDirectoriesArborescence().size() << endl;

	for( vector<Settings::DirectoryConfig>::iterator it = directoriesArborescence.begin();
		 it != directoriesArborescence.end(); ++it )
		cout << "Directory : " << it->name << endl;
}

void Application::NavigateThroughDirectories()
{
	m_status = APP_Status::S_RUNNING;

	std::vector<std::string> badFiles;

	for( const auto& directory : m_settings.GetDirectoriesArborescence() )
	{
		if( directory.name == "Bin" || directory.name == "FileChecker" ) // replace by DirectoryConfig of StartPath
			continue;

		CheckDirectory( m_settings.GetArborescenceStartPath(), directory, badFiles );
	}

	SendToBin( badFiles );
	LogFilesSent( badFiles );
}

void Application::CheckDirectory( std::string& _path, const Settings::DirectoryConfig& _directory, std::vector<std::string>& _badFiles )
{
	_path.append( _directory.name + "/" );

	Arborescence::CheckArborescence( _path, _directory, _badFiles );
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Nomenclature_Check ) == 0 )
		Nomenclature::CheckNomenclature( _path, m_settings.GetNomenclatureConfig(), _badFiles );
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Extension_Check ) == 0 )
		Extension::CheckFilesExtensions( _path, _directory, _badFiles );
	
	if( ( _directory.flags & (int)DirectoryFlags::Exclude_Recursive_Check ) == (int)DirectoryFlags::Exclude_Recursive_Check )
		return;

	for( const auto& subDir : _directory.subDirectories )
		CheckDirectory( _path, subDir, _badFiles );
}

void Application::SendToBin( const std::vector<std::string>& _files )
{
	for( const auto& file : _files )
		FileManipulator::MoveFile( file, m_settings.GetMoveDirectoryPath() );
}

void Application::LogFilesSent( const std::vector<std::string>& _files )
{
	std::cout << "------------ Check Report ------------" <<std::endl;
	for( const auto& file : _files )
		std::cout << file << std::endl;

	std::cout << "Number of files sent to bin : " << _files.size() << std::endl;
}
