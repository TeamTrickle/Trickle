#include "Back.h"

void Back::Initialize() {
	this->backimg.TextureCreate(this->fileName);
	position.x = 0;
	position.y = 0;
	Scale.x = 1920.0f;
	Scale.y = 1080.0f;
}

void Back::UpDate() {}

void Back::Render() {
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 1920, 1080);
	this->backimg.Draw(draw, src);

}
void Back::Finalize() {
	this->backimg.Finalize();
}
