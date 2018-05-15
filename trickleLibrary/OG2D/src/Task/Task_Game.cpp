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

#define ADD_FUNCTION(a) \
	[](std::vector<GameObject*>* objs_) { a(objs_); }

Game::Game()
{

}

Game::~Game()
{
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
		{ 100,250 },
		{ 400,800 }
	};

	Vec2 blockpos = Vec2(1536, 100);  //1536,100
	_waterpos = { 150,100 };
	Vec2 fanpos[2] = { Vec2(64 * 12,64 * 7), Vec2(64 * 20,64 * 10) };
	float fanrange[2] = { 18,6 };

	std::cout << "Game" << std::endl;

	//扇風機画像読み込み
	this->fanTex.Create((std::string)"fan.png");
	//マップ初期処理
	switch (*MapNum)
	{
	case 0:
		//txt読み込み消したので削除しています。
		this->Kill();
		break;
	case 1:
		//map.LoadMap((std::string)"tutorial1.csv", Format::csv);
		/*walkui.Initialize(Vec2(200, 300), Box2D(100, 300, 200, 300), (std::string)"walkui.png", 300, 4);
		walkui.SetPlayerPtr(&player);
		jumpui.Initialize(Vec2(400, 300), Box2D(400, 300, 200, 300), (std::string)"pusha.png", 300, 2);
		jumpui.SetPlayerPtr(&player);
		getbucketui.Initialize(Vec2(1200, 200), Box2D(1150, 200, 100, 200), (std::string)"pushb.png", 300, 2);
		getbucketui.SetPlayerPtr(&player);
		getwaterui.Initialize(Vec2(100, 200), Box2D(0, 0, 0, 0), (std::string)"arrowdown.png", 300, 1);
		getwaterui.SetPlayerPtr(&player);
		spillwaterui.Initialize(Vec2(1600, 200), Box2D(1550, 200, 300, 200), (std::string)"pushx.png", 300, 2);
		spillwaterui.SetPlayerPtr(&player);*/
		/*for (int i = 0; i < 1; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(bucketpos[i]);
		}
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Goal();
			this->goal.push_back(w);
			w->Initialize(Vec2(25 * 64, 5 * 64));
			gameprocess.Set_Goal(w);
		}*/
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
	case 2:
		/*map.LoadMap((std::string)"tutorial2.csv", Format::csv);
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(bucketpos[i]);
		}
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Goal();
			this->goal.push_back(w);
			w->Initialize(Vec2(10 * 64, 10 * 64));
			gameprocess.Set_Goal(w);
		}*/
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
	case 3:
		/*map.LoadMap((std::string)"tutorial3.csv", Format::csv);
		kanetuki.Create(Vec2(64 * 12, 64 * 10), Vec2(64, 64));
		kanetuki.SetWaterPool(&water);		*/
		/*for (int i = 0; i < 1; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(Vec2(100,400));
		}
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Goal();
			this->goal.push_back(w);
			w->Initialize(Vec2(16 * 64, 8 * 64));
			gameprocess.Set_Goal(w);
		}*/
		//位置変更
		_waterpos.y += 64 * 4;
		/*	fan[0].Initialize(Vec2(64, 64 * 2), fanrange[0], Fan::Dir::RIGHT, true);
		fan[0].SetTexture(&this->fanTex);
		fan[0].SetWindRange(Vec2(64 * 15, 64));*/
		{
			//map生成
			auto mapload = Map::Create((std::string)"tutorial3.csv");
			//加熱器生成
			//auto kanetuki = Kanetuki::Create(Vec2(64 * 12, 64 * 10), Vec2(64, 64));
			//バケツ生成
			for (int i = 0; i < 1; ++i)
			{
				auto bucket = Bucket::Create(Vec2(100, 400));
			}
			//goal生成
			for (int i = 0; i < 1; ++i)
			{
				//auto goal = Goal::Create(true, Vec2(16 * 64, 8 * 64));
			}
			//扇風機生成
			for (int i = 0; i < 1; ++i)
			{
			/*	auto fan = Fan::Create(Vec2(64, 64 * 2), fanrange[0], Fan::Dir::RIGHT, true);
				fan->SetTexture(&this->fanTex);
				fan->SetWindRange(Vec2(64 * 15, 64));*/
			}
		}
		break;
	case 4:
		/*map.LoadMap((std::string)"tutorial4.csv", Format::csv);
		kanetuki.Create(Vec2(16 * 64, 18 * 64), Vec2(64, 64));*/
		/*kanetuki.SetWaterPool(&water);
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(bucketpos[i]);
		}
		for (int i = 0; i < 2; ++i)
		{
			seihyouki[i].Create(Vec2(4 * 64, 11 * 64), Vec2(64,64));
			seihyouki[i].SetWaterPool(&water);
		}*/
		{
			//map生成
			auto mapload = Map::Create((std::string)"tutorial4.csv");
			//加熱器生成
			auto kanetuki = Kanetuki::Create(Vec2(16 * 64, 18 * 64), Vec2(64, 64));
			//バケツ生成
			for (int i = 0; i < 1; ++i)
			{
				auto bucket = Bucket::Create(bucketpos[i]);
			}
			//製氷機生成
			for (int i = 0; i < 2; ++i)
			{
				auto seihyouki = Seihyouki::Create(Vec2(4 * 64, 11 * 64), Vec2(64, 64));
			}
		}
		break;
	case 5:
		//map.LoadMap((std::string)"stage1.csv", Format::csv);
		//kanetuki.Create(Vec2(64 * 18, 64 * 16), Vec2(64 * 2, 64 * 2));
		//kanetuki.SetWaterPool(&water);
		//for (int i = 0; i < 2; ++i)
		//{
		//	seihyouki[i].Create(Vec2(64 * 5, 64 * 7), Vec2(64, 64));
		//	seihyouki[i].SetWaterPool(&water);
		//	//swich[i].Initialize(Vec2(64 * (10 + i * 2), 64 * 14));
		//	fan[i].Initialize(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT, true);
		//	fan[i].SetTexture(&this->fanTex);
		//}
		/*for (int i = 0; i < 2; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(bucketpos[i]);
		}*/
		/*	for (int i = 0; i < 1; ++i)
		{
			auto w = new Block();
			this->block.push_back(w);
			w->Initialize(blockpos);
		}
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Goal();
			this->goal.push_back(w);
			w->Initialize();
			gameprocess.Set_Goal(w);
		}*/
		{
			//map生成
			auto mapload = Map::Create((std::string)"stage1.csv");
			//加熱器生成
			auto kanetuki = Kanetuki::Create(Vec2(64 * 18, 64 * 16), Vec2(64 * 2, 64 * 2));
			for (int i = 0; i < 2; ++i)
			{
				//製氷機生成
				auto seihyouki = Seihyouki::Create(Vec2(64 * 5, 64 * 7), Vec2(64, 64));
				//扇風機生成
				auto fan = Fan::Create(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT, true);
				fan->SetTexture(&this->fanTex);
			}
			//バケツ生成
			for (int i = 0; i < 2; ++i)
			{
				auto bucket = Bucket::Create(bucketpos[i]);
			}
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
		/*map.LoadMap((std::string)"stage2.csv", Format::csv);
		for (int i = 0; i < 1; ++i)
		{
			auto w = new Bucket();
			this->bucket.push_back(w);
			w->Initialize(bucketpos[i]);
		}*/
		break;
	default:
		std::cout << "マップ番号が存在しません" << std::endl;
		break;
	}
	//水初期処理
	this->waterTex.Create((std::string)"watertest.png");
	rm->SetTextureData((std::string)"waterTex", &waterTex);
	//プレイヤー初期処理
	this->playerTex.Create((std::string)"player2.png");
	/*player.Initialize();
	this->player.SetTexture(&this->playerTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			player.AddObject(&map.hitBase[y][x]);
		}
	}
	for (int i = 0; i < this->bucket.size(); ++i)
	{
		player.AddBucket(this->bucket[i]);
	}
	for (int i = 0; i < this->block.size(); ++i)
	{
		player.AddBlock(this->block[i]);
	}*/
	auto player = Player::Create(Vec2(200, 200));
	player->SetTexture(&this->playerTex);
	this->timecnt = 0;

	OGge->DebugFunction = true;

	
	//gameprocess.Initialize();
	//auto gameprocess = GameProcessManagement::Create();

	//水出現処理
	/*auto w = new Water(_waterpos);
	w->SetTexture(&this->waterTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			if (map._arr[y][x] > 0)
			{
				w->AddGameObject(&map.hitBase[y][x]);
			}
		}
	}
	for (int i = 0; i < this->water.size(); ++i)
	{
		if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
		{
			w->AddGameObject(this->water[i]);
			this->water[i]->AddGameObject(w);
		}
	}
	water.push_back(w);
	player.AddWater(w);
	for (int i = 0; i < this->goal.size(); ++i)
	{
		goal[i]->AddWater(w);
	}
	for (int i = 0; i < 2; ++i)
	{
		fan[i].SetWaterPool(w);
	}*/
	auto water = Water::Create(_waterpos);
	water->SetTexture(&this->waterTex);
	//cm.AddChild(water[water.size() - 1]);
	switch (*MapNum)
	{
	case 3:
		player->SetPos(Vec2(200, 400));
		break;
		default:
			break;
	}
	__super::Init((std::string)"game");


	auto gameprocess = GameProcessManagement::Create();
	return true;
}
//-------------------------------------------------------------------------------------------------
void Game::UpDate()
{

	//std::cout << bucket[0]->GetHold() << bucket[1]->GetHold() << std::endl;

	//gameprocess.UpDate();
	{
		auto goal = OGge->GetTask<Goal>("Goal");
		if (goal != nullptr)
		{
			if (OGge->in->key.down(Input::KeyBoard::ENTER))
			{
				goal->cleared = true;
			}
		}
	}


	timecnt++;
	if (timecnt >= 120)
	{
		timecnt = 0;
		//Water出現処理
		/*auto w = new Water(_waterpos);
		w->SetTexture(&this->waterTex);
		for (int y = 0; y < map.mapSize.y; ++y)
		{
			for (int x = 0; x < map.mapSize.x; ++x)
			{
				if (map._arr[y][x] > 0)
				{
					w->AddGameObject(&map.hitBase[y][x]);
				}
			}
		}
		for (int i = 0; i < this->water.size(); ++i)
		{
			if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
			{
				w->AddGameObject(this->water[i]);
				this->water[i]->AddGameObject(w);
			}
		}
		water.push_back(w);
		player.AddWater(w);
		for (int i = 0; i < this->goal.size(); ++i)
		{
			this->goal[i]->AddWater(w);
		}
		for (int i = 0; i < 2; ++i)
		{
			fan[i].SetWaterPool(w);
		}*/
		//cm.AddChild(water[water.size() - 1]);
		auto water = Water::Create(_waterpos);
		water->SetTexture(&this->waterTex);
	}
	
	
//-------------------------------------------------------------------------------------------------
	//if (OGge->in->down(Input::in::B3, 0)) {
	//	//バケツから水がこぼれる処理
	//	for (int i = 0; i < this->bucket.size(); ++i) {
	//		if (bucket[i]->capacity > 0 && bucket[i]->hold) {
	//			Water* sizuku = bucket[i]->Spill();
	//			sizuku->SetTexture(&this->waterTex);
	//			for (int y = 0; y < map.mapSize.y; ++y)
	//			{
	//				for (int x = 0; x < map.mapSize.x; ++x)
	//				{
	//					if (map._arr[y][x] > 0)
	//					{
	//						sizuku->AddGameObject(&map.hitBase[y][x]);
	//					}
	//				}
	//			}
	//			for (int i = 0; i < this->water.size(); ++i)
	//			{
	//				if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
	//				{
	//					sizuku->AddGameObject(this->water[i]);
	//					this->water[i]->AddGameObject(sizuku);
	//				}
	//			}
	//			water.push_back(sizuku);
	//			player.AddWater(sizuku);
	//			for (int j = 0; j < this->goal.size(); ++j)
	//			{
	//				this->goal[j]->AddWater(sizuku);
	//			}
	//			for (int i = 0; i < 2; ++i)
	//			{
	//				fan[i].SetWaterPool(sizuku);
	//			}
	//			//cm += sizuku;
	//			//cm.AddChild(water[water.size() - 1]);
	//		}
	//	}
	//}
//-------------------------------------------------------------------------------------------------
	//for (int i = 0; i < water.size(); ++i)
	//{
	//	for (int j = 0; j < this->bucket.size(); ++j) {
	//		if (this->bucket[j]->WaterHit(water[i]))
	//		{
	//			//水とバケツの判定処理
	//			if (water[i]->GetSituation() == Water::Situation::Normal && water[i]->GetState() == Water::State::LIQUID && water[i]->invi <= 0)
	//			{
	//				float w = water[i]->waterMove();
	//				if (bucket[j]->capacity < 1.0f)
	//				{
	//					bucket[j]->capacity += w;
	//					water[i]->SetSituation(Water::Situation::CreaDelete);
	//					water[i]->Finalize();
	//					player.DeleteWater(water[i]);
	//					for (int j = 0; j < this->goal.size(); ++j)
	//					{
	//						this->goal[j]->DeleteWater(water[i]);
	//					}
	//					for (int j = 0; j < 2; ++j)
	//					{
	//						fan[j].DeleteWaterPool(water[i]);
	//					}
	//					for (int j = 0; j < water.size(); ++j)
	//					{
	//						if (i != j)
	//						{
	//							water[j]->DeleteGameObject(water[i]);
	//						}
	//					}
	//					delete water[i];
	//					water[i] = nullptr;
	//					water.erase(water.begin() + i);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
	//for (int i = 0; i < water.size(); ++i)
	//{
	//	//水の状態で地面の落ちた時に消える時の処理
	//	if (water[i]->GetSituation() == Water::Situation::CreaDelete)
	//	{
	//		//	cm - water[i];
	//		water[i]->Finalize();
	//		player.DeleteWater(water[i]);
	//		for (int j = 0; j < this->goal.size(); ++j)
	//		{
	//			this->goal[j]->DeleteWater(water[i]);
	//		}
	//		for (int j = 0; j < 2; ++j)
	//		{
	//			fan[j].DeleteWaterPool(water[i]);
	//		}
	//		for (int j = 0; j < water.size(); ++j)
	//		{
	//			if (i != j)
	//			{
	//				if (!water[j]->DeleteGameObject(water[i]))
	//				{
	//					break;
	//				}
	//			}
	//		}
	//		delete water[i];
	//		water[i] = nullptr;
	//		water.erase(water.begin() + i);
	//	}
	//	else
	//	{
	//		water[i]->UpDate();
	//	}
	//}
	//player.UpDate();
	//for (int i = 0; i < this->block.size(); ++i)
	//{
	//	//block[i]->UpDate(map, *block[i], player);
	//	block[i]->PlCheckHit(player, *block[i]);
	//}
	//for (int i = 0; i < this->bucket.size(); ++i)
	//{
	//	//bucket[i]->UpDate(map, *bucket[i]);
	//}
	
	
	/*for (int i = 0; i < this->goal.size(); ++i)
	{
		this->goal[i]->UpDate();
	}*/
	//UI------------------------------------
	//switch (*MapNum)
	//{
	//case 0:
	//	//ギミックの更新
	//	kanetuki.UpDate();
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		seihyouki[i].UpDate();
	//		fan[i].UpDate();
	//	}
	//	break;
	//case 1:
	///*	walkui.UpDate();
	//	jumpui.UpDate();
	//	getbucketui.UpDate();
	//	getwaterui.UpDate();
	//	spillwaterui.UpDate();*/

	//	
	//	break;
	//case 2:
	//	break;
	//case 3:
	//	/*switchui.UpDate();
	//	evaporationui.UpDate();*/
	//	kanetuki.UpDate();
	//	for (int i = 0; i < 1; ++i)
	//	{
	//		this->fan[i].UpDate();
	//	}
	//	break;
	//case 4:
	//	kanetuki.UpDate();
	//	seihyouki[0].UpDate();
	//	break;
	//case 5:
	//	//ギミックの更新
	//	kanetuki.UpDate();
	//	//実際に動かすのは１つ
	//	seihyouki[0].UpDate();
	//	for (int i = 0; i < 2; ++i)
	//	{
	//		this->fan[i].UpDate();
	//	}
	//	break;
	//case 6:
	//	break;
	//default:
	//	break;
	//}
	//--------------------------------------


	//カメラ処理
	Camera_move();


	//nowtask = gameprocess.Goal_Event();
	if (OGge->in->on(Input::in::D2, 0) && OGge->in->on(In::D1))
	{
		this->Kill();
	}
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//マップチップの描画
	
	
	//プレイヤー描画
	//player.Render2D();
	////水描画
	//for (int i = 0; i < water.size(); ++i)
	//{
	//	water[i]->Render2D();
	//}
	//UI------------------------------------
	switch (*MapNum)
	{
	case 0:
		break;
	case 1:
	/*	walkui.Render2D();
		jumpui.Render2D();
		getbucketui.Render2D();
		getwaterui.Render2D();
		spillwaterui.Render2D();*/
		break;
	case 2:
		break;
	case 3:
		/*switchui.Render2D();
		evaporationui.Render2D();*/
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
	//--------------------------------------
}
//-------------------------------------------------------------------------------------------------
bool Game::Finalize()
{
	std::cout << "Game" << std::endl;
	/*for (int i = 0; i < this->block.size(); ++i)
	{
		block[i]->Finalize();
		delete block[i];
	}
	map.Finalize();
	player.Finalize();*/
	/*for (int i = 0; i < this->goal.size(); ++i)
	{
		this->goal[i]->Finalize();
		delete this->goal[i];
	}*/
	//for (int i = 0; i < bucket.size(); ++i) {
	//	bucket[i]->Finalize();
	//}
	//for (int i = 0; i < bucket.size(); ++i)
	//{
	//	this->bucket.pop_back();
	//}
	
	/*for (int i = 0; i < this->bucket.size(); ++i)
	{
		bucket[i]->Finalize();
		delete bucket[i];
	}
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Finalize();
		delete water[i];
	}
	water.clear();*/
	/*for (int i = 0; i < 2; ++i) {
		swich[i].Finalize();
		fan[i].Finalize();
	}*/

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
	auto players = OGge->GetTasks<Player>("player");
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
	this->waterTex.Finalize();
	this->playerTex.Finalize();
	this->fanTex.Finalize();
	//UI
	/*walkui.Finalize();
	jumpui.Finalize();
	getbucketui.Finalize();
	getwaterui.Finalize();
	spillwaterui.Finalize();*/
	//switchui.Finalize();
	//evaporationui.Finalize();
	//this->water.clear();
	//this->bucket.clear();
	//this->block.clear();
	//this->goal.clear();
	return true;
}
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	//デバッグ用
	//std::cout << OGge->camera->GetSize().x << "//"<<OGge->camera->GetPos().x << std::endl;
	//カメラの移動
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