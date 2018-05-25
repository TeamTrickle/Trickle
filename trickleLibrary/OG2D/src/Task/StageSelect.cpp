#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
StageSelect::StageSelect()
{
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
}

StageSelect::~StageSelect()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (state == State::ToTitle)
		{
			auto nexttask = Title::Create();
		}
		else
		{
			auto nexttask = Game::Create();
		}
	}
}

bool StageSelect::Initialize()
{
	cursorPos.x = 600.0f;
	cursorPos.y = 100.0f;

	tutorialPos = Vec2(700.0f, 100.0f);
	stage1Pos = Vec2(700.0f, 200.0f);
	stage2Pos = Vec2(700.0f, 300.0f);
	toTitlePos = Vec2(700.0f, 400.0f);

	Vec2 kari = toTitlePos;
	toTitlePos = stage2Pos;
	stage2Pos = kari;
	//画像の読み込み
	texBack.Create((std::string)"back.png");
	texCursor.Create((std::string)"Collision.png");
	texTutorial.Create((std::string)"tutorial.png");
	texStage1.Create((std::string)"stage1.png");
	texStage2.Create((std::string)"stage2.png");
	texToTitle.Create((std::string)"totitle.png"); 
	this->Testdoor.Create((std::string)"testResource.png");
	//プレイヤーNPCの生成
	auto chara = Chara::Create(std::string("player2.png"), Vec2(10, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//背景の描画
	auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//マップ生成
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.1f);
	//タグ指定
	__super::Init((std::string)"select");
	//描画順指定
	__super::SetDrawOrder(0.5f);
	//初期モード設定
	this->mode = Mode::from1;
	//テスト処理
	OGge->camera->SetSize(Vec2(1920, 1080));
	this->testObj.CreateObject(Cube, Vec2(0, 0), Vec2(128, 128), 0.0f);
	//停止位置の設定
	this->Entrance.emplace_back(LEFT, 950 - 100 - chara->Scale.x);
	this->Entrance.emplace_back(RIGTH, 950 + 100);
	this->Entrance.emplace_back(LEFT, 1250 - 100 - chara->Scale.x);
	this->Entrance.emplace_back(RIGTH, 1250 + 100);
	this->Entrance.emplace_back(LEFT, 1650 - 100 - chara->Scale.x);
	this->Entrance.emplace_back(RIGTH, 1650 + 100);
	return true;
}

void StageSelect::UpDate()
{
	//テスト
	std::cout << "x:" << this->testObj.position.x << "y:" << this->testObj.position.y << std::endl;
	CursorMove();
	if (OGge->in->key.on(In::A))
	{
		this->testObj.position.x -= 10.0f;
	}
	if (OGge->in->key.on(In::D))
	{
		this->testObj.position.x += 10.0f;
	}
	if (OGge->in->key.on(In::W))
	{
		this->testObj.position.y -= 10.0f;
	}
	if (OGge->in->key.on(In::S))
	{
		this->testObj.position.y += 10.0f;
	}

	if (OGge->in->down(In::B2))
	{
		switch (state) {
		case Tutorial:
			*MapNum = 3;	
			if (OGge->in->on(In::SL))
			{
				*MapNum = 1;
			}
			if (OGge->in->on(In::SR))
			{
				*MapNum = 2;
			}
			break;
		case Stage1:
			*MapNum = 5;	break;
		case Stage2:	//未実装
			//*MapNum = 6;	break;
			break;
		case ToTitle:
			break;
		default:
			*MapNum = 0;	break;
		}
		this->Kill();
	}

	switch (this->mode)
	{
	case Mode::from1:	//生成から落下と硬直
	{
		this->From1();
	}
		break;
	case Mode::from2:	//キャラとカメラの横移動
	{
		this->From2();
	}
		break;
	case Mode::from3:	//決定待ち
	{
		this->From3();
	}
		break;
	case Mode::from4:	//決定後処理
	{
		this->From4();
	}
		break;
	case Mode::End:		//次へ
	{
		this->Kill();
	}
		break;
	default:
		break;
	}
	this->ModeCheck();
}

void StageSelect::Render2D()
{
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
		/*Box2D draw(stage2Pos.x, stage2Pos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texStage2.Draw(draw, src);*/
	}
	//タイトルに戻る
	{
		Box2D draw(toTitlePos.x, toTitlePos.y, 256.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 256);
		src.OffsetSize();
		texToTitle.Draw(draw, src);
	}
	//ドア
	for (int i = 1; i <= 3; ++i)
	{
		Box2D draw(400 * i + 450, 640, 128, 256);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, this->Testdoor.GetTextureSize().x, this->Testdoor.GetTextureSize().y);
		this->Testdoor.Draw(draw, src);
	}
	//テスト
	{
		Box2D draw(this->testObj.position, this->testObj.Scale);
		draw.OffsetSize();
		Box2D src(0, 128, 128, 128);
		src.OffsetSize();
		this->texCursor.Draw(draw, src);
	}


}

