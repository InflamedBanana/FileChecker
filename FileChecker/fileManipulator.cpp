#include "fileManipulator.h"
#include <algorithm>

namespace FileManipulator
{
	using namespace std;

	vector<std::string> GetFilesInDirectory( const string &directory )
	{
		vector<std::string> files;

		for( const auto& file : fs::directory_iterator( directory ) )
			if( fs::is_regular_file( file ) )
				files.push_back( file.path().string() );

		return files;
	}

	vector<std::string> GetDirectoriesAtPath( const string &directory )
	{
		vector<std::string> files;

		for( const auto& file : fs::directory_iterator( directory ) )
		{
			if( fs::is_directory( file ) )
			{
				std::string str( file.path().string() );
				replace( str.begin(), str.end(), '\\', '/' );
				files.push_back( str );
			}
		}

		return files;
	}

	std::string GetDirectoryAtPath( const string& _directoryPath, const string& _directoryName )
	{
		for( const auto& file : fs::directory_iterator( _directoryPath ) )
			if( fs::is_directory( file ) && file.path().filename().compare( _directoryName ) == 0 )
				return file.path().string();

		return "";
	}

	set<fs::path> GetAllFilesInRecursiveDirectory( const string &directory, const std::set<fs::path> *exceptions )
	{
		set<fs::path> files;

		for( auto& file : fs::recursive_directory_iterator( directory ) )
		{
			if( exceptions != nullptr && exceptions->find( file ) != exceptions->end() )
				continue;
			else if( fs::is_regular_file( file ) )
				files.insert( file );
		}

		return files;
	}

	bool DirectoryContainsFile( const std::string& _directoryPath, const std::string& _fileName )
	{
		fs::path directory( _directoryPath ), fileToFind( _fileName );

		for( auto& file : fs::directory_iterator( directory ) )
			if( file.path() == fileToFind )
				return true;

		return false;
	}

	bool RenameFile( const std::string &_filePath, const string &newName )
	{
		fs::path filePath( _filePath );
		fs::path newFilePath( _filePath );
		newFilePath.replace_filename( newName );

		error_code error;

		fs::rename( filePath, newFilePath, error );
		return error.value() == 0;
	}

	bool MoveFile( const std::string &_filePath, const std::string &_destinationPath )
	{
		error_code error;
		fs::path file( _filePath ), destination( _destinationPath );

		fs::rename( file, destination / file.filename(), error );
		return error.value() == 0;
	}

	bool CreateDirectory( const std::string& _dirPath )
	{
		error_code error;
		fs::create_directories( _dirPath, error );

		return error.value() == 0;
	}

	bool PathExists( const std::string & _path )
	{
		return fs::exists( _path );;
	}
}