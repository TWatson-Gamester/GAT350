#pragma once
#include "Object.h"
#include "Core/Serializable.h"
#include <memory>
#include <list>
#include <vector>

namespace gn {
	class Actor;
	class Engine;
	class Renderer;

	class Scene : public Object, public ISerializable {
	public:
		void Update(float dt);
		void Draw(Renderer* renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveActor(Actor* actor);
		void RemoveAllActors();

		Actor* FindActor(const std::string name);

		template<typename T>
		T* GetActor();

		template<typename T>
		std::vector<T*> GetActors();

		// Inherited via ISerializable
		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

	public:
		Engine* engine = nullptr;

	private:
		std::vector<std::unique_ptr<Actor>> actors;
		std::vector<std::unique_ptr<Actor>> newActors;

	};


	template<typename T>
	inline T* Scene::GetActor(){
		for (auto& actor : actors) {
			if (dynamic_cast<T*>(actor.get())) {
				return dynamic_cast<T*>(actor.get());
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActors(){
		std::vector<T*> results;
		for (auto& actor : actors) {
			if (dynamic_cast<T*>(actor.get())) {
				results.push_back(dynamic_cast<T*>(actor.get()));
			}
		}
		return results;
	}
}