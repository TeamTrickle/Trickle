#include "Sound.h"
//---------------------------------
//@:Soundclass
//---------------------------------
Sound::Sound()
{

};
Sound::Sound(std::string& path_, bool loop) :
	buffer(std::make_shared<Audio::Buffer>(filepath_ + path_)),
	source(std::make_shared<Audio::Source>())
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
void Sound::createSound(std::string& path_, bool loop)
{
	this->buffer = std::make_shared<Audio::Buffer>(filepath_ + path_);
	this->source = std::make_shared<Audio::Source>();
	this->source->BindBuffer(*this->buffer);
	this->looping(loop);
	this->pitch(1.0f);
	this->volume_ = 1.0f;
	this->volume(this->volume_);
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
void Sound::SetVolume(float maxVolume_)
{
	this->volume_ = maxVolume_;
}
float Sound::GetVolume() const
{
	return this->volume_;
}