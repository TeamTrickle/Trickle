#pragma once
#include "OGSystem\Audio\Sound.h"
#include "OGSystem\Texture\Texture.h"

class ResourceManager
{
	//std::vector<S_Data> soundData;
	std::vector<std::pair<std::string, Sound*>> soundData;
	//std::vector<T_Data> textureData;
	std::vector<std::pair<std::string, Texture*>> textureData;
public:
	void SetSoundData(const std::string&,Sound*);
	Sound* GetSoundData(const std::string&);
	void SetTextureData(const std::string&,Texture*);
	Texture* GetTextureData(const std::string&);
	bool DeleteTexture(const std::string&);
	bool DeleteSound(const std::string&);
	virtual ~ResourceManager();
};