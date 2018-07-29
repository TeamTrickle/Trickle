#include "Senpuki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"


Fan::Fan() {
	this->taskName = "Senpuki";
	this->soundname = "wind1.wav";
}
Fan::~Fan() {}
bool Fan::Initialize(Vec2 pos, float r, Dir d, /*std::shared_ptr<Switch>& swich,*/float effectdis, bool active) {
	this->taskName = "Senpuki";			//検索時に使うための名を登録する
	__super::Init(taskName);			//TaskObject内の処理を行う
	SetDrawOrder(0.5f);

										//アニメーションのリセットをする
	animetion.AnimetionReset();

	//画像関連の描画パス
	std::string filePath = "fan.png";      //扇風機の画像
	image.Create(filePath);
	//風の画像
	std::string filePathWind = "wind1.png";
	windimage.Create(filePathWind);
	std::string filePathWind2 = "wind2.png";
	windimage2.Create(filePathWind2);
	std::string filePathWind3 = "wind3.png";
	windimage3.Create(filePathWind3);
	std::string filePathWind4 = "wind4.PNG";
	windimage4.Create(filePathWind4);
	std::string filePathWind5 = "wind5.PNG";
	windimage5.Create(filePathWind5);


	//サウンドの生成
	this->startflag = true;
	sound.create(soundname, true);
	//エフェクト関連情報
	this->effectCnt = 0;
	this->endpos = effectdis;

	range = r;
	dir = d;
	//this->swich_ = swich;
	this->active_ = active;
	//扇風機の描画座標
	position = pos;

	if (dir == Fan::Dir::LEFT)
	{
		strength = -5;
		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + 64, 64.f), 0.0f);
	}
	else
	{
		strength = 5;
		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
	}

	return true;
}
void Fan::SetWindRange(Vec2&) {

}
void Fan::UpDate() {
	if (active_) {
		SendWind();
		//風のエフェクト生成-----------------------------------------------------------------------------------------------
		this->effectCnt++;

		if (this->effectCnt % 15 == 0)
		{
			effectnum = rand() % 5 + 1;
			//扇風機が右向きの時
			if (dir == RIGHT)
			{
				auto effect = Effect::Create(Vec2(this->position.x+32,this->position.y), Vec2(0, 64), Vec2(256, 64), 1, 200);
				effect->SetWind(Vec2(64 * 8, 64), effect->position, Vec2(effect->position.x + endpos, effect->position.y), Effect::Mode::WindR);
				switch (effectnum)
				{
				case 1:
					effect->SetTexture(&windimage);
					break;
				case 2:
					effect->SetTexture(&windimage2);
					break;
				case 3:
					effect->SetTexture(&windimage3);
					break;
				case 4:
					effect->SetTexture(&windimage4);
					break;
				case 5:
					effect->SetTexture(&windimage5);
					break;
				}
			}
			//扇風機が左向きの時
			else
			{
				auto effect = Effect::Create(Vec2(this->position.x + 32, this->position.y), Vec2(0, 64), Vec2(256, 64), 1, 200, 5);
				effect->SetWind(Vec2(64 * 4, 64), effect->position, Vec2(effect->position.x - endpos, effect->position.y), Effect::Mode::WindL);
				switch (effectnum)
				{
				case 1:
					effect->SetTexture(&windimage);
					break;
				case 2:
					effect->SetTexture(&windimage2);
					break;
				case 3:
					effect->SetTexture(&windimage3);
					break;
				case 4:
					effect->SetTexture(&windimage4);
					break;
				case 5:
					effect->SetTexture(&windimage5);
					break;
				}
			}
		}
		if (this->effectCnt == 300)
		{
			this->effectCnt = 0;
		}
		//---------------------------------------------------------------------------------------------------------------
	}

	//アニメーションを動かす処理
	animetion.AnimetionMove(this->active_);

	//サウンドの再生について
	if (active_)
	{
		volControl.Play(&this->position, 1000.0f, 0.6f, sound);
		if (startflag)
		{
			sound.play();
			startflag = false;
		}
	}
	if (!active_)	//スイッチがオフ
	{
		if (sound.isplay())
		{
			sound.stop();
		}
		startflag = true;
	}

}
void Fan::Render2D() {
	//扇風機本体の描画
	Box2D draw(position, Vec2(64, 64));
	draw.OffsetSize();
	Box2D src = this->Src;
	this->animetion.AnimetionSrc(src, this->active_);
	src.OffsetSize();
	if (this->dir == Fan::Dir::LEFT)
	{
		float k = src.w;
		src.w = src.x;
		src.x = k;
	}

	this->image.Draw(draw, src);

	//デバッグ用
	if (active_) WindHitBase.LineDraw();
}
bool Fan::Finalize() {
	return image.Finalize();
}
void Fan::SendWind() {
	auto water = OGge->GetTasks<Water>("water");
	if (water)
	{
		for (auto id = (*water).begin(); id != (*water).end(); ++id)
		{
			if ((*id)->CubeHit(this->WindHitBase))
			{
				if ((*id)->GetState() == Water::State::GAS)
				{
					(*id)->MovePos_x((float)this->strength);
				}
			}
		}
	}
}
void Fan::Animetion::AnimetionReset()
{
	this->animetionframe = 0;
	this->speed = 0;
}
void Fan::Animetion::AnimetionMove(bool flag)
{
	this->speed = 2;
	//扇風機が稼働している
	if (flag)
	{
		//扇風機を動かす(アニメーション)
		if (animetionframe <= 100)
		{
			animetionframe++;
		}
		else if (animetionframe <= 170)
		{
			animetionframe += speed;
		}
		else
		{
			animetionframe += speed;
			if (animetionframe >= 300)
			{
				animetionframe = 170;
			}
		}
	}
	else
	{
		//扇風機を遅くする（アニメーション）
		if (animetionframe >= 100)
		{
			animetionframe -= 5;
		}
		else if (animetionframe > 0)
		{
			animetionframe -= speed;
		}
		else
		{
			this->AnimetionReset();
		}
	}
}
void Fan::Animetion::AnimetionSrc(Box2D& src, bool flag)
{
	if (flag)
	{
		//アニメーションの計算をする
		if (animetionframe <= 120)
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
		else if (animetionframe <= 160)
		{
			src.x += (animetionframe / 8 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 5 % 3)* src.w;
		}
	}
	else
	{
		//アニメーションの計算をする
		if (animetionframe >= 160)
		{
			src.x += (animetionframe / 9 % 3)* src.w;
		}
		else if (animetionframe >= 120)
		{
			src.x += (animetionframe / 12 % 3)* src.w;
		}
		else
		{
			src.x += (animetionframe / 15 % 3)* src.w;
		}
	}
}

