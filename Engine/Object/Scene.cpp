 #include "Scene.h"
#include "Engine.h"
#include <algorithm>

namespace gn {
	void Scene::Update(float dt) {
		//Add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();
		//Update actors
		std::for_each(actors.begin(), actors.end(), [dt](auto& actor) {actor->Update(dt); });

		//destroy actors
		auto iter = actors.begin();
		while (iter != actors.end()) {
			if ((*iter)->destroy) {
				iter = actors.erase(iter); // Equals so that when it gets removed it grabs and sets up the next iter. Instead of stopping
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer* renderer) {
		std::for_each(actors.begin(), actors.end(), [renderer](auto& actor) {
			if (actor->active) {
				actor->Draw(renderer);
			}
			});
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor.get()->scene = this;
		actor->Initialize();
		newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor) {
	}

	void Scene::RemoveAllActors() {
		actors.clear();
	}

	Actor* Scene::FindActor(const std::string name){

		for (auto& actor : actors) {
			if (actor->name == name) return actor.get();
		}
		return nullptr;
	}

	bool Scene::Write(const rapidjson::Value& value) const{
		return false;
	}

	bool Scene::Read(const rapidjson::Value& value){
		if (value.HasMember("actors") && value["actors"].IsArray()) {
			for (auto& actorValue : value["actors"].GetArray()) {
				std::string type;
				JSON_READ(actorValue, type);

				bool prototype = false;
				JSON_READ(actorValue, prototype);

				auto actor = ObjectFactory::Instance().Create<Actor>(type);
				if (actor) {
					actor->scene = this;
					actor->Read(actorValue);

					if (prototype) {
						std::string name = actor->name;
						ObjectFactory::Instance().RegisterPrototype<Actor>(name, std::move(actor));

					}
					else {
						AddActor(std::move(actor));
					}
				}
			}
		}
		return true;
	}

}