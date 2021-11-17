#pragma once
#include "Component/Component.h"
#include "Audio/AudioChannel.h"

namespace gn{
	class AudioComponent : public Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<AudioComponent>(*this); }

		virtual void Update() override;

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Play();
		void Stop();

	public:
		std::string soundName;
		float volume = 1.0f;
		float pitch = 1.0f;
		bool loop = false;
		bool playOnAwake = false;


	private:
		AudioChannel channel;
		bool played{ false };

	};
}
