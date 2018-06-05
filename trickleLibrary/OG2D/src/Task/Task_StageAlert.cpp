#include "Task_StageAlert.h"
#include "StageFileSys.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

void StageAlert::AnimPlay() {
	playingAnime = &anis.front();
	anis = anis_origin;
}

StageAlert::SP StageAlert::Create(bool flag_)
{
	auto to = StageAlert::SP(new StageAlert());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize()) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool StageAlert::Initialize() {
	// リソース初期化
	background.Create((std::string)"stagealert_background.png");
	star.Create((std::string)"stagealert_star.png");
	mission.Create((std::string)"stagealert_mission.png");
	clearFlag.Create((std::string)"stagealert_clearflag.png");

	// 元画像初期化
	Animation seq1{
		Box2D(50, 50, 100, 100),
		Box2D(50, 50, 100, 100),
		[&]() -> bool {
			return true;
		}
	};
	anis_origin.push(seq1);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	return true;
}

void StageAlert::UpDate() {
	if (isAnimPlaying()) {
		if (!playingAnime && playingAnime->action()) {
			anis.pop();
			playingAnime = &anis.front();
		}
	}
}

void StageAlert::Render2D() {

}

void StageAlert::Finalize() {
	background.Finalize();
	star.Finalize();
	mission.Finalize();
	clearFlag.Finalize();
}

inline bool StageAlert::isAnimPlaying() const {
	return !anis.empty();
}



bool StageAlert::SetStageData(const std::string& fPath) {
	std::ifstream file(fPath, std::ios::in);
	if (file.is_open()) {
		file >> stageName;
		std::ifstream saveFile(Stage::GetSaveFilePath(fPath), std::ios::in);
		isClear = saveFile.is_open();
		for (auto& a : achievements) {
			file >> a.first;
			if (isClear) {
				std::string buf;
				saveFile >> buf;
				a.second = (stoi(buf) != 0) ? true : false;
			}
			else {
				a.second = false;
			}
		}
		return true;
	}
	return false;
}