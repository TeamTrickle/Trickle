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

void StageAlert::SelectFirstElement()
{
	SetStageData(infoRes.begin()->first);
}

void StageAlert::setActive(const bool& a){
	active = a;
}

bool StageAlert::isActive() const {
	return active;
}

void StageAlert::setPosition(const Vec2& p)
{
	position = p;
	positioning();
}

Vec2 StageAlert::getPosition() const
{
	return position;
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
	background.Create((std::string)"selectframe2.png");
	background.Rotate(180.f);
	clearFlag.Create((std::string)"selectflower.png");
	clearStarTex = rm->GetTextureData((std::string)"Ster.png");
	if (clearStarTex == nullptr) {
		clearStarTex = new Texture();
		clearStarTex->Create((std::string)"Ster.png");
		rm->SetTextureData((std::string)"Ster.png", clearStarTex);
	}
	normalStarTex = rm->GetTextureData((std::string)"SterB.png");
	if (normalStarTex == nullptr) {
		normalStarTex = new Texture();
		normalStarTex->Create((std::string)"SterB.png");
		rm->SetTextureData((std::string)"SterB.png", normalStarTex);
	}

	windowSize = winSize;
	draws.insert({ &background, Box2D(350, 0, 1625, 650) });
	srcs.insert ({ &background, Box2D(0, 0,	TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y) });
	Box2D batch = Box2D((int)draws[&background].x + 450, (int)draws[&background].y + 195, 50, 50);
	for (int i = 0; i < starFixedDraw.size(); ++i) {
		starFixedDraw[i] = batch;
		achievementFixedDraw[i] = batch;
		achievementFixedDraw[i].x += 60.f;
		achievementFixedDraw[i].w = 600.f;
		batch.y += 50;
	}

	missionDraw = Box2D(
		(int)draws[&background].x + 195,
		(int)draws[&background].y + 220,
		260, 64
	);
	missionSrc = Box2D(0, 643, 420, 62);

	titleDraw = draws[&background];
	titleDraw.x += 530;
	titleDraw.y += 80;
	titleDraw.w = 600;
	titleDraw.h = 110;

	clearFlagDraw = draws[&background];
	clearFlagDraw.x += 1200;
	clearFlagDraw.y += 70;
	clearFlagDraw.w = 270;
	clearFlagDraw.h = 270;

	previewer = MapPreviewer::Create(true, 
		Box2D(
			(int)windowSize.x + 50,
			(int)windowSize.y + 300,
			(int)windowSize.w - 100,
			(int)windowSize.h - 325
		));
	previewer->setVisible(active);
	this->setPosition(Vec2(winSize.x, winSize.y));

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	return true;
}

void StageAlert::positioning()
{
	draws[&background] = Box2D((int)position.x, (int)position.y, 1625, 650);
	srcs[&background] = Box2D(0, 0, TEXTURE_SIZE(background).x, TEXTURE_SIZE(background).y);
	Box2D batch = Box2D((int)draws[&background].x + 450, (int)draws[&background].y + 195, 50, 50);
	for (int i = 0; i < starFixedDraw.size(); ++i) {
		starFixedDraw[i] = batch;
		achievementFixedDraw[i] = batch;
		achievementFixedDraw[i].x += 60.f;
		achievementFixedDraw[i].w = 600.f;
		batch.y += 50;
	}

	missionDraw = Box2D(
		(int)draws[&background].x + 195,
		(int)draws[&background].y + 220,
		260, 64
	);
	missionSrc = Box2D(0, 643, 420, 62);

	titleDraw = draws[&background];
	titleDraw.x += 530;
	titleDraw.y += 80;
	titleDraw.w = 600;
	titleDraw.h = 110;

	clearFlagDraw = draws[&background];
	clearFlagDraw.x += 1200;
	clearFlagDraw.y += 70;
	clearFlagDraw.w = 270;
	clearFlagDraw.h = 270;

	previewer->setSize(
		Box2D(
			int(position.x + 200),
			int(position.y + 350),
			int(windowSize.w - 100),
			int(windowSize.h - 325)
		));
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
			Box2D draw = d.second;
			draw.OffsetSize();
			Box2D src = srcs[d.first];
			src.OffsetSize();
			(d.first)->Draw(draw, src);
		}

		Box2D draw, src;

		draw = missionDraw;
		draw.OffsetSize();
		src = missionSrc;
		src.OffsetSize();
		auto uiTex = rm->GetTextureData((std::string)"fontui");
		uiTex->Rotate(-30.f);
		uiTex->Draw(draw, src);
		uiTex->Rotate(0.f);

		// 情報
		draw = titleDraw;
		src = currentRes->title;
		draw.OffsetSize();
		src.OffsetSize();

		currentRes->atlas->Draw(draw, src);
		for (int i = 0; i < StageInfoRes::MAX_ACHIEVEMENT; ++i) {
			if (currentRes->isThisAchievementClear(i)) {
				draw = starFixedDraw[i];
				src = getSrcOriginal(clearStarTex);
				draw.OffsetSize();
				src.OffsetSize();
				clearStarTex->Draw(draw, src);
			}
			else {
				draw = starFixedDraw[i];
				src = getSrcOriginal(normalStarTex);
				draw.OffsetSize();
				src.OffsetSize();
				normalStarTex->Draw(draw, src);
			}
			draw = achievementFixedDraw[i];
			src = currentRes->achievement[i].first;
			draw.w = src.w;
			draw.OffsetSize();
			src.OffsetSize();
			currentRes->atlas->Draw(draw, src);
		}

		draw = clearFlagDraw;
		src = currentRes->clearSrc;
		draw.OffsetSize();
		src.OffsetSize();
		clearFlag.Draw(draw, src);
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
	if (rm->GetTextureData((std::string)"Ster.png") != nullptr) {
		rm->DeleteTexture((std::string)"Ster.png");
		delete clearStarTex;
	}
	if (rm->GetTextureData((std::string)"SterB.png") != nullptr) {
		rm->DeleteTexture((std::string)"SterB.png");
		delete normalStarTex;
	}
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
	if (!currentRes) {
		return;
	}
	previewer->replaceThumbnail(&currentRes->mapInfo);
	previewer->setVisible(true);
}