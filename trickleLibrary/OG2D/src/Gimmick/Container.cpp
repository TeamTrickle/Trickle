#include "Container.h"

using namespace std;

void GimmickC::Initialize()
{
	cout << "—eŠí‚Ì‰Šú‰»" << endl;
	this->ContainerImg.TextureCreate(this->fileName);
	water = 0.0f;
	hold = false;
	hitRight = false;
	hitLeft = false;
	hitBottom = false;

	//position.x = 10;
	//position.y = 100;
	//Scale.x = 128.0f;
	//Scale.y = 128.0f;
	CreateObject(Cube, Vec2(10.0f, 100.0f), Vec2(128.0f, 128.0f), 0.0f);
}

TaskFlag GimmickC::UpDate()
{
	TaskFlag nowtask = Container;
	cout << position.y << endl;

	if (hold == true)
	{
		/*
		this->position.x=
		this->position.y=
		*/
	}
	if (hitBottom == false)
	{
		if (speed <= 5.0f)
		{
			speed += 0.2f;
		}
		this->position.y += speed;
	}

	return nowtask;
}

void GimmickC::Finalize()
{
	cout << "—eŠí‚Ì‰ð•ú" << endl;
	this->ContainerImg.Finalize();
}

void GimmickC::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	this->ContainerImg.Draw(draw, src);
}
