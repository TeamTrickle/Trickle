#include "Task_Sample.h"

void Sample::Initialize()
{
	std::cout << "Sample‰Šú‰»" << std::endl;
	objsmp.Initialize();
	objsmp2.Initialize();
	map.LoadMap("test.txt");
}

TaskFlag Sample::UpDate()
{
	TaskFlag nowtask = Task_Sample;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Sample2;
	}
	objsmp.UpDate();
	objsmp2.UpDate();
	objsmp.hitcheck = objsmp.hit(objsmp2);
	return nowtask;
}

void Sample::Render2D()
{
	objsmp.Render();
	objsmp2.Render();
	map.MapRender();
}

void Sample::Finalize()
{
	std::cout << "Sample‰ð•ú" << std::endl;
	objsmp.Finalize();
	objsmp2.Finalize();
	map.Finalize();
}

void ObjectSample::Initialize()
{
	this->sampleimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 100.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;
}

void ObjectSample::UpDate()
{
	if (Input::KeyInputOn(Input::UP))
	{
		this->position.y += 1.0f;
	}
	if (Input::KeyInputOn(Input::DOWN))
	{
		this->position.y -= 1.0f;
	}
	if (Input::KeyInputOn(Input::RIGHT))
	{
		this->position.x += 1.0f;
	}
	if (Input::KeyInputOn(Input::LEFT))
	{
		this->position.x -= 1.0f;
	}
	if (Input::KeyInputOn(Input::Q))
	{
		this->angle -= 1.0f;
	}
	if (Input::KeyInputOn(Input::E))
	{
		this->angle += 1.0f;
	}
}

void ObjectSample::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitcheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->sampleimg.Rotate(this->angle);
	this->sampleimg.Draw(draw, src);
}

void ObjectSample::Finalize()
{
	this->sampleimg.Finalize();
}

void ObjectSample2::Initialize()
{
	this->sampleimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(100.0f, 200.0f), Vec2(128.0f, 128.0f), 0.0f);
	this->hitcheck = false;
}

void ObjectSample2::UpDate()
{
	
}

void ObjectSample2::Render()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src(0, 0, 128, 128);
	if (hitcheck)
	{
		src.y += 128;
		src.OffsetSize();
	}
	this->sampleimg.Rotate(this->angle);
	this->sampleimg.Draw(draw, src);
}

void ObjectSample2::Finalize()
{
	this->sampleimg.Finalize();
}