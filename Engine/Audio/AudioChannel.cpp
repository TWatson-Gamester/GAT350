#include "AudioChannel.h"

namespace gn {
	bool AudioChannel::isPlaying(){
		if (channel == nullptr) return false;
		bool isPlaying;
		channel->isPlaying(&isPlaying);
		return isPlaying;
	}

	void AudioChannel::Stop(){
		if (isPlaying()) {
			channel->stop();
		}
	}

	void AudioChannel::SetPitch(float pitch){
		if (isPlaying()) {
			channel->setPitch(pitch);
		}
	}

	float AudioChannel::GetPitch(){
		float pitch;
		if (isPlaying()) {
			channel->getPitch(&pitch);
		}
		return pitch;
	}

	void AudioChannel::SetVolume(float volume)
	{
		if (isPlaying()) {
			channel->setVolume(volume);
		}
	}

	float AudioChannel::GetVolume()
	{
		float volume;
		if (isPlaying()) {
			channel->getVolume(&volume);
		}
		return volume;
	}

}