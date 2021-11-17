#pragma once
#include <string>

namespace gn {
	std::string string_tolower(const std::string& str);
	bool iString_Compate(const std::string& str1, const std::string& str2);
	std::string unique_string(const std::string& str);
}