#include <iostream>
#include "fileChecks.h"
#include "fileManipulator.h"
#include <vector>
#include "UString.h"
#include <algorithm>

typedef Settings::DirectoryConfig::DirectoryFlags DirectoryFlags;

using namespace std;

bool AnyOf( const vector<string>& _strVector, const string& _str )
{
	return any_of( _strVector.begin(), _strVector.end(),
				   [&_str]( const string& _s ) { return ( _s.compare( _str ) == 0 ); } );
}

void RemoveAssociatedFiles( fs::path _file, unordered_set<string>& _badFiles,
							const vector<string>& _associatedFiles )
{
	for( const auto& associatedFileExtension : _associatedFiles )
	{
		_file.replace_extension( associatedFileExtension );
		_badFiles.insert( _file.string() );
	}
}

namespace Nomenclature
{
	namespace
	{
		bool CompareNomenclature( const fs::path& _file, const Settings::NomenclatureConfig& _nomenclatureConfig,
								  const vector<string>& _associatedFiles )
		{
			if( _associatedFiles.size() > 0 && AnyOf( _associatedFiles, _file.extension().string() ) ) return true;

			vector<string> fileName( uString::split( _file.filename().string(), _nomenclatureConfig.separator ) );

			if( _nomenclatureConfig.definitions.size() > fileName.size() ) return false;

			for( int i = 0; i < _nomenclatureConfig.definitions.size(); ++i )
			{
				if( _nomenclatureConfig.definitions[ i ].size() == 0 ) continue;

				if( !any_of( _nomenclatureConfig.definitions[ i ].begin(), _nomenclatureConfig.definitions[ i ].end(),
					[&i, &fileName]( const string _definition ) { return ( _definition.compare( fileName[ i ] ) == 0 ); } ) )
					return false;
			}
			return true;
		}
	}

	void CheckNomenclature( const string& _path, const Settings::NomenclatureConfig& _nomenclatureConfig,
							unordered_set<string>& _badFiles, const vector<string>& _associatedFiles )
	{
		for( auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CompareNomenclature( file, _nomenclatureConfig, _associatedFiles ) )
			{
				_badFiles.insert( file );
				if( _associatedFiles.size() > 0 )
				{
					RemoveAssociatedFiles( file, _badFiles, _associatedFiles );
				}
			}
		}
	}


}

namespace Arborescence
{
	void CheckArborescence( const string& _path, const Settings::DirectoryConfig& _directory,
							unordered_set<string>& _badFiles, const vector<string>& _associatedFiles )
	{
		vector<string> explorerSubDirs = FileManipulator::GetDirectoriesAtPath( _path );

		for( const auto& arboSubDir : _directory.subDirectories )
		{
			cout << "arbo check : " << arboSubDir.name << endl;
			if( !FileManipulator::DirectoryContainsFile( _path, _path + arboSubDir.name ) )
				FileManipulator::CreateDirectory( _path + arboSubDir.name );
			else
				explorerSubDirs.erase( find( explorerSubDirs.begin(), explorerSubDirs.end(), _path + arboSubDir.name ) );
		}

		for( const auto& explorerSubDir : explorerSubDirs )
		{
			_badFiles.insert( explorerSubDir );
			if( _associatedFiles.size() > 0 )
				RemoveAssociatedFiles( _path, _badFiles, _associatedFiles );
		}

		explorerSubDirs.clear();
	}
}

namespace Extension
{
	namespace
	{
		bool CheckFileExtension( const fs::path _file, const vector<string>& _extensions )
		{
			if( !_file.has_extension() ) return false;
			if( _extensions.size() == 0 ) return false;

			return AnyOf( _extensions, _file.extension().string() );
		}
	}

	void CheckFilesExtensions( const string & _path, const Settings::DirectoryConfig & _dirConfig,
							   unordered_set<string>& _badFiles, const vector<string>& _associatedFiles )
	{
		if( _dirConfig.extensionRestricts.size() == 0 ) return;
		for( const auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CheckFileExtension( file, _dirConfig.extensionRestricts ) )
			{
				_badFiles.insert( file );
				if( _associatedFiles.size() > 0 )
					RemoveAssociatedFiles( file, _badFiles, _associatedFiles );
			}
		}
	}
}
