//#include "arborescenceChecker.h"
//#include "fileManipulator.h"
//#include <algorithm>
//#include <string>
//#include <algorithm>
//#include <iostream>
//
//typedef Settings::DirectoryConfig::DirectoryFlags DirectoryFlags;
//
//ArborescenceChecker::ArborescenceChecker() : m_status( APP_Status::S_STARTED ) {}
//ArborescenceChecker::~ArborescenceChecker() {}
//
//ArborescenceChecker* ArborescenceChecker::s_arborescenceChkr = nullptr;
//
//void ArborescenceChecker::Start( Settings& settings )
//{
//	if( s_arborescenceChkr != nullptr ) return;
//
//	s_arborescenceChkr = new ArborescenceChecker;
//	s_arborescenceChkr->Run( settings );
//}
//
//void ArborescenceChecker::Stop()
//{
//	delete s_arborescenceChkr;
//	s_arborescenceChkr = nullptr;
//}
//
//void ArborescenceChecker::Run( Settings& _settings )
//{
//	// Check For All Root Directories ( from settings.GetStartPath() )
//	std::cout << "Arborescence Checker running" << std::endl;
//	for( const auto& directory : _settings.GetDirectoriesArborescence() )
//	{
//		std::cout << "Check Directory " << directory.name << std::endl;
//		/*if( FileManipulator::GetDirectoryAtPath( settings.GetArborescenceStartPath(), directory.name ) == "" )
//			FileManipulator::CreateDirectory( settings.GetArborescenceStartPath() + directory.name );*/
//
//		if( !FileManipulator::DirectoryContainsFile( _settings.GetArborescenceStartPath(), directory.name ) )
//			FileManipulator::CreateDirectory( _settings.GetArborescenceStartPath() + directory.name );
//
//		if( directory.name == "Bin" || directory.name == "FileChecker" ) // Really crappy
//			continue;
//
//		CheckDirectory( _settings.GetArborescenceStartPath(), directory, _settings );
//
//		Stop();
//	}
//}
//
//void ArborescenceChecker::CheckDirectory( std::string _path, const Settings::DirectoryConfig& _directory, const Settings& _settings )
//{
//	_path.append( _directory.name + "/" );
//
//	std::vector<std::string> explorerSubDirs = FileManipulator::GetDirectoriesAtPath( _path );
//
//	for( const auto& arboSubDir : _directory.subDirectories )
//	{
//		if( !FileManipulator::DirectoryContainsFile( _path, _path + arboSubDir.name ) )
//			FileManipulator::CreateDirectory( _path + arboSubDir.name );
//		else
//			explorerSubDirs.erase( std::find( explorerSubDirs.begin(), explorerSubDirs.end(), _path + arboSubDir.name ) ); // should work
//	}
//
//	for( const auto& explorerSubDir : explorerSubDirs )
//		FileManipulator::MoveFile( explorerSubDir, _settings.GetMoveDirectoryPath() );
//
//	explorerSubDirs.clear();
//	
//	//if( !_directory.excludeFromExtensionCheck )
//	//if(_directory.flags & 
//	if( _directory.flags & DirectoryFlags::Exclude_Extension_Check != DirectoryFlags::Exclude_Extension_Check )
//		CheckFilesExtensionInDirectory( _path, _directory.extensionRestricts, _settings );
//
//	//if( _directory.excludeRecursiveChecks ) return;
//	if( _directory.flags & DirectoryFlags::Exclude_Recursive_Check == DirectoryFlags::Exclude_Recursive_Check ) return;
//
//	for( const auto& subDir : _directory.subDirectories )
//		CheckDirectory( _path, subDir, _settings );
//}
//
//void ArborescenceChecker::CheckFilesExtensionInDirectory( const std::string _directory, const std::vector<std::string>& _extensions, const Settings& _settings )
//{
//	//Check directory files extensions to match directory settings
//	for( auto& file : FileManipulator::GetFilesInDirectory( _directory ) )
//		if( !CheckFileExtension( file, _extensions ) )
//			FileManipulator::MoveFile( file, _settings.GetMoveDirectoryPath() );
//}
//
//bool ArborescenceChecker::CheckFileExtension( const fs::path _file, const std::vector<std::string>& _extensions )
//{
//	if( !_file.has_extension() ) return false;
//	if( _extensions.size() < 1 ) return false;
//
//	return std::any_of( _extensions.begin(), _extensions.end(), [&_file]( const std::string& _str ) { return _str.compare( _file.extension().string() ); } );
//}
//
//namespace Arborescence
//{
//	void CheckArborescence( const std::string& _path, const Settings::DirectoryConfig& _directory, std::vector<std::string>& _badFiles )
//	{
//
//		std::vector<std::string> explorerSubDirs = FileManipulator::GetDirectoriesAtPath( _path );
//
//		for( const auto& arboSubDir : _directory.subDirectories )
//		{
//			if( !FileManipulator::DirectoryContainsFile( _path, _path + arboSubDir.name ) )
//				FileManipulator::CreateDirectory( _path + arboSubDir.name );
//			else
//				explorerSubDirs.erase( std::find( explorerSubDirs.begin(), explorerSubDirs.end(), _path + arboSubDir.name ) ); // should work
//		}
//
//		for( const auto& explorerSubDir : explorerSubDirs )
//			_badFiles.push_back( explorerSubDir );
//			//FileManipulator::MoveFile( explorerSubDir, _settings.GetMoveDirectoryPath() );
//
//		explorerSubDirs.clear();
//
//	}
//}
