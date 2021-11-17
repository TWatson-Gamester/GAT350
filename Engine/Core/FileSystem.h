#pragma once

#include <string>

namespace gn {
	void SetFilePath(const std::string& pathname);
	std::string GetFilePath();
}