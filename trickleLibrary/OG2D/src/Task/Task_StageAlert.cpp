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

#define TEXTURE_SIZE(X) (int)X.GetTextureSize()
bool StageAlert::Initialize() {
	// ÉäÉ\Å[ÉXèâä˙âª
	background.Create((std::string)"stagealert_background.png");
	star.Create((std::string)"stagealert_star.png");
	mission.Create((std::string)"stagealert_mission.png");
	clearFlag.Create((std::string)"stagealert_clearflag.png");

	draws.insert({ &background, Box2D(500, 50,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	srcs.insert ({ &background, Box2D(0, 0,		TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });

	previewer = MapPreviewer::Create(true, 
		Box2D(550, 150, TEXTURE_SIZE(background).x - 50, TEXTURE_SIZE(background).y - 50), 
		"stageinfo_test.jpg");
	(*previewer).setVisible(true);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	std::cout << "stagealert ê∂ê¨" << std::endl;
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
	for (auto& d : draws) {
		Box2D draw = d.second;
		draw.OffsetSize();
		Box2D src = srcs[d.first];
		src.OffsetSize();
		(d.first)->Draw(draw, src);
	}
}

void StageAlert::Finalize() {
	background.Finalize();
	star.Finalize();
	mission.Finalize();
	clearFlag.Finalize();
	(*previewer).Kill();
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