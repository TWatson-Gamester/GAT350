#pragma once

#include "Framework/System.h"
#include "AudioChannel.h"
#include <fmod.hpp>
#include <string>
#include <map>

namespace gn
{
	class AudioSystem : public System
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		void AddAudio(const std::string& name, const std::string& filename);
		AudioChannel PlayAudio(const std::string& name, float volume = 1.0f, float pitch = 1.0f, bool loop = false);

	private:
		FMOD::System* fmodSystem;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}
