#include "Task_Game.h"
#include "Task\Task_Result.h"
#include "Map\Map.h"
#include "Player\Player.h"
#include "Block\block.h"
#include "Bucket\bucket.h"
#include "Goal\Goal.h"
#include "Water\water.h"
#include "GameProcessManagement\GameProcessManagement.h"
#include "UI\UI.h"
#include "Gimmick\NO_MOVE\Kanetuki.h"
#include "Gimmick\NO_MOVE\Seihyouki.h"
#include "Gimmick\NO_MOVE\Senpuki.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Gimmick\NO_MOVE\TimeSign.h"
#include "GameProcessManagement\Timer.h"
#include "Task\Task_Pause.h"
#include "Task\StageSelect.h"
#include "Back\Back.h"
#include "Task_Title.h"
#include "Effect\Effect.h"
#include "Map\Ornament.h"
#include "Load\LoadLogo.h"
#include "Gimmick\NO_MOVE\Door.h"
#include "UI/GoalDirectionUI.h"
#include "VolumeControl/volumeControl.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{
	gamesoundname = "game.wav";
	tutorialsoundname = "tutorial.wav";

	this->canvolControl = true;
	//this->ResetKillCount();
	OGge->camera->SetSize(Vec2(1920, 1080));
}

Game::~Game()
{
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
	}
	//解放処理と次のsceneの生成
	this->Finalize();
	//OGge->DeleteTasks();


}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	OGge->camera->SetSize(Vec2(1280, 720));
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);

	//Pauseタスクの生成
	auto pause = Pause::Create();

	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 16,7 };
	//扇風機画像読み込み
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
	this->fireice.Create((std::string)"fireice.png");
	rm->SetTextureData((std::string)"fireIce", &this->fireice);
	this->PaintTex.Create("paintTest.png");
	rm->SetTextureData((std::string)"paintTex", &this->PaintTex);
	this->EffectTest.Create("EffectTest.png");
	rm->SetTextureData((std::string)"Effect", &this->EffectTest);
	this->Effectsond.Create("sandsmoke.png");
	rm->SetTextureData((std::string)"sandsmoke", &this->Effectsond);
	this->texSteam.Create("steam.png");
	rm->SetTextureData(std::string("steam"), &this->texSteam);
	this->goalTex.Create("goal.png");
	rm->SetTextureData((std::string)"goalTex", &this->goalTex);
	this->goalDirectionTex.Create((std::string)"goalarrow.png");
	rm->SetTextureData((std::string)"goalDirectionTex", &this->goalDirectionTex);
	this->arrowflower.Create((std::string)"arrowflower.png");
	rm->SetTextureData((std::string)"arrowflowerTex", &this->arrowflower);
	this->doorTex.Create("door.png");
	rm->SetTextureData((std::string)"WswitchTex", &this->WswitchTex);
	this->WswitchTex.Create("Collision.png");
	this->pipeTex.Create("pipe.png");
	//ui生成
	UImng_.reset(new UImanager());
	UImng_->Initialize(*MapNum);
	//マップ初期処理
	switch (*MapNum)
	{
	case 0:
		//txt読み込み消したので削除しています。
		this->Kill();
		break;
	case 1:		//水１
	{
		//map生成
		auto mapload = Map::Create((std::string)"water1.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		break;
	}
	case 2:		//水２
	{
		//map生成
		auto mapload = Map::Create((std::string)"water2.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		break;
	}
	case 3:		//水３
	{
		//map生成
		auto mapload = Map::Create((std::string)"water3.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 4:		//水4
	{
		//map生成
		auto mapload = Map::Create((std::string)"water4.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		break;
	}
	case 5:		//氷1
	{
		//map生成
		auto mapload = Map::Create((std::string)"ice1.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器生成
		auto kanetuki = Kanetuki::Create(Vec2(17 * 64, 18 * 64), Vec2(64, 64), Kanetuki::Angle::RIGHT, false);
		//製氷機生成
		auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 10 * 64), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT, false);
		//製氷機用スイッチ生成
		auto iceSwitch = Switch::Create(Vec2(64 * 7, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//加熱器用スイッチ生成
		auto heaterSwitch = Switch::Create(Vec2(64 * 14, 64 * 15), std::vector<std::shared_ptr<GameObject>>{kanetuki}, Switch::TargetType::Heater);
		break;
	}
	case 6:		//氷2
	{
		//map生成
		auto mapload = Map::Create((std::string)"ice2.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器
		Kanetuki::Create(Vec2(64 * 21, 64 * 8), Vec2(64 * 2, 64), Kanetuki::Angle::LEFT, true);
		//製氷機
		auto seihyouki = Seihyouki::Create(Vec2(64 * 3, 64 * 6), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT, false);
		//製氷機スイッチ
		Switch::Create(Vec2(64 * 13, 64 * 4), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);

		break;
	}
	case 7:		//氷3
	{
		//map生成
		auto mapload = Map::Create((std::string)"ice3.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器
		Kanetuki::Create(Vec2(64 * 9, 64 * 6), Vec2(64 * 5, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		Kanetuki::Create(Vec2(64 * 23, 64 * 7), Vec2(64 * 3, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		//製氷機
		auto seihyouki = Seihyouki::Create(Vec2(64 * 4, 64 * 4), Vec2(64 * 2.5f, 64.f), Seihyouki::Angle::RIGHT, false);
		//製氷機スイッチ
		Switch::Create(Vec2(64 * 3, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);

		break;
	}
	case 8:		//氷4
	{
		//map生成
		auto mapload = Map::Create((std::string)"ice4.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器
		//Kanetuki::Create(Vec2(64 * 17, 64 * 5), Vec2(64, 64 * 2), Kanetuki::Angle::BOTTOM, true);
		//製氷機
		auto seihyouki = Seihyouki::Create(Vec2(64 * 6, 64 * 5), Vec2(64 * 2.5f, 64.f), Seihyouki::Angle::RIGHT, false);
		//製氷機スイッチ
		Switch::Create(Vec2(64 * 5, 64 * 9), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//重さドア
		auto door = Door::Create(Vec2(64 * 13, 64 * 6), Vec2(32, 64 * 2), false, Door::Direction::HEIGHT);
		door->SetTexture(&doorTex);
		//重さスイッチ
		auto ws = WeightSwitch::Create(Vec2(64 * 2 + 32, 64 * 9 + 34), Vec2(64 * 2, 30), 1, std::vector<std::shared_ptr<GameObject>>{door});
		ws->SetTexture(&WswitchTex);
		break;
	}
	case 9:		//蒸気1
	{
		//map生成
		auto mapload = Map::Create((std::string)"steam1.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器生成
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 15, 64 * 10 - 32), Vec2(64 * 2, 64+32), Kanetuki::Angle::UP, false);
		//扇風機生成
		auto fan = Fan::Create(Vec2(64 * 11, 64 * 2), 10, Fan::Dir::RIGHT, 64 * 5, true);
		//加熱器用スイッチ生成
		auto swich = Switch::Create(Vec2(64 * 13, 64 * 9), std::vector<std::shared_ptr<GameObject>>{kanetuki1/*, kanetuki2*/}, Switch::TargetType::Heater);
		break;
	}
	case 10:	//蒸気2
	{
		//map生成
		auto mapload = Map::Create((std::string)"steam2.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器生成
		Kanetuki::Create(Vec2(64 * 9, 64 * 19 - 32), Vec2(64 * 3, 64 + 32), Kanetuki::Angle::UP, true);
		//扇風機
		auto fan1 = Fan::Create(Vec2(64 * 8, 64 * 15), 8, Fan::Dir::RIGHT, 64, true);
		auto fan2 = Fan::Create(Vec2(64 * 17, 64 * 11), 9, Fan::Dir::LEFT, 64*9, false);
		auto fan3 = Fan::Create(Vec2(64 * 8, 64 * 5), 9, Fan::Dir::RIGHT, 64, false);
		auto fan4 = Fan::Create(Vec2(64 * 17, 64), 13, Fan::Dir::LEFT, 64*13, true);
		//扇風機スイッチ
		Switch::Create(Vec2(64 * 12, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan1, fan2}, Switch::TargetType::Fan);
		Switch::Create(Vec2(64 * 13, 64 * 6), std::vector<std::shared_ptr<GameObject>>{fan3, fan4}, Switch::TargetType::Fan);

		break;
	}
	case 11:	//蒸気3
	{
		//map生成
		auto mapload = Map::Create((std::string)"steam3.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器
		Kanetuki::Create(Vec2(64 * 10, 64 * 10 - 32), Vec2(64 * 3, 64 + 32), Kanetuki::Angle::UP, true);
		//製氷機
		auto seihyouki = Seihyouki::Create(Vec2(64 * 2, 64 * 7), Vec2(64 * 1.5f, 64.f), Seihyouki::Angle::RIGHT, false);
		//扇風機
		Fan::Create(Vec2(64 * 5, 64 * 2), 8.5f, Fan::Dir::RIGHT, 64, true);
		//製氷機スイッチ
		Switch::Create(Vec2(64 * 4, 64 * 9), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);

		break;
	}
	case 12:	//蒸気4
	{
		//map生成
		auto mapload = Map::Create((std::string)"steam4.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//加熱器
		Kanetuki::Create(Vec2(64 * 12, 64 * 15 - 20), Vec2(64 * 3, 64 + 20), Kanetuki::Angle::UP, true);
		//扇風機
		Fan::Create(Vec2(64 * 11, 64 * 2), 8, Fan::Dir::RIGHT, 64, true);

		break;
	}
	case 13:		//ステージ１
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage1.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();

		//テスト追加重さで反応するswitchのscale.yは30規定でお願いします
		//auto wswitch = WeightSwitch::Create(Vec2(400, 920), Vec2(200, 30), 1.0f);
		//wswitch->SetTexture(&WswitchTex);

		//ゲームのサウンドに使用
		sound.create(gamesoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//扇風機の生成
		auto fan1 = Fan::Create(fanpos[1], fanrange[1], Fan::Dir::LEFT, 64 * 8, false);
		auto fan2 = Fan::Create(fanpos[0], fanrange[0], Fan::Dir::RIGHT, 64 * 9, true);
		//加熱器生成
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 19, 64 * 15 - 32), Vec2(64 * 2, 84), Kanetuki::Angle::UP, false);
		//製氷機生成
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 6, 64 * 7), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT, false);

		//スイッチの生成
		//扇風機用
		{auto swith = Switch::Create(Vec2(64 * 18, 64 * 8), std::vector<std::shared_ptr<GameObject>>{ fan1, fan2 }, Switch::TargetType::Fan); }
		//加熱器用
		{auto swith = Switch::Create(Vec2(64 * 17, 64 * 14), std::vector<std::shared_ptr<GameObject>>{ kanetuki1/*, kanetuki2*/ }, Switch::TargetType::Heater); }
		//製氷機用
		{auto swith = Switch::Create(Vec2(64 * 5, 64 * 5), std::vector<std::shared_ptr<GameObject>>{ seihyouki1/*, seihyouki2*/ }, Switch::TargetType::IceMachine); }

		//ブロック生成
		for (int i = 0; i < 1; ++i)
		{
			auto block = Block::Create(Vec2(1536, 70));
		}
		break;
	}
	case 14:	//ステージ2
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage2.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();
		//ゲームのサウンドに使用
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//扇風機
		Fan::Create(Vec2(64 * 16, 64 * 4), 6, Fan::Dir::RIGHT, 7, true);
		//加熱器
		Kanetuki::Create(Vec2(64 * 16, 64 * 12 + 32), Vec2(64 * 3, 64 + 32), Kanetuki::Angle::UP, true);
		//製氷機
		auto seihyouki = Seihyouki::Create(Vec2(64 * 3, 64 * 4), Vec2(64 * 2, 64), Seihyouki::Angle::RIGHT, false);
		//switch
		Switch::Create(Vec2(64 * 2, 64 * 9), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//横向き扉
		auto door1 = Door::Create(Vec2(64 * 3, 64 * 11), Vec2(64 * 3, 32), false, Door::Direction::WIDTH);
		auto door2 = Door::Create(Vec2(64 * 3, 64 * 13), Vec2(64 * 3, 32), false, Door::Direction::WIDTH);
		door1->SetTexture(&doorTex);
		door2->SetTexture(&doorTex);
		//重さスイッチ
		auto ws1 = WeightSwitch::Create(Vec2(64, 64 * 9 + 30), Vec2(64, 30), 1, std::vector<std::shared_ptr<GameObject>>{door2});
		ws1->SetTexture(&WswitchTex);
		auto ws2 = WeightSwitch::Create(Vec2(64*22, 64*12+30), Vec2(64, 30), 2, std::vector<std::shared_ptr<GameObject>>{door1});
		ws2->SetTexture(&WswitchTex);
		break;
	}
	case 15:	//ステージ3
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage3.csv");
		//水の位置
		_waterpos = mapload->getWaterPos();

		//ゲームのサウンドに使用
		sound.create(gamesoundname, true);
		sound.volume(0.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//扇風機
		Vec2 fanpos[5] = { Vec2(64 * 11,64 * 6),Vec2(64 * 20,64 * 4),Vec2(64 * 26,64 * 17),Vec2(64 * 30,64 * 23),Vec2(64 * 34,64 * 27) };
		auto fan1 = Fan::Create(fanpos[0], 7, Fan::Dir::LEFT, 64 * 7, true);
		auto fan2 = Fan::Create(fanpos[1], 11, Fan::Dir::RIGHT, 64 * 5, true);
		auto fan3 = Fan::Create(fanpos[2], 19, Fan::Dir::LEFT, 64 * 19, true);
		auto fan4 = Fan::Create(fanpos[3], 8, Fan::Dir::RIGHT, 64 * 2, true);
		auto fan5 = Fan::Create(fanpos[4], 4.5f, Fan::Dir::LEFT, 64 * 5, false);
		//加熱器
		auto kanetsuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 21 - 20), Vec2(64 * 3, 84), Kanetuki::Angle::UP, false);
		auto kanetsuki4 = Kanetuki::Create(Vec2(64 * 18, 64 * 29), Vec2(64 * 5, 64 + 32), Kanetuki::Angle::BOTTOM, true);
		auto kanetsuki9 = Kanetuki::Create(Vec2(64 * 33, 64 * 32 - 20), Vec2(64 * 2, 84), Kanetuki::Angle::UP, true);
		//製氷機
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 9, 64 * 12), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT, false);
		auto seihyouki3 = Seihyouki::Create(Vec2(64 * 9, 64 * 22), Vec2(64 * 2, 64), Seihyouki::Angle::LEFT, false);
		//扇風機スイッチ
		auto fanSwitch1 = Switch::Create(Vec2(64 * 19, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan2, fan3}, Switch::TargetType::Fan);
		auto fanSwitch2 = Switch::Create(Vec2(64 * 31, 64 * 31), std::vector<std::shared_ptr<GameObject>>{fan4, fan5}, Switch::TargetType::Fan);
		//加熱器スイッチ
		auto heaterSwitch1 = Switch::Create(Vec2(64 * 20, 64 * 20), std::vector<std::shared_ptr<GameObject>>{kanetsuki1/*, kanetsuki2, kanetsuki3*/}, Switch::TargetType::Heater);
		//製氷機スイッチ
		auto iceSwitch = Switch::Create(Vec2(64 * 12, 64 * 20), std::vector<std::shared_ptr<GameObject>>{seihyouki1, /*seihyouki2,*/ seihyouki3/*, seihyouki4*/}, Switch::TargetType::IceMachine);
		//ブロック
		auto block = Block::Create(Vec2(64 * 20, 64 * 29));
		auto block2 = Block::Create(Vec2(64 * 33, 64 * 11));
		break;
	}
	default:
		std::cout << "マップ番号が存在しません" << std::endl;
		break;
	}	//水初期処理
	{
		//水画像の読み込み
		this->waterTex.Create("waterTex.png");
		this->waterRed.Create("WaterRed.png");
		this->waterBlue.Create("WaterBlue.png");
		this->waterPurple.Create("WaterPurple.png");
		//リソース管理classへデータを渡す
		rm->SetTextureData((std::string)"waterTex", &this->waterTex);
		rm->SetTextureData((std::string)"waterRed", &this->waterRed);
		rm->SetTextureData((std::string)"waterBlue", &this->waterBlue);
		rm->SetTextureData((std::string)"waterPurple", &this->waterPurple);
	}
	auto back2Img = Back::Create("back2.png", 1920, 1080);
	back2Img->SetScroll();
	back2Img->SetDrawOrder(0.0f);
	//水が自動で降ってくる時間の初期化
	this->timecnt = 0;
	//水の生成
	auto water = Water::Create(_waterpos);
	//画像を渡す
	water->SetTexture(&this->waterTex);

	//タスクに名前を登録
	__super::Init((std::string)"game");
	__super::SetDrawOrder(0.25f);
	//ゲームクリア判定を生成
	auto gameprocess = GameManager::Create();
	//装飾
	auto ornament = Ornament::Create();
	return true;
}
//-------------------------------------------------------------------------------------------------
void Game::UpDate()
{
	timecnt++;
	if (timecnt >= 120)
	{
		timecnt = 0;
		auto water = Water::Create(_waterpos);
		water->SetTexture(&this->waterTex);
	}
	//カメラ処理
	Camera_move();
	ce.CameraMove();
	// Pause処理
	auto player = OGge->GetTask<Player>("Player");
	if (player)
	{
		if (OGge->in->down(In::D2) && !player->GetInput()) {
			if (!player->GetInputAuto())
			{
				OGge->SetPause(true);
			}
		}
	}

	//フェードアウト
	//フェードイン
	if (canvolControl)
	{
		sound.volume(volControl.FadeIn(canvolControl));
	}
	if (canvolControl == false)
	{
		sound.volume(volControl.FadeOut(true));
	}


	//UI
	UImng_->UpDate();
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//水生成位置のパイプ
	{
		Box2D draw(_waterpos.x - 103, _waterpos.y - 150, 256.f, 171.f);
		draw.OffsetSize();
		Box2D src(0, 0, 768, 512);
		pipeTex.Draw(draw, src);
	}
}
//-------------------------------------------------------------------------------------------------
bool Game::Finalize()
{
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		map->Kill();
	}
	auto block = OGge->GetTasks<Block>("block");
	for (auto id = (*block).begin(); id != (*block).end(); ++id)
	{
		(*id)->Kill();
	}
	auto UIs = OGge->GetTasks<UI>("UI");
	for (auto id = (*UIs).begin(); id != (*UIs).end(); ++id)
	{
		(*id)->Kill();
	}
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		(*id)->Kill();
	}
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = (*goals).begin(); id != (*goals).end(); ++id)
	{
		(*id)->Kill();
	}
	auto kanetukis = OGge->GetTasks<Kanetuki>("Kanetuki");
	for (auto id = (*kanetukis).begin(); id != (*kanetukis).end(); ++id)
	{
		(*id)->Kill();
	}
	auto fans = OGge->GetTasks<Fan>("Senpuki");
	for (auto id = (*fans).begin(); id != (*fans).end(); ++id)
	{
		(*id)->Kill();
	}
	auto seihyoukis = OGge->GetTasks<Seihyouki>("Seihyouki");
	for (auto id = (*seihyoukis).begin(); id != (*seihyoukis).end(); ++id)
	{
		(*id)->Kill();
	}
	auto players = OGge->GetTasks<Player>("Player");
	for (auto id = (*players).begin(); id != (*players).end(); ++id)
	{
		(*id)->Kill();
	}
	auto gamepros = OGge->GetTasks<GameManager>("GM");
	for (auto id = (*gamepros).begin(); id != (*gamepros).end(); ++id)
	{
		(*id)->Kill();
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		(*id)->Kill();
	}
	auto timers = OGge->GetTasks<Timer>("Timer");
	for (auto id = (*timers).begin(); id != (*timers).end(); ++id)
	{
		(*id)->Kill();
	}
	auto pauses = OGge->GetTasks<Pause>("pause");
	for (auto id = pauses->begin(); id != pauses->end(); ++id)
	{
		(*id)->Kill();
	}
	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	auto switches = OGge->GetTasks<Switch>("Switch");
	for (auto id = switches->begin(); id != switches->end(); ++id)
	{
		(*id)->Kill();
	}
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	auto ornament = OGge->GetTasks<Ornament>("Ornament");
	for (auto id = ornament->begin(); id != ornament->end(); ++id)
	{
		(*id)->Kill();
	}
	auto timer = OGge->GetTasks<TimeSign>("timesign");
	for (auto id = timer->begin(); id != timer->end(); ++id)
	{
		(*id)->Kill();
	}
	auto goalDirection = OGge->GetTasks<GoalDirection>("GoalDirection");
	for (auto id = goalDirection->begin(); id != goalDirection->end(); ++id)
	{
		(*id)->Kill();
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		(*id)->Kill();
	}
	auto ws = OGge->GetTasks<WeightSwitch>("WeightSwitch");
	for (auto id = ws->begin(); id != ws->end(); ++id) {
		(*id)->Kill();
	}
	auto paints = OGge->GetTasks<Paint>("Paint");
	for (auto id = paints->begin(); id != paints->end(); ++id)
	{
		(*id)->Kill();
	}
	auto clouds = OGge->GetTasks<Cloud>("cloud");
	for (auto id = clouds->begin(); id != clouds->end(); ++id) {
		(*id)->Kill();
	}
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	rm->DeleteTexture((std::string)"Effect");
	rm->DeleteTexture((std::string)"paintTex");
	rm->DeleteTexture((std::string)"sandsmoke");
	rm->DeleteTexture((std::string)"waterRed");
	rm->DeleteTexture((std::string)"waterBlue");
	rm->DeleteTexture((std::string)"waterPurple");
	rm->DeleteTexture((std::string)"steam");
	rm->DeleteTexture((std::string)"goalTex");
	rm->DeleteTexture((std::string)"fireIce");
	rm->DeleteTexture((std::string)"goalDirectionTex");
	rm->DeleteTexture((std::string)"arrowflowerTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
	this->EffectTest.Finalize();
	this->waterBlue.Finalize();
	this->waterPurple.Finalize();
	this->waterRed.Finalize();
	this->PaintTex.Finalize();
	this->Effectsond.Finalize();
	this->texSteam.Finalize();
	this->goalTex.Finalize();
	this->goalDirectionTex.Finalize();
	this->arrowflower.Finalize();
	this->doorTex.Finalize();
	return true;
}
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	//カメラの移動
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = goals->begin(); id != goals->end(); ++id)
	{
		if (!(*id)->GetLock())
		{
			return;
		}
	}
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (player && map)
	{
		if (!player->GetInputAuto())
		{
			//OGge->camera->MovePos(player->GetEst());

			//カメラ処理
			Vec2 NowCameraPos = OGge->camera->GetPos();
			Vec2 NowCameraSize = OGge->camera->GetSize();

			//プレイヤーを画面中央
			float PlayerCenter_x = NowCameraSize.x / 2.0f;
			float PlayerCenter_y = NowCameraSize.y / 2.0f;
			//カメラ座標を求める
			float camera_x = float(player->GetPos().x) - PlayerCenter_x;
			float camera_y = float(player->GetPos().y) - PlayerCenter_y;
			//カメラの座標を更新
			NowCameraPos.x = camera_x;
			NowCameraPos.y = camera_y;

			//左右のスクロール範囲の設定(サイズの10分の1)
			float Boundary = NowCameraSize.x / 10.0f;
			//現在スクロール値とプレイヤーの座標の差を修正
			Vec2 NowPlayerPos = { player->GetPos().x - NowCameraPos.x,player->GetPos().y - NowCameraPos.y };
			//x座標
			if (NowPlayerPos.x < Boundary) {
				NowCameraPos.x = NowPlayerPos.x - Boundary;
			}
			if (NowPlayerPos.x > NowCameraSize.x - Boundary) {
				NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
			}
			//y座標
			if (NowPlayerPos.y < Boundary) {
				NowCameraPos.y = NowPlayerPos.y - Boundary;
			}
			if (NowPlayerPos.y > NowCameraSize.y - Boundary) {
				NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
			}
			//画面外処理
			if (NowCameraPos.x < 0) {
				NowCameraPos.x = 0;
			}
			if (NowCameraPos.x + NowCameraSize.x > map->mapSize.x * map->DrawSize.x) {
				NowCameraPos.x = (map->mapSize.x * map->DrawSize.x) - NowCameraSize.x;
			}
			if (NowCameraPos.y < 0) {
				NowCameraPos.y = 0;
			}
			if (NowCameraPos.y + NowCameraSize.y > map->mapSize.y * map->DrawSize.y) {
				NowCameraPos.y = (map->mapSize.y * map->DrawSize.y) - NowCameraSize.y;
			}
			//OGge->camera->SetPos(NowCameraPos);
			this->CameraSetPos(NowCameraPos);
		}
	}
}
void Game::CameraSetPos(const Vec2& pos)
{
	ce.SetEndPos(pos);
}

Game::SP Game::Create(bool flag_)
{
	auto to = Game::SP(new Game());
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