bool StageSelect::Finalize()
{
	texBack.Finalize();
	texCursor.Finalize();
	texTutorial.Finalize();
	texStage1.Finalize();
	texStage2.Finalize();
	texToTitle.Finalize();
	this->Testdoor.Finalize();
	//このオブジェクト内で生成したものを削除する
	auto chara = OGge->GetTasks<Chara>("Chara");
	for (auto id = (*chara).begin(); id != (*chara).end(); ++id)
	{
		(*id)->Kill();
	}
	auto back = OGge->GetTasks<Back>("back");
	for (auto id = (*back).begin(); id != (*back).end(); ++id)
	{
		(*id)->Kill();
	}
	auto map = OGge->GetTasks<Map>("map");
	for (auto id = (*map).begin(); id != (*map).end(); ++id)
	{
		(*id)->Kill();
	}
	return true;
}

void StageSelect::CursorMove() {
	if (cursorPos.y > tutorialPos.y)
	{
		if (OGge->in->down(In::CU))
		{
			cursorPos.y -= 100.0f;
		}
	}
	if (cursorPos.y < toTitlePos.y)
	{
		if (OGge->in->down(In::CD))
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

void StageSelect::From1()
{
	//キャラを検索
	auto chara = OGge->GetTask<Chara>("Chara");
	//存在した場合
	if (chara)
	{
		//当たり判定を行う番号ならば
		if (chara->CollisionNumCheck(-1))
		{
			//地面に接触しているか
			if (chara->FootCheck())
			{
				//一定カウントを超えたら
				if (this->timeCnt > 60)
				{
					//次へ移動
					this->mode = Mode::from2;
					this->camera_anim.Set(OGge->camera->GetPos(),Vec2(OGge->camera->GetPos().x + 200,OGge->camera->GetPos().y));
				}
			}
			else
			{
				//していない時は0にしておく
				this->timeCnt = 0;
			}
		}
	}
}

void StageSelect::From2()
{
	//キャラの情報を取得
	auto chara = OGge->GetTask<Chara>("Chara");
	//存在している場合
	if (chara)
	{
		//強制移動をさせる
		chara->ManualMove(Vec2(3.0f, 0.0f));
	}
	//カメラの位置を送る
	OGge->camera->SetPos(this->camera_anim.Move());
	//移動が終了したら
	if (!this->camera_anim.isPlay())
	{
		//次へ移動
		this->mode = Mode::from3;
	}
}
void StageSelect::From3()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	if (chara)
	{
		//キャラクターが動いていない時だけ入力を行う
		//そうでないならキャラクターの移動を目的地まで移動させる
		if (!chara->GetMove().x && !chara->GetMove().y)
		{
			
		}
	}
}
void StageSelect::From4()
{

}
void StageSelect::ModeCheck()
{
	if (this->preMode != this->mode)
	{
		this->timeCnt = 0;
		this->preMode = this->mode;
	}
	else
	{
		this->timeCnt++;
	}
}


StageSelect::Animation::Animation()
{

}

void StageSelect::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
}

Vec2 StageSelect::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

bool StageSelect::Animation::isPlay() const
{
	if (this->easing_x.isplay() || this->easing_y.isplay())
	{
		return true;
	}
	return false;
}

StageSelect::SP StageSelect::Create(bool flag_)
{
	auto to = StageSelect::SP(new StageSelect());
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