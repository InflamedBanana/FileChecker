#include "fileManipulator.h"

namespace FileManipulator
{
	using namespace std;

	set<fs::path> GetFilesInDirectory(const string &directory)
	{
		set<fs::path> files;

		for (const auto& file : fs::directory_iterator(directory))
			if (fs::is_regular_file(file))
				files.insert(file);

		return files;
	}

	set<fs::path> GetDirectoriesAtPath(const string &directory)
	{
		set<fs::path> files;

		for (const auto& file : fs::directory_iterator(directory))
			if ( fs::is_directory(file) )
				files.insert(file);

		return files;
	}

	set<fs::path> GetAllFilesInRecursiveDirectory(const string &directory, const std::set<fs::path> *exceptions)
	{
		set<fs::path> files;

		for ( auto& file : fs::recursive_directory_iterator(directory))
		{
			if ( exceptions != nullptr && exceptions->find(file) != exceptions->end() )
				continue;
			else if ( fs::is_regular_file(file) )
				files.insert(file);
		}

		return files;
	}

	bool RenameFile(const fs::path &filePath, const string &newName, const bool &addExtension)
	{
		std::string newFileName(newName);

		if( addExtension )
			newFileName.append( filePath.extension().string() );

		return MoveFile(filePath, fs::path(filePath).replace_filename(newFileName) );
	}
	bool MoveFile(const fs::path &filePath, const fs::path &destinationPath)
	{
		error_code error;
		fs::rename(filePath, destinationPath, error);

		return ( error.value() == 0 );
	}
}