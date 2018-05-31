#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Load\LoadLogo.h"
#include "Gate\Gate.h"

StageSelect::StageSelect()
{
	
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
	this->nowPos = -1;
	this->soundname = "title.wav";      //サウンドのファイル名格納
}

StageSelect::~StageSelect()
{
	this->Finalize();
	/*for (int i = 2; i >= 0; --i)
	{
		delete this->gate[i];
	}*/
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
	this->Testdoor.Create((std::string)"door.png");
	//プレイヤーNPCの生成
	auto chara = Chara::Create(std::string("player2.png"), Vec2(400, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//背景の描画
	auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//マップ生成
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.1f);
	//サウンドの生成
	//タグ指定
	__super::Init((std::string)"select");
	//描画順指定
	__super::SetDrawOrder(0.5f);
	//初期モード設定
	this->mode = Mode::from1;
	//テスト処理
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(100, 0));
	//停止位置の設定
	for (int i = 1; i <= 3; ++i)
	{
		//this->gate[i - 1] = new Gate((400.f * i) + 450.f, 640.f);
		auto gate = Gate::Create((400.f * i) + 450.f, 640.f);
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	//ロード画面を読み込み終了時に殺す
	auto load = OGge->GetTask<Load>("load");
	if (load)
	{
		load->Kill();
	}
	return true;
}

void StageSelect::UpDate()
{
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
	//ドア
	/*for (int i = 0; i < 3; ++i)
	{
		Box2D draw(this->gate[i]->position, this->gate[i]->Scale);
		draw.OffsetSize();
		Box2D src(0.f, 0.f, 256.f, 512.f);
		this->Testdoor.Draw(draw, src);
	}*/
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
	delete rm->GetSoundData((std::string)"titleBGM");
	rm->DeleteSound((std::string)"titleBGM");
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
	auto gates = OGge->GetTasks<Gate>("gate");
	for (auto id = gates->begin(); id != gates->end(); ++id)
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
				if (this->timeCnt > 30)
				{
					//次へ移動
					this->mode = Mode::from2;
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(OGge->camera->GetPos().x + 100, OGge->camera->GetPos().y));
					this->nowPos = 0;
					chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 10.f);
					auto gates = OGge->GetTasks<Gate>("gate");
					for (auto id = gates->begin(); id != gates->end(); ++id)
					{
						if (this->nowPos / 2 == (*id)->GetID())
						{
							(*id)->ToOpen();
						}
					}
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
	//カメラの位置を送る
	OGge->camera->SetPos(this->camera_anim.Move(10.f));
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
		if (!chara->isAutoPlay())
		{
			if (OGge->in->down(In::CL))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::LEFT)
				{
					if (this->nowPos > 1)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos -= 2;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y),10.f);
					}
				}
				else
				{
					if (this->nowPos > 0)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos -= 1;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 5.f);
					}
				}
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						(*id)->ToOpen();
					}
				}
			}
			if (OGge->in->down(In::CR))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < 4)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos += 2;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 10.f);
					}
				}
				else
				{
					if (this->nowPos < 5)
					{
						for (auto id = gates->begin(); id != gates->end(); ++id)
						{
							if (this->nowPos / 2 == (*id)->GetID())
							{
								(*id)->ToClose();
							}
						}
						this->nowPos += 1;
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second, chara->position.y), 5.f);
					}
				}
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						(*id)->ToOpen();
					}
				}
			}
			if (OGge->in->down(In::B2))
			{
				switch (this->nowPos)
				{
				case 0:
				case 1:
					this->state = State::Tutorial;
					*MapNum = 1;
					break;
				case 2:
				case 3:
					this->state = State::Stage1;
					*MapNum = 5;
					break;
				case 4:
				case 5:
					this->state = State::Stage2;
					*MapNum = 6;
					break;
				default:
					this->state = State::ToTitle;
					break;
				}
				auto gates = OGge->GetTasks<Gate>("gate");
				for (auto id = gates->begin(); id != gates->end(); ++id)
				{
					if (this->nowPos / 2 == (*id)->GetID())
					{
						chara->Set(chara->position, Vec2((*id)->position.x, chara->position.y), 5.0f);
					}
				}
				this->mode = Mode::from4;
			}
		}
	}
}
void StageSelect::From4()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	if (chara)
	{
		if (!chara->isAutoPlay())
		{
			this->mode = Mode::End;
		}
	}
	else
	{
		this->mode = Mode::End;
	}
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

Vec2 StageSelect::Animation::Move(const float time)
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
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
