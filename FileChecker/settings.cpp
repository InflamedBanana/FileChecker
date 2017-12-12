#include "settings.h"
#include <fstream>
#include "JsonParser.h"
#include <iostream>
#include <memory>

//using namespace std;
using namespace rapidjson;


Settings::Settings(const std::string& filePath)
{
	LoadSettings(filePath);
}

Settings::~Settings(){}

void Settings::LoadSettings(const std::string& filePath)
{
	// create directories with jsonparser;
	if (!JSON_Parser::ConfigFileExists(filePath))
	{
		JSON_Parser::GenerateConfigFile(filePath);

		std::cout << "-------------------" << std::endl;
		std::cout << "Config File created" << std::endl;
		std::cout << "-------------------" << std::endl << std::endl;
	}
	Document parsedSettings(JSON_Parser::ParseFile(filePath));

	if (parsedSettings.HasMember("FileChecker configs"))
	{
		if (parsedSettings["FileChecker configs"].HasMember("Nomenclature"))
		{
			if (parsedSettings["FileChecker configs"]["Nomenclature"].HasMember("Separator"))
			{
				const Value& separator(parsedSettings["FileChecker configs"]["Nomenclature"]["Separator"]);
				m_nomenclatureConfig.separator = separator.GetString()[0];
			}
			if (parsedSettings["FileChecker configs"]["Nomenclature"].HasMember("Definitions"))
			{
				const Value& definitions(parsedSettings["FileChecker configs"]["Nomenclature"]["Definitions"]);
				if (definitions.IsObject())
				{
					for (Value::ConstMemberIterator mit = definitions.GetObject().MemberBegin(); mit != definitions.GetObject().MemberEnd();
						++mit)
					{
						std::vector<std::string> defArray;
						for (Value::ConstValueIterator vit = mit->value.Begin(); vit != mit->value.End(); ++vit)
							defArray.push_back(vit->GetString());

						m_nomenclatureConfig.definitions.push_back(defArray);
						m_nomenclatureConfig.nomenclature.push_back(mit->name.GetString());
					}
				}
			}
		}
		if (parsedSettings["FileChecker configs"].HasMember("ArborescenceConfig"))
		{
			if (parsedSettings["FileChecker configs"]["ArborescenceConfig"].HasMember("CheckByNomenclature"))
			{
				const Value& nomenclatureCheck(parsedSettings["FileChecker configs"]["ArborescenceConfig"]["CheckByNomenclature"]);
				m_fileValidationConfig.checkByNomenclature = nomenclatureCheck.GetBool();
			}
			if (parsedSettings["FileChecker configs"]["ArborescenceConfig"].HasMember("CheckByExtension"))
			{
				const Value& extensionCheck(parsedSettings["FileChecker configs"]["ArborescenceConfig"]["CheckByExtension"]);
				m_fileValidationConfig.checkByExtension = extensionCheck.GetBool();
			}
		}
		if (parsedSettings["FileChecker configs"].HasMember("MoveDirectory"))
		{
			if (parsedSettings["FileChecker configs"]["MoveDirectory"].HasMember("Path"))
			{
				const Value& moveDirectoryPath(parsedSettings["FileChecker configs"]["MoveDirectory"]["Path"]);
				m_moveDirectoryPath = moveDirectoryPath.GetString();
			}
		}
	}

	if (parsedSettings.HasMember("Arborescence"))
	{
		if (parsedSettings["Arborescence"].HasMember("StartPath"))
			m_arborescenceStartPath = parsedSettings["Arborescence"]["StartPath"].GetString();

		if (parsedSettings["Arborescence"].HasMember("Directories"))
		{
			const Value& directories = parsedSettings["Arborescence"]["Directories"];

			for (Value::ConstValueIterator it = directories.Begin(); it != directories.End(); ++it)
				m_directoriesArborescence.push_back(CreateDirectoryConfig((*it)));
		}
	}
}

Settings::DirectoryConfig Settings::CreateDirectoryConfig(const Value& value)
{
	Settings::DirectoryConfig newDir;

	if (!value.IsObject()) return newDir;

	if (value.HasMember("Name"))
		newDir.name = value["Name"].GetString();
	if (value.HasMember("ExcludeFromNomenclatureCheck"))
		newDir.excludeFromNomenclatureCheck = value["ExcludeFromNomenclatureCheck"].GetBool();
	if (value.HasMember("ExcludeFromExtensionCheck"))
		newDir.excludeFromExtensionCheck = value["ExcludeFromExtensionCheck"].GetBool();
	if (value.HasMember("ExcludeRecursiveChecks"))
		newDir.excludeRecursiveChecks = value["ExcludeRecursiveChecks"].GetBool();
	if (value.HasMember("NomenclatureRestrict"))
	{
		for (Value::ConstValueIterator it = value["NomenclatureRestrict"].Begin(); it != value["NomenclatureRestrict"].End(); ++it)
			newDir.nomenclatureRestricts.push_back(it->GetString());
	}
	if (value.HasMember("ExtensionRestrict"))
	{
		for (Value::ConstValueIterator it = value["ExtensionRestrict"].Begin(); it != value["ExtensionRestrict"].End(); ++it)
			newDir.extensionRestricts.push_back(it->GetString());
	}
	if (value.HasMember("Directories"))
	{
		for (Value::ConstValueIterator it = value["Directories"].Begin(); it != value["Directories"].End(); ++it)
			newDir.subDirectories.push_back(CreateDirectoryConfig((*it)));
	}

	return newDir;
}
