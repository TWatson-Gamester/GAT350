#pragma once
#include <memory>

namespace gn {
	class Object {
	public:
		virtual ~Object() {}

		virtual void Create() {}

		virtual std::unique_ptr<Object> Clone() const { return std::unique_ptr<Object>(); }
	};
}
