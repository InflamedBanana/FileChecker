#pragma once

#ifndef DEF_UTILITY_STRING
#define DEF_UTILITY_STRING

#include <vector>
#include <sstream>

namespace Utility_String
{
	std::vector<std::string> Split(const std::string& _str, const char& _separator)
	{
		std::vector<std::string> fileNameParts;
		std::istringstream iss(_str);
		std::string temp;

		while (std::getline(iss, temp, _separator))
			fileNameParts.push_back(temp);

		return fileNameParts;
	}
}

namespace uString = Utility_String;

#endif // ! 

