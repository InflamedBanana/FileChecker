#pragma once
#ifndef DEF_FILEMANIP
#define DEF_FILEMANIP

#include <string>
#include <set>
#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace FileManipulator
{
	std::set<fs::path> GetFilesInDirectory(const std::string &directory);
	std::set<fs::path> GetDirectoriesAtPath(const std::string &directory);
	std::set<fs::path> GetAllFilesInRecursiveDirectory(const std::string &directory, const std::set<fs::path> *exceptions = nullptr );
	bool MoveFile(const fs::path &file, const fs::path &destination);
	bool RenameFile(const fs::path &file, const std::string &newName, const bool &addExtension = false);
};

#endif // !DEF_FILEMANIP
