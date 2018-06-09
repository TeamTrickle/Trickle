#include "MapPreviewer.h"
#include <iostream>

const std::array<Vec2, 4> MapPreviewer::CamMoveSeq = {
	Vec2(1, 0),
	Vec2(0, -1),
	Vec2(-1, 0),
	Vec2(0, 1)
};

MapPreviewer::~MapPreviewer() {
	mapThumbnail.Finalize();
	std::cout << "MapPreviewer ‰ð•ú" << std::endl;
}

MapPreviewer::SP MapPreviewer::Create(bool flag_, const Box2D& size, const std::string& mf)
{
	auto to = MapPreviewer::SP(new MapPreviewer());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(size, mf)) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool MapPreviewer::Initialize(const Box2D& size, const std::string& mapFile) {
	windowSize = size;
	mapThumbnail.Create(mapFile);
	thumbSize = mapThumbnail.GetTextureSize();

	__super::Init((std::string)"mappreviewer");
	__super::SetDrawOrder(0.85f);
	std::cout << "MapPreviewer ¶¬" << std::endl;
	return true;
}

void MapPreviewer::UpDate() {
	if (visible) {
		
	}
}

void MapPreviewer::Render2D() {
	if (visible) {
		Box2D draw = windowSize;
		draw.OffsetSize();
		Box2D src(
			(int)pointPos.x, 
			(int)pointPos.y, 
			(int)windowSize.w, 
			(int)windowSize.h
		);
		src.OffsetSize();
		mapThumbnail.Draw(draw, src);
	}
}

void MapPreviewer::replaceThumbnail(const std::string& filePath) {
	mapThumbnail.Finalize();
	mapThumbnail.Create(filePath);
	pointPos = Vec2(0.f, 0.f);
	thumbSize = mapThumbnail.GetTextureSize();
}

void MapPreviewer::setVisible(const bool& v) {
	this->visible = v;
}

bool MapPreviewer::isVisible() const {
	return this->visible;
}