void Fan::changeActive() {
	this->active_ = !this->active_;
}

Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, /*std::shared_ptr<Switch>& swich,*/ float effectdis, bool active, bool flag) {
	Fan::SP to = Fan::SP(new Fan());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, r, d, /*swich,*/effectdis, active))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;

}

//void Fan::DataInput()
//{
//	this->taskName = "Senpuki";			//検索時に使うための名を登録する
//	__super::Init(taskName);			//TaskObject内の処理を行う
//
//										//アニメーションのリセットをする
//	animetion.AnimetionReset();
//
//	//画像関連の描画パス
//	std::string filePath = "fan.png";
//	image.Create(filePath);
//
//	//サウンドの生成
//	this->startflag = false;
//	sound.create(soundname, true);
//	sound.volume(0.8f);
//}
////常時稼働　扇風機
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	range = r;
//	dir = d;
//	//扇風機の描画座標
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//
//	std::cout << "常時起動扇風機　初期化" << std::endl;
//	return true;
//}
////反転フラグあり　扇風機
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan> target)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	range = r;
//	dir = d;
//	//扇風機の描画座標
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r + 16.f, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//
//	this->SetFanTarget(target);
//	std::cout << "反転フラグ扇風機　初期化" << std::endl;
//	return true;
//}
////スイッチあり　扇風機
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>&obj)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	range = r;
//	dir = d;
//	//扇風機の描画座標
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//	this->SetSwitchTarget(obj);
//	std::cout << "スイッチあり扇風機　初期化" << std::endl;
//	return true;
//}
////スイッチあり　反転フラグあり
//bool Fan::Initialize(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan> fantarget, std::shared_ptr<Switch>& switchtarget)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	range = r;
//	dir = d;
//	//扇風機の描画座標
//	position = pos;
//
//	if (dir == Fan::Dir::LEFT)
//	{
//		strength = -5;
//		this->WindHitBase.CreateObject(Cube, Vec2(position.x - (64.f * r), position.y), Vec2(64.f * r + pos.x - (pos.x - 64), 64.f), 0.0f);
//	}
//	else
//	{
//		strength = 5;
//		this->WindHitBase.CreateObject(Cube, pos, Vec2(64 * r, 64.f), 0.0f);
//	}
//	this->DataInput();
//
//	this->SetFanTarget(fantarget);
//	this->SetSwitchTarget(switchtarget);
//
//	std::cout << "スイッチあり扇風機　初期化" << std::endl;
//	return true;
//}
//void Fan::Animetion::AnimetionReset()
//{
//	this->animetionframe = 0;
//	this->speed = 0;
//}
//void Fan::SetFlag()
//{
//	//お互いのフラグを管理している場合
//	if (target != nullptr && fantarget != nullptr)
//	{
//		//スイッチのフラグを格納する
//		switchflag = !target->GetisON();
//		//ターゲットのスイッチからフラグを格納する
//		fanflag = !fantarget->GetSwitchFlag();
//	}
//	//スイッチからフラグを取り出す
//	else if (target != nullptr)
//	{
//		//スイッチのフラグを代入する
//		switchflag = target->GetisON();
//	}
//	//ある扇風機からフラグを取り出す（反転）
//	else if (fantarget != nullptr)
//	{
//		switchflag = !fantarget->GetSwitchFlag();
//	}
//	else
//	{
//		//スイッチがない場合は常時稼働する
//		switchflag = true;
//	}
//}
//void Fan::SetSwitchTarget(std::shared_ptr<Switch>&obj)
//{
//	if (obj != nullptr)
//	{
//		this->target = obj;
//	}
//}
//void Fan::SetFanTarget(std::shared_ptr<Fan> &obj)
//{
//	if (obj != nullptr)
//	{
//		this->fantarget = obj;
//	}
//}
//bool Fan::GetSwitchFlag()
//{
//	return switchflag;
//}
//void Fan::Animetion::AnimetionMove(bool flag)
//{
//	this->speed = 2;
//	//扇風機が稼働している
//	if (flag)
//	{
//		//扇風機を動かす(アニメーション)
//		if (animetionframe <= 300)
//		{
//			animetionframe++;
//		}
//		else
//		{
//			animetionframe += speed;
//		}
//	}
//	else
//	{
//		//扇風機を遅くする（アニメーション）
//		if (animetionframe >= 300)
//		{
//			animetionframe -= 5;
//		}
//		else if (animetionframe > 0)
//		{
//			animetionframe -= speed;
//		}
//		else
//		{
//			this->AnimetionReset();
//		}
//	}
//}
//void Fan::UpDate()
//{
//	//--------------------
//	//更新時に行う処理を記述
//	//--------------------
//	this->SetFlag();
//	//アニメーションを動かす処理
//	animetion.AnimetionMove(GetSwitchFlag());
//	//お互いのフラグを扱っている場合
//	if (target != nullptr && this->fantarget != nullptr)
//	{
//		//お互いがtrueのときのみ起動させる
//		if (GetSwitchFlag() && this->fanflag)
//		{
//			Motion();
//		}
//	}
//	//trueなら扇風機が起動する
//	else if (GetSwitchFlag())
//	{
//		Motion();
//	}
//	else
//	{
//		//値をリセットする
//		animetion.AnimetionReset();
//	}
//
//	//サウンドの再生について
//	if (switchflag)
//	{
//		if (startflag)
//		{
//			sound.play();
//			startflag = false;
//		}
//	}
//	if (switchflag == false)
//	{
//		if (sound.isplay() == true)
//		{
//			sound.stop();
//		}
//		startflag = true;
//	}
//}
//void Fan::Animetion::AnimetionSrc(Box2D& src, bool flag)
//{
//	if (flag)
//	{
//		//アニメーションの計算をする
//		if (animetionframe <= 120)
//		{
//			src.x += (animetionframe / 15 % 3)* src.w;
//		}
//		else if (animetionframe <= 160)
//		{
//			src.x += (animetionframe / 8 % 3)* src.w;
//		}
//		else
//		{
//			src.x += (animetionframe / 5 % 3)* src.w;
//		}
//	}
//	else
//	{
//		//アニメーションの計算をする
//		if (animetionframe >= 160)
//		{
//			src.x += (animetionframe / 15 % 3)* src.w;
//		}
//		else if (animetionframe >= 120)
//		{
//			src.x += (animetionframe / 8 % 3)* src.w;
//		}
//		else
//		{
//			src.x += (animetionframe / 5 % 3)* src.w;
//		}
//	}
//}
//void Fan::Render2D()
//{
//	//--------------------
//	//描画時に行う処理を記述
//	//--------------------
//	Box2D draw(position, Vec2(64, 64));
//	draw.OffsetSize();
//	Box2D src = this->Src;
//	this->animetion.AnimetionSrc(src, GetSwitchFlag());
//	src.OffsetSize();
//	if (this->dir == Fan::Dir::LEFT)
//	{
//		int k = src.w;
//		src.w = src.x;
//		src.x = k;
//	}
//
//	this->image.Draw(draw, src);
//}
//
//bool Fan::Finalize()
//{
//	//-----------------------------------------
//	//このオブジェクトが消滅するときに行う処理を記述
//	//-----------------------------------------
//
//	//次のタスクを作るかかつアプリケーションが終了予定かどうか
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//
//	}
//	return true;
//}
//void Fan::SetWindRange(Vec2& b)
//{
//	this->WindHitBase.Scale = b;
//}
//void Fan::Motion()
//{
//	auto water = OGge->GetTasks<Water>("water");
//	if (water)
//	{
//		for (auto id = (*water).begin(); id != (*water).end(); ++id)
//		{
//			if ((*id)->hit(this->WindHitBase))
//			{
//				if ((*id)->GetState() == Water::State::GAS)
//				{
//					(*id)->MovePos_x(this->strength);
//				}
//			}
//		}
//	}
//}
////----------------------------
////ここから下はclass名のみ変更する
////ほかは変更しないこと
////----------------------------
//Fan::Fan()
//{
//	std::cout << "扇風機　生成" << std::endl;
//	soundname = "wind1.wav";
//}
//Fan::~Fan()
//{
//	this->Finalize();
//	std::cout << "扇風機　解放" << std::endl;
//}
////常時稼働
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////スイッチあり
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Switch>&target, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////扇風機の反転フラグあり
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& target, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
////スイッチあり　扇風機の反転フラグあり
//Fan::SP Fan::Create(Vec2 pos, float r, Fan::Dir d, std::shared_ptr<Fan>& fantarget, std::shared_ptr<Switch>& switchtarget, bool flag_)
//{
//	Fan::SP to = Fan::SP(new Fan());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, r, d, fantarget, switchtarget))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}