#include "Task_Game.h"
void Game::Initialize()
{
	Vec2 bucketpos[2] = {
		{100,250},
		{200,250}
	};
	Vec2 gimmickpos[6]
	{
		{ 64 * 19,64 * 8 },     //スイッチ　上
		{ 64 * 18,64 * 15 },    //加熱器 左
		{ 64 * 11,64 * 7 },     //扇風機 上
		{ 64 * 19 ,64 * 10 },   //扇風機 下
		{ 64 * 12 ,64 *14 },	//スイッチ　下
		{ 64 * 19,64 * 15 },    //加熱器　右
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

	//当たり判定後の処理でクラスの参照に必要なデータを取得する
	senpuki.SetParent(&map);                    //mapのアドレス値を格納する
	for (int i = 0; i < 2; ++i)
	{
		senpuki.SetParent(&switch_[i], i);      //Switchのアドレス値を格納する &switch_[0]
	}
	switch_[0].SetParent(&player);              //Playerのアドレス値を取得してSwitchクラスのPlayer*に代入する
	switch_[1].SetParent(&player);              //同じアドレス値が持ってくる
	switch_[0].SetParent(&senpuki);             //扇風機のアドレス値を参照する
	switch_[1].SetParent(&senpuki);             //扇風機のアドレス値を参照する


												//ステージやギミックが複数ある場合の座標値を予め設定し、vectorに代入する

	senpuki.Set_Pos(gimmickpos[2]);             //扇風機の上の座標値をvectorに登録する
	senpuki.Set_Pos(gimmickpos[3]);             //扇風機の下の座標値をvectorに登録する
	switch_[0].Set_Pos(gimmickpos[0]);          //スイッチの上の座標値をvectorに登録する
	switch_[1].Set_Pos(gimmickpos[4]);          //スイッチの下の座標値をvectorに登録する
	//kanetuki.Input_Pos(gimmickpos[1]);          //加熱機の座標値をvectorに登録する
	//kanetuki.Input_Pos(gimmickpos[5]);          //加熱機の座標値をvectorに登録する
	seihyouki.Input_Pos(gimmickpos[1]);         //仮処理

	//ギミックの初期化

	senpuki.Initialize(gimmickpos[2]);			//扇風機の初期化処理に移る（Vec2 扇風機の座標）
	switch_[0].Initlaize(gimmickpos[0],&switch_[0]);        //Switchクラスの初期化処理をする(Vec2 初期座標)
	switch_[1].Initlaize(gimmickpos[4],&switch_[1]);        //Switchクラスの初期化処理をする(Vec2 初期座標)
	//kanetuki.Initialize();                                  //加熱機を動かす
	seihyouki.Initialize();

												//当たり判定矩形を登録する
	cm.AddChild(switch_);                       //Switchのアドレスをvector objsにputh.back()する &switch[0]
	cm.AddChild(&switch_[1]);                   //Switchのアドレス2つ目をputh.back()する
	cm.AddChild(&senpuki.range);                //視野範囲のアドレスを参照する
	//cm.AddChild(&kanetuki.hitBace[0]);          //当たり判定矩形を登録する
	//cm.AddChild(&kanetuki.hitBace[1]);          //当たり判定矩形を登録する
	cm.AddChild(&seihyouki.hitBace);            //当たり判定矩形を登録する
}

TaskFlag Game::UpDate()
{
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

	cm.Run();
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
	TaskFlag nowtask = Task_Game;
	if (gameEngine->input.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
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