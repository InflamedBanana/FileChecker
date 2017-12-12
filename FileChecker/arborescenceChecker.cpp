#include "arborescenceChecker.h"
#include "fileManipulator.h"
#include <algorithm>
#include <string>
#include <algorithm>
#include <iostream>

ArborescenceChecker::ArborescenceChecker() : m_status( APP_Status::S_STARTED ) {}
ArborescenceChecker::~ArborescenceChecker() {}

ArborescenceChecker* ArborescenceChecker::s_arborescenceChkr = nullptr;

void ArborescenceChecker::Start( Settings& settings )
{
	if( s_arborescenceChkr != nullptr ) return;

	s_arborescenceChkr = new ArborescenceChecker;
	s_arborescenceChkr->Run( settings );
}

void ArborescenceChecker::Stop()
{
	delete s_arborescenceChkr;
	s_arborescenceChkr = nullptr;
}

void ArborescenceChecker::Run( Settings& settings )
{
	// Check For All Root Directories ( from settings.GetStartPath() )
	std::cout << "Arborescence Checker running" << std::endl;
	for( const auto& directory : *settings.GetDirectoriesArborescence() )
	{
		std::cout << "Check Directory " << directory.name << std::endl;
		if( FileManipulator::GetDirectoryAtPath( settings.GetArborescenceStartPath(), directory.name ) == "" )
			FileManipulator::CreateDirectory( settings.GetArborescenceStartPath() + directory.name );

		if( directory.name == "Bin" || directory.name == "FileChecker" ) // Really crappy
			continue;

		CheckDirectory( settings.GetArborescenceStartPath(), directory, settings );
	}
}

void ArborescenceChecker::CheckDirectory( std::string _path, const Settings::DirectoryConfig& _directory, const Settings& _settings )
{
	_path.append( _directory.name + "/" );

	std::vector<std::string> currentSubDirectories = FileManipulator::GetDirectoriesAtPath( _path );
	
	for( const auto& currentSubDir : currentSubDirectories )
		std::cout << "current sub dir " << currentSubDir << std::endl;

	/*for( const auto& currentDir : currentSubDirectories )
	{
		
	}*/

	for( const auto& subDir : _directory.subDirectories )
	{
		std::vector<std::string>::iterator it;

		std::cout << "subdir " << _path + subDir.name << std::endl;

		if( !FileManipulator::DirectoryContainsFile( _path, _path + subDir.name ) )
			FileManipulator::CreateDirectory( _path + subDir.name );
		else
			currentSubDirectories.erase( it ); // should not erase
	}

	for( const auto& subDir : currentSubDirectories )
		FileManipulator::MoveFile( subDir, _settings.GetMoveDirectoryPath() );

	currentSubDirectories.clear();

	if( !_directory.excludeFromExtensionCheck )
		CheckFilesExtensionInDirectory(_path, _directory.extensionRestricts, _settings);

	if( _directory.excludeRecursiveChecks ) return;

	for( const auto& subDir : _directory.subDirectories )
		CheckDirectory( _path, subDir, _settings );
	//Check each directories & Recursive directories, see if they exist. If not create it. If a directory exist and it shouldn't, move it to bin
}

void ArborescenceChecker::CheckFilesExtensionInDirectory( const std::string _directory, const std::vector<std::string>& _extensions, const Settings& _settings )
{
	//Check directory files extensions to match directory settings
	for( auto& file : FileManipulator::GetFilesInDirectory( _directory ) )
		if( !CheckFileExtension( file, _extensions ) )
			FileManipulator::MoveFile( file, _settings.GetMoveDirectoryPath() );
}

bool ArborescenceChecker::CheckFileExtension( const fs::path _file, const std::vector<std::string>& _extensions )
{
	if( !_file.has_extension() ) return false;
	if( _extensions.size() < 1 ) return false;

	return std::any_of( _extensions.begin(), _extensions.end(), [&_file]( const std::string& _str ) { return _str.compare( _file.extension().string() ); } );

	/*bool hasWrongExtension(true);

	for (const auto& ext : _extension)
		if (ext.compare(_file.extension().string()) == 0 )
				hasWrongExtension = false;

	return hasWrongExtension;*/
}
