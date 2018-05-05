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

	//オプションで変更した音量を反映できることを確認

	//sound.createSound(std::string("playandhope.wav"), true);
	//サウンド自体の音量を設定
	//sound.SetVolume(1.0f);
	//サウンドデータをSoundManagerに登録
	//gameEngine->soundManager->SetSound(&sound);
	//最大音量を指定
	//gameEngine->soundManager->SetMaxVolume(vol);

	//サウンドの音量を最大音量に合わせて適用させる
	//gameEngine->soundManager->Application();
	//サウンドの再生
	//sound.play();
}

TaskFlag Title::Update()
{
	TaskFlag nowtask = Task_Title;

	CursorMove();

	if (state == Start)
	{
		if (gameEngine->in.down(Input::in::D2))
		{
			nowtask = Task_StageSelect;
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
		if (gameEngine->in.down(Input::in::D2))
		{
			nowtask = Task_Option;
		}
	}

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

