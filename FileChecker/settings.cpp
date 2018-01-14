#include "settings.h"
#include <fstream>
#include "JsonParser.h"
#include <iostream>
#include "fileManipulator.h"
#include "application_paths.h"

using namespace rapidjson;


Settings::Settings( const std::string& filePath )
{
	LoadSettings( filePath );
}

Settings::~Settings() {}

void Settings::MoveToBin( const std::unordered_set<std::string>& _files, const bool _logFiles )
{
	if( !FileManipulator::PathExists( BIN_DIRECTORY_PATH ) )
		CreateBinDirectory();

	for( const auto& file : _files )
		FileManipulator::MoveFile( file, BIN_DIRECTORY_PATH );

	if( _logFiles )
		LogFilesSentToBin( _files );
}

void Settings::CreateBinDirectory()
{
	FileManipulator::CreateDirectory( BIN_DIRECTORY_PATH );
}

void Settings::LogFilesSentToBin( const std::unordered_set<std::string>& _files )
{
	std::cout << "------------ Check Report ------------" << std::endl;
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
	Document parsedSettings( JSON_Parser::ParseFile( _filePath ) );

	if( parsedSettings.HasMember( "FileChecker configs" ) )
	{
		if( parsedSettings[ "FileChecker configs" ].HasMember( "Nomenclature" ) )
		{
			if( parsedSettings[ "FileChecker configs" ][ "Nomenclature" ].HasMember( "Separator" ) )
			{
				const Value& separator( parsedSettings[ "FileChecker configs" ][ "Nomenclature" ][ "Separator" ] );
				m_nomenclatureConfig.separator = separator.GetString()[ 0 ];
			}
			if( parsedSettings[ "FileChecker configs" ][ "Nomenclature" ].HasMember( "Definitions" ) )
			{
				const Value& definitions( parsedSettings[ "FileChecker configs" ][ "Nomenclature" ][ "Definitions" ] );
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
		if( parsedSettings[ "FileChecker configs" ].HasMember( "MoveDirectory" ) )
		{
			if( parsedSettings[ "FileChecker configs" ][ "MoveDirectory" ].HasMember( "Path" ) )
			{
				const Value& moveDirectoryPath( parsedSettings[ "FileChecker configs" ][ "MoveDirectory" ][ "Path" ] );
				m_moveDirectoryPath = moveDirectoryPath.GetString();
			}
			if( parsedSettings[ "FileChecker configs" ][ "MoveDirectory" ].HasMember( "Move_Associated_Files" ) )
			{
				const Value& associatedFile( parsedSettings[ "FileChecker configs" ][ "MoveDirectory" ][ "Move_Associated_Files" ] );
				for( Value::ConstValueIterator mit = associatedFile.Begin(); mit != associatedFile.End(); ++mit )
					m_associatedFiles.push_back( mit->GetString() );
			}
		}
	}

	if( parsedSettings.HasMember( "Arborescence" ) )
	{
		if( parsedSettings[ "Arborescence" ].HasMember( "Directories" ) )
		{
			const Value& directories = parsedSettings[ "Arborescence" ][ "Directories" ];

			for( Value::ConstValueIterator it = directories.Begin(); it != directories.End(); ++it ) //FIXME that's bad, transform "Directories into object instead
			{
				//m_directoriesArborescence.push_back( CreateDirectoryConfig( ( *it ) ) );
				m_arborescenceRootDirectory = CreateDirectoryConfig( ( *it ) );
			}

			//Move That somewhere else
			DirectoryConfig binDirectory;

			int flags = (int)DirectoryConfig::DirectoryFlags::Exclude_Extension_Check | (int)DirectoryConfig::DirectoryFlags::Exclude_Nomenclature_Check
				| (int)DirectoryConfig::DirectoryFlags::Exclude_Recursive_Check;
			
			binDirectory.flags = flags;
			binDirectory.name = "Bin";
			m_arborescenceRootDirectory.subDirectories.push_back( binDirectory );

			DirectoryConfig fileDirectory;
			fileDirectory.flags = flags;
			fileDirectory.name = "FileChecker";
			m_arborescenceRootDirectory.subDirectories.push_back( fileDirectory );

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
	{
		newDir.name = value[ "Name" ].GetString();
	}

	if( value.HasMember( "Exclude_Nomenclature_Check" ) && value[ "Exclude_Nomenclature_Check" ].GetBool() )
	{
		newDir.flags |= (int)DirectoryConfig::DirectoryFlags::Exclude_Nomenclature_Check;
	}

	if( value.HasMember( "Exclude_Extension_Check" ) && value[ "Exclude_Extension_Check" ].GetBool() )
	{
		newDir.flags |= (int)DirectoryConfig::DirectoryFlags::Exclude_Extension_Check;
	}

	if( value.HasMember( "Exclude_Recursive_Checks" ) && value[ "Exclude_Recursive_Checks" ].GetBool() )
	{
		newDir.flags |= (int)DirectoryConfig::DirectoryFlags::Exclude_Recursive_Check;
	}

	if( ( newDir.flags & (int)DirectoryConfig::DirectoryFlags::Exclude_Extension_Check ) == 0
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
