#include "Task_Game.h"
#define ADD_FUNCTION(a) \
	[](std::vector<Object*>* objs_) { a(objs_); }
//-------------------------------------------------------------------------------------------------
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{ 100,250 },
		{ 200,250 }
	};

	Vec2 blockpos = Vec2(1536, 100);  //1536,100


	std::cout << "Game" << std::endl;

	//バケツ初期処理
	bucket.Initialize(bucketpos[0]);
	cm.AddChild(&bucket);
	//ブロック初期処理
	block.Initialize(blockpos);
	cm.AddChild(&block);
	//背景初期処理
	back.Initialize();
	//マップ初期処理
	switch (*MapNum)
	{
	case 0:
		map.LoadMap("prototype.txt");
		break;
	case 1:
		map.LoadMap("tutorial1.csv", Format::csv);
		walkui.Initialize(Vec2(200, 300), Box2D(100, 300, 200, 300), "walkui.png", 300, 4);
		walkui.SetPlayerPtr(&player);
		jumpui.Initialize(Vec2(400, 300), Box2D(400, 300, 200, 300), "pusha.png", 300, 2);
		jumpui.SetPlayerPtr(&player);
		getbucketui.Initialize(Vec2(1200, 200), Box2D(1150, 200, 100, 200), "pushb.png", 300, 2);
		getbucketui.SetPlayerPtr(&player);
		getwaterui.Initialize(Vec2(100, 200), Box2D(0, 0, 0, 0), "arrowdown.png", 300, 1);
		getwaterui.SetPlayerPtr(&player);
		spillwaterui.Initialize(Vec2(1600, 200), Box2D(1550, 200, 300, 200), "pushx.png", 300, 2);
		spillwaterui.SetPlayerPtr(&player);
		//cm.AddChild(&walkui);
		//cm.AddChild(&jumpui);
		//cm.AddChild(&getbucketui);
		//cm.AddChild(&getwaterui);
		//cm.AddChild(&spillwaterui);
		break;
	case 2:
		map.LoadMap("tutorial2.csv", Format::csv);
		break;
	case 3:
		map.LoadMap("tutorial3.csv", Format::csv);
		//switchui;
		//switchui.SetPlayerPtr(&player);
		//evaporationui;
		//evaporationui.SetPlayerPtr(&player);
		//cm.AddChild(&switchui);
		//cm.AddChild(&evaporationui);
		break;
	case 4:
		map.LoadMap("tutorial4.csv", Format::csv);
		break;
	case 5:
		map.LoadMap("stage1.csv", Format::csv);
		break;
	case 6:
		map.LoadMap("stage2.csv", Format::csv);
		break;
	default:
		std::cout << "マップ番号が存在しません" << std::endl;
		break;
	}
	//水初期処理
	this->waterTex.TextureCreate((std::string)"watertest.png");
	//プレイヤー初期処理
	this->playerTex.TextureCreate((std::string)"player2.png");
	player.Initialize();
	this->player.SetTexture(&this->playerTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			player.AddObject(&map.hitBase[y][x]);
		}
	}
	player.AddBucket(&this->bucket);
	player.AddBlock(&this->block);
	cm.AddChild(&player);
	this->timecnt = 0;
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
	goal.Initialize();
	cm.AddChild(&goal);

	//横田さん風

	Vec2 fanpos[2] = { Vec2(64 * 11,64 * 7), Vec2(64 * 19,64 * 10) };
	float fanrange[2] = { 18,6 };
	for (int i = 0; i < 2; ++i) {
		swich[i].Initialize(Vec2(64 * (10 + i * 2), 64 * 14));
		fan[i].Initialize(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT, (i == 0) ? true : false);
		fan[i].SetWaterPool(&water);
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].SetTarget(&fan[0]);
		swich[i].SetTarget(&fan[1]);
	}

	//ギミックの初期化をします
	for (int i = 0; i < 2; ++i)
	{
		seihyouki[i].Create(Vec2(64 * 6 + i * 64, 64 * 11), Vec2(64, 64));
		seihyouki[i].SetWaterPool(&water);
	}
	kanetuki.Create(Vec2(18 * 64, 15 * 64), Vec2(64 * 2, 64 * 2));
	kanetuki.SetWaterPool(&water);

	swich[0].ON_OFF();

	gameprocess.Set_Goal(&goal);
	gameprocess.Initialize();

	for (int i = 0; i < 2; ++i)
	{
		cm.AddChild(&seihyouki[i].hitBace);
	}
	//水出現処理
	auto w = new Water(Vec2(150, 100));

	

	w->SetTexture(&this->waterTex);
	for (int y = 0; y < map.mapSize.y; ++y)
	{
		for (int x = 0; x < map.mapSize.x; ++x)
		{
			if (map._arr[y][x] > 0)
			{
				w->AddObject(&map.hitBase[y][x]);
			}
		}
	}
	for (int i = 0; i < this->water.size(); ++i)
	{
		if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
		{
			w->AddObject(this->water[i]);
			this->water[i]->AddObject(w);
		}
	}
	water.push_back(w);
	player.AddWater(w);
	//cm.AddChild(water[water.size() - 1]);
}
//-------------------------------------------------------------------------------------------------
TaskFlag Game::Update()
{
	//ギミックの更新
	kanetuki.Update();
	for (int i = 0; i < 2; ++i)
	{
		seihyouki[i].UpDate();
		fan[i].UpDate();
	}

	gameprocess.Update();
	
	timecnt++;
	if (timecnt >= 120)
	{
		timecnt = 0;
		//Water出現処理
		auto w = new Water(Vec2(150, 100));
		w->SetTexture(&this->waterTex);
		for (int y = 0; y < map.mapSize.y; ++y)
		{
			for (int x = 0; x < map.mapSize.x; ++x)
			{
				if (map._arr[y][x] > 0)
				{
					w->AddObject(&map.hitBase[y][x]);
				}
			}
		}
		for (int i = 0; i < this->water.size(); ++i)
		{
			if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
			{
				w->AddObject(this->water[i]);
				this->water[i]->AddObject(w);
			}
		}
		water.push_back(w);
		player.AddWater(w);
		//cm.AddChild(water[water.size() - 1]);
	}
	

	
//-------------------------------------------------------------------------------------------------
	if (gameEngine->in.down(Input::in::B3, 0)) {
		//バケツから水がこぼれる処理
		if (bucket.capacity > 0) {
			Water* sizuku = bucket.Spill();
			sizuku->SetTexture(&this->waterTex);
			for (int y = 0; y < map.mapSize.y; ++y)
			{
				for (int x = 0; x < map.mapSize.x; ++x)
				{
					if (map._arr[y][x] > 0)
					{
						sizuku->AddObject(&map.hitBase[y][x]);
					}
				}
			}
			for (int i = 0; i < this->water.size(); ++i)
			{
				if (this->water[i]->GetSituation() != Water::Situation::Deleteform)
				{
					sizuku->AddObject(this->water[i]);
					this->water[i]->AddObject(sizuku);
				}
			}
			water.push_back(sizuku);
			player.AddWater(sizuku);
			//cm += sizuku;
			//cm.AddChild(water[water.size() - 1]);
		}
	}
//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < water.size(); ++i)
	{
		if (this->bucket.WaterHit(water[i]))
		{
			//水とバケツの判定処理
			if (water[i]->GetSituation() == Water::Situation::Normal && water[i]->GetState() == Water::State::LIQUID && water[i]->invi <= 0)
			{
				float w = water[i]->waterMove();
				if (bucket.capacity < 1.0f)
				{
					bucket.capacity += w;
					water[i]->SetSituation(Water::Situation::CreaDelete);
					water[i]->Finalize();
					
					player.DeleteWater(water[i]);
					for (int j = 0; j < water.size(); ++j)
					{
						if (i != j)
						{
							water[j]->DeleteObject(water[i]);
						}
					}
					delete water[i];
					water[i] = nullptr;
					water.erase(water.begin() + i);
				}
			}
		}
	}
	for (int i = 0; i < water.size(); ++i)
	{
		//水の状態で地面の落ちた時に消える時の処理
		if (water[i]->GetSituation() == Water::Situation::CreaDelete)
		{
			//	cm - water[i];
			water[i]->Finalize();
			player.DeleteWater(water[i]);
			for (int j = 0; j < water.size(); ++j)
			{
				if (i != j)
				{
					if (!water[j]->DeleteObject(water[i]))
					{
						break;
					}
				}
			}
			delete water[i];
			water[i] = nullptr;
			water.erase(water.begin() + i);
		}
		else
		{
			water[i]->Update();
		}
	}
	player.Update();

	block.Update(map, block, player);
	bucket.Update(map, bucket);
	
	block.PlCheckHit(player, block);

	//UI------------------------------------
	switch (*MapNum)
	{
	case 0:
		break;
	case 1:
		walkui.Update();
		jumpui.Update();
		getbucketui.Update();
		getwaterui.Update();
		spillwaterui.Update();
		break;
	case 2:
		break;
	case 3:
		switchui.Update();
		evaporationui.Update();
		break;
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

	cm.Run();
	if (gameEngine->in.key.on(Input::KeyBoard::A))
	{
		gameEngine->camera->MovePos(Vec2(-3.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::D))
	{
		gameEngine->camera->MovePos(Vec2(+3.0f, 0.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::W))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, -3.0f));
	}
	if (gameEngine->in.key.on(Input::KeyBoard::S))
	{
		gameEngine->camera->MovePos(Vec2(0.0f, 3.0f));
	}
	if (gameEngine->in.Pad_Connection) {
		Vec2 cameraest = { 0,0 };
		cameraest.x = gameEngine->in.pad[0].axis(Input::GamePad::AXIS_RIGHT_X) *10.f;
		cameraest.y = gameEngine->in.pad[0].axis(Input::GamePad::AXIS_RIGHT_Y) * 10.f;
		cameraest.y = -cameraest.y;
		gameEngine->camera->MovePos(cameraest);
	}
	if (gameEngine->in.key.down(Input::KeyBoard::U))
	{
		for (int i = 0; i < water.size(); ++i)
		{
			if (water[i]->GetState() == Water::State::LIQUID)
			{
				water[i]->SetState(Water::State::GAS);
			}
			else
			{
				water[i]->SetState(Water::State::LIQUID);
			}
		}
	}
	if (gameEngine->in.key.on(Input::KeyBoard::H))
	{
		bucket.position.x -= 3.0f;
	}
	if (gameEngine->in.key.on(Input::KeyBoard::K))
	{
		bucket.position.x += 3.0f;
	}
	if (gameEngine->in.key.down(In::I))
	{
		for (int i = 0; i < water.size(); ++i)
		{
			if (water[i]->GetState() == Water::State::LIQUID)
			{
				water[i]->SetState(Water::State::SOLID);
			}
			else
			{
				water[i]->SetState(Water::State::LIQUID);
			}
		}
	}


	//カメラ処理
	Camera_move();


	TaskFlag nowtask = Task_Game;
	nowtask = gameprocess.Goal_Event();
	if (gameEngine->in.down(Input::in::D2, 0) && gameEngine->in.down(In::D1))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}
