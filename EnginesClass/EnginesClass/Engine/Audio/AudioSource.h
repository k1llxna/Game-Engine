#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <string>
#include <glm/glm.hpp>
#include "../Core/Component.h"
#include "../Rendering/3D/GameObject.h"

class AudioSource : public Component
{
public:
    AudioSource(std::string soundName_, bool loopSound_, bool is3D_, bool howPlay_);
    ~AudioSource();

    virtual bool OnCreate(class GameObject* parent_) override;
    virtual void Update(float deltaTime_) override;

    bool IsPlaying();
    void PlaySound(float volume);

private:
    int channelID;
    std::string audioName;
};
#endif // !AUDIOSOURCE_H