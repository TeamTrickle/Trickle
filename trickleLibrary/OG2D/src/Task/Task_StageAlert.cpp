#include "Task_StageAlert.h"
#include "StageFileSys.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

void StageAlert::AnimPlay() {
	anis = anis_origin;
	playingAnime = &anis.front();
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
	
	auto bgSize = background.GetTextureSize();
	
	Animation seq1{
		Box2D(50, 50, (int)bgSize.x + 50, (int)bgSize.y + 50),
		Box2D(0, 0, (int)bgSize.x, (int)bgSize.y),
		[&]() -> bool {
			if (!seq1.ease.isplay()) {
				std::cout << "seq1 終了" << std::endl;
				return true;
			}
			seq1.draw.w = 
				seq1.ease.bounce.In(seq1.ease.Time(3.f),
									0.f,
									bgSize.x,
									3.f);
			return false;
		}
	};
	anis_origin.push(seq1);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	std::cout << "stagealert 生成" << std::endl;
	return true;
}

void StageAlert::UpDate() {
	if (isAnimPlayable()) {
		if (!playingAnime || playingAnime->action()) {
			anis.pop();
			if (isAnimPlayable()) {
				playingAnime = &anis.front();
			}
			else {
				playingAnime = nullptr;
			}
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

inline bool StageAlert::isAnimPlayable() const {
	return !anis.empty();
}

inline Box2D StageAlert::GetFixedCameraCoord(const Box2D& origin) const {
	Vec2 camPos = OGge->camera->GetPos();
	return Box2D(origin.x + camPos.x, origin.y + camPos.y, origin.w, origin.h);
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