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
	this->decisionsoundname = "decision.wav";
	this->canVolControl = false;
	this->isPause = false;
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
	this->LadderTex.Create("mapchip2.png");
	this->totitleTex.Create("totitle.png");
	//プレイヤーNPCの生成
	auto chara = Chara::Create(std::string("player.png"), Vec2(400, -200));
	chara->SetDirection(Chara::Direction::RIGHT);
	chara->SetAutoFlag(true);
	//背景の描画
	auto back = Back::Create(std::string("back.png"), Vec2(1920 * 2 + 200, 1080));
	//雲
	Cloud::Create("cloud1.png", 0.5f);
	Cloud::Create("cloud2.png", 1.5f);
	//マップ生成
	auto map = Map::Create(std::string("select.csv"));
	map->SetDrawOrder(0.5f);
	//ステージ概要表示用案内板
	auto board = StageAlert::Create(true, Box2D(400, 0, 1328, 550));
	auto board2 = StageAlert::Create(true, Box2D(400 + 1920, 0, 1328, 550));
	(*board) << "./data/monitor0.txt";
	(*board) << "./data/monitor1.txt";
	(*board) << "./data/monitor2.txt";
	(*board2) << "./data/monitor3.txt";
	(*board2) << "./data/monitor4.txt";
	(*board2) << "./data/monitor5.txt";
	//サウンドの生成
	//BGM
	if (rm->GetSoundData((std::string)"titleBGM") == nullptr)
	{
		sound = new Sound();

		sound->create(soundname, true);
		rm->SetSoundData((std::string)"titleBGM", sound);
		//this->canVolControl = true;
		sound->play();
	}
	//決定音
	decisionsound.create(decisionsoundname, false);

	//タグ指定
	__super::Init((std::string)"select");
	//描画順指定
	__super::SetDrawOrder(0.6f);
	//初期モード設定
	this->mode = Mode::createTask;
	//テスト処理
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(100, 0));
	this->doorNumber = 6;
	//停止位置の設定
	for (int i = 1; i <= this->doorNumber / 2; ++i)
	{
		auto gate = Gate::Create((490.f * i) + 100.f, 640.f);      //元データ(490.f*i)+450.f
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	for (int i = 1; i <= this->doorNumber / 2; ++i)
	{
		auto gate = Gate::Create((490.f * i) + 100.f + 1920.f, 640.f);      //元データ(490.f*i)+450.f
		gate->SetTexture(&this->Testdoor);
		this->Entrance.emplace_back(LEFT, gate->position.x - chara->Scale.x);
		this->Entrance.emplace_back(RIGTH, gate->position.x + gate->Scale.x);
	}
	this->Entrance.emplace_back(LEFT, 31.f * 64.f + 1920.f - chara->Scale.x);
	auto load = OGge->GetTask<Load>("load");
	if (load)
	{
		load->ALLTaskUpDateStop();
	}
	return true;
}

void StageSelect::UpDate()
{
	if (canVolControl)
	{
		if (rm->GetSoundData((std::string)"titleBGM") == nullptr)
		{
			sound->volume(volControl.FadeOut(this->canVolControl));
		}
		else
		{
			sound = rm->GetSoundData((std::string)"titleBGM");
			sound->volume(volControl.FadeOut(this->canVolControl));
		}
	}
	switch (this->mode)
	{
	case Mode::createTask:	//生成から落下と硬直
	{
		this->CreateTask();
	}
	break;
	case Mode::objectMoveTask:	//キャラとカメラの横移動
	{
		this->ObjectMoveTask();
	}
	break;
	case Mode::waitTask:	//決定待ち
	{
		this->WaitTask();
	}
	break;
	case Mode::afterMoveTask:	//決定後処理
	{
		this->AfterMoveTask();
		this->canVolControl = true;
	}
	break;
	case Mode::End:		//次へ
	{
		auto load = Load::Create();
		if (load)
		{
			load->AddDeleteObjectName(this->GetTaskName());
		}
	}
	break;
	default:
		break;
	}
	this->ModeCheck();
}

void StageSelect::PauseUpDate()
{
	OGge->camera->SetPos(this->camera_anim.Move(10.f));
	if (!this->camera_anim.isPlay())
	{
		this->timeCnt++;
		OGge->SetPause(false);
		this->isPause = false;
	}
}

void StageSelect::Render2D()
{

	//壁の描画
	{
		for (int i = 0; i < 2; ++i)
		{
			Box2D draw = Box2D(450 + (i * 1920), 600, 1500, 300);
			draw.OffsetSize();
			Box2D src = Box2D(0.f, 0.f, Wall.GetTextureSize().x, Wall.GetTextureSize().y);
			this->Wall.Draw(draw, src);
		}
	}
	//ハシゴ
	for (int i = 0; i < 8; ++i)
	{
		Box2D draw(31.f*64.f + 1920.f, i * 128.f, 128.f, 128.f);
		draw.OffsetSize();
		Box2D src(768, 256, 256, 256);
		src.OffsetSize();
		this->LadderTex.Draw(draw, src);
	}
	//totitle看板
	{
		Box2D draw(1920 * 2 - 500 + 200+167, 1080 - 250+83, 333, 167);
		draw.OffsetSize();
		Box2D src(0, 0, 1000, 500);
		this->totitleTex.Draw(draw, src);
	}
}

bool StageSelect::Finalize()
{
	//画像の解放
	this->Testdoor.Finalize();
	this->Wall.Finalize();
	this->LadderTex.Finalize();
	this->totitleTex.Finalize();
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
	auto clouds = OGge->GetTasks<Cloud>("cloud");
	for (auto id = clouds->begin(); id != clouds->end(); ++id)
	{
		(*id)->Kill();
	}
	//扉情報すべて削除
	this->Entrance.clear();
	return true;
}

