#include "Task_Game.h"
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
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

	uitest.Initialize(player.position, "UItest1.png", 2, 180);
	Pause = false;
}

TaskFlag Game::UpDate()
{
	if (gameEngine->input.keyboard.down(Input::KeyBoard::Q))
	{
		Pause = !Pause;
	}

	if (Pause) {
		if (gameEngine->input.keyboard.on(Input::KeyBoard::A))
		{
			gameEngine->camera->Move(Vec2(-3.0f, 0.0f));
		}
		if (gameEngine->input.keyboard.on(Input::KeyBoard::D))
		{
			gameEngine->camera->Move(Vec2(+3.0f, 0.0f));
		}
		if (gameEngine->input.keyboard.on(Input::KeyBoard::W))
		{
			gameEngine->camera->Move(Vec2(0.0f, -3.0f));
		}
		if (gameEngine->input.keyboard.on(Input::KeyBoard::S))
		{
			gameEngine->camera->Move(Vec2(0.0f, 3.0f));
		}
		if (gameEngine->input.Pad_Connection) {
			Vec2 cameraest = { 0,0 };
			cameraest.x = gameEngine->input.gamepad[0].axis(Input::GamePad::AXIS_RIGHT_X) *10.f;
			cameraest.y = gameEngine->input.gamepad[0].axis(Input::GamePad::AXIS_RIGHT_Y) * 10.f;
			cameraest.y = -cameraest.y;
			gameEngine->camera->position += cameraest;
		}
	}
	else {
		Vec2 cameraPos(player.position.x - 960 / 2, player.position.y - 540 / 2);
		gameEngine->camera->SetPos(cameraPos);
		timecnt++;
		if (timecnt >= 120)
			//if(gameEngine->input.DOWN(Input::Key::L))
		{
			timecnt = 0;
			//Water生成
			auto w = new Water(Vec2(150, 100));
			water.push_back(w);
			cm.AddChild(water[water.size() - 1]);
		}

		// テスト用
		// ------------------------------------------
		if (gameEngine->input.down(Input::in::B3, 0)/* || gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_3)*/) {
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

		uitest.Update();
		uitest.Move(player.position);


		cm.Run();
		if (gameEngine->input.keyboard.down(Input::KeyBoard::U))
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
		if (gameEngine->input.keyboard.on(Input::KeyBoard::H))
		{
			bucket.position.x -= 3.0f;
		}
		if (gameEngine->input.keyboard.on(Input::KeyBoard::K))
		{
			bucket.position.x += 3.0f;
		}
	}
	TaskFlag nowtask = Task_Game;
	if (gameEngine->input.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
	{
		nowtask = Task_Title;
	}
	return nowtask;

}

void Game::Render2D()
{
	uitest.Render();

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

	uitest.Finalize();

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
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	cm.Destroy();
}