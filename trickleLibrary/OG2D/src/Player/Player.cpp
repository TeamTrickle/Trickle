#include "Player.h"


void Player::Initialize()
{
	std::cout << "Player‰Šú‰»" << std::endl;
	this->playerimg.TextureCreate(this->fileName);
	//position.x = 100;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(10.0f, 100.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;

	speed = 5.0f;
}

void Player::UpDate()
{
	Vec2 est;
	if (Key::KeyInputOn(GLFW_KEY_LEFT)) {
		est.x -= 1;
	}
	if (Key::KeyInputOn(GLFW_KEY_RIGHT)) {
		est.x += 1;
	}
	if (Key::KeyInputOn(GLFW_KEY_UP)) {
		est.y += 1;
	}
	if (Key::KeyInputOn(GLFW_KEY_DOWN)) {
		est.y -= 1;
	}
	est.Normalize();
	est *= speed;
	position += est;
}

void Player::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	this->playerimg.Draw(draw, src);
}

void Player::Finalize()
{
	std::cout << "Player‰ð•ú" << std::endl;
	this->playerimg.Finalize();

}