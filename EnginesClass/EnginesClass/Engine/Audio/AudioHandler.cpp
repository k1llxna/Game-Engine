#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::audioInstance = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::soundMap = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channelMap = std::map<int, FMOD::Channel*>();

AudioHandler::AudioHandler() {}
AudioHandler::~AudioHandler() {
}

AudioHandler* AudioHandler::GetInstance() {
	if (audioInstance.get() == nullptr) {
		audioInstance.reset(new AudioHandler);
	}
	return audioInstance.get();
}

bool AudioHandler::Init(glm::vec3 pos_ = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 forDir_ = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 upDir_ = glm::vec3(0.0f, 1.0f, 0.0f)) {
	FMOD::System_Create(&fmodSystem);
	if (!fmodSystem->getNumDrivers(0)) {
		return false;
	}
	else {
		fmodSystem->init(5, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);
		FMOD_VECTOR fmodPos = GlmToFmod(pos_);
		FMOD_VECTOR fmodVel = GlmToFmod(vel_);
		FMOD_VECTOR fmodFor = GlmToFmod(forDir_);
		FMOD_VECTOR fmodUp = GlmToFmod(upDir_);
		fmodSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodFor, & fmodUp);
		return true;
	}
}

void AudioHandler::OnDestroy() {
	for (auto s : soundMap) {
		s.first.empty();
		s.second->release();
		s.second = nullptr;
	}

	for (auto c : channelMap) {
		c.second->stop();
		c.second = nullptr;
	}
	fmodSystem->release();
	fmodSystem = nullptr;
}

FMOD_VECTOR AudioHandler::GlmToFmod(glm::vec3 vector_) {
	FMOD_VECTOR fmodVec;
	fmodVec.x = vector_.x;
	fmodVec.y = vector_.y;
	fmodVec.z = vector_.z;

	return fmodVec;
}

FMOD::Sound* AudioHandler::GetSound(std::string soundName_) {
	for (auto s : soundMap) {
		if (s.first == soundName_) {
			return s.second;
		}
	}
	return nullptr;
}

void AudioHandler::LoadSound(std::string s_, bool ifLoop_, bool is3D_, bool howPlay_) {
	if (GetSound(s_)) {
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;
	FMOD_MODE loopMode;
	FMOD_MODE is3d;
	FMOD_MODE streamType;

	if (ifLoop_) {
		loopMode = FMOD_LOOP_NORMAL;
	}

	else {
		loopMode = FMOD_LOOP_OFF;
	}

	if (is3D_) {
		is3d = FMOD_3D;
	}

	else {
		is3d = FMOD_2D;
	}

	if (howPlay_) {
		streamType = FMOD_CREATESTREAM;
	}

	else {
		streamType = FMOD_CREATECOMPRESSEDSAMPLE;
	}

	mode = mode | loopMode | is3d | streamType;

	FMOD::Sound* sound = nullptr;

	std::string path = "./Resources/AudioClips/" + s_;
	fmodSystem->createSound(path.c_str(), mode, nullptr, &sound);
	soundMap.emplace(s_, sound);
}

bool AudioHandler::IsPlaying(int channelID_){
	if (channelMap[channelID_]) {
		bool isPlaying;
		channelMap[channelID_]->isPlaying(&isPlaying);
		return isPlaying;
	}
	return false;
}

int AudioHandler::PlaySound(std::string soundName_, glm::vec3 soundPos_, glm::vec3 soundVel_, float volume_){
	int channelID = -1;
	if (!GetSound(soundName_)) {
		LoadSound(soundName_, false, true, false);
	}

	FMOD::Channel* audioChannel = nullptr;

	fmodSystem->playSound(soundMap[soundName_], nullptr, true, &audioChannel);
	FMOD_VECTOR FMODPosition = GlmToFmod(soundPos_);
	FMOD_VECTOR FMODVelocity = GlmToFmod(soundVel_);
	FMOD_MODE is3d = FMOD_3D;

	if (audioChannel->getMode(&is3d) == FMOD_3D)
	{
		audioChannel->set3DAttributes(&FMODPosition, &FMODVelocity);
	}
	audioChannel->setVolume(volume_);

	audioChannel->setPaused(false);
	channelID = channelCount;
	channelCount++;

	channelMap.emplace(channelID, audioChannel);
	return channelID;
}

void AudioHandler::UpdatePosition(int channelID_, glm::vec3 soundPos_, glm::vec3 soundVel_){
	if (channelMap[channelID_]) {
		FMOD_VECTOR pos = GlmToFmod(soundPos_);
		FMOD_VECTOR vel = GlmToFmod(soundVel_);
		channelMap[channelID_]->set3DAttributes(&pos, &vel);
	}
}
