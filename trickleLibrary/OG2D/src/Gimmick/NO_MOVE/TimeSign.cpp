#include "TimeSign.h"


TimeSign::~TimeSign() {
	Finalize();
}

TimeSign::SP TimeSign::Create(const Vec2& p, bool flag_ = true) {
	TimeSign::SP to = TimeSign::SP(new TimeSign());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(p))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool TimeSign::Initialize(const Vec2& pos) {
	setPosition(pos);
	setAtlasPath(atlasPath, extension);

	__super::Init((std::string)"timesign");
	__super::SetDrawOrder(0.5f);
	return true;
}

void TimeSign::UpDate() {

}

void TimeSign::Render2D() {

}

void TimeSign::Finalize() {
	ClearNumberAtlas();
}

void TimeSign::ClearNumberAtlas() {
	for (auto& a : numberAtlas) {
		a.second.Finalize();
	}
	spacer.Finalize();
	numberAtlas.clear();

	originPos.w = 0;
	originPos.h = 0;
}

void TimeSign::setAtlasPath(const std::string& path, const std::string& ext) {
	atlasPath = path;
	extension = ext;
	ClearNumberAtlas();

	for (int i = 0; i < 10; ++i) {
		Texture number;
		number.Create(path + std::to_string(i) + extension);
		numberAtlas.insert({ i, number });
	}
	spacer.Create(path + "spacer" + extension);
	
	Vec2 tileSize = numberAtlas[0].GetTextureSize();
	originPos.w = tileSize.x;
	originPos.h = tileSize.y;
}

void TimeSign::setAtlasAngle(const float& a) {
	for (auto& n : numberAtlas)
		n.second.Rotate(a);
	spacer.Rotate(a);
}

void TimeSign::setPosition(const Vec2& p) {
	originPos.x = p.x;
	originPos.y = p.y;
}

Vec2& TimeSign::getPosition() const {
	return Vec2(originPos.x, originPos.y);
}