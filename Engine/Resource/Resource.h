#pragma once

#include <string>

namespace gn {
	class Resource {
	public:
		virtual bool Load(const std::string& fileName, void* data = nullptr) = 0;
	};
 }