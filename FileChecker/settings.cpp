#define _CRT_SECURE_NO_WARNINGS 1

#include "settings.h"
#include <fstream>
#include "JsonParser.h"
#include <iostream>
#include "fileManipulator.h"
#include "application_paths.h"
#include <sstream>
#include <time.h>

using namespace rapidjson;

Settings::Settings( const std::string& filePath )
{
	LoadSettings( filePath );
}

Settings::~Settings() {}

void Settings::WriteLogs( const std::unordered_set<std::string>& _files, const bool _logFiles )
{
	if( !FileManipulator::PathExists( LOG_DIRECTORY_PATH ) )
		FileManipulator::CreateDirectory( LOG_DIRECTORY_PATH );

	std::stringstream logs("");

	time_t currentTime( time( nullptr ) );
	struct tm* timeInfos( localtime( &currentTime ) );
	std::string timeStr;
	timeStr.append( std::to_string( timeInfos->tm_mday ) + "_" 
					+ std::to_string( timeInfos->tm_mon + 1) + "_" 
					+ std::to_string( timeInfos->tm_hour ) + "_"
					+ std::to_string( timeInfos->tm_min ) + "_" 
					+ std::to_string( timeInfos->tm_sec ) );

	logs << "---- Log file for the FileChecker tool ----" << std::endl;
	logs << " - Report from " << asctime( timeInfos ) << " : " << _files.size() << " wrong files." << std::endl << std::endl;

	for( const auto& text : _files )
		logs << text.c_str() << std::endl;
	std::string fileName( "FileChecker_Logs_" );
	fileName.append( timeStr );
	
	if( _logFiles )
		LogFilesSentToBin( _files );

	if( !FileManipulator::CreateTextFile( LOG_DIRECTORY_PATH, fileName, logs ) )
		std::cout << "Couln't Create Log File..."<< std::endl;
}

//void Settings::MoveToBin( const std::unordered_set<std::string>& _files, const bool _logFiles )
//{
//	if( !FileManipulator::PathExists( BIN_DIRECTORY_PATH ) )
//		CreateBinDirectory();
//
//	for( const auto& file : _files )
//		FileManipulator::MoveFile( file, BIN_DIRECTORY_PATH );
//
//	if( _logFiles )
//		LogFilesSentToBin( _files );
//}

//void Settings::CreateBinDirectory()
//{
//	FileManipulator::CreateDirectory( BIN_DIRECTORY_PATH );
//}

void Settings::LogFilesSentToBin( const std::unordered_set<std::string>& _files )
{
	std::cout << std::endl << "------------ Check Report ------------" << std::endl;
	for( const auto& file : _files )
		std::cout << file << std::endl;

	std::cout << "Number of files sent to bin : " << _files.size() << std::endl;
}

