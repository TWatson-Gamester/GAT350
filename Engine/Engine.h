#pragma once

#define REGISTER_CLASS(CLASS) gn::ObjectFactory::Instance().Register<CLASS>(#CLASS);

//Core
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Utilities.h"
#include "Core/Json.h"
#include "Core/Serializable.h"

//Framework
#include "Framework/System.h"
#include "Framework/EventSystem.h"
#include "Framework/Singleton.h"
#include "Framework/Factory.h"

//Math
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/MathTypes.h"

//Input
#include "Input/InputSystem.h"

//Objects
#include "Object/Actor.h"
#include "Object/Scene.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Material.h"
#include "Graphics/VertexBuffer.h"

//Audio
#include "Audio/AudioSystem.h"

//Component
#include "Component/PhysicsComponent.h"
#include "Component/AudioComponent.h"
#include "Component/CameraComponent.h"
#include "Component/CameraController.h"
#include "Component/LightComponent.h"
#include "Component/MeshComponent.h"
#include "Component/ModelComponent.h"

//Resource
#include "Resource/ResourceSystem.h"

#include <vector>
#include <memory>
#include <algorithm>

namespace gn {

	using ObjectFactory = Singleton<Factory<std::string, Object>>;

	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems) {
			if ( dynamic_cast<T*>(system.get()) ) return dynamic_cast<T*>(system.get());
			//If it finds the system, then it will return a pointer to it, if not it returns null
		}

		return nullptr;
	}
}