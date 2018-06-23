#include "Task_Result.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Effect/Effect.h"
#include "StageSelect.h"

Result::Result() {
	this->taskName = "Result";
	__super::Init(taskName);
	starsoundname = "kira2.wav";
}
Result::~Result() {
	this->Finalize();
}

bool Result::Initialize() {
	fontui.Create((std::string)"fontui.png");
	numberui.Create((std::string)"number.png");

	backTex.Create((std::string)"back.png");
	this->starTex.Create((std::string)"resultstar.png");
	this->frameTex.Create((std::string)"resultframe.png");
	this->stareffectTex.Create((std::string)"stareffect.png");
	//this->clearTex

	//サウンドの生成
	soundstar.create(starsoundname, false);    //星のはまる音声
	soundstar.volume(1.0f);

	//sound.create(soundname, true);           //BGM未実装
	//sound.volume(1.0f);
	//sound.play();

	this->nowMode = Mode1;
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT);
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	Map::Create((std::string)"result.csv");
	//TIME
	time.nowWH = Vec2(0, 0);
	time.pos = Vec2(150 + 64 * 2, 280 + 32);
	for (int i = 0; i < 3; ++i) {
		//星の枠
		starFrame[i].nowWH = Vec2(0, 0);
		starFrame[i].pos = Vec2(300 + 64 + i * 200, 370 + 64 - 8 * i);
		//星
		star[i].nowWH = Vec2(512, 512);
		star[i].pos = Vec2(1280, 300);
		star[i].bezcnt = 0.0f;
		star[i].angle = -5;
		//星出すフラグ
		starFlag[i] = false;
		starturn[i] = false;
		num[i] = 0;
	}
	num[3] = 0;
	cnt = 0;
	this->maxTrueNumber = -1;
	this->RoadData();
	return true;
}
void Result::UpDate() {
	OGge->camera->SetSize(Vec2(1280, 720));
	auto npc = OGge->GetTask<Chara>("Chara");
	float pretimew = 0, pretimeh = 0;
	float prestarw[3] = {}, prestarh[3] = {};
	float starytmp[3] = {};
	float presfw = 0, presfh = 0;
	switch (nowMode) {
	case Mode1:
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			this->nowMode = Mode2;
		}
		break;
	case Mode2:
		++cnt;
		//TIME
		if (time.nowWH.x < 64 * 4) {
			pretimew = time.nowWH.x;
			time.nowWH.x = time.easeX.expo.In(time.easeX.Time(3), 0.0f, 64 * 4, 3);
			time.pos.x -= (time.nowWH.x - pretimew) / 2.0f;
			if (time.nowWH.x >= 64 * 4) {
				time.nowWH.x = 64 * 4;
				time.pos.x = 150;
			}
		}
		if (time.nowWH.y < 64) {
			pretimeh = time.nowWH.y;
			time.nowWH.y = time.easeY.bounce.In(time.easeY.Time(3), 0.0f, 64, 3);
			time.pos.y -= (time.nowWH.y - pretimeh) / 2.0f;
			if (time.nowWH.y >= 64) {
				time.nowWH.y = 64;
				time.pos.y = 280;
			}
		}
		//星の枠
		for (int i = 0; i < 3; ++i) {
			if (starFrame[i].nowWH.x < 64 * 2) {
				presfw = starFrame[i].nowWH.x;
				starFrame[i].nowWH.x = starFrame[i].easeX.expo.In(starFrame[i].easeX.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.x -= (starFrame[i].nowWH.x - presfw) / 2.0f;
				if (starFrame[i].nowWH.x >= 64 * 2) {
					starFrame[i].nowWH.x = 64 * 2;
					starFrame[i].pos.x = 300 + i * 200;
				}
			}
			if (starFrame[i].nowWH.y < 64 * 2) {
				presfh = starFrame[i].nowWH.y;
				starFrame[i].nowWH.y = starFrame[i].easeY.bounce.In(starFrame[i].easeY.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.y -= (starFrame[i].nowWH.y - presfh) / 2.0f;
				if (starFrame[i].nowWH.y >= 64 * 2) {
					starFrame[i].nowWH.y = 64 * 2;
					starFrame[i].pos.y = 370 - i * 8;
				}
			}
		}
		if (cnt >= 100) {
			this->nowMode = Mode3;
			cnt = 0;
		}
		break;
	case Mode3:
		++cnt;
		if (cnt < 120) {
			for (int i = 0; i < 4; ++i) {
				num[i] = random::GetRand(0, 9);
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				num[i] = this->timer[i];
			}
		}
		if (cnt >= 150) {
			this->nowMode = Mode4;
			cnt = 0;
		}
		break;
	case Mode4:
		if (this->maxTrueNumber == -1)
		{
			this->nowMode = Mode5;
			break;
		}
		++cnt;
		//星出現
		for (int i = 0; i < 3; ++i) {
			if (starFlag[i] && cnt >= 20 * i) {	
				star[i].bezcnt += 0.03f;
				star[i].angle += 15;
				//X
				star[i].pos.x = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 1280 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 1000 + star[i].bezcnt * star[i].bezcnt * (300 + i * 200);
					if (star[i].pos.x <= 300 + i * 200) {
						star[i].pos.x = 300 + i * 200;
					}
				//Y
				star[i].pos.y = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 300 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 0 + star[i].bezcnt * star[i].bezcnt * (370 - i * 8);
				if (star[i].pos.y >= 370 - i * 8) {
					star[i].pos.y = 370 - i * 8;
				}
				//W,H縮小
				star[i].nowWH.x = star[i].nowWH.y = star[i].easeX.cubic.Out(star[i].easeX.Time(5), 512, 128 - 512, 5);
				if (star[i].nowWH.x <= 128) {
					star[i].nowWH.x = star[i].nowWH.y = 128;
				}
				//停止地点に到着
				if (star[i].pos == Vec2(300 + i * 200, 370 - i * 8) && star[i].nowWH == Vec2(128, 128)) {
					star[i].angle = -5;
					//サウンドの再生
					soundstar.play();

					//auto eff = Effect::Create(Vec2(300 + i * 200, 370 - i * 8), Vec2(32, 32), Vec2(256, 256), 5, 5);
					//eff->SetMode(Effect::Mode::Decrease);
					//eff->SetTexture(&this->stareffectTex);
					//eff->Set(eff->position, Vec2(eff->position.x + random::GetRand(-30, 30), eff->position.y + random::GetRand(-30, 30)));
				}
			}
		}
		if (star[this->maxTrueNumber].pos == Vec2(300 + this->maxTrueNumber * 200, 370 - this->maxTrueNumber * 8) && star[this->maxTrueNumber].nowWH == Vec2(128,128)) {
			this->nowMode = Mode5;
		}
		break;
	case Mode5:
		//アニメーションが終わるまで(５回ジャンプ＋位置調整)は入力できない
		if (npc->happyCnt < 7) {
			npc->Happy(7);
			//クリアUI出現(未実装)
		}
		else {
			if (OGge->in->down(Input::in::B2))
			{
				npc->MoveReset();
				npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
				this->nowMode = Mode6;
			}
		}

		break;
	case Mode6:
		//プレイヤ退場
		npc->AutoMove();
		if (npc->position.x >=  1450) {
			this->nowMode = Non;
			this->Kill();
		}
		break;
	case Non:
	default:
		break;
	}
}
void Result::Render2D() {
	//背景
	{
		backTex.Draw(Box2D(0, 0, 1280, 720), Box2D(0, 0, 1280, 720));
	}
	//モニター枠
	{
		Box2D draw((1280 - 1400) / 2, 720 - 700 - 32, 1400, 700);
		draw.OffsetSize();
		Box2D src(0, 0, 1000, 500);
		frameTex.Draw(draw, src);
	}
	//Result
	{
		Box2D draw(470, 110, 64 * 6, 64);
		draw.OffsetSize();
		Box2D src = Box2D(0, 64 * 2, 64 * 6, 64);
		src.OffsetSize();
		fontui.Rotate(-5);
		fontui.Draw(draw, src);
	}
	//rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
	//TIME
	{
		Box2D draw(time.pos.x, time.pos.y, time.nowWH.x, time.nowWH.y);
		draw.OffsetSize();
		Box2D src(0, 64 * 3, 64 * 4, 64);
		src.OffsetSize();
		fontui.Draw(draw, src);
	}
	//星の枠
	{
		for (int i = 0; i < 3; ++i) {
			Box2D draw(starFrame[i].pos.x, starFrame[i].pos.y, starFrame[i].nowWH.x, starFrame[i].nowWH.y);
			draw.OffsetSize();
			Box2D src(0, 0, 256, 256);
			starTex.Rotate(-5);
			starTex.Draw(draw, src);
		}
	}
	//タイム
	{
		if (nowMode >= Mode3) {
			//数字
			for (int i = 0; i < 4; ++i) {
				Box2D draw(150 + 64 * 4 + 100 + 96 * i, 250 - 7 * i, 96, 96);
				draw.OffsetSize();
				Box2D src(64 * num[i], 0, 64, 64);
				src.OffsetSize();
				numberui.Rotate(-5);
				numberui.Draw(draw, src);
			}
			//：
			Box2D draw(150 + 96 * 4 + 100 + 40, 260 - 17, 64, 64);
			draw.OffsetSize();
			Box2D src(64 * 10, 0, 40, 64);
			src.OffsetSize();
			numberui.Draw(draw, src);
		}
	}
	//星
	{
		if (nowMode >= Mode4) {
			for (int i = 0; i < 3; ++i) {
				Box2D draw(star[i].pos, star[i].nowWH);
				draw.OffsetSize();
				Box2D src(256, 0, 256, 256);
				src.OffsetSize();
				starTex.Rotate(star[i].angle);
				starTex.Draw(draw, src);
			}
		}
	}
}
bool Result::Finalize() {
	//解放処理
	this->backTex.Finalize();
	//this->clearTex.Finalize();
	this->frameTex.Finalize();
	this->fontui.Finalize();
	this->numberui.Finalize();
	this->starTex.Finalize();
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	auto npc = OGge->GetTask<Chara>("Chara");
	if (npc) { npc->Kill(); }
	auto map = OGge->GetTask<Map>("map");
	if (map) { map->Kill(); }
	//ステージセレクトに戻る
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		StageSelect::Create();
	}

	return true;
}
void Result::RoadData()
{
	std::ifstream ifs("./data/Result/save" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		this->Kill();
	}
	std::string line;
	std::getline(ifs, line);
	std::istringstream* is = new std::istringstream(line);
	std::string text;
	for (int i = 0; i < 2; ++i)
	{
		int t_time;
		std::getline(*is, text, ',');
		(std::stringstream)text >> t_time;
		this->timer[i * 2] = t_time / 10;
		this->timer[i * 2 + 1] = t_time % 10;
	}
	std::getline(ifs, line);
	delete is;
	is = new std::istringstream(line);
	for (int i = 0; i < 3; ++i)
	{
		std::getline(*is, text, ',');
		if (text == "t")
		{
			this->starFlag[i] = true;
			this->maxTrueNumber = (__int8)i;
		}
	}
	delete is;
}

