#include "TimeSign.h"
#include "GameProcessManagement\GameProcessManagement.h"


TimeSign::~TimeSign() {
	Finalize();
}

TimeSign::SP TimeSign::Create(const std::string& bp, const Vec2& p, bool flag_ = true) {
	TimeSign::SP to = TimeSign::SP(new TimeSign());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(bp, p))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool TimeSign::Initialize(const std::string& basePath, const Vec2& pos) {
	base.Create(basePath);
	Vec2 baseSize = base.GetTextureSize();
	originPos.w = baseSize.x;
	originPos.h = baseSize.y;
	setPosition(pos);

	__super::Init((std::string)"timesign");
	__super::SetDrawOrder(0.5f);
	return true;
}

void TimeSign::UpDate() {
	auto timeSrc = OGge->GetTask<GameManager>((std::string)"GM");
	if (timeSrc) {
		currentTime[0] = timeSrc->MinuteTime() / 10;
		currentTime[1] = timeSrc->MinuteTime() % 10;
		currentTime[2] = timeSrc->SecondsTime() / 10;
		currentTime[3] = timeSrc->SecondsTime() % 10;
	}
}

void TimeSign::Render2D() {
	// ”wŒi‰æ‘œ
	{
		Box2D draw = originPos;
		draw.OffsetSize();
		Box2D src(0.f, 0.f, originPos.w, originPos.h);
		src.OffsetSize();
		base.Draw(draw, src);
	}

	// ”š
	for (int i = 0; i < timerDraws.size(); ++i) {
		Box2D draw = timerDraws[i];
		draw.OffsetSize();
		Box2D src = numberSrcs[currentTime[i]];
		src.OffsetSize();
		numberAtlas.Draw(draw, src);
	}
}

void TimeSign::Finalize() {
	ClearNumberAtlas();
	base.Finalize();
}

void TimeSign::ClearNumberAtlas() {
	numberAtlas.Finalize();
	numberSrcs.clear();
}

void TimeSign::setAtlas(const std::string& path, const Box2D& lettersize) {
	ClearNumberAtlas();
	numberAtlas.Create(path);
	
	int number = 0;
	Box2D numberBox = Box2D(0.f , lettersize.y, lettersize.w, lettersize.h);
	while (number < 10) {
		numberSrcs.insert({
			number,
			numberBox
		});
		number += 1;
		numberBox.x += lettersize.x;
	}
}

void TimeSign::setAtlasAngle(const float& a) {
	rotateAngle = a;
	numberAtlas.Rotate(a);
}

void TimeSign::setPosition(const Vec2& p) {
	originPos.x = p.x;
	originPos.y = p.y;
}

Vec2& TimeSign::getPosition() const {
	return Vec2(originPos.x, originPos.y);
}

void TimeSign::setDialogPos(const Vec2& pos) {
	timerDraws[0].x = pos.x;
	timerDraws[0].y = pos.y;
	setAtlasAngle(rotateAngle);
}