#include "TimeSign.h"
#include "GameProcessManagement\GameProcessManagement.h"


TimeSign::~TimeSign() {
	Finalize();
}

TimeSign::SP TimeSign::Create(const std::string& bp, const Box2D& p, bool flag_ = true) {
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

bool TimeSign::Initialize(const std::string& basePath, const Box2D& pos) {
	for (auto& t : timerDraws)
		t = Box2D(0.f, 0.f, 0.f, 0.f);

	//base.Create(basePath);
	base = rm->GetTextureData((std::string)basePath);
	originPos = pos;

	__super::Init((std::string)"timesign");
	__super::SetDrawOrder(0.1f);
	return true;
}

void TimeSign::UpDate() {
	auto timeSrc = OGge->GetTask<GameManager>((std::string)"GM");
	if (timeSrc) {
		if (currentTime[4] != timeSrc->SecondsTime() % 10) {
			currentTime[2] = (currentTime[2] == 1) ? 0 : 1;
		}

		currentTime[0] = timeSrc->MinuteTime() / 10;
		currentTime[1] = timeSrc->MinuteTime() % 10;
		currentTime[3] = timeSrc->SecondsTime() / 10;
		currentTime[4] = timeSrc->SecondsTime() % 10;
		activate = true;
	}
	else {
		std::cout << "TimeSignÉGÉâÅ[ÅFéûä‘èÓïÒÇéùÇ¡ÇƒÇ±ÇÍÇ‹ÇπÇÒ" << std::endl;
		activate = false;
	}
}

void TimeSign::Render2D() {
	if (activate) {
		// îwåiâÊëú
		{
			Box2D draw = originPos;
			draw.OffsetSize();
			Vec2 srcRange = base->GetTextureSize();
			Box2D src(0.f, 0.f, srcRange.x, srcRange.y);
			src.OffsetSize();
			base->Draw(draw, src);
		}

		// êîéö
		for (int i = 0; i < timerDraws.size(); ++i) {
			Box2D draw = timerDraws[i];
			Box2D src = numberSrcs[currentTime[i]];
			if (isCommaDrawable(i)) {
				switch (currentTime[2]) {
				case 0:		src = numberSrcs[':']; break;
				case 1:		src = numberSrcs[' ']; break;
				}
			}
			else if (i == 2) continue;
			draw.OffsetSize();
			src.OffsetSize();
			numberAtlas->Draw(draw, src);
		}
	}
}

void TimeSign::Finalize() {
	ClearNumberAtlas();
	//base.Finalize();
}

void TimeSign::ClearNumberAtlas() {
	//numberAtlas.Finalize();
	numberSrcs.clear();
}

inline bool TimeSign::isCommaDrawable(const int& idx) const {
	return idx == 2 && (numberSrcs.find(':') != numberSrcs.end());
}

void TimeSign::setAtlas(const std::string& path, 
						const Box2D& lettersize, 
						const Box2D& initPos = Box2D(0, 0, 0, 0)) {
	ClearNumberAtlas();
	//numberAtlas.Create(path);
	numberAtlas = rm->GetTextureData((std::string)path);
	timerDraws[0] = initPos;
	timerDraws[0].x = originPos.x + initPos.x;
	timerDraws[0].y = originPos.y + initPos.y;
	
	char number = 0;
	Box2D numberBox = Box2D(0.f , lettersize.y, lettersize.w, lettersize.h);
	while (number < 10) {
		numberSrcs.insert({
			number,
			numberBox
		});
		number += 1;
		numberBox.x += lettersize.w;
	}
	setAtlasAngle(0);
}

void TimeSign::setAtlasAngle(const float& a) {
	rotateAngle = a;
	numberAtlas->Rotate(a);

	for (int i = 1; i < timerDraws.size(); ++i) {
		auto prevDraw = timerDraws[i - 1];
		if (!isCommaDrawable(i - 1)) {
			if (i == 3) 
				prevDraw = timerDraws[1];
		}
		timerDraws[i] = prevDraw;
		timerDraws[i].x = prevDraw.x + prevDraw.w;
		timerDraws[i].y += prevDraw.w * sin(a * PI / 180);
	}
}

void TimeSign::setComma(const Box2D& d, const Box2D& f, const Box2D& s) {
	timerDraws[2] = d;
	numberSrcs.insert({ ':', f });
	numberSrcs.insert({ ' ', s });
	setAtlasAngle(rotateAngle);
}

void TimeSign::setPosition(const Vec2& p) {
	originPos.x = p.x;
	originPos.y = p.y;
}

Vec2 TimeSign::getPosition() const {
	return Vec2(originPos.x, originPos.y);
}

void TimeSign::setDialogPos(const Vec2& pos) {
	timerDraws[0].x = pos.x;
	timerDraws[0].y = pos.y;
	setAtlasAngle(rotateAngle);
}