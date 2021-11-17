#pragma once
#include <iostream>

namespace gn {
	template<class T>
	class Singleton {
	public:
		Singleton(const Singleton&) = delete;
		Singleton* operator = (const Singleton&) = delete;

		static T& Instance() {
			static T instance;
			return instance;
		}

	protected:
		Singleton(){}
	};

}