void StageSelect::CreateTask()
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
					this->mode = Mode::objectMoveTask;
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

void StageSelect::ObjectMoveTask()
{
	//カメラの位置を送る
	OGge->camera->SetPos(this->camera_anim.Move(10.f));
	//移動が終了したら
	if (!this->camera_anim.isPlay())
	{
		auto board = OGge->GetTasks<StageAlert>("stagealert");
		//if (board) {
		//	board->setActive(true);
		//	board->SetStageData("./data/monitor0.txt");
		//}
		for (auto id = board->begin(); id != board->end(); ++id)
		{
			(*id)->setActive(true);
			(*id)->SelectFirstElement();
		}
		//次へ移動
		this->mode = Mode::waitTask;
	}
}
void StageSelect::WaitTask()
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
				//画面が変わるならばカメラを移動する
				if (this->nowPos == 5)
				{
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(200.f, 0.f));
					this->timeCnt = 0;
					this->isPause = true;
				}
				auto board = OGge->GetTasks<StageAlert>("stagealert");
				std::string curStageName = "./data/monitor" + std::to_string(this->nowPos / 2) + ".txt";
				//if (board && board->isExist(curStageName)) {
				//	//board->AnimPlay();
				//	board->SetStageData(curStageName);
				//}
				for (auto id = board->begin(); id != board->end(); ++id)
				{
					if ((*id)->isExist(curStageName))
					{
						(*id)->SetStageData(curStageName);
					}
				}
			}
			//right入力
			if (OGge->in->down(In::CR) || OGge->in->down(In::LR))
			{
				auto gates = OGge->GetTasks<Gate>("gate");
				if (chara->nowDirection() == Chara::Direction::RIGHT)
				{
					if (this->nowPos < this->doorNumber * 2)
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
					if (this->nowPos < this->doorNumber * 2)
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
				//画面が変わるならカメラの移動
				if (this->nowPos == 6)
				{
					this->camera_anim.Set(OGge->camera->GetPos(), Vec2(OGge->camera->GetSize().x + 200.f, 0.f));
					this->timeCnt = 0;
					this->isPause = true;
				}
				auto board = OGge->GetTasks<StageAlert>("stagealert");
				std::string curStageName = "./data/monitor" + std::to_string(this->nowPos / 2) + ".txt";
				//if (board && board->isExist(curStageName)) {
				//	//board->AnimPlay();
				//	board->SetStageData(curStageName);
				//}
				for (auto id = board->begin(); id != board->end(); ++id)
				{
					if ((*id)->isExist(curStageName))
					{
						(*id)->SetStageData(curStageName);
					}
				}
			}
			//決定入力
			if (OGge->in->down(In::B2))
			{
				//サウンドの再生
				decisionsound.play();

				switch (this->nowPos)
				{
				case 0:
				case 1:
					this->state = State::Tutorial1;
					*MapNum = 1;
					break;
				case 2:
				case 3:
					this->state = State::Tutorial2;
					*MapNum = 5;
					break;
				case 4:
				case 5:
					this->state = State::Tutorial3;
					//*MapNum = 6;
					*MapNum = 9;
					break;
				case 6:
				case 7:
					//梯子を上る
					this->state = State::Stage1;
					//*MapNum = 1;
					*MapNum = 13;
					break;
				case 8:
				case 9:
					this->state = State::Stage2;
					//*MapNum = 5;
					*MapNum = 14;
					break;
				case 10:
				case 11:
					this->state = State::Stage3;
					//*MapNum = 6;
					*MapNum = 15;
					break;
				case 12:
					this->state = State::ToTitle;
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
				this->mode = Mode::afterMoveTask;
			}
		}
		else
		{
			if(chara->position.x >= 2016.f && chara->position.x <= 2144.f && this->isPause)
			{
				OGge->SetPause(true);
			}
		}
	}
}
void StageSelect::AfterMoveTask()
{
	auto chara = OGge->GetTask<Chara>("Chara");
	
	if (chara)
	{
		if (!chara->isAutoPlay())
		{
			if (this->nowPos == 12)
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
		if (this->timeCnt >= 10000)
		{
			this->timeCnt = 1000;
		}
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
		auto charas = OGge->GetTasks<Chara>("Chara");
		for (auto id = charas->begin(); id != charas->end(); ++id)
		{
			(*id)->Kill();
		}
	}
}


StageSelect::Animation::Animation()
{

}

void StageSelect::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
}

Vec2 StageSelect::Animation::Move()
{
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

Vec2 StageSelect::Animation::Move(const float time)
{
	return Vec2(this->easing_x.sine.Out(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.linear.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

Vec2 StageSelect::Animation::Move(const Easing::Name name, const Easing::Mode mode, const float time)
{
	switch (name)
	{
	case Easing::Name::Back:
		break;
	case Easing::Name::Bounce:
		break;
	case Easing::Name::Circ:
		break;
	case Easing::Name::Cubic:
		break;
	case Easing::Name::Elastic:
		break;
	case Easing::Name::Expo:
		break;
	case Easing::Name::Quad:
		break;
	case Easing::Name::Quart:
		break;
	case Easing::Name::Quint:
		break;
	case Easing::Name::Sine:
		break;
	default:
		break;
	}
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(time), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(time), this->StartPos.y, this->EndPos.y, time));
}

bool StageSelect::Animation::isPlay() const
{
	return this->easing_x.isplay() || this->easing_y.isplay() ? true : false;
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
