#include "Task_Option.h"

void Option::Initialize()
{
	this->soundName = "playandhope.wav";

	texBack.TextureCreate("back.png");    //1920*1080
	texBar.TextureCreate("Collision.png");
	texGear.TextureCreate("Collision.png");

	this->vol = 0.5f;

	Option::Set();    //サウンドの用意
}
TaskFlag Option::Update()
{
	TaskFlag nowtask = Task_Option;

	VolControl();    //サウンドのボリュームコントロール
	DrawVol();     //移動する描画について

	if (gameEngine->in.down(Input::in::B1))
	{
		sound.stop();
		nowtask = Task_Title;
	}
	return nowtask;
}
void Option::Finalize()
{
	texBack.Finalize();
	texBar.Finalize();
	texGear.Finalize();
}
void Option::Render()
{
	//背景の描画
	{
		Box2D draw(Vec2(0, 0), gameEngine->window->GetSize());  //画像サイズは仮
		draw.OffsetSize();
		Box2D src(0, 0, 1920, 1080);
		src.OffsetSize();
		texBack.Draw(draw, src);
	}
	//音量の描画
	{
		Box2D draw(80.0f, 300.0f, barwidth, 32.0f);     //画像サイズは仮
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texBar.Draw(draw, src);
	}
	//歯車の表示
	{
		Box2D draw(gearPos + 20, 284.0f, 64.0f, 64.0f);     //画像サイズは仮
		draw.OffsetSize();
		Box2D src(128, 0, 128, 128);
		src.OffsetSize();
		texGear.Draw(draw, src);
	}
}

void Option::Set()
{
	sound.createSound(soundName, true);
	//サウンド自体の音量を設定 ここをユーザーが変更?
	sound.SetVolume(1.0f);
	//サウンドデータをSoundManagerに登録
	gameEngine->soundManager->SetSound(&sound);
	//サウンドの再生
	sound.play();
}

void Option::VolControl()
{
	//音量調節について
	//上キーで音量を上げる
	if (gameEngine->in.down(In::CU))
	{
		if (vol < 1.0f)
		{
			vol += 0.1f;
		}
	}
	//下キーで音量を下げる
	if (gameEngine->in.down(In::CD))
	{
		if (vol > 0.1f)
		{
			vol -= 0.1f;
		}
	}
	//サウンドの音量の調整用 使用しない
	//sound.volume(vol);
	//最大音量を指定
	gameEngine->soundManager->SetMaxVolume(vol);
	//サウンドの音量を最大音量に合わせて適用させる
	gameEngine->soundManager->Application();
}

//音量調節画像の位置調節
void Option::DrawVol()
{
	nowVol = vol / 0.1f;
	if (nowVol >= 1)
	{
		gearPos = nowVol * 80;
		barwidth = nowVol * 80;
	}
	else
	{
		gearPos = 48;
		barwidth = nowVol * 80;
	}
}