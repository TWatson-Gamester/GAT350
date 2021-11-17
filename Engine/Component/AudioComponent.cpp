#include "AudioComponent.h"
#include "Engine.h"

namespace gn {

	void AudioComponent::Update(){
		if (playOnAwake && !played)
		{
			played = true;
			Play();
		}
	}

	void AudioComponent::Play(){
		//<stop channel>
		channel.Stop();
			//channel = <get audio system>->PlayAudio(soundName, volume, pitch, loop);
		channel = owner->scene->engine->Get<AudioSystem>()->PlayAudio(soundName, volume, pitch, loop);
	}

	void AudioComponent::Stop(){
		//<stop channel>
		channel.Stop();
	}

	bool AudioComponent::Write(const rapidjson::Value& value) const{
		return false;
	}

	bool AudioComponent::Read(const rapidjson::Value& value){
		//<json read soundName, volume, pitch, loop, playOnAwake>
		JSON_READ(value, soundName);
		JSON_READ(value, volume);
		JSON_READ(value, pitch);
		JSON_READ(value, loop);
		JSON_READ(value, playOnAwake);

			// add the audio to the audio system if there's a valid soundName string
			if (soundName != "") owner->scene->engine->Get<AudioSystem>()->AddAudio(soundName, soundName);

		return true;
	}

}