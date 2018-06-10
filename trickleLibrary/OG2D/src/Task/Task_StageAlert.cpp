#include "Task_StageAlert.h"
#include "StageFileSys.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

void StageAlert::AnimPlay() {
	previewer->replaceThumbnail(previewSrcName);
	previewer->setVisible(true);
	anis = anis_origin;
	playingAnime = &anis.front();
}

StageAlert::SP StageAlert::Create(bool flag_, const Box2D& winSize)
{
	auto to = StageAlert::SP(new StageAlert());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(winSize)) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

#define TEXTURE_SIZE(X) (int)X.GetTextureSize()
bool StageAlert::Initialize(const Box2D& winSize) {
	// ƒŠƒ\[ƒX‰Šú‰»
	background.Create((std::string)"stagealert_background.png");
	mission.Create((std::string)"stagealert_mission.png");
	clearFlag.Create((std::string)"stagealert_clearflag.png");

	windowSize = winSize;
	draws.insert({ &background, Box2D(500, 50,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	srcs.insert ({ &background, Box2D(0, 0,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	draws.insert({ &mission,    Box2D((int)draws[&background].x + 20, (int)draws[&background].y + 175, TEXTURE_SIZE(mission).x, TEXTURE_SIZE(mission).y) });
	srcs.insert ({ &mission,    Box2D(0, 0, TEXTURE_SIZE(mission).x, TEXTURE_SIZE(mission).y) });
	draws.insert({ &stageNameTex, Box2D((int)draws[&background].x + 405, (int)draws[&background].y + 30 , 0, 100) });
	srcs.insert ({ &stageNameTex, Box2D(0, 0, 0, 0) });
	Box2D batch = Box2D((int)draws[&background].x + 310, (int)draws[&background].y + 150, 50, 50);
	for (auto& a : starsTex) {
		draws.insert({ &a, batch });
		srcs.insert({ &a, Box2D(0, 0, TEXTURE_SIZE(a).x, TEXTURE_SIZE(a).y) });
		batch.y += 50;
	}
	batch.x = (int)draws[&background].x + 330;
	batch.y = (int)draws[&background].y + 150;
	for (auto& a : achievementsTex) {
		draws.insert({ &a, batch });
		srcs.insert({ &a, Box2D(0, 0, 0, 0) });
		batch.y += 50;
	}

	previewer = MapPreviewer::Create(true, 
		Box2D(
			(int)windowSize.x + 50,
			(int)windowSize.y + 300,
			(int)windowSize.w - 100,
			(int)windowSize.h - 325
		), "stageinfo_test.jpg");
	previewer->setVisible(true);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	std::cout << "stagealert ¶¬" << std::endl;
	return true;
}

void StageAlert::changeTexture(Texture* target, const std::string& texName, bool optimizeW = false) {
	target->Finalize();
	target->Create(texName);
	srcs[target].w = TEXTURE_SIZE((*target)).x;
	srcs[target].h = TEXTURE_SIZE((*target)).y;

	if (optimizeW) {
		draws[target].w = srcs[target].w;
	}
}
#undef TEXTURE_SIZE

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
		Box2D draw = OptimizeForWindowSize(d.second);
		draw.OffsetSize();
		Box2D src = srcs[d.first];
		src.OffsetSize();
		(d.first)->Draw(draw, src);
	}
}

void StageAlert::Finalize() {
	(*previewer).Kill();
	for (auto& d : draws) {
		d.first->Finalize();
	}
}

inline bool StageAlert::isAnimPlayable() const {
	return !anis.empty();
}

inline Box2D StageAlert::GetFixedCameraCoord(const Box2D& origin) const {
	Vec2 camPos = OGge->camera->GetPos();
	return Box2D(origin.x + camPos.x, origin.y + camPos.y, origin.w, origin.h);
}

Box2D StageAlert::OptimizeForWindowSize(const Box2D& b) const
{
	Box2D ret = b;
	if (ret.x < windowSize.x)							ret.x = windowSize.x;
	if (ret.x + ret.w > windowSize.x + windowSize.w)	ret.w = windowSize.w;
	if (ret.y < windowSize.y)							ret.y = windowSize.y;
	if (ret.y + ret.h > windowSize.y + windowSize.h)	ret.h = windowSize.h;
	return ret;
}

bool StageAlert::SetStageData(const std::string& fPath) {
	std::ifstream file(fPath, std::ios::in);
	if (file.is_open()) {
		file >> stageName;
		file >> previewSrcName;
		std::ifstream saveFile(Stage::GetSaveFilePath(fPath), std::ios::in);
		isClear = saveFile.is_open();

		int i = 0;
		for (auto& a : achievements) {
			file >> a.first;
			if (isClear) {
				std::string buf;
				saveFile >> buf;
				a.second = (stoi(buf) != 0) ? true : false;
				changeTexture(&starsTex[i], "Ster.png");
			}
			else {
				a.second = false;
				changeTexture(&starsTex[i], "SterB.png");
			}
			changeTexture(&achievementsTex[i], a.first, true);
			i += 1;
		}

		changeTexture(&stageNameTex, stageName, true);
		previewer->replaceThumbnail(previewSrcName);
		return true;
	}

	return false;
}