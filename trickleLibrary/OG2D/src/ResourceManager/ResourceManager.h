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
	void SetSoundData(std::string&,Sound*);
	Sound* GetSoundData(std::string&);
	void SetTextureData(std::string&,Texture*);
	Texture* GetTextureData(std::string&);
	virtual ~ResourceManager();
};