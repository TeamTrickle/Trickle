#include "Task_Title.h"

void Title::Initialize()
{
	std::cout << "Title初期化" << std::endl;
	objsmp.Initialize();
	objsmp2.Initialize();
	map.LoadMap("test.txt");
}

TaskFlag Title::UpDate()
{
	TaskFlag nowtask = Task_Title;
	if (gameEngine->input.down(Input::in::D2, 0)/* || gameEngine->gamepad[0].ButtonDown(GLFW_JOYSTICK_8)*/)
	{
		nowtask = Task_Game;
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::A))
	{
		gameEngine->camera->Move(Vec2(-1.0f, 0.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::D))
	{
		gameEngine->camera->Move(Vec2(+1.0f, 0.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::W))
	{
		gameEngine->camera->Move(Vec2(0.0f, -1.0f));
	}
	if (gameEngine->input.keyboard.on(Input::KeyBoard::S))
	{
		gameEngine->camera->Move(Vec2(0.0f, 1.0f));
	}
	objsmp.UpDate();
	objsmp2.UpDate();
	objsmp.hitcheck = map.MapHitCheck(objsmp);
	return nowtask;
}

void Title::Render2D()
{
	
	objsmp.Render();
	objsmp2.Render();
	map.MapRender();
}

void Title::Finalize()
{
	std::cout << "Title解放" << std::endl;
	objsmp.Finalize();
	objsmp2.Finalize();
	map.Finalize();
}

void ObjectSample::Initialize()
{
	// イヤヤヤヤー！きゃーーーねこだー！！！
	this->sampleimg.TextureCreate(this->fileName);
	CreateObject(Cube, Vec2(10.0f, 100.0f), Vec2(128.0f, 128.0f), 0.0f);
	footHit.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.f), 0.f);
	this->hitcheck = false;
}

void ObjectSample::UpDate()
{
	if (gameEngine->input.on(Input::in::CU, 0))
	{
		this->position.y -= 5.0f;
	}
	if (gameEngine->input.on(Input::in::CD, 0))
	{
		this->position.y += 5.0f;
	}
	if (gameEngine->input.on(Input::in::CR,0))
	{
		this->position.x += 5.0f;
	}
	if (gameEngine->input.on(Input::in::CL,0))
	{
		this->position.x -= 5.0f;
	}
	if (gameEngine->input.on(Input::in::L1,0))
	{
		this->angle -= 1.0f;
	}
	if (gameEngine->input.on(Input::in::R1,0))
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