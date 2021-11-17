#pragma once
#include "Component/Component.h"
#include "Math/MathTypes.h"

namespace gn {

	class PhysicsComponent : public Component {
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<PhysicsComponent>(*this); }


		void Update() override;
		virtual void ApplyForce(const glm::vec3& force) { acceleration += force; };

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public: 
		glm::vec3 velocity = {0,0,0};
		glm::vec3 acceleration = { 0,0,0 };
		float drag = 1;
	};
}