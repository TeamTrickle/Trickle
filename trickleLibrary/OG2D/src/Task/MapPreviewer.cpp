#include "MapPreviewer.h"
#include <iostream>

std::array<Vec2, 4> MapPreviewer::CamMoveSeq = {
	Vec2(1, 0),
	Vec2(0, 1),
	Vec2(-1, 0),
	Vec2(0, -1)
};

MapPreviewer::~MapPreviewer() {
}

MapPreviewer::SP MapPreviewer::Create(bool flag_, const Box2D& size)
{
	auto to = MapPreviewer::SP(new MapPreviewer());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(size)) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool MapPreviewer::Initialize(const Box2D& size) {
	windowSize = size;
	thumbSize = Vec2(0, 0);
	visible = false;

	__super::Init((std::string)"mappreviewer");
	__super::SetDrawOrder(0.85f);
	return true;
}

void MapPreviewer::UpDate() {
	if (visible) {
		Vec2 est = pointPos + (CamMoveSeq[curMoveIdx] * camSpeed);
		if (isShootable(est)) {
			pointPos = est;
		}
		else {
			++curMoveIdx;
			if (curMoveIdx >= CamMoveSeq.size()) {
				curMoveIdx = 0;
				// ƒvƒŒƒrƒ…[‰æ‘œ‚ª•¡”‘¶Ý‚·‚éê‡·‚µ‘Ö‚¦
				if (thumbnails->size() > 1) {
					++curThumbnailIdx;
					if (curThumbnailIdx >= thumbnails->size()) {
						curThumbnailIdx = 0;
					}
					mapThumbnail = (*thumbnails)[curThumbnailIdx];
					resetMetadata();
				}
			}
		}
	}
}

void MapPreviewer::Render2D() {
	if (visible) {
		Box2D draw = windowSize;
		draw.OffsetSize();
		Box2D src(
			(int)pointPos.x, 
			(int)pointPos.y, 
			(int)(windowSize.w * zoom.x), 
			(int)(windowSize.h * zoom.y)
		);
		src.OffsetSize();
		mapThumbnail->Draw(draw, src);
	}
}

bool MapPreviewer::isShootable(const Vec2& v) const {
	return
		v.x >= 0 &&
		v.y >= 0 &&
		v.x + (windowSize.w * zoom.x) < thumbSize.x &&
		v.y + (windowSize.h * zoom.y) < thumbSize.y;
}

void MapPreviewer::resetMetadata() {
	thumbSize = mapThumbnail->GetTextureSize();
	pointPos = Vec2(0.f, 0.f);
	if (thumbSize.x < windowSize.w ||
		thumbSize.y < windowSize.h) {
		zoom.x = 0.5f;
		zoom.y = 0.5f;
		camSpeed = 2.5f;
	}
	else {
		zoom.x = 1.f;
		zoom.y = 1.f;
		camSpeed = 5.f;
	}
}

void MapPreviewer::replaceThumbnail(std::vector<Texture*>* tex) {
	thumbnails = tex;
	mapThumbnail = (*thumbnails)[0];
	resetMetadata();
}

void MapPreviewer::setVisible(const bool& v) {
	this->visible = v;
}

bool MapPreviewer::isVisible() const {
	return this->visible;
}

void MapPreviewer::setSize(const Box2D& s)
{
	windowSize = s;
}

Box2D MapPreviewer::getSize() const
{
	return windowSize;
}
