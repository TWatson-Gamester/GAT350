#pragma once
#include "System.h"
#include "Object/Object.h"
#include <string>
#include <map>
#include <list>
#include <functional>
#include <variant>

namespace gn {
	struct Event {
		std::string name;
		Object* receiver{ nullptr };
		std::variant<int, bool, float, std::string, void*> data;
	};

	class EventSystem : public System {
	public:
		using function_t = std::function<void(const Event&)>;

		virtual void Startup() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;

		void Subscribe(const std::string& name, function_t function, Object* receiver = nullptr);
		void Notify(const Event& event);
		void Unsubscribe(const std::string& name, Object* receiver);
		
	private:
		struct Observer {
			function_t function;
			Object* receiver;
		};

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}