Result::SP Result::Create(bool flag) {
	Result::SP to = Result::SP(new Result());
	if (to)
	{
		to->me = to;
		if (flag)
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




////別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
//#include "Task\StageSelect.h"
//#include "GameProcessManagement\FlagUI.h"
//#include "Player\ResultPlayer.h"
//#include "GameProcessManagement\ClearUI.h"
//#include "GameProcessManagement\GoalTimeUI.h"
//#include "GameProcessManagement\MissionUI.h"
//#include "GameProcessManagement\FrameTime.h"
//#include "Effect/SterEffect.h"
////#include "GameProcessManagement/GameProcessManagement.h"
//#include "Effect\SterEffect.h"
//#include <algorithm>
/////285 
//
//bool Result::Initialize()
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	this->taskName = "Result";		//検索時に使うための名を登録する
//	__super::Init(taskName);		//TaskObject内の処理を行う
//
//	//フラグの設定
//	this->Result_DataInput();
//	this->Flag = 0;
//
//	this->image.Create((std::string)"back.png");
//	this->maptile.Create((std::string)"tile.jpg");
//
//	SetDrawOrder(0.0f);
//
//	Vec2 camerasize = OGge->camera->GetSize();
//	Vec2 windowsize = OGge->window->GetSize();
//	//カメラのサイズとウィンドウにおけるアスペクト比の計算
//	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);
//
//	//生成フラグをリセットする
//	this->createtask.ResetCreateFlag();
//	this->createtask.ResetNextFlag();
//	this->createtask.SetNextFlag(CreateFlag::Timeui);
//
//	//リザルト画面に表示にする
//	auto player = ResultPlayer::Create(Vec2(-96, (int)camerasize.y - 50 - 96), Vec2(3, 0));
//	auto mission = MissionUI::Create();
//	std::cout << "結果画面処理　初期化" << std::endl;
//	return true;
//}
//
//void Result::UpDate()
//{
//	//--------------------
//	//更新時に行う処理を記述
//	//--------------------
//	//タイトルシーンへ遷移
//	
//	//条件をまずチェックする
//	this->UI_Think();
//	//フラグによってCreateする
//	this->UI_Create();
//
//	auto resultplayer = OGge->GetTask<ResultPlayer>("ResultPlayer");
//	if (!resultplayer)
//	{
//		if (OGge->in->down(In::B2))
//		{
//			Kill();
//		}
//	}
//	
//}
//void Result::Render2D()
//{
//	//--------------------
//	//描画時に行う処理を記述
//	//--------------------
//	Vec2 camerasize = OGge->camera->GetSize();
//	{
//		Box2D draw(Vec2(0, 0), camerasize);
//		draw.OffsetSize();
//		Box2D src = this->backSrc;
//		src.OffsetSize();
//		image.Draw(draw, src);
//	}
//	{
//		int count = 0;
//		for (int y = camerasize.y - 50; y <= camerasize.y; y += 64)
//		{
//			for (int x = 0; x <= camerasize.x / 64; ++x)
//			{
//				Box2D draw(Vec2(x * 64, (int)camerasize.y - 50 + count * 64), Vec2(64, 64));
//				draw.OffsetSize();
//				Box2D src = this->maptileSrc;
//				src.OffsetSize();
//				maptile.Draw(draw, src);
//			}
//			count++;
//		}
//		
//	}
//}
//bool Result::Finalize()
//{
//	//-----------------------------------------
//	//このオブジェクトが消滅するときに行う処理を記述
//	//-----------------------------------------
//	//次のタスクを作るかかつアプリケーションが終了予定かどうか
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		image.Finalize();
//		maptile.Finalize();
//
//		auto player = OGge->GetTasks<ResultPlayer>("ResultPlayer");
//		auto ster = OGge->GetTasks<FlagUI>("Ster");
//		auto clear = OGge->GetTasks<ClearUI>("ClearUI");
//		auto effect = OGge->GetTasks<SterEffect>("SterEffect");
//		auto goaltime = OGge->GetTasks<GoalTimeUI>("GoalTimeUI");
//		auto mission = OGge->GetTasks<MissionUI>("MissionUI");
//		auto frametime = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
//
//		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*player).begin(); id != (*player).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*clear).begin(); id != (*clear).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*goaltime).begin(); id != (*goaltime).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*effect).begin(); id != (*effect).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
//		{
//			(*id)->Kill();
//		}
//		auto stageselect = StageSelect::Create();
//	}
//	return true;
//}
//void Result::CreateTask::ResetCreateFlag()
//{
//	this->createflag &= ~this->createflag;
//}
//void Result::CreateTask::ResetNextFlag()
//{
//	this->nextflag &= ~this->nextflag;
//}
//void Result::CreateTask::SetCreateFlag(CreateFlag flag)
//{
//	this->createflag |= flag;
//}
//void Result::CreateTask::SetNextFlag(CreateFlag flag)
//{
//	this->nextflag |= flag;
//}
//void Result::UI_Think()
//{
//	switch (this->createtask.nextflag)
//	{
//	case 1 << 0:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Timeui)
//		{
//			auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
//			auto missonUI = OGge->GetTask<MissionUI>("MissionUI");
//			if (player != nullptr && missonUI != nullptr)
//			{
//				//Playerが止まったら・・・
//				if (player->GetResetWalkStop() && missonUI->isEasingPleyfinish())
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Timeui);
//				}
//			}
//		}
//		break;
//	case 1 << 1:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Starui)
//		{
//			auto frametimeUI = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");
//			for (auto id = (*frametimeUI).begin(); id != (*frametimeUI).end(); ++id)
//			{
//				this->createtask.SetCreateFlag(CreateFlag::Starui);
//			}
//		}
//		break;
//	case 1 << 2:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Effect)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				if ((*id)->is_Scale())
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Effect);
//				}
//			}
//
//		}
//		break;
//	case 1 << 3:
//		if ((this->createtask.nextflag & 0x0F) == CreateFlag::Clearui)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//			std::vector<bool> flag;
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				flag.push_back((*id)->GetEffectEnd());
//			}
//			//全てのEffectの演出が終了したら
//			for (auto id = (*sters).begin(); id != (*sters).end(); ++id)
//			{
//				if (std::all_of(flag.begin(), flag.end(), [](bool flag) {return flag == true; }))
//				{
//					this->createtask.SetCreateFlag(CreateFlag::Clearui);
//				}
//			}
//		}
//		break;
//	default:
//		break;
//	}
//}
//void Result::UI_Create()
//{
//	///注意！！　ここはフラグをセットして1フレームのみ動かす関数です。
//	Vec2 camerasize = OGge->camera->GetSize();
//	Vec2 windowsize = OGge->window->GetSize();
//	//カメラのサイズとウィンドウにおけるアスペクト比の計算
//	Vec2 aspect = Vec2(camerasize.x / windowsize.x, camerasize.y / windowsize.y);
//
//	switch (this->createtask.createflag)
//	{
//	case 1 << 0:
//		//Playerが一定のところまで歩いたら・・・
//		if ((this->createtask.createflag & CreateFlag::Timeui) == CreateFlag::Timeui)
//		{
//			auto goaltime = GoalTimeUI::Create(Vec2(camerasize.x * 0.15f, camerasize.y * 0.2f));
//			for (int i = 0; i < 5; ++i)
//			{
//				auto time = FrameTimeUI::Create(Vec2(goaltime->position.x + goaltime->Scale.x + (20 + i * 64), goaltime->position.y + 20), i, FrameTime);
//			}
//			//生成するフラグをリセットする
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//次に生成するタスク
//			this->createtask.SetNextFlag(CreateFlag::Starui);
//		}
//		break;
//	case 1 << 1:
//		if ((this->createtask.createflag & CreateFlag::Starui) == CreateFlag::Starui)
//		{
//			//int selectflag[3] = { GameProcessManagement::Flag1,GameProcessManagement::Flag2,GameProcessManagement::Flag4 };
//
//			//for (int i = 0; i < 3; ++i)
//			//{
//			//	auto ster = FlagUI::Create(Vec2((camerasize.x / 2 - 200) + 100 * (i + 1), camerasize.y * 0.5f), selectflag[i]);
//			//}
//			//フラグのリセット
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//次に生成するタスク
//			this->createtask.SetNextFlag(CreateFlag::Effect);
//		}
//		break;
//	case 1 << 2:
//		if ((this->createtask.createflag & CreateFlag::Effect) == CreateFlag::Effect)
//		{
//			auto sters = OGge->GetTasks<FlagUI>("Ster");
//
//			//最初だけは条件なしで生成する
//			{
//				int count = 0;
//				for (auto id = sters->begin(); id != sters->end(); ++id, ++count)
//				{
//					if (count == 0)
//					{
//						auto effect = SterEffect::Create((*id));
//					}
//					else
//					{
//						auto Effect = OGge->GetTasks<SterEffect>("SterEffect");
//						if (!Effect)
//						{
//							continue;
//						}
//						auto effect = SterEffect::Create((*id), *(Effect->begin() + count - 1));
//					}
//				}
//			}
//			//生成するフラグをリセットする
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//次に生成するタスク
//			this->createtask.SetNextFlag(CreateFlag::Clearui);
//		}
//		break;
//	case 1 << 3:
//		if ((this->createtask.createflag & CreateFlag::Clearui) == CreateFlag::Clearui)
//		{
//			auto clearui = ClearUI::Create(Vec2(camerasize.x * 0.70f, camerasize.y / 2));
//			//フラグのリセット
//			this->createtask.ResetCreateFlag();
//			this->createtask.ResetNextFlag();
//			//次に生成するタスク
//			this->createtask.SetNextFlag(CreateFlag::NON);
//		}
//		break;
//	default:
//		break;
//	}	
//}
//int Result::to_String(std::string& text)
//{
//	std::istringstream ss;
//	ss = std::istringstream(text);
//
//	int num = atoi(text.c_str());
//	ss >> num;
//
//	return num;
//}
//void Result::Result_DataInput()
//{
//	std::string GameFalg;			//ゲームフラグ
//	//データの読み込み
//	std::ifstream fin(TimeFilePath);
//
//	if (!fin)
//	{
//		return;
//	}
//	//読み込んだデータを入れておく変数
//	std::string line;
//	//ファイル全体のテキストを読み込み
//	while (std::getline(fin, line))
//	{
//		//文字列を操作するための入力クラス、直接アクセスする
//		std::istringstream _fin(line);
//		//一字書き込み変数
//		std::string text;
//		
//		//タイムの書き込み
//		std::getline(_fin, text, ',');
//		(std::stringstream)text >> FrameTime;
//
//		//ステージごとのフラグを書き込む
//		std::string nowStagenumber;
//		int nowStage = 0;
//
//		//フラグの読み込み
//		while (std::getline(_fin, text, ','))
//		{
//			if (text == "Stage1")
//			{
//				nowStagenumber = text.substr(5);
//				//文字列からint型にする
//				nowStage = this->to_String(nowStagenumber);
//			}
//			else if(text == "Stage2")
//			{
//				nowStagenumber = text.substr(5);
//				//文字列からint型にする
//				nowStage = this->to_String(nowStagenumber);
//			}
//		}
//	}
//	fin.close();
//}
//int Result::GetFlag()
//{
//	return this->Flag;
//}
////----------------------------
////ここから下はclass名のみ変更する
////ほかは変更しないこと
////----------------------------
//Result::Result()
//{
//	std::cout << "結果画面処理　生成" << std::endl;
//	//カメラ座標を元に戻す
//	OGge->camera->SetPos(Vec2(0, 0));
//	//カメラのサイズを元に戻す
//	OGge->camera->SetSize(Vec2(60 * 16 , 60 * 9));
//	FrameTime = 0;
//}
//
//Result::~Result()
//{
//	this->Finalize();
//	std::cout << "結果画面処理　解放" << std::endl;
//}
//
//Result::SP Result::Create(bool flag_)
//{
//
//	Result::SP to = Result::SP(new Result());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize())
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}