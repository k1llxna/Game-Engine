#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>
#include <fmod.hpp>
#include "../Core/Debug.h"
#include "AudioSource.h"

class AudioHandler {
public:
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();
	bool Init(glm::vec3 pos_, glm::vec3 vel_, glm::vec3 forDir_, glm::vec3 upDir_);
	void OnDestroy();

private:
	AudioHandler();
	~AudioHandler();

	friend class AudioSource;

	FMOD::System* fmodSystem;
	static std::map<std::string, FMOD::Sound*> soundMap;
	static std::map<int, FMOD::Channel*> channelMap;

	int channelCount;

	FMOD_VECTOR GlmToFmod(glm::vec3 vector_);
	FMOD::Sound* GetSound(std::string soundName_);

	static std::unique_ptr<AudioHandler> audioInstance;
	friend std::default_delete<AudioHandler>;

	void LoadSound(std::string s_, bool ifLoop_, bool is3D_, bool howPlay_);
	bool IsPlaying(int channelID_);
	int PlaySound(std::string soundName_, glm::vec3 soundPos_, glm::vec3 soundVel_, float volume_);
	void UpdatePosition(int channelID_, glm::vec3 soundPos_, glm::vec3 soundVel_);
};
#endif