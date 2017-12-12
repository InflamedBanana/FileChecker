#include <iostream>
//#include <string>
#include <sstream>
#include "nomenclatureChecker.h"
#include "fileManipulator.h"
#include <vector>
#include "UString.h"

using namespace std;

NomenclatureChecker::NomenclatureChecker() : m_status( APP_Status::S_STARTED ), m_nbOfFilesChecked( 0 ),
m_nbOfWrongFiles( 0 ) {}

NomenclatureChecker::~NomenclatureChecker() {}

NomenclatureChecker* NomenclatureChecker::s_nomenclatureChkr = nullptr;

void NomenclatureChecker::Start( Settings& settings )
{
	if( s_nomenclatureChkr != nullptr ) return;

	s_nomenclatureChkr = new NomenclatureChecker;
	s_nomenclatureChkr->Run( settings );
}

void NomenclatureChecker::Stop()
{
	s_nomenclatureChkr->m_status = APP_Status::S_STOPPED;
	delete s_nomenclatureChkr;
	s_nomenclatureChkr = nullptr;
}

void NomenclatureChecker::Run( Settings& settings )
{
	m_status = APP_Status::S_RUNNING;

	for( auto& directory : *( settings.GetDirectoriesArborescence() ) ) //every root directories
		CheckDirectory( settings.GetArborescenceStartPath(), directory, settings );

	cout << endl << "Number of files checked : " << m_nbOfFilesChecked << '.' << endl;
	cout << "Number of wrong files : " << m_nbOfWrongFiles << '.' << endl;

	Stop();
}

void NomenclatureChecker::CheckDirectory( fs::path _path, Settings::DirectoryConfig& _directory, Settings& _settings )
{
	_path.append( _directory.name ) / "/";

	if( !_directory.excludeFromNomenclatureCheck )
	{
		for( auto& file : FileManipulator::GetFilesInDirectory( _path.string() ) )
		{
			if( !CompareNomenclature( file, _settings ) )
			{
				FileManipulator::MoveFile( file, _settings.GetMoveDirectoryPath() );
				++m_nbOfWrongFiles;
			}

			cout << file << endl;
			++m_nbOfFilesChecked;
		}
	}

	if( _directory.excludeRecursiveChecks ) return;

	for( auto& subDirectory : _directory.subDirectories )
		CheckDirectory( _path, subDirectory, _settings );
}

bool NomenclatureChecker::CompareNomenclature( const fs::path &file, Settings &settings )
{
	//vector<string> fileName(SplitFileName(file, settings));
	vector<string> fileName( uString::Split( file.filename().string(), settings.GetNomenclatureConfig()->separator ) );


	for( int i = 0; i < settings.GetNomenclatureConfig()->definitions.size(); ++i )
	{
		if( i >= fileName.size() ) return false;
		if( settings.GetNomenclatureConfig()->definitions[ i ].size() == 0 ) return true;

		bool isBadlyNamed( true );

		for( const auto& nDef : settings.GetNomenclatureConfig()->definitions[ i ] )
			if( fileName[ i ].compare( nDef ) == 0 ) isBadlyNamed = false;

		if( isBadlyNamed ) return false;
	}
	return true;
}
