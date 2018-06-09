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

#include "GameProcessManagement\GameClearCamera.h"
#include "GameProcessManagement\Timer.h"
#include "Task\Task_Pause.h"
#include "Task\StageSelect.h"
#include "Back\Back.h"
#include "Task_Title.h"
#include "Effect\Effect.h"

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{
	gamesoundname = "game.wav";
	tutorialsoundname = "tutorial.wav";
	//this->ResetKillCount();
}

Game::~Game()
{
	//解放処理と次のsceneの生成
	this->Finalize();
	//OGge->DeleteTasks();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		if (OGge->in->on(In::D1) && OGge->in->on(In::D2) && OGge->in->on(In::L1) && OGge->in->on(In::R1))
		{
			auto next = Title::Create();
		}
		else
		{
			if (*MapNum < 4)
			{
				*MapNum = *MapNum + 1;
				auto next = Game::Create();
			}
			//次にチュートリアルを控えているものは次のチュートリアルへ移動
			else if (*MapNum == 4)
			{
				//チュートリアル終了でセレクトに戻る
				auto next = StageSelect::Create();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	auto backImage = Back::Create(std::string("back.png"), 1920, 1080);
	//Pauseタスクの生成
	auto pause = Pause::Create();

	////switchまではそのまま
	//Vec2 bucketpos[2] = {
	//	{ 150,250 },
	//	{ 400,800 }
	//};

	//Vec2 blockpos = Vec2(1536, 70);  //1536,100
	_waterpos = { 200,100 };
	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 16,7 };

	std::cout << "Game初期化" << std::endl;

	//扇風機画像読み込み
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
	this->PaintTex.Create("paintTest.png");
	rm->SetTextureData((std::string)"paintTex", &this->PaintTex);
	this->EffectTest.Create("EffectTest.png");
	rm->SetTextureData((std::string)"Effect", &this->EffectTest);
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
	case 1:		//チュートリアル１
	{
		//map生成
		auto mapload = Map::Create((std::string)"tutorial1.csv");
		//水の位置
		_waterpos.x = 64 * 7;
		_waterpos.y = 64 * 15;
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
	}
	break;
	case 2:		//チュートリアル２
	{
		//map生成
		auto mapload = Map::Create((std::string)"tutorial2.csv");
		//水の位置(勘)
		_waterpos.x = 64 * 8;
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

	}
	break;
	case 3:		//チュートリアル３
		//位置変更
		_waterpos.x = 6 * 64;
		_waterpos.y = 64 * 12;
		{
			//map生成
			auto mapload = Map::Create((std::string)"tutorial3.csv");
			//チュートリアルのサウンドに使用
			sound.create(tutorialsoundname, true);
			sound.volume(1.0f);
			OGge->soundManager->SetSound(&sound);
			sound.play();

			//加熱器生成
			auto kanetuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 17), Vec2(64 * 2, 64), false);
			//auto kanetuki2 = Kanetuki::Create(Vec2(64 * 22, 64 * 17), false);
			//扇風機生成
			auto fan = Fan::Create(Vec2(64 * 14, 64 * 7), 13, Fan::Dir::RIGHT, true);
			//加熱器用スイッチ生成
			auto swich = Switch::Create(Vec2(64 * 18, 64 * 16), std::vector<std::shared_ptr<GameObject>>{kanetuki1/*, kanetuki2*/}, Switch::TargetType::Heater);
		}
		break;
	case 4:		//チュートリアル４
	{
		//map生成
		auto mapload = Map::Create((std::string)"tutorial4.csv");
		//水の位置
		_waterpos.x = 64 * 5;
		_waterpos.y = 64 * 2;
		//チュートリアルのサウンドに使用
		sound.create(tutorialsoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();
		//加熱器生成
		auto kanetuki = Kanetuki::Create(Vec2(17 * 64, 18 * 64), Vec2(64, 64), false);
		//製氷機生成
		auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 10 * 64), Vec2(64 * 2, 64));
		//製氷機用スイッチ生成
		auto iceSwitch = Switch::Create(Vec2(64 * 7, 64 * 8), std::vector<std::shared_ptr<GameObject>>{seihyouki}, Switch::TargetType::IceMachine);
		//加熱器用スイッチ生成
		auto heaterSwitch = Switch::Create(Vec2(64 * 14, 64 * 15), std::vector<std::shared_ptr<GameObject>>{kanetuki}, Switch::TargetType::Heater);
	}
	break;
	case 5:		//ステージ１
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage1.csv");

		//ゲームのサウンドに使用
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//スイッチを対象にした扇風機の生成
		auto fan1 = Fan::Create(fanpos[1], fanrange[1], Fan::Dir::LEFT, false);
		//fanを対象にした扇風機の生成（スイッチによって扇風機を入れ替えることができる）
		auto fan2 = Fan::Create(fanpos[0], fanrange[0], Fan::Dir::RIGHT, true);
		//加熱器生成
		auto kanetuki1 = Kanetuki::Create(Vec2(64 * 19, 64 * 15 - 32), Vec2(64 * 2, 84), false);		//ToDo:位置を変えるのではなく判定範囲を広げること
		//auto kanetuki2 = Kanetuki::Create(Vec2(64 * 20, 64 * 15 - 32), false);
		//製氷機生成
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 6, 64 * 7), Vec2(64 * 2, 64));
		//auto seihyouki2 = Seihyouki::Create(Vec2(64 * 7, 64 * 7));

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
	}
	break;
	case 6:
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage2.csv");
		//水の位置
		_waterpos.x = 64 * 9 + 32;
		_waterpos.y = 64 * 3;

		//ゲームのサウンドに使用
		sound.create(gamesoundname, true);
		sound.volume(1.0f);
		OGge->soundManager->SetSound(&sound);
		sound.play();

		//扇風機
		Vec2 fanpos[5] = { Vec2(64 * 11,64 * 6),Vec2(64 * 20,64 * 6),Vec2(64 * 25,64 * 17),Vec2(64 * 30,64 * 23),Vec2(64 * 34,64 * 27) };
		auto fan1 = Fan::Create(fanpos[0], 7, Fan::Dir::LEFT, true);
		auto fan2 = Fan::Create(fanpos[1], 12, Fan::Dir::RIGHT, true);
		auto fan3 = Fan::Create(fanpos[2], 15, Fan::Dir::LEFT, true);
		auto fan4 = Fan::Create(fanpos[3], 8, Fan::Dir::RIGHT, true);
		auto fan5 = Fan::Create(fanpos[4], 4.5f, Fan::Dir::LEFT, false);
		//加熱器
		auto kanetsuki1 = Kanetuki::Create(Vec2(64 * 21, 64 * 21 - 20), Vec2(64 * 3, 84), false);
		//auto kanetsuki2 = Kanetuki::Create(Vec2(64 * 22, 64 * 21 - 20), false);
		//auto kanetsuki3 = Kanetuki::Create(Vec2(64 * 23, 64 * 21 - 20), false);
		auto kanetsuki4 = Kanetuki::Create(Vec2(64 * 18, 64 * 29), Vec2(64 * 5, 64 + 32), true);
		//auto kanetsuki5 = Kanetuki::Create(Vec2(64 * 19, 64 * 29 + 32), true);
		//auto kanetsuki6 = Kanetuki::Create(Vec2(64 * 20, 64 * 29 + 32), true);
		//auto kanetsuki7 = Kanetuki::Create(Vec2(64 * 21, 64 * 29 + 32), true);
		//auto kanetsuki8 = Kanetuki::Create(Vec2(64 * 22, 64 * 29 + 32), true);
		auto kanetsuki9 = Kanetuki::Create(Vec2(64 * 33, 64 * 32 - 20), Vec2(64 * 2, 84) , true);
		//auto kanetsuki10 = Kanetuki::Create(Vec2(64 * 34, 64 * 32 - 20), true);
		//製氷機
		auto seihyouki1 = Seihyouki::Create(Vec2(64 * 9, 64 * 12), Vec2(64 * 2, 64));
		//auto seihyouki2 = Seihyouki::Create(Vec2(64 * 10, 64 * 12));
		auto seihyouki3 = Seihyouki::Create(Vec2(64 * 9, 64 * 22), Vec2(64 * 2, 64));
		//auto seihyouki4 = Seihyouki::Create(Vec2(64 * 10, 64 * 22));
		//扇風機スイッチ
		auto fanSwitch1 = Switch::Create(Vec2(64 * 19, 64 * 12), std::vector<std::shared_ptr<GameObject>>{fan2, fan3}, Switch::TargetType::Fan);
		auto fanSwitch2 = Switch::Create(Vec2(64 * 31, 64 * 31), std::vector<std::shared_ptr<GameObject>>{fan4, fan5}, Switch::TargetType::Fan);
		//加熱器スイッチ
		auto heaterSwitch1 = Switch::Create(Vec2(64 * 20, 64 * 20), std::vector<std::shared_ptr<GameObject>>{kanetsuki1/*, kanetsuki2, kanetsuki3*/}, Switch::TargetType::Heater);
	//	auto heaterSwitch2 = Switch::Create(Vec2(64 * 35, 64 * 31), std::vector<std::shared_ptr<GameObject>>{kanetsuki5, kanetsuki6, kanetsuki7}, Switch::TargetType::Heater);
		//製氷機スイッチ
		auto iceSwitch = Switch::Create(Vec2(64 * 12, 64 * 20), std::vector<std::shared_ptr<GameObject>>{seihyouki1, /*seihyouki2,*/ seihyouki3/*, seihyouki4*/}, Switch::TargetType::IceMachine);
		//ブロック
		auto block = Block::Create(Vec2(64 * 20, 64 * 29));
		auto block2 = Block::Create(Vec2(64 * 33, 64 * 10));
		//this->Kill();
		break;
	}
	default:
		std::cout << "マップ番号が存在しません" << std::endl;
		break;
	}
	//水初期処理
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

	//水が自動で降ってくる時間の初期化
	this->timecnt = 0;
	//水の生成
	auto water = Water::Create(_waterpos);
	//画像を渡す
	water->SetTexture(&this->waterTex);
	switch (*MapNum)
	{
	case 3:
		//プレイヤーの位置を変更
	//	player->SetPos(Vec2(200, 400));
		break;
	default:
		break;
	}
	//タスクに名前を登録
	__super::Init((std::string)"game");
	//ゲームクリア判定を生成
	auto gameprocess = GameProcessManagement::Create();
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

	// Pause処理
	if (OGge->in->key.down(In::D2)){
		OGge->SetPause(true);
	}

	//UI
	UImng_->UpDate();

	if (OGge->in->on(In::D1) && OGge->in->on(In::D2))
	{
		this->Kill();
	}

	if (OGge->in->key.down(In::E))
	{
		auto player = OGge->GetTask<Player>("Player");
		if (player)
		{
			auto effect = Effect::Create(player->position, Vec2(64, 64), Vec2(64, 64), 13, 60, 5);
			effect->SetTexture(rm->GetTextureData((std::string)"Effect"));
			effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 200));
		}
	}

	{
		auto goal = OGge->GetTask<Goal>("Goal");
		if (goal != nullptr)
		{
			if (OGge->in->key.down(Input::KeyBoard::Q))
			{
				goal->cleared = true;
			}
		}

		auto cameraMove = OGge->GetTask<GameClearCamera>("GameClearCamera");
		if (cameraMove != nullptr)
		{
			if (cameraMove->GetCameraMoveFinish())
			{
				this->Kill();
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{

}
//-------------------------------------------------------------------------------------------------
bool Game::Finalize()
{
	std::cout << "Game解放" << std::endl;
	//各オブジェクトが存在している場合にKillする。
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
	auto gamepros = OGge->GetTasks<GameProcessManagement>("GameProcessManagement");
	for (auto id = (*gamepros).begin(); id != (*gamepros).end(); ++id)
	{
		(*id)->Kill();
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		(*id)->Kill();
	}
	auto gamecamera = OGge->GetTasks<GameClearCamera>("GameClearCamera");
	for (auto id = (*gamecamera).begin(); id != (*gamecamera).end(); ++id)
	{
		(*id)->Kill();
	}
	auto timers = OGge->GetTasks<Timer>("Timer");
	for (auto id = (*timers).begin(); id != (*timers).end(); ++id)
	{
		(*id)->Kill();
	}
	/*auto pauses = OGge->GetTasks<Pause>("pause");
	for (auto id = pauses->begin(); id != pauses->end(); ++id)
	{
		(*id)->Kill();
	}*/
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
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	rm->DeleteTexture((std::string)"Effect");
	rm->DeleteTexture((std::string)"paintTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
	this->EffectTest.Finalize();
	this->waterBlue.Finalize();
	this->waterPurple.Finalize();
	this->waterRed.Finalize();
	this->PaintTex.Finalize();
	return true;
}
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	//デバッグ用
	//std::cout << OGge->camera->GetSize().x << "//"<<OGge->camera->GetPos().x << std::endl;
	//カメラの移動
	auto goal = OGge->GetTask<Goal>("Goal");
	if (goal != nullptr)
	{
		if (goal->ClearCheck())
		{
			return;
		}
	}
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (player && map)
	{
		OGge->camera->MovePos(player->GetEst());

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
		if (NowCameraPos.x + NowCameraSize.x >(map->mapSize.x - 1) * map->DrawSize.x) {
			NowCameraPos.x = ((map->mapSize.x - 1)* map->DrawSize.x) - NowCameraSize.x;
		}
		if (NowCameraPos.y < 0) {
			NowCameraPos.y = 0;
		}
		if (NowCameraPos.y + NowCameraSize.y >(map->mapSize.y)* map->DrawSize.y) {
			NowCameraPos.y = ((map->mapSize.y)* map->DrawSize.y) - NowCameraSize.y;
		}

		OGge->camera->SetPos(NowCameraPos);
	}
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