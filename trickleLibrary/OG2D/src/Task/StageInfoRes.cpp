#include "StageInfoRes.h"
#include "StageFileSys.h"
#include "OGSystem\ResourceManager\ResourceManager.h"



std::vector<std::string> StageInfoRes::SplitString(const std::string& str, const char& hotkey) {
	std::vector<std::string> ret;
	std::string buf = "";
	for (auto& c : str) {
		if (c == hotkey) {
			ret.push_back(buf);
			buf = "";
			continue;
		}
		buf += c;
	}
	if (!ret.empty()) {
		ret.push_back(buf);
	}

	return ret;
}

Box2D StageInfoRes::stringToBox2D(const std::string& str) {
	auto attribs = SplitString(str, ',');
	if (attribs.size() == 4) {
		return Box2D(stof(attribs[0]), 
					 stof(attribs[1]), 
					 stof(attribs[2]), 
					 stof(attribs[3]));
	}
	return Box2D();
}

Texture* StageInfoRes::loadFromTexture(std::string& path) {
	Texture* ret = rm->GetTextureData(path);
	if (ret == nullptr) {
		rm->SetTextureData(path, ret);
	}
	return ret;
}

StageInfoRes::StageInfoRes(const std::string& filePath) {
	std::string buf;

	std::ifstream file(filePath, std::ios::in);
	if (file.is_open()) {
		file >> atlasFileName;
		atlas = loadFromTexture(atlasFileName);
		file >> mapInfoFileName;
		mapInfo = loadFromTexture(mapInfoFileName);

		std::ifstream saveFile(Stage::GetSaveFilePath(filePath), std::ios::in);
		bool isCleared = saveFile.is_open();
		
		for (auto& a : achievement) {
			file >> buf;
			a.first = stringToBox2D(buf);
			if (isCleared) {
				saveFile >> buf;
				a.second = (stoi(buf) != 0) ? true : false;
			}
			else {
				a.second = false;
			}
		}
	}
}

StageInfoRes::~StageInfoRes() {
	atlas->Finalize();
	mapInfo->Finalize();
	rm->DeleteTexture(atlasFileName);
	rm->DeleteSound(mapInfoFileName);
}

bool StageInfoRes::isThisAchievementClear(const int& idx) const
{
	if (idx < MAX_ACHIEVEMENT && idx >= 0) {
		return achievement[idx].second;
	}
	return false;
}
