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

	Vec2 blockpos = Vec2(1536, 100);

	//ジャスティン風のギミックの場合

	//Vec2 gimmickpos[6]
	//{
	//	{ 64 * 19,64 * 8 },     //スイッチ 上
	//	{ 64 * 18,64 * 15 },    //加熱器 左
	//	{ 64 * 11,64 * 7 },     //扇風機 上
	//	{ 64 * 19 ,64 * 10 },   //扇風機 下
	//	{ 64 * 12 ,64 * 14 },	//スイッチ 下
	//	{ 64 * 19,64 * 15 },    //加熱器 右
	//};


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

	block.Initialize(blockpos);
	cm.AddChild(&block);

	back.Initialize();
	map.LoadMap("prototype.txt");
	
	
	player.Register(&cm);
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
		cm.AddChild(&swich[i]);
		cm.AddChild(&fan[i]);
	}
	for (int i = 0; i < 2; ++i) {
		swich[i].SetTarget(&fan[0]);
		swich[i].SetTarget(&fan[1]);
	}
	swich[0].ON_OFF();

	//ジャスティン風 現在は製氷機が動きます

	//senpuki.SetParent(&map);                    //mapのアドレス値を格納する
	//for (int i = 0; i < 2; ++i)
	//{
	//	senpuki.SetParent(&switch_, i);      //Switchのアドレス値を格納する &switch_[0]
	//}

	//senpuki.Set_Pos(gimmickpos[2]);             //扇風機の上の座標値をvectorに登録する
	//senpuki.Set_Pos(gimmickpos[3]);             //扇風機の下の座標値をvectorに登録する
	//switch_.Set_Pos(gimmickpos[0]);             //スイッチの上の座標値をvectorに登録する
	//switch_.Set_Pos(gimmickpos[4]);             //スイッチの下の座標値をvectorに登録する
	//											//kanetuki.Input_Pos(gimmickpos[1]);        //加熱機の座標値をvectorに登録する
	//											//kanetuki.Input_Pos(gimmickpos[5]);        //加熱機の座標値をvectorに登録する
	//seihyouki.Input_Pos(gimmickpos[1]);         //仮処理

	////ギミックの初期化

	//senpuki.Initialize(gimmickpos[2]);			//扇風機の初期化処理に移る（Vec2 扇風機の座標）
	//switch_.Initlaize();        //Switchクラスの初期化処理をする(Vec2 初期座標)
	//							//kanetuki.Initialize();                                  //加熱機を動かす
	//seihyouki.Initialize();

	////当たり判定矩形を登録する
	//cm.AddChild(&switch_.hitBace[0]);           //Switchのアドレスをvector objsにputh.back()
	//cm.AddChild(&switch_.hitBace[1]);           //Switchのアドレスを追加
	//cm.AddChild(&senpuki);
	//cm.AddChild(&senpuki.range);                //視野範囲のアドレスを参照する
	//											//cm.AddChild(&kanetuki.hitBace[0]);          //当たり判定矩形を登録する
	//											//cm.AddChild(&kanetuki.hitBace[1]);          //当たり判定矩形を登録する
	//cm.AddChild(&seihyouki.hitBace);            //当たり判定矩形を登録する

}
//-------------------------------------------------------------------------------------------------
TaskFlag Game::Update()
{
	timecnt++;
	if (timecnt >= 120)
		//if(gameEngine->input.DOWN(Input::Key::L))
	{
		timecnt = 0;
		//Water?ｿｽ?ｿｽ?ｿｽ?ｿｽ
		auto w = new Water(Vec2(150, 100));
		water.push_back(w);
		cm.AddChild(water[water.size() - 1]);
	}

	
//-------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------
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

	/*block.maphitF = map.MapHitCheck(block.footBase);
	block.maphitH = map.MapHitCheck(block.headBase);
	block.maphitL = map.MapHitCheck(block.leftBase);
	block.maphitR = map.MapHitCheck(block.rightBase);*/

	block.PlCheckHitF(player);
	block.PlCheckHitH(player);
	block.PlCheckHitL(player);
	block.PlCheckHitR(player);
	
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
	if (gameEngine->in.down(Input::in::D2, 0)/*|| gameEngine->gamepad[0].DOWN(GLFW_JOYSTICK_8)*/)
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
	//プレイヤー描画
	player.Render();
	for (int i = 0; i < water.size(); ++i)
	{
		water[i]->Render();
	}
	block.Render();
	goal.Render();
	bucket.Render();
	//マップチップの描画
	map.MapRender();
	
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
//-------------------------------------------------------------------------------------------------
//カメラ処理
void Game::Camera_move()
{
	////デバッグ用
	//std::cout << gameEngine->camera->GetSize().x << "//"<<gameEngine->camera->GetPos().x << std::endl;
	////カメラの移動
	//gameEngine->camera->MovePos(player.GetEst());

	////カメラ処理
	//Vec2 NowCameraPos = gameEngine->camera->GetPos();
	//Vec2 NowCameraSize = gameEngine->camera->GetSize();

	////プレイヤーを画面中央
	//float PlayerCenter_x = NowCameraSize.x / 2.0f;
	//float PlayerCenter_y = NowCameraSize.y / 2.0f;
	////カメラ座標を求める
	//float camera_x = float(player.position.x) - PlayerCenter_x;
	//float camera_y = float(player.position.y) - PlayerCenter_y;
	////カメラの座標を更新
	//NowCameraPos.x = camera_x;
	//NowCameraPos.y = camera_y;


	////左右のスクロール範囲の設定(サイズの10分の1)
	//float Boundary = NowCameraSize.x / 10.0f;
	////現在スクロール値とプレイヤーの座標の差を修正
	//Vec2 NowPlayerPos = { player.position.x - NowCameraPos.x,player.position.y - NowCameraPos.y };
	////x座標
	//if (NowPlayerPos.x < Boundary){
	//	NowCameraPos.x = NowPlayerPos.x - Boundary;
	//}
	//if (NowPlayerPos.x > NowCameraSize.x - Boundary){
	//	NowCameraPos.x = (NowPlayerPos.x + NowCameraPos.x) - NowPlayerPos.x + Boundary;
	//}
	////y座標
	//if (NowPlayerPos.y < Boundary){
	//	NowCameraPos.y = NowPlayerPos.y - Boundary;
	//}
	//if (NowPlayerPos.y > NowCameraSize.y - Boundary){
	//	NowCameraPos.y = (NowCameraSize.y + NowCameraPos.y) - NowPlayerPos.y + Boundary;
	//}


	//----------------------------------------------------------------------------------------
	//ここから横田編集

	Vec2 NowCameraPos = gameEngine->camera->GetPos();
	Vec2 NowCameraSize = gameEngine->camera->GetSize();

	//カメラが動かない範囲
	float NoMoveLeft = NowCameraPos.x + NowCameraSize.x*(7.0f / 16.0f);
	float NoMoveRight = NowCameraPos.x + NowCameraSize.x*(9.0f / 16.0f);
	float NoMoveUp = NowCameraPos.y + NowCameraSize.y*(7.0f / 16.0f);
	float NoMoveBottom = NowCameraPos.y + NowCameraSize.y*(9.0f / 16.0f);
	Vec2 cameracenter = Vec2(NowCameraPos.x + NowCameraSize.x*0.5f, NowCameraPos.y + NowCameraSize.y*0.5f);
	Vec2 playercenter = Vec2(player.position.x + player.Scale.x*0.5f, player.position.y + player.Scale.y*0.5f);
	//当たり判定時の処理は終わった後なのでplayer.estは考慮する必要なし？
	//プレイヤがカメラの動かない範囲を超えていたらカメラ移動
	//x軸
	if (playercenter.x < NoMoveLeft) {
		float cameraest = NoMoveLeft - playercenter.x;
		NowCameraPos.x -= cameraest;
	}
	if (playercenter.x > NoMoveRight) {
		float cameraest = playercenter.x - NoMoveRight;
		NowCameraPos.x += cameraest;
	}
	//y軸
	if (playercenter.y < NoMoveUp) {
		float cameraest = NoMoveUp - playercenter.y;
		NowCameraPos.y -= cameraest;
	}
	if (playercenter.y > NoMoveBottom) {
		float cameraest = playercenter.y - NoMoveBottom;
		NowCameraPos.y += cameraest;
	}
	//y軸は動かなくていいかも？
	//NowCameraPos.y = playercenter.y - cameracenter.y;    //注意：めり込みの影響でめっちゃガタつきます

	//ここまで横田
	//-----------------------------------------------------------------------------------------------

	//画面外処理
	if (NowCameraPos.x < 0) {
		NowCameraPos.x = 0;
	}
	if (NowCameraPos.x + NowCameraSize.x > 34 * map.DrawSize.x) {
		NowCameraPos.x = (34 * map.DrawSize.x) - NowCameraSize.x;
	}
	if (NowCameraPos.y < 0) {
		NowCameraPos.y = 0;
	}
	if (NowCameraPos.y + NowCameraSize.y > 16 * map.DrawSize.y) {
		NowCameraPos.y = (16 * map.DrawSize.y) - NowCameraSize.y;
	}
	gameEngine->camera->SetPos(NowCameraPos);
}