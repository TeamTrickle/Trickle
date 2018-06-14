#include "Task_StageAlert.h"
#include "StageFileSys.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

bool StageAlert::operator<<(const std::string& path) {
	return preloadResource(path);
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
	Box2D batch = Box2D((int)draws[&background].x + 310, (int)draws[&background].y + 150, 50, 50);
	for (auto& a : starsTex) {
		draws.insert({ &a, batch });
		srcs.insert({ &a, Box2D(0, 0, TEXTURE_SIZE(a).x, TEXTURE_SIZE(a).y) });
		batch.y += 50;
	}

	previewer = MapPreviewer::Create(true, 
		Box2D(
			(int)windowSize.x + 50,
			(int)windowSize.y + 300,
			(int)windowSize.w - 100,
			(int)windowSize.h - 325
		), "");
	previewer->setVisible(true);

	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
	std::cout << "stagealert ¶¬" << std::endl;
	return true;
}

bool StageAlert::preloadResource(const std::string& path) {
	StageInfoRes* res = new StageInfoRes(path);
	infoRes.insert({ path, res });
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
	for (auto& r : infoRes) {
		delete r.second;
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
	
}