#include "ResourceManager.h"

void ResourceManager::SetSoundData(const std::string& dataname,Sound* sound)
{
	for (auto id = this->soundData.begin(); id != soundData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, Sound*> d;
	d.first = dataname;
	d.second = sound;
	this->soundData.push_back(d);
}

void ResourceManager::SetTextureData(const std::string& dataname, Texture* texture)
{
	for (auto id = this->textureData.begin(); id != this->textureData.end(); ++id)
	{
		if ((*id).first == dataname)
		{
			return;
		}
	}
	std::pair<std::string, Texture*> d;
	d.first = dataname;
	d.second = texture;
	this->textureData.push_back(d);
}

Sound* ResourceManager::GetSoundData(const std::string& dataname)
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

Texture* ResourceManager::GetTextureData(const std::string& dataname)
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
	for (auto id = this->textureData.begin(); id != this->textureData.end(); ++id)
	{
		id->second->Finalize();
	}
	this->soundData.clear();
	this->textureData.clear();
}

bool ResourceManager::DeleteTexture(const std::string& name)
{
	for (auto id = this->textureData.begin(); id != this->textureData.end(); ++id)
	{
		if ((*id).first == name)
		{
			this->textureData.erase(id);
			return true;
		}
	}
	return false;
}

bool ResourceManager::DeleteSound(const std::string& name)
{
	for (auto id = this->soundData.begin(); id != this->soundData.end(); ++id)
	{
		if ((*id).first == name)
		{
			this->soundData.erase(id);
			return true;
		}
	}
	return false;
}