#include "PhysicsComponent.h"
#include "Engine.h"

namespace gn {
	void PhysicsComponent::Update() {
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= drag;
		
		//acceleration = Vector2::zero;
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, drag);
		return true;
	}
}