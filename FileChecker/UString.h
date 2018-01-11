#pragma once

#ifndef DEF_UTILITY_STRING
#define DEF_UTILITY_STRING

#include <vector>
#include <sstream>

namespace Utility_String
{
	///Split a string and puts it in a preconstructed array.
	template<typename Out>
	void split(const std::string& _str, const char& _delimiter, Out _splitted)
	{
		std::istringstream iss(_str);
		std::string split;

		while (std::getline(iss, split, _delimiter ))
			if(!split.empty())
				*(_splitted++) = split;
	}

	///Split a string and return a new vector
	std::vector<std::string> split(const std::string& _str, const char& _delimiter)
	{
		std::vector<std::string> splittedStr;
		split(_str, _delimiter, std::back_inserter(splittedStr));
		return splittedStr;
	}
}

namespace uString = Utility_String;

#endif // ! 

