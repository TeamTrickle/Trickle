#include "Task_Sample.h"

void Sample::Initialize()
{
	std::cout << "Sample‰Šú‰»" << std::endl;
	//objsmp.Initialize();
	map.LoadMap("test.txt");
}

TaskFlag Sample::UpDate()
{
	TaskFlag nowtask = Task_Sample;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Sample2;
	}
	//objsmp.UpDate();
	return nowtask;
}

void Sample::Render2D()
{
	//objsmp.Render();
	map.MapRender();
}

void Sample::Finalize()
{
	std::cout << "Sample‰ð•ú" << std::endl;
	//objsmp.Finalize();
	map.Finalize();
}

//void ObjectSample::Initialize()
//{
//	this->sampleimg.TextureCreate(this->fileName);
//	CreateObject(Cube, Vec2(0.0f, 0.0f), Vec2(128.0f, 128.0f), 0.0f);
//	this->hitcheck = false;
//}
//
//void ObjectSample::UpDate()
//{
//	if (Input::KeyInputOn(Input::UP))
//	{
//		this->position.y += 1.0f;
//	}
//	if (Input::KeyInputOn(Input::DOWN))
//	{
//		this->position.y -= 1.0f;
//	}
//	if (Input::KeyInputOn(Input::RIGHT))
//	{
//		this->position.x += 1.0f;
//	}
//	if (Input::KeyInputOn(Input::LEFT))
//	{
//		this->position.x -= 1.0f;
//	}
//	if (Input::KeyInputOn(Input::Q))
//	{
//		this->angle -= 1.0f;
//	}
//	if (Input::KeyInputOn(Input::E))
//	{
//		this->angle += 1.0f;
//	}
//}
//
//void ObjectSample::Render()
//{
//	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
//	draw.OffsetSize();
//	Box2D src(0, 0, 128, 128);
//	if (hitcheck)
//	{
//		src.y += 128;
//		src.OffsetSize();
//	}
//	this->sampleimg.Rotate(this->angle);
//	this->sampleimg.Draw(draw, src);
//}
//
//void ObjectSample::Finalize()
//{
//	this->sampleimg.Finalize();
//}
