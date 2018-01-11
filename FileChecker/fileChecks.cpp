#include <iostream>
//#include <string>
//#include <sstream>
#include "fileChecks.h"
#include "fileManipulator.h"
#include <vector>
#include "UString.h"
#include <algorithm>

typedef Settings::DirectoryConfig::DirectoryFlags DirectoryFlags;

//using namespace std;

//NomenclatureChecker::NomenclatureChecker() : m_status( APP_Status::S_STARTED ), m_nbOfFilesChecked( 0 ),
//m_nbOfWrongFiles( 0 ) {}
//
//NomenclatureChecker::~NomenclatureChecker() {}
//
//NomenclatureChecker* NomenclatureChecker::s_nomenclatureChkr = nullptr;
//
//void NomenclatureChecker::Start( Settings& settings )
//{
//	if( s_nomenclatureChkr != nullptr ) return;
//
//	s_nomenclatureChkr = new NomenclatureChecker;
//	s_nomenclatureChkr->Run( settings );
//}
//
//void NomenclatureChecker::Stop()
//{
//	s_nomenclatureChkr->m_status = APP_Status::S_STOPPED;
//	delete s_nomenclatureChkr;
//	s_nomenclatureChkr = nullptr;
//}
//
//void NomenclatureChecker::Run( Settings& settings )
//{
//	m_status = APP_Status::S_RUNNING;
//
//	for( auto& directory :  settings.GetDirectoriesArborescence() ) //every root directories
//		CheckDirectory( settings.GetArborescenceStartPath(), directory, settings );
//
//	cout << endl << "Number of files checked : " << m_nbOfFilesChecked << '.' << endl;
//	cout << "Number of wrong files : " << m_nbOfWrongFiles << '.' << endl;
//
//	Stop();
//}
//
//void NomenclatureChecker::CheckDirectory( fs::path _path, Settings::DirectoryConfig& _directory, Settings& _settings )
//{
//	_path.append( _directory.name ) / "/";
//
//	//if( !_directory.excludeFromNomenclatureCheck )
//	if( _directory.flags & DirectoryFlags::Exclude_Nomenclature_Check != DirectoryFlags::Exclude_Nomenclature_Check )
//	{
//		for( auto& file : FileManipulator::GetFilesInDirectory( _path.string() ) )
//		{
//			if( !CompareNomenclature( file, _settings ) )
//			{
//				FileManipulator::MoveFile( file, _settings.GetMoveDirectoryPath() );
//				++m_nbOfWrongFiles;
//			}
//
//			cout << file << endl;
//			++m_nbOfFilesChecked;
//		}
//	}
//
//	if( _directory.flags & DirectoryFlags::Exclude_Recursive_Check == DirectoryFlags::Exclude_Recursive_Check ) return;
//
//	for( auto& subDirectory : _directory.subDirectories )
//		CheckDirectory( _path, subDirectory, _settings );
//}
//
//bool NomenclatureChecker::CompareNomenclature( const fs::path &file, Settings &settings )
//{
//	//vector<string> fileName(SplitFileName(file, settings));
//	vector<string> fileName( uString::split( file.filename().string(), settings.GetNomenclatureConfig().separator ) );
//
//	for( int i = 0; i < settings.GetNomenclatureConfig().definitions.size(); ++i )
//	{
//		if( i >= fileName.size() ) return false;
//		if( settings.GetNomenclatureConfig().definitions[ i ].size() == 0 ) return true;
//
//		bool isBadlyNamed( true );
//
//		for( const auto& nDef : settings.GetNomenclatureConfig().definitions[ i ] )
//			if( fileName[ i ].compare( nDef ) == 0 ) isBadlyNamed = false;
//
//		if( isBadlyNamed ) return false;
//	}
//	return true;
//}

namespace Nomenclature
{
	namespace
	{
		bool CompareNomenclature( const std::string& _file, const Settings::NomenclatureConfig& _nomenclatureConfig )
		{
			std::vector<std::string> fileName( uString::split( _file, _nomenclatureConfig.separator ) );

			if( _nomenclatureConfig.definitions.size() > fileName.size() ) return false;

			for( int i = 0; i < _nomenclatureConfig.definitions.size(); ++i )
			{
				if( _nomenclatureConfig.definitions[ i ].size() == 0 ) continue;

				if( !any_of( _nomenclatureConfig.definitions[i].begin(), _nomenclatureConfig.definitions[i].end(),
					[&i, &fileName]( const std::string _definition ) { return fileName[ i ].compare( _definition ); } ) )
					return false;
			}
			return true;
		}
	}

	void CheckNomenclature(const std::string& _path, const Settings::NomenclatureConfig& _nomenclatureConfig, std::vector<std::string>& _badFiles )
	{
		for( auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CompareNomenclature( file, _nomenclatureConfig ) )
				_badFiles.push_back( file );
		}
		_badFiles.push_back( "Nomenclature" );
	}

	
}

namespace Arborescence
{
	void CheckArborescence( const std::string& _path, const Settings::DirectoryConfig& _directory, std::vector<std::string>& _badFiles )
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
			_badFiles.push_back( explorerSubDir );

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
			std::cout << "file : " << _file.string() << " file extension " << _file.extension().string() << std::endl;
			return std::any_of( _extensions.begin(), _extensions.end(), [&_file]( const std::string& _str ) { return _str.compare( _file.extension().string() ); } );
		}
	}

	void CheckFilesExtensions( const std::string & _path, const Settings::DirectoryConfig & _dirConfig, std::vector<std::string>& _badFiles )
	{
		std::cout << "directory : " << _dirConfig.name << std::endl;
		std::cout << "directory extensions :" << std::endl;
		for( const auto& ext : _dirConfig.extensionRestricts )
			std::cout << ext << std::endl;

		for( const auto& file : FileManipulator::GetFilesInDirectory( _path ) )
		{
			if( !CheckFileExtension( file, _dirConfig.extensionRestricts ) )
				_badFiles.push_back( file );
		}

		_badFiles.push_back( "file Extension" );
	}
}
