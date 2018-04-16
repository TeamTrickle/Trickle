#include "SoundManager.h"
SoundManager::SoundManager()
{
	this->MaxVolume = 1.0f;
}
void SoundManager::SetMaxVolume(const float volume_)
{
	this->MaxVolume = volume_;
}
float SoundManager::GetMaxVolume() const
{
	return this->MaxVolume;
}
void SoundManager::SetVolume(const Sound* s, const float value_)
{
	s->volume(value_ * this->MaxVolume);
}
void SoundManager::SetSound(Sound* s) 
{
	sounddata.push_back(s);
}
bool SoundManager::DeleteSoundData(const Sound* s) 
{
	for (auto id = sounddata.begin(); id != sounddata.end(); ++id)
	{
		if ((*id) == s)
		{
			this->sounddata.erase(id);
			return true;
		}
	}
	return false;
}
void SoundManager::AllDelete() 
{
	this->sounddata.clear();
}
SoundManager::~SoundManager()
{
	this->sounddata.clear();
}
SoundManager::SP SoundManager::Create()
{
	return SoundManager::SP(new SoundManager());
}
void SoundManager::Application()
{
	for (int i = 0; i < this->sounddata.size(); ++i)
	{
		this->sounddata[i]->volume(sounddata[i]->GetVolume() * this->GetMaxVolume());
	}
}