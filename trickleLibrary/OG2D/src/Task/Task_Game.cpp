#include "Task_Game.h"
#define ADD_FUNCTION(a) \
	[](std::vector<Object*>* objs_) { a(objs_); }

void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
	};

	Vec2 blockpos = Vec2(1536 , 100);       //1536�e�X�g

	std::cout << "Game" << std::endl;
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

	block.Initialize(blockpos);           //�u���b�N�̐���
	cm.AddChild(&block);

	back.Initialize();
	map.LoadMap("prototype.txt");
	
	// �����蔻��e�X�g
	player.Register(&cm);
	//cm.AddChild(&bucket);
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	gameEngine->DebugFunction = true;
	goal.Initialize();
	cm.AddChild(&goal);

	Vec2 fanpos[2] = { Vec2(64 * 11,64 * 7), Vec2(64 * 19,64 * 10) };
	float fanrange[2] = { 18,6 };
	for (int i = 0; i < 2; ++i) {
		swich[i].Initialize(Vec2(64 * (10 + i*2), 64 * 14));
 		fan[i].Initialize(fanpos[i], fanrange[i], (i == 0) ? Fan::Dir::RIGHT : Fan::Dir::LEFT, (i == 0) ? true : false);
		cm.AddChild(&swich[i]);
		cm.AddChild(&fan[i]);
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].SetTarget(&fan[0]);
		swich[i].SetTarget(&fan[1]);
	}
	swich[0].ON_OFF();
}

TaskFlag Game::Update()
{
	timecnt++;
	if (timecnt >= 120)
	//if(gameEngine->input.DOWN(Input::Key::L))
	{
		timecnt = 0;
		//Water����
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	// �e�X�g�p
	// ------------------------------------------
	if (gameEngine->in.down(Input::in::B3, 0)/* || gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_3)*/) {
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
	player.Update();
	/*for (int i = 0; i < 2; ++i) {
		player.TakeBucket(bucket[i]);
	}*/
	player.TakeBucket(&bucket);

	block.Update(map, block);
	bucket.Update(map, bucket);
	//�u���b�N�̋����e�X�g��!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*block.maphitF = map.MapHitCheck(block.footBase);
	block.maphitH = map.MapHitCheck(block.headBase);
	block.maphitL = map.MapHitCheck(block.leftBase);
	block.maphitR = map.MapHitCheck(block.rightBase);*/

	block.PlCheckHitF(player);
	block.PlCheckHitH(player);
	block.PlCheckHitL(player);
	block.PlCheckHitR(player);

	//fan_switch test ★★★
	//for (int i = 0; i < 2; ++i) {
	//	fan[i].ChangeState();
	//	swich[i].ChangeState();
	//}

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
	TaskFlag nowtask = Task_Game;
	if (gameEngine->in.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
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
	block.Render();
	goal.Render();
	bucket.Render();
	map.MapRender();
	back.Render();
}

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
	}
	while (!this->water.empty())
	{
		this->water.pop_back();
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].Finalize();
		fan[i].Finalize();
	}
	cm.Destroy();
}