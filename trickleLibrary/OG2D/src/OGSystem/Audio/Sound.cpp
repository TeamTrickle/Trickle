#include "Sound.h"
//---------------------------------
//@:Soundclass
//---------------------------------
Sound::Sound()
	:filepath_("./data/bgm/")
{

};
Sound::Sound(const std::string& path_, const bool loop) :
	buffer(std::make_shared<Buffer>(filepath_ + path_)),
	source(std::make_shared<Source>())
{
	this->source->BindBuffer(*this->buffer);
	this->looping(loop);
	this->pitch(1.0f);
	this->volume_ = 1.0f;
	this->volume(this->volume_);
}
Sound::~Sound()
{

};
bool Sound::create(const std::string& path_, const bool loop)
{
	this->buffer = std::make_shared<Buffer>(filepath_ + path_);
	this->source = std::make_shared<Source>();
	this->source->BindBuffer(*this->buffer);
	this->looping(loop);
	this->pitch(1.0f);
	this->volume_ = 1.0f;
	this->volume(this->volume_);
	return true;
}
void Sound::play() const
{
	this->source->Play();
}
void Sound::stop() const
{
	this->source->Stop();
}
void Sound::pause() const
{
	this->source->Pause();
}
void Sound::volume(const float value_) const
{
	this->source->Volume(value_);
}
void Sound::pitch(const float value_) const
{
	this->source->Pitch(value_);
}
void Sound::looping(const bool loop_) const
{
	this->source->Looping(loop_);
}
bool Sound::isplay() const
{
	return this->source->isPlay();
}
float Sound::currenttime() const
{
	return this->source->currenttime();
}
float Sound::duration() const
{
	return this->buffer->GetTime();
}
void Sound::setVolume(float maxVolume_)
{
	this->volume_ = maxVolume_;
}
float Sound::getVolume() const
{
	return this->volume_;
}