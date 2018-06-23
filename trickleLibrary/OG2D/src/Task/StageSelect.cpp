#include "StageSelect.h"
#include "Task\Task_Game.h"
#include "Task\Task_Title.h"
#include "Task\Task_StageAlert.h"
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
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (state == State::ToTitle)
		{
			auto nexttask = Title::Create();
			nexttask->BackTitleSkip();
		}
		else
		{
			auto nexttask = Game::Create();
		}
	}
}

bool StageSelect::Initialize()
{
	//画像の読み込み
	this->Testdoor.Create((std::string)"door.png");
	this->Wall.Create((std::string)"wall2.PNG");
	//プレイヤーNPCの生成
	auto chara = Chara::Create(std::string("player.png"), Vec2(400, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//背景の描画
	auto back = Back::Create(std::string("back.png"), Vec2(1920 + 200, 1080));
	//マップ生成
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.5f);
	//ステージ概要表示用案内板
	auto board = StageAlert::Create(true, Box2D(500, 50, 1328, 550));
	(*board) << "monitor0.txt";
	(*board) << "monitor1.txt";
	(*board) << "monitor2.txt";
	//サウンドの生成
	if (rm->GetSoundData((std::string)"titleBGM") == nullptr)
	{
		sound = new Sound();
		sound->create(soundname, true);
		rm->SetSoundData((std::string)"titleBGM", sound);
		sound->play();
	}
	//タグ指定
	__super::Init((std::string)"select");
	//描画順指定
	__super::SetDrawOrder(0.3f);
	//初期モード設定
	this->mode = Mode::from1;
	//テスト処理
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(100, 0));
	//停止位置の設定
	for (int i = 1; i <= 3; ++i)
	{
		auto gate = Gate::Create((490.f * i) + 100.f, 640.f);      //元データ(490.f*i)+450.f
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->_arr[y][x] == 23)
			{
				//梯子位置(x座標)の検索
				this->Entrance.emplace_back(LEFT, map->hitBase[y][x].position.x - chara->Scale.x);
			}
		}
	}
	//読み込み終了でロード画面を破棄
	auto load = OGge->GetTasks<Load>("load");
	for (auto id = load->begin(); id != load->end(); ++id)
	{
		(*id)->Kill();
	}

	std::cout << "StageSelect 生成完了" << std::endl;
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

	//壁の描画
	{
		Box2D draw = Box2D(450, 600, 1500, 300);
		draw.OffsetSize();
		Box2D src = Box2D(0.f, 0.f, Wall.GetTextureSize().x, Wall.GetTextureSize().y);
		this->Wall.Draw(draw, src);
		//OG::LineHitDraw(&draw);
	}
}

bool StageSelect::Finalize()
{
	//画像の解放
	this->Testdoor.Finalize();
	this->Wall.Finalize();
	//サウンドの解放
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
	auto alert = OGge->GetTasks<StageAlert>("stagealert");
	for (auto id = alert->begin(); id != alert->end(); ++id)
	{
		(*id)->Kill();
	}
	//扉情報すべて削除
	this->Entrance.clear();
	return true;
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
				if (this->CheckTime(30))
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
		auto board = OGge->GetTask<StageAlert>("stagealert");
		if (board) {
			board->setActive(true);
			board->SetStageData("monitor0.txt");
		}
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
			//Left入力
			if (OGge->in->down(In::CL) || OGge->in->down(In::LL))
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
				auto board = OGge->GetTask<StageAlert>("stagealert");
				std::string curStageName = "monitor" + std::to_string(this->nowPos / 2) + ".txt";
				if (board && board->isExist(curStageName)) {
					//board->AnimPlay();
					board->SetStageData(curStageName);
				}
			}
			//right入力
			if (OGge->in->down(In::CR) || OGge->in->down(In::LR))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < 6)
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
				auto board = OGge->GetTask<StageAlert>("stagealert");
				std::string curStageName = "monitor" + std::to_string(this->nowPos / 2) + ".txt";
				if (board && board->isExist(curStageName)) {
					//board->AnimPlay();
					board->SetStageData(curStageName);
				}
			}
			//決定入力
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
				case 6:
					//梯子を上る
					this->state = State::ToTitle;
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
						if (chara->nowDirection() == Chara::Direction::LEFT)
						{
							chara->Set(chara->position, Vec2((*id)->position.x - chara->Scale.x, chara->position.y), 10.0f);
							chara->SetRestriction((*id)->Get_Door_x());
							break;
						}
						else
						{
							chara->Set(chara->position, Vec2((*id)->position.x + (*id)->Scale.x, chara->position.y), 10.0f);
							chara->SetRestriction((*id)->Get_Door_w());
							break;
						}
					}
					else
					{
						//ドアの横にいない時(梯子の時)
						chara->Set(chara->position, Vec2(this->Entrance[this->nowPos].second + chara->Scale.x, chara->position.y), 5.f);
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
			if (this->nowPos == 6)
			{
				this->nowPos += 1;
				chara->Set(chara->position, Vec2(chara->position.x, -200.f), 30.f);
				return;
			}
			this->GateClose();
		}
	}
	else
	{
		this->GateClose();
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

void StageSelect::GateClose()
{
	auto gates = OGge->GetTasks<Gate>("gate");
	for (auto id = gates->begin(); id != gates->end(); ++id)
	{
		if (this->nowPos / 2 == (*id)->GetID())
		{
			if ((*id)->ToClose())
			{
				this->timeCnt = 0;
			}
		}
	}
	if (this->timeCnt > 40)
	{
		this->mode = Mode::End;
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

bool StageSelect::CheckTime(int t)
{
	return this->timeCnt > t ? true : false;
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
