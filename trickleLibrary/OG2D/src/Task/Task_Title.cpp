#include "Task_Title.h"

bool Title::Initialize()
{
	std::cout << "Title初期化" << std::endl;
	sound.create(std::string("playandhope.wav"), true);
	map.LoadMap((std::string)"test.txt");

	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	startPos = Vec2(700.0f, 100.0f);
	pausePos = Vec2(700.0f, 200.0f);
	closePos = Vec2(700.0f, 300.0f);

	texCursor.Create((std::string)"Collision.png");
	texStart.Create((std::string)"start.png");
	texClose.Create((std::string)"close.png");
	texPause.Create((std::string)"pause.png");

	//オプションで変更した音量を反映できることを確認

	//sound.create(std::string("playandhope.wav"), true);
	//サウンド自体の音量を設定
	//sound.SetVolume(1.0f);
	//サウンドデータをSoundManagerに登録
	//OGge->soundManager->SetSound(&sound);
	//最大音量を指定
	//OGge->soundManager->SetMaxVolume(vol);

	//サウンドの音量を最大音量に合わせて適用させる
	//OGge->soundManager->Application();
	//サウンドの再生
	//sound.play();
	return true;
}

void Title::UpDate()
{
	CursorMove();

	if (state == Start)
	{
		if (OGge->in->down(Input::in::B2))
		{
			
		}
	}

	if (state == Close)
	{
		//ゲームを終了する処理、またはタスクを移行
		if (OGge->in->down(Input::in::B2))
		{
			OGge->GameEnd();
		}
	}

	if (state == Pause)
	{
		if (OGge->in->down(Input::in::B2))
		{
			
		}
	}
}

void Title::Render2D()
{
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

bool Title::Finalize()
{
	std::cout << "Title解放" << std::endl;
	map.Finalize();

	//使用画像の解放
	texCursor.Finalize();
	texStart.Finalize();
	texClose.Finalize();
	texPause.Finalize();

	return true;
}

void Title::CursorMove()
{
	if (cursorPos.y > startPos.y)
	{
		if (OGge->in->down(In::CU))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < closePos.y)
	{
		if (OGge->in->down(In::CD))
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

Title::SP Title::Create(bool flag_)
{
	auto to = Title::SP(new Title());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}