bool Settings::LoadSettings( const std::string& _filePath )
{
	// create directories with jsonparser;
	if( !FileManipulator::PathExists( _filePath ) )
	{
		JSON_Parser::GenerateConfigFile( _filePath );

		std::cout << "-------------------" << std::endl;
		std::cout << "Config File created" << std::endl;
		std::cout << "-------------------" << std::endl << std::endl;
		return false;
	}
	Document* parsedSettings = new Document;

	if( !JSON_Parser::ParseFile( _filePath, parsedSettings ) )
		return false;

	Value* parentValue = &(*parsedSettings)["FileChecker configs"];

	if( parsedSettings->HasMember( "FileChecker configs" ) )
	{
		Value* childValue = parentValue;

		if( parentValue->HasMember( "Nomenclature" ) )
		{
			childValue = &( *parentValue )[ "Nomenclature" ];

			if( childValue->HasMember( "Separator" ) )
			{
				const Value& separator( (*childValue)[ "Separator" ] );
				m_nomenclatureConfig.separator = separator.GetString()[ 0 ];
			}


			if( childValue->HasMember( "Definitions" ) )
			{
				const Value& definitions( (*childValue)[ "Definitions" ] );

				if( definitions.IsObject() )
				{
					for( Value::ConstMemberIterator mit = definitions.GetObject().MemberBegin(); mit != definitions.GetObject().MemberEnd();
						 ++mit )
					{
						std::vector<std::string> defArray;
						for( Value::ConstValueIterator vit = mit->value.Begin(); vit != mit->value.End(); ++vit )
							defArray.push_back( vit->GetString() );

						m_nomenclatureConfig.definitions.push_back( defArray );
						m_nomenclatureConfig.nomenclature.push_back( mit->name.GetString() );
					}
				}
			}
		}

		/*if( parentValue->HasMember( "Log_Options" ) )
		{*/
			//childValue = &( *parentValue )[ "Log_Options" ];
			/*if( childValue->HasMember( "Path" ) )
			{
				const Value& moveDirectoryPath( (*childValue)[ "Path" ] );
				m_moveDirectoryPath = moveDirectoryPath.GetString();
			}*/

			if( parentValue->HasMember( "Associated_Files" ) )
			{
				const Value& associatedFile( (*parentValue)[ "Associated_Files" ] );

				for( auto mit = associatedFile.Begin(); mit != associatedFile.End(); ++mit )
					m_associatedFiles.push_back( mit->GetString() );
			}

			if( parentValue->HasMember( "Directory_Names_Exceptions" ) )
			{
				const Value& directoriesExceptions( ( *parentValue )[ "Directory_Names_Exceptions" ] );

				for( auto mit = directoriesExceptions.Begin(); mit != directoriesExceptions.End(); ++mit )
					m_directoriesExceptions.push_back( mit->GetString() );
			}
		//}
	}

	if( parsedSettings->HasMember( "Arborescence" ) )
	{
		parentValue = &( *parsedSettings )[ "Arborescence" ];

		if( parentValue->HasMember( "Directories" ) )
		{
			const Value& directories = (*parentValue)[ "Directories" ];

			for( Value::ConstValueIterator it = directories.Begin(); it != directories.End(); ++it ) //FIXME that's bad, transform "Directories into object instead
			{
				//m_directoriesArborescence.push_back( CreateDirectoryConfig( ( *it ) ) );
				m_arborescenceRootDirectory = CreateDirectoryConfig( ( *it ) );
			}

			////Move That somewhere else
			//DirectoryConfig binDirectory;

			//int flags = (int)DirectoryConfig::DirectoryFlags::Exclude_Extension_Check | (int)DirectoryConfig::DirectoryFlags::Exclude_Nomenclature_Check
			//	| (int)DirectoryConfig::DirectoryFlags::Exclude_Recursive_Check;
			//
			//binDirectory.flags = flags;
			//binDirectory.name = "Bin";
			//m_arborescenceRootDirectory.subDirectories.push_back( binDirectory );

			//DirectoryConfig fileDirectory;
			//fileDirectory.flags = flags;
			//fileDirectory.name = "FileChecker";
			//m_arborescenceRootDirectory.subDirectories.push_back( fileDirectory );

			//m_arborescenceRootDirectory
		}
	}

	return true;
}

Settings::DirectoryConfig Settings::CreateDirectoryConfig( const Value& value )
{
	assert( value.IsObject() );

	Settings::DirectoryConfig newDir;

	if( value.HasMember( "Name" ) )
		newDir.name = value[ "Name" ].GetString();

	if( JSON_Parser::CheckBoolValue( value, "Exclude_Nomenclature_Check" ) )
		newDir.flags |= DIRFLAG_EXCL_NOMENCLATURE;

	if( JSON_Parser::CheckBoolValue( value, "Exclude_Extension_Check" ) )
		newDir.flags |= DIRFLAG_EXCL_EXTENSION;

	if( JSON_Parser::CheckBoolValue( value, "Exclude_Recursive_Check" ) )
		newDir.flags |= DIRFLAG_EXCL_RECURSIVE;

	if( ( newDir.flags & DIRFLAG_EXCL_EXTENSION ) == 0
		&& value.HasMember( "ExtensionRestrict" ) )
	{
		for( Value::ConstValueIterator it = value[ "ExtensionRestrict" ].Begin(); it != value[ "ExtensionRestrict" ].End(); ++it )
			newDir.extensionRestricts.push_back( it->GetString() );

		if( m_associatedFiles.size() > 0 )
		{
			for( const auto& associatedFile : m_associatedFiles )
				newDir.extensionRestricts.push_back( associatedFile );
		}
	}

	if( value.HasMember( "Directories" ) )
	{
		for( Value::ConstValueIterator it = value[ "Directories" ].Begin(); it != value[ "Directories" ].End(); ++it )
			newDir.subDirectories.push_back( CreateDirectoryConfig( ( *it ) ) );
	}

	return newDir;
}
