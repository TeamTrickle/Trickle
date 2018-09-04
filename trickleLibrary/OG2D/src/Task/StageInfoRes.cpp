#include "StageInfoRes.h"
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
	ret.push_back(buf);

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
		ret = new Texture();
		ret->Create(path);
		rm->SetTextureData(path, ret);
	}
	return ret;
}

StageInfoRes::StageInfoRes(const std::string& filePath) {
	clearSrc = Box2D(0, 0, 512, 512);
	std::string buf;

	std::ifstream file(filePath, std::ios::in);
	if (file.is_open()) {
		file >> atlasFileName;
		atlas = loadFromTexture(atlasFileName);
		file >> buf;
		loadThumbnails(buf);
		file >> buf;
		title = stringToBox2D(buf);

		std::string saveFilePath = "";
		if (filePath == "./data/monitor0.txt") saveFilePath = "data/Result/data4.bin";
		if (filePath == "./data/monitor1.txt") saveFilePath = "data/Result/data8.bin";
		if (filePath == "./data/monitor2.txt") saveFilePath = "data/Result/data12.bin";
		if (filePath == "./data/monitor3.txt") saveFilePath = "data/Result/data13.bin";
		if (filePath == "./data/monitor4.txt") saveFilePath = "data/Result/data14.bin";
		if (filePath == "./data/monitor5.txt") saveFilePath = "data/Result/data15.bin";
		std::ifstream saveFile(saveFilePath, std::ios::in);
		bool isCleared = saveFile.is_open();

		if (isCleared) {
			saveFile >> buf;
			if (buf == "-1" || buf == "-2,-2") {
				isCleared = false;
				clearFlag = false;
			}
			else {
				clearFlag = true;
				clearSrc = Box2D(512, 0, 512, 512);
			}
		}

		bool isAchievementAvaliable = false;
		std::array<bool, MAX_ACHIEVEMENT> isClearAchievement;
		if (clearFlag || buf == "-2,-2") {
			saveFile >> buf;
			auto flags = SplitString(buf, ',');
			for (int i = 0; i < isClearAchievement.size(); ++i) {
				isClearAchievement[i] = (flags[i] == "f") ? false : true;
			}
			isAchievementAvaliable = true;
		}
		
		int i = 0;
		for (auto& a : achievement) {
			file >> buf;
			a.first = stringToBox2D(buf);
			saveFile >> clearFlag;
			if (isAchievementAvaliable) {
				a.second = isClearAchievement[i];
			}
			else {
				a.second = false;
			}
			i += 1;
		}
	}
}

StageInfoRes::~StageInfoRes() {
	atlas->Finalize();
	if (rm->GetTextureData(atlasFileName) != nullptr) {
		atlas->Finalize();
		delete atlas;
		rm->DeleteTexture(atlasFileName);
	}
	for (int i = 0; i < mapInfo.size(); ++i) {
		if (rm->GetTextureData(mapInfoName[i]) != nullptr) {
			rm->DeleteTexture(mapInfoName[i]);
			delete mapInfo[i];
		}
		rm->DeleteTexture(mapInfoName[i]);
	}
}

bool StageInfoRes::isThisAchievementClear(const int& idx) const
{
	if (idx < MAX_ACHIEVEMENT && idx >= 0) {
		return achievement[idx].second;
	}
	return false;
}

void StageInfoRes::loadThumbnails(const std::string& longstr) {
	auto filePaths = SplitString(longstr, '|');
	for (auto& f : filePaths) {
		Texture* tex = rm->GetTextureData(f);
		if (!tex) {
			tex = new Texture();
			tex->Create(f);
			rm->SetTextureData(f, tex);
		}
		mapInfo.push_back(tex);
		mapInfoName.push_back(f);
	}
}
