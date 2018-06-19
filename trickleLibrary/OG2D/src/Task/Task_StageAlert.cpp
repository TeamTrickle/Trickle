#include "Task_StageAlert.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

bool StageAlert::operator<<(const std::string& path) {
	return preloadResource(path);
}

bool StageAlert::isExist(const std::string& path) {
	return infoRes.find(path) != infoRes.end();
}

void StageAlert::setActive(const bool& a){
	active = a;
}

bool StageAlert::isActive() const {
	return active;
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
	// リソース初期化
	background.Create((std::string)"stagealert_background.png");
	mission.Create((std::string)"stagealert_mission.png");
	clearFlag.Create((std::string)"stagealert_clearflag.png");
	clearStarTex.Create((std::string)"Ster.png");
	normalStarTex.Create((std::string)"SterB.png");
	rm->SetTextureData((std::string)"Ster.png", &clearStarTex);
	rm->SetTextureData((std::string)"SterB.png", &normalStarTex);

	windowSize = winSize;
	draws.insert({ &background, Box2D(500, 50,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	srcs.insert ({ &background, Box2D(0, 0,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	draws.insert({ &mission,    Box2D((int)draws[&background].x + 20, (int)draws[&background].y + 175, TEXTURE_SIZE(mission).x, TEXTURE_SIZE(mission).y) });
	srcs.insert ({ &mission,    Box2D(0, 0, TEXTURE_SIZE(mission).x, TEXTURE_SIZE(mission).y) });
	Box2D batch = Box2D((int)draws[&background].x + 310, (int)draws[&background].y + 150, 50, 50);
	for (int i = 0; i < starFixedDraw.size(); ++i) {
		starFixedDraw[i] = batch;
		achievementFixedDraw[i] = batch;
		achievementFixedDraw[i].x += 60.f;
		achievementFixedDraw[i].w = 600.f;
		batch.y += 50;
	}

	titleDraw = draws[&background];
	titleDraw.x += 380;
	titleDraw.y += 10;
	titleDraw.w = 600;
	titleDraw.h = 110;

	clearFlagDraw = draws[&background];
	clearFlagDraw.x += 1100;
	clearFlagDraw.y += 420;
	clearFlagDraw.w = 500;
	clearFlagDraw.h = 500;

	previewer = MapPreviewer::Create(true, 
		Box2D(
			(int)windowSize.x + 50,
			(int)windowSize.y + 300,
			(int)windowSize.w - 100,
			(int)windowSize.h - 325
		));
	previewer->setVisible(active);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	std::cout << "stagealert 生成" << std::endl;
	return true;
}
#undef TEXTURE_SIZE

Box2D StageAlert::getSrcOriginal(Texture* tex) const {
	return Box2D(
		0.f, 0.f,
		tex->GetTextureSize().x,
		tex->GetTextureSize().y
	);
}

bool StageAlert::preloadResource(const std::string& path) {
	StageInfoRes* res = new StageInfoRes(path);
	infoRes.insert({ path, res });
	return true;
}

void StageAlert::UpDate() {
	
}

void StageAlert::Render2D() {
	if (isActive()) {
		// 非変動要素
		for (auto& d : draws) {
			Box2D draw = OptimizeForWindowSize(d.second);
			draw.OffsetSize();
			Box2D src = srcs[d.first];
			src.OffsetSize();
			(d.first)->Draw(draw, src);
		}

		// 情報
		Box2D draw, src;

		draw = titleDraw;
		src = currentRes->title;
		draw.OffsetSize();
		src.OffsetSize();

		currentRes->atlas->Draw(draw, src);
		for (int i = 0; i < StageInfoRes::MAX_ACHIEVEMENT; ++i) {
			if (currentRes->isThisAchievementClear(i)) {
				draw = starFixedDraw[i];
				src = getSrcOriginal(&clearStarTex);
				draw.OffsetSize();
				src.OffsetSize();
				clearStarTex.Draw(draw, src);
			}
			else {
				draw = starFixedDraw[i];
				src = getSrcOriginal(&normalStarTex);
				draw.OffsetSize();
				src.OffsetSize();
				normalStarTex.Draw(draw, src);
			}
			draw = achievementFixedDraw[i];
			src = currentRes->achievement[i].first;
			draw.w = src.w;
			draw.OffsetSize();
			src.OffsetSize();
			currentRes->atlas->Draw(draw, src);
		}

		if (currentRes->clearFlag) {
			draw = clearFlagDraw;
			src = Box2D(0.f, 0.f, clearFlag.GetTextureSize().x, clearFlag.GetTextureSize().y);
			draw.OffsetSize();
			src.OffsetSize();
			clearFlag.Draw(draw, src);
		}
	}
}

void StageAlert::Finalize() {
	(*previewer).Kill();
	for (auto& d : draws) {
		d.first->Finalize();
	}
	for (auto& r : infoRes) {
		delete r.second;
	}
	clearFlag.Finalize();
	clearStarTex.Finalize();
	normalStarTex.Finalize();
	rm->DeleteTexture((std::string)"Ster.png");
	rm->DeleteTexture((std::string)"SterB.png");
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

void StageAlert::SetStageData(const std::string& fPath) {
	currentRes = infoRes[fPath];
	previewer->replaceThumbnail(currentRes->mapInfo[0]);
	previewer->setVisible(true);
}