#include "fileChecks.h"
#include "fileManipulator.h"
#include <vector>
#include "UString.h"
#include <algorithm>

typedef Settings::DirectoryConfig::DirectoryFlags DirectoryFlags;

namespace Nomenclature
{
	namespace
	{
		bool CompareNomenclature( const fs::path& _file, const Settings::NomenclatureConfig& _nomenclatureConfig )
		{
			std::vector<std::string> fileName( uString::split( _file.filename().string(), _nomenclatureConfig.separator ) );

			if( _nomenclatureConfig.definitions.size() > fileName.size() ) return false;

			for( int i = 0; i < _nomenclatureConfig.definitions.size(); ++i )
			{
				if( _nomenclatureConfig.definitions[ i ].size() == 0 ) continue;


				if( !std::any_of( _nomenclatureConfig.definitions[ i ].begin(), _nomenclatureConfig.definitions[ i ].end(),
					[&i, &fileName]( const std::string _definition ) { return ( _definition.compare( fileName[ i ] ) == 0 ); } ) )
					return false;
			}
			return true;
		}
	}

	void CheckNomenclature( const std::string& _path, const Settings::NomenclatureConfig& _nomenclatureConfig, std::unordered_set<std::string>& _badFiles )
	{
		for( auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CompareNomenclature( file, _nomenclatureConfig ) )
				_badFiles.insert( file );
		}
		_badFiles.insert( "Nomenclature" );
	}


}

namespace Arborescence
{
	void CheckArborescence( const std::string& _path, const Settings::DirectoryConfig& _directory, std::unordered_set<std::string>& _badFiles )
	{
		std::vector<std::string> explorerSubDirs = FileManipulator::GetDirectoriesAtPath( _path );

		for( const auto& arboSubDir : _directory.subDirectories )
		{
			if( !FileManipulator::DirectoryContainsFile( _path, _path + arboSubDir.name ) )
				FileManipulator::CreateDirectory( _path + arboSubDir.name );
			else
				explorerSubDirs.erase( std::find( explorerSubDirs.begin(), explorerSubDirs.end(), _path + arboSubDir.name ) );
		}

		for( const auto& explorerSubDir : explorerSubDirs )
			_badFiles.insert( explorerSubDir );

		explorerSubDirs.clear();

	}
}

namespace Extension
{
	namespace
	{
		bool CheckFileExtension( const fs::path _file, const std::vector<std::string>& _extensions )
		{
			if( !_file.has_extension() ) return false;
			if( _extensions.size() == 0 ) return false;

			return std::any_of( _extensions.begin(), _extensions.end(), [&_file]( const std::string& _str ) { return ( _str.compare( _file.extension().string() ) == 0 ); } );
		}
	}

	void CheckFilesExtensions( const std::string & _path, const Settings::DirectoryConfig & _dirConfig, std::unordered_set<std::string>& _badFiles )
	{
		for( const auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CheckFileExtension( file, _dirConfig.extensionRestricts ) )
				_badFiles.insert( file );
		}

		_badFiles.insert( "file Extension" );
	}
}
