#pragma once
#include "Audio.h"
class Sound
{
private:
	std::shared_ptr<Buffer> buffer;
	std::shared_ptr<Source> source;
	bool isloop_;
	const std::string filepath_;
	float volume_;
public:
	Sound();
	explicit Sound(const std::string& path_, const bool loop = false);
	~Sound();
	bool create(const std::string& path_, const bool loop = false);
	void play() const;
	void stop() const;
	void pause() const;
	void volume(const float value_) const;
	void pitch(const float value_) const;
	void looping(const bool loop_) const;
	bool isplay() const;
	float currenttime() const;
	float duration() const;
	void setVolume(float maxVolume_);
	float getVolume() const;
};