#include "StageSelect.h"

void StageSelect::Initialize()
{
	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	tutorialPos = Vec2(700.0f, 100.0f);
	stage1Pos = Vec2(700.0f, 200.0f);
	stage2Pos = Vec2(700.0f, 300.0f);
	toTitlePos = Vec2(700.0f, 400.0f);

	texBack.TextureCreate("back.png");
	texCursor.TextureCreate("Collision.png");
	texTutorial.TextureCreate("tutorial.png");
	texStage1.TextureCreate("stage1.png");
	texStage2.TextureCreate("stage2.png");
	texToTitle.TextureCreate("totitle.png");
}

TaskFlag StageSelect::UpDate()
{
	CursorMove();

	TaskFlag nowTask = Task_StageSelect;
	if (gameEngine->in.key.down(In::ENTER))
	{
		switch (state) {
		case Tutorial:
			*MapNum = 1;	break;
		case Stage1:
			*MapNum = 5;	break;
		case Stage2:	//未実装
			//*MapNum = 6;	break;
		default:
			*MapNum = 0;	break;
		}
		nowTask = (state == ToTitle) ? Task_Title : Task_Game;
	}
	return nowTask;
}

void StageSelect::Render()
{
	//背景
	{
		Box2D draw(Vec2(0, 0), gameEngine->window->GetSize());
		draw.OffsetSize();
		Box2D src(0, 0, 1920, 1080);
		src.OffsetSize();
		texBack.Draw(draw, src);
	}
	//カーソル
	{
		Box2D draw(cursorPos.x, cursorPos.y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		src.OffsetSize();
		texCursor.Draw(draw, src);
	}
	//チュートリアル
	{
		Box2D draw(tutorialPos.x, tutorialPos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texTutorial.Draw(draw, src);
	}
	//ステージ１
	{
		Box2D draw(stage1Pos.x, stage1Pos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texStage1.Draw(draw, src);
	}
	//ステージ２
	{
		Box2D draw(stage2Pos.x, stage2Pos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texStage2.Draw(draw, src);
	}
	//タイトルに戻る
	{
		Box2D draw(toTitlePos.x, toTitlePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texToTitle.Draw(draw, src);
	}


}

void StageSelect::Finalize()
{
	texCursor.Finalize();
	texTutorial.Finalize();
	texStage1.Finalize();
	texStage2.Finalize();
	texToTitle.Finalize();
}

void StageSelect::CursorMove() {
	if (cursorPos.y > tutorialPos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::UP))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < toTitlePos.y)
	{
		if (gameEngine->in.key.down(Input::KeyBoard::DOWN))
		{
			cursorPos.y += 100.0f;
		}
	}

	if (cursorPos.y == tutorialPos.y)
	{
		state = Tutorial;
	}
	if (cursorPos.y == stage1Pos.y)
	{
		state = Stage1;
	}
	if (cursorPos.y == stage2Pos.y)
	{
		state = Stage2;
	}
	if (cursorPos.y == toTitlePos.y)
	{
		state = ToTitle;
	}

}