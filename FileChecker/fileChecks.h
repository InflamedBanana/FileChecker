#pragma once
#ifndef DEF_FILECHECK
#define DEF_FILECHECK

#include <string>
#include "settings.h"
#include <unordered_set>

namespace Nomenclature
{
	void CheckNomenclature( const std::string& _path, const Settings::NomenclatureConfig& _nomenclatureConfig, 
							std::unordered_set<std::string>& _badFiles, const std::vector<std::string>& _associatedFiles );
}

namespace Arborescence
{
	void CheckArborescence( const std::string& _path, const Settings::DirectoryConfig& _directory,
							std::unordered_set<std::string>& _badFiles, const std::vector<std::string>& _associatedFiles,
							const std::vector<std::string>& _exceptions );
}

namespace Extension
{
	void CheckFilesExtensions( const std::string& _path, const Settings::DirectoryConfig& _dirConfig
							   , std::unordered_set<std::string>& _badFiles, const std::vector<std::string>& _associatedFiles );
}

#endif