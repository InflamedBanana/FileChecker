#pragma once
#ifndef DEF_FILEMANIP
#define DEF_FILEMANIP

#include <string>
#include <set>
#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace FileManipulator
{
	std::vector<std::string> GetFilesInDirectory( const std::string &directory );
	std::vector<std::string> GetDirectoriesAtPath( const std::string &directory );
	std::string GetDirectoryAtPath( const std::string& _directoryPath, const std::string& _directoryName );
	bool DirectoryContainsFile( const std::string& _directoryPath, const std::string& _fileName );
	std::set<fs::path> GetAllFilesInRecursiveDirectory( const std::string &directory, const std::set<fs::path> *exceptions = nullptr );
	bool MoveFile( const std::string &_filePath, const std::string &_destinationPath );
	bool RenameFile( const std::string &_filePath, const std::string &newName );
	bool CreateDirectory( const std::string& _dirPath );
};

#endif // !DEF_FILEMANIP