//-------------------------------------------------------------------------------------------------
void Game::Render2D()
{
	//背景描画
	back.Render();
	//マップチップの描画
	map.MapRender();
	//ブロック描画
	block.Render();
	//ゴール描画
	goal.Render();
	//バケツ描画
	bucket.Render();
	//プレイヤー描画
	player.Render();
	//水描画
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
	//UI------------------------------------
	switch (*MapNum)
	{
	case 0:
		break;
	case 1:
		walkui.Render();
		jumpui.Render();
		getbucketui.Render();
		getwaterui.Render();
		spillwaterui.Render();
		break;
	case 2:
		break;
	case 3:
		switchui.Render();
		evaporationui.Render();
		break;
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
void Game::Finalize()
{
	std::cout << "Game" << std::endl;
	block.Finalize();
	back.Finalize();
	map.Finalize();
	player.Finalize();
	goal.Finalize();
	//for (int i = 0; i < bucket.size(); ++i) {
	//	bucket[i]->Finalize();
	//}
	//for (int i = 0; i < bucket.size(); ++i)
	//{
	//	this->bucket.pop_back();
	//}
	bucket.Finalize();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Finalize();
		delete water[i];
	}
	water.clear();
	for (int i = 0; i < 2; ++i) {
		swich[i].Finalize();
		fan[i].Finalize();
	}
	this->waterTex.Finalize();
	this->playerTex.Finalize();

	//UI
	walkui.Finalize();
	jumpui.Finalize();
	getbucketui.Finalize();
	getwaterui.Finalize();
	spillwaterui.Finalize();
	//switchui.Finalize();
	//evaporationui.Finalize();


	cm.Destroy();
}
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	//デバッグ用
	//std::cout << gameEngine->camera->GetSize().x << "//"<<gameEngine->camera->GetPos().x << std::endl;
	//カメラの移動
	gameEngine->camera->MovePos(player.GetEst());

	//カメラ処理
	Vec2 NowCameraPos = gameEngine->camera->GetPos();
	Vec2 NowCameraSize = gameEngine->camera->GetSize();

	//プレイヤーを画面中央
	float PlayerCenter_x = NowCameraSize.x / 2.0f;
	float PlayerCenter_y = NowCameraSize.y / 2.0f;
	//カメラ座標を求める
	float camera_x = float(player.position.x) - PlayerCenter_x;
	float camera_y = float(player.position.y) - PlayerCenter_y;
	//カメラの座標を更新
	NowCameraPos.x = camera_x;
	NowCameraPos.y = camera_y;


	//左右のスクロール範囲の設定(サイズの10分の1)
	float Boundary = NowCameraSize.x / 10.0f;
	//現在スクロール値とプレイヤーの座標の差を修正
	Vec2 NowPlayerPos = { player.position.x - NowCameraPos.x,player.position.y - NowCameraPos.y };
	//x座標
	if (NowPlayerPos.x < Boundary){
		NowCameraPos.x = NowPlayerPos.x - Boundary;
	}
	if (NowPlayerPos.x > NowCameraSize.x - Boundary){
		NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
	}
	//y座標
	if (NowPlayerPos.y < Boundary){
		NowCameraPos.y = NowPlayerPos.y - Boundary;
	}
	if (NowPlayerPos.y > NowCameraSize.y - Boundary){
		NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
	}
	//画面外処理
	if (NowCameraPos.x < 0) {
		NowCameraPos.x = 0;
	}
	if (NowCameraPos.x + NowCameraSize.x > map.mapSize.x * map.DrawSize.x) {
		NowCameraPos.x = (map.mapSize.x * map.DrawSize.x) - NowCameraSize.x;
	}
	if (NowCameraPos.y < 0) {
		NowCameraPos.y = 0;
	}
	if (NowCameraPos.y + NowCameraSize.y > map.mapSize.y * map.DrawSize.y) {
		NowCameraPos.y = (map.mapSize.y * map.DrawSize.y) - NowCameraSize.y;
	}
	gameEngine->camera->SetPos(NowCameraPos);
}