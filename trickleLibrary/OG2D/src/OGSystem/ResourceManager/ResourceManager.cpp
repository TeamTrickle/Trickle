#include "ResourceManager.h"

void ResourceManager::SetSoundData(const std::string& dataname, Sound* sound)
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

bool ResourceManager::CreateSound(const std::string& name, const std::string& path)
{
	for (auto id = this->soundData.begin(); id != this->soundData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	Sound* so = new Sound();
	so->create(path);
	std::pair<std::string, Sound*> d;
	d.first = name;
	d.second = so;
	this->soundData.push_back(d);
	return true;
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

bool ResourceManager::CreateTexture(const std::string& name, const std::string& path)
{
	for (auto id = this->textureData.begin(); id != this->textureData.end(); ++id)
	{
		if ((*id).first == name)
		{
			return false;
		}
	}
	Texture* tex = new Texture();
	tex->Create(path);
	std::pair<std::string, Texture*> d;
	d.first = name;
	d.second = tex;
	this->textureData.push_back(d);
	return true;
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
	for (auto& d : this->soundData)
	{
		if (d.second)
		{
			delete d.second;
		}
	}
	for (auto& d : this->textureData)
	{
		if (d.second)
		{
			d.second->Finalize();
			delete d.second;
		}
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
			if ((*id).second)
			{
				(*id).second->Finalize();
				delete (*id).second;
			}
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
			if ((*id).second)
			{
				delete (*id).second;
			}
			this->soundData.erase(id);
			return true;
		}
	}
	return false;
}