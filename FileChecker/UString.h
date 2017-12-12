#pragma once

#ifndef DEF_UTILITY_STRING
#define DEF_UTILITY_STRING

#include <vector>
#include <sstream>

namespace Utility_String
{
	//std::vector<std::string> Split(const std::string& _str, const char& _separator)
	//{
	//	std::vector<std::string> fileNameParts;
	//	std::istringstream iss(_str);
	//	std::string temp;

	//	while (std::getline(iss, temp, _separator))
	//		fileNameParts.push_back(temp);

	//	return fileNameParts;
	//}

	template<typename Out>
	void split(const std::string& _str, const char& _delimiter, Out _splitted)
	{
		std::istringstream iss(_str);
		std::string split;

		while (std::getline(iss, split, _separator))
			if(!split.empty())
				*(_splitted++) = split;
	}

	std::vector<std::string> split(const std::string& _str, const char& _delimiter)
	{
		std::vector<std::string> splittedStr;
		split(_str, _delimiter, std::back_inserter(splittedStr));
		return splittedStr;
	}
}

namespace uString = Utility_String;

#endif // ! 

