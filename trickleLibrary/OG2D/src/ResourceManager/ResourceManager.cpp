#include "ResourceManager.h"

void ResourceManager::SetSoundData(std::string& dataname,Sound* sound)
{
	std::pair<std::string, Sound*> d;
	d.first = dataname;
	d.second = sound;
	this->soundData.push_back(d);
}

void ResourceManager::SetTextureData(std::string& dataname, Texture* texture)
{
	std::pair<std::string, Texture*> d;
	d.first = dataname;
	d.second = texture;
	this->textureData.push_back(d);
}

Sound* ResourceManager::GetSoundData(std::string& dataname)
{
	for (auto id = this->soundData.begin(); id != this->soundData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return (*id).second;
		}
	}
	return nullptr;
}

Texture* ResourceManager::GetTextureData(std::string& dataname)
{
	for (auto id = this->textureData.begin(); id != this->textureData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return (*id).second;
		}
	}
	return nullptr;
}

ResourceManager::~ResourceManager()
{
	this->soundData.clear();
	this->textureData.clear();
}