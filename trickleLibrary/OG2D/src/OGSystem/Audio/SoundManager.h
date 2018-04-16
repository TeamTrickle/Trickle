#pragma once
#include "Sound.h"

class SoundManager
{
public:
	explicit SoundManager();
	~SoundManager();
	typedef std::shared_ptr<SoundManager> SP;
	static SP Create();
	void SetMaxVolume(const float value_);
	float GetMaxVolume() const;
	void SetVolume(const Sound* s, const float value_);
	void SetSound(Sound* s);
	bool DeleteSoundData(const Sound* s);
	void AllDelete();
	void Application();
private:
	float MaxVolume;
	std::vector<Sound*> sounddata;
};