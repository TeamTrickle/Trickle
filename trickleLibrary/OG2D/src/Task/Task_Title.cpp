#include "Task_Title.h"

void Title::Initialize()
{
	std::cout << "Title初期化" << std::endl;
	sound.createSound(std::string("playandhope.wav"), true);
	map.LoadMap("test.txt");

	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	startPos = Vec2(700.0f, 100.0f);
	pausePos = Vec2(700.0f, 200.0f);
	closePos = Vec2(700.0f, 300.0f);

	texCursor.TextureCreate("Collision.png");
	texStart.TextureCreate("start.png");
	texClose.TextureCreate("close.png");
	texPause.TextureCreate("pause.png");
}

TaskFlag Title::Update()
{
	TaskFlag nowtask = Task_Title;

	CursorMove();

	if (state == Start)
	{
		if (gameEngine->in.down(Input::in::D2))
		{
			nowtask = Task_Game;
		}
	}

	if (state == Close)
	{
		//ゲームを終了する処理、またはタスクを移行
		if (gameEngine->in.down(Input::in::D2))
		{
			gameEngine->GameEnd();
		}
	}

	if (state == Pause)
	{
		//設定を行うタスクへ
	}


	/*
	if (gameEngine->in.down(Input::in::D2))
	{
		nowtask = Task_Game;
	}
	if (gameEngine->in.key.on(Input::KeyBoard::A))
	{
		gameEngine->camera->MovePos(Vec2(-1.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::D))
	{
		gameEngine->camera->MovePos(Vec2(+1.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::W))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, -1.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::S))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, 1.0f));
	}
	if (gameEngine->in.on(Input::in::B1, 0))
	{
		gameEngine->camera->MoveSize(Vec2(1.0f, 0.0f));
	}
	if (gameEngine->in.on(Input::in::B2, 0))
	{
		gameEngine->camera->MoveSize(Vec2(0.0f, 1.0f));
	}
	if (gameEngine->in.on(In::B3))
	{
		gameEngine->camera->MoveSize(Vec2(16.f, 9.f));
	}
	if (gameEngine->in.on(In::B4))
	{
		gameEngine->camera->MoveSize(Vec2(-16.f, -9.f));
	}
	if (gameEngine->in.key.down(In::M))
	{
		if (sound.isplay())
		{
			sound.stop();
		}
		else
		{
			sound.play();
			sound.volume(0.2f);
		}
	}*/
	return nowtask;
}

void Title::Render2D()
{
	map.MapRender();
	//カーソルの表示
	{
		//表示位置、大きさは仮ゲームスタート
		Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texCursor.Draw(draw, src);
	}
	//ゲームスタート
	{
		Box2D draw(startPos.x, startPos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texStart.Draw(draw, src);
	}
	//終了
	{
		Box2D draw(closePos.x, closePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texClose.Draw(draw, src);
	}
	//設定
	{
		Box2D draw(pausePos.x, pausePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texPause.Draw(draw, src);
	}
	
}

void Title::Finalize()
{
	std::cout << "Title解放" << std::endl;
	map.Finalize();

	//使用画像の解放
	texCursor.Finalize();
	texStart.Finalize();
	texClose.Finalize();
	texPause.Finalize();

	cm.Destroy();
}

void Title::CursorMove()
{
	if (cursorPos.y > startPos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::UP))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < closePos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::DOWN))
		{
			cursorPos.y += 100.0f;
		}
	}

	if (cursorPos.y == startPos.y)
	{
		state = Start;
	}
	if (cursorPos.y == pausePos.y)
	{
		state = Pause;
	}
	if (cursorPos.y == closePos.y)
	{
		state = Close;
	}
}

/*void ObjectSample::Initialize()
{
// イヤヤヤヤー！きゃーーーねこだー！！！
this->sampleimg.TextureCreate(this->fileName);
CreateObject(Cube, Vec2(10.0f, 100.0f), Vec2(128.0f, 128.0f), 0.0f);
footHit.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.f), 0.f);
this->hitcheck = false;


Object::CollisionIn = [&](const Object& o_) {
std::cout << "Collision Start : " << o_.objectTag << std::endl;
};

Object::CollisionProcess = [&](const Object& o_) {
std::cout << "Collision On Process : " << o_.objectTag << std::endl;
};

Object::CollisionOut = [&](const Object& o_) {
std::cout << "Collision End : " << o_.objectTag << std::endl;
};
}

void ObjectSample::UpDate()
{
if (gameEngine->in.on(Input::in::CU, 0))
{
this->position.y -= 5.0f;
}
if (gameEngine->in.on(Input::in::CD, 0))
{
this->position.y += 5.0f;
}
if (gameEngine->in.on(Input::in::CR,0))
{
this->position.x += 5.0f;
}
if (gameEngine->in.on(Input::in::CL,0))
{
this->position.x -= 5.0f;
}
if (gameEngine->in.on(Input::in::L1,0))
{
this->angle -= 1.0f;
}
if (gameEngine->in.on(Input::in::R1,0))
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
}*/