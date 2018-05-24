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

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{

}

Game::~Game()
{
	//解放処理と次のsceneの生成
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		auto nextTask = Result::Create(true);
	}
}

//-------------------------------------------------------------------------------------------------
bool Game::Initialize()
{
	//switchまではそのまま
	Vec2 bucketpos[2] = {
		{ 150,250 },
		{ 400,800 }
	};

	Vec2 blockpos = Vec2(1536, 100);  //1536,100
	_waterpos = { 200,100 };
	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 18,6 };

	std::cout << "Game" << std::endl;

	//扇風機画像読み込み
	this->fanTex.Create((std::string)"fan.png");
	this->playerTex.Create((std::string)"player2.png");
	rm->SetTextureData((std::string)"playerTex", &this->playerTex);
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
		//ui生成
		auto uiwalk = UI::Create(Vec2(200, 300), Box2D(100, 300, 200, 300), (std::string)"walkui.png", 300, 4);
		auto uijump = UI::Create(Vec2(400, 300), Box2D(400, 300, 200, 300), (std::string)"pusha.png", 300, 2);
		auto uigetbucket = UI::Create(Vec2(1200, 200), Box2D(1150, 200, 100, 200), (std::string)"pushb.png", 300, 2);
		auto uigetwater = UI::Create(Vec2(100, 200), Box2D(0, 0, 0, 0), (std::string)"arrowdown.png", 300, 1);
		auto apillwater = UI::Create(Vec2(1600, 200), Box2D(1550, 200, 300, 200), (std::string)"pushx.png", 300, 2);
		//バケツ生成
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//ゴール生成
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true, Vec2(25 * 64, 5 * 64));
		}
	}
	break;
	case 2:		//チュートリアル２
	{
		//map生成
		auto mapload = Map::Create((std::string)"tutorial2.csv");
		//バケツ生成
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//goal生成
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true, Vec2(10 * 64, 10 * 64));
		}
	}
	break;
	case 3:		//チュートリアル３
		//位置変更
		_waterpos.y += 64 * 4;
		{
			//map生成
			auto mapload = Map::Create((std::string)"tutorial3.csv");
			//加熱器生成
			auto kanetuki = Kanetuki::Create(Vec2(64 * 12, 64 * 10));
			//バケツ生成
			for (int i = 0; i < 1; ++i)
			{
				auto bucket = Bucket::Create(Vec2(100, 400));
			}
			//goal生成
			for (int i = 0; i < 1; ++i)
			{
				auto goal = Goal::Create(true, Vec2(16 * 64, 8 * 64));
			}
			//扇風機生成
			for (int i = 0; i < 1; ++i)
			{
				auto fan = Fan::Create(Vec2(64, 64 * 2), fanrange[0], Fan::Dir::RIGHT, true);
				fan->SetTexture(&this->fanTex);
				fan->SetWindRange(Vec2(64 * 15, 64));
			}
		}
		break;
	case 4:		//チュートリアル４
	{
		//map生成
		auto mapload = Map::Create((std::string)"tutorial4.csv");
		//加熱器生成
		auto kanetuki = Kanetuki::Create(Vec2(16 * 64, 18 * 64));
		//バケツ生成
		for (int i = 0; i < 1; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}
		//製氷機生成
		for (int i = 0; i < 2; ++i)
		{
			auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 11 * 64));
		}
	}
	break;
	case 5:		//ステージ１
	{
		//map生成
		auto mapload = Map::Create((std::string)"stage1.csv");
		//加熱器生成
		for (int i = 0; i < 2; ++i)
		{
			auto kanetuki = Kanetuki::Create(Vec2(64 * (18 + i), 64 * 16));
		}
		for (int i = 0; i < 2; ++i)
		{
			//製氷機生成
			auto seihyouki = Seihyouki::Create(Vec2(64 * 5, 64 * 7));
			//扇風機生成
			auto fan = Fan::Create(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT);
			fan->SetTexture(&this->fanTex);
		}
		auto swith = Switch::Create(Vec2(64 * 18,64 * 13),OGge->GetTask<Player>("player"),true);
		//バケツ生成
		/*for (int i = 0; i < 2; ++i)
		{
			auto bucket = Bucket::Create(bucketpos[i]);
		}*/
		//ブロック生成
		for (int i = 0; i < 1; ++i)
		{
			auto block = Block::Create(blockpos);
		}
		//ゴール生成
		for (int i = 0; i < 1; ++i)
		{
			auto goal = Goal::Create(true);
		}
	}
	break;
	case 6:
		this->Kill();
		break;
	default:
		std::cout << "マップ番号が存在しません" << std::endl;
		break;
	}
	//水初期処理
	{
		//水画像の読み込み
		this->waterTex.Create((std::string)"waterTex.png");
		//リソース管理classへデータを渡す
		rm->SetTextureData((std::string)"waterTex", &waterTex);
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

	if (OGge->in->on(Input::in::D2, 0) && OGge->in->on(In::D1))
	{
		this->Kill();
	}

	{
		auto goal = OGge->GetTask<Goal>("Goal");
		if (goal != nullptr)
		{
			if (OGge->in->key.down(Input::KeyBoard::ENTER))
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
	std::cout << "Game" << std::endl;
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
	rm->DeleteTexture((std::string)"playerTex");
	rm->DeleteTexture((std::string)"waterTex");
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
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
		float camera_x = float(player->position.x) - PlayerCenter_x;
		float camera_y = float(player->position.y) - PlayerCenter_y;
		//カメラの座標を更新
		NowCameraPos.x = camera_x;
		NowCameraPos.y = camera_y;


		//左右のスクロール範囲の設定(サイズの10分の1)
		float Boundary = NowCameraSize.x / 10.0f;
		//現在スクロール値とプレイヤーの座標の差を修正
		Vec2 NowPlayerPos = { player->position.x - NowCameraPos.x,player->position.y - NowCameraPos.y };
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