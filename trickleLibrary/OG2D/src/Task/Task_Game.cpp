#include "Task_Game.h"
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
	};
	Vec2 gimmickpos[3]
	{
		{ 64 * 19,64 * 8 },		//スイッチ
		{ 64 * 8,64 * 15 },		//加熱器
		{ 64 * 11,64 * 7 }		//扇風機
	};
	std::cout << "Game初期化" << std::endl;
	player.Initialize();
	/*for (int i = 0; i < 2; ++i)
	{
		auto w = new Bucket(Vec2(bucketpos[i].x, bucketpos[i].y));
		bucket.push_back(w);
	}
	for (int i = 0; i < bucket.size(); ++i)
	{
		bucket[i]->Initialize();
		cm.AddChild(bucket[i]);
	}*/
	bucket.Initialize(bucketpos[0]);
	cm.AddChild(&bucket);
	back.Initialize();
	map.LoadMap("prototype.txt");
	
	// 当たり判定テスト
	player.Register(&cm);
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
	goal.Initialize();
	cm.AddChild(&goal);

	//ギミックの初期化
	senpuki.Initialize(gimmickpos[2]);			//扇風機の初期化処理に移る（扇風機の座標）
	//当たり判定の登録
	senpuki.SetParent(&player);					//Playerのアドレスを参照する（Playerのアドレス値）
	cm.AddChild(&senpuki);						//扇風機のアドレスをvector objsにputh.back()する
}

TaskFlag Game::UpDate()
{
	timecnt++;
	if (timecnt >= 120)
	//if(Input::KeyInputDown(Input::Key::L))
	{
		timecnt = 0;
		//Water生成
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	// テスト用
	// ------------------------------------------
	if (Input::KeyInputDown(Input::Key::C)/* || gameEngine->gamepad[0].ButtonDown(GLFW_JOYSTICK_3)*/) {
		//for (int i = 0; i < 2; ++i) {
		//	if (bucket[i]->capacity > 0) {
		//		Water* sizuku = bucket[i]->Spill();
		//		water.push_back(sizuku);
		//		//cm += sizuku;
		//		cm.AddChild(water[water.size() - 1]);
		//	}
		//}
		if (bucket.capacity > 0) {
				Water* sizuku = bucket.Spill();
				water.push_back(sizuku);
				//cm += sizuku;
				cm.AddChild(water[water.size() - 1]);
		}
	}

	// ------------------------------------------
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Update();
		if (water[i]->GetSituation() == Water::Situation::CreaDelete)
		{
			cm - water[i];
			water[i]->Finalize();
			water.erase(water.begin() + i);
		}
	}
	player.UpDate();
	/*for (int i = 0; i < 2; ++i) {
		player.TakeBucket(bucket[i]);
	}*/
	player.TakeBucket(&bucket);

	cm.Run();
	if (Input::KeyInputOn(Input::A))
	{
		gameEngine->camera->Move(Vec2(-3.0f, 0.0f));
	}
	if (Input::KeyInputOn(Input::D))
	{
		gameEngine->camera->Move(Vec2(+3.0f, 0.0f));
	}
	if (Input::KeyInputOn(Input::W))
	{
		gameEngine->camera->Move(Vec2(0.0f, -3.0f));
	}
	if (Input::KeyInputOn(Input::S))
	{
		gameEngine->camera->Move(Vec2(0.0f, 3.0f));
	}
	Vec2 cameraest = { 0,0 };
	/*cameraest.x = gameEngine->gamepad[0].axis(Input::AXIS_LEFT) *10.f;
	cameraest.y = gameEngine->gamepad[0].axis(Input::AXIS_RIGHT) * 10.f;
	cameraest.y = -cameraest.y;
	gameEngine->camera->position += cameraest;*/
	if (Input::KeyInputDown(Input::U))
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
	if (Input::KeyInputOn(Input::H))
	{
		bucket.position.x -= 3.0f;
	}
	if (Input::KeyInputOn(Input::K))
	{
		bucket.position.x += 3.0f;
	}
	TaskFlag nowtask = Task_Game;
	if (Input::KeyInputUp(Input::SPACE) /*|| gameEngine->gamepad[0].ButtonDown(GLFW_JOYSTICK_8)*/)
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Game::Render2D()
{
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
	player.Render();
	/*for (int i = 0; i < bucket.size(); ++i) {
		bucket[i]->Render();
	}*/
	goal.Render();
	bucket.Render();
	map.MapRender();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game解放" << std::endl;
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
	senpuki.Finalize();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Finalize();
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	cm.Destroy();
}