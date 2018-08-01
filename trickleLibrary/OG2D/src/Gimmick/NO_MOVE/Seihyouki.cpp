#include "Seihyouki.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"


Seihyouki::Seihyouki()
	:
	maxChangeTime(5),maxCnt(30)
{}


bool Seihyouki::Initialize(Vec2& pos, Vec2 range, Angle ang, bool active) {
	this->taskName = "Seihyouki";	//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う
	SetDrawOrder(0.5f);

	changeStateCnt = 0;
	CreateObject(Cube, pos, range, 0);
	this->active = active;
	this->SetTexture(rm->GetTextureData((std::string)"fireIce"));

	this->animCnt = 0;
	this->coldNum = 0;
	this->timeCnt = 0;
	draw.clear();
	draw.resize(1);

	this->angle = ang;

	return true;
}
void Seihyouki::UpDate() {
	this->animCnt++;
	if (this->animCnt > 150)
	{
		this->animCnt = 0;
	}
	if (active) {
		toIce();
	}
	if (this->active)
	{
		if (this->timeCnt < this->maxCnt)
		{
			++this->timeCnt;
		}
	}
	else
	{
		if (this->timeCnt > 0)
		{
			--this->timeCnt;
		}
	}
}

void Seihyouki::Render2D() {
	//デバッグ用
	//if (active) 
	{
		LineDraw();
		//Box2D drawRL,srcR;
		if (angle==RIGHT)
		{
					coldNum = 1;
					float angle = 90.0f;
					for (int i = 0; i < coldNum; ++i) {
						draw[i] = Box2D(position.x+15 + (64 * i), position.y-32.0f, 64.f, Scale.y*2.0f);
						Vec2 origin = Vec2(draw[i].w, draw[i].h);
						draw[i].w *= ((float)this->timeCnt / (float)this->maxCnt);
						draw[i].h *= ((float)this->timeCnt / (float)this->maxCnt);
						draw[i].y += (origin.y - draw[i].h) / 2.f;
						draw[i].x -= (origin.x - draw[i].w) / 2.f;
						draw[i].OffsetSize();
					}
					Box2D src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
					src.OffsetSize();

					coldImg->Rotate(angle);
					for (auto draw_ : draw) {
						this->coldImg->Draw(draw_, src);
					}
		}
		else if (angle==LEFT)
		{
			coldNum = 1;
			float angle = 270.0f;
			for (int i = 0; i < coldNum; ++i) {
				draw[i] = Box2D(position.x+32.0f + (64 * i), position.y-32.0f, 64.f, Scale.y*2.0f);
				Vec2 origin = Vec2(draw[i].w, draw[i].h);
				draw[i].w *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].h *= ((float)this->timeCnt / (float)this->maxCnt);
				draw[i].y += (origin.y - draw[i].h) / 2.f;
				draw[i].x += (origin.x - draw[i].w) * 1.5f;
				draw[i].OffsetSize();
			}
			Box2D src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
			src.OffsetSize();

			coldImg->Rotate(angle);
			for (auto draw_ : draw) {
				this->coldImg->Draw(draw_, src);
			}
		}
		//上向きの製氷機使っていない
		//else if (angle == UP)
		//{
		//			for (int i = 0; i < coldNum; ++i) {
		//				draw[i] = Box2D(position.x + (64 * i), position.y, 64.f, Scale.y);
		//				draw[i].OffsetSize();
		//			}
		//			src = { 256 * (animCnt / 5 % 3), 256, 256, 256 };
		//			src.OffsetSize();

		//			for (auto draw_ : draw) {
		//				this->coldImg->Draw(draw_, src);
		//			}
		//}
	}
}
bool Seihyouki::Finalize() {
	//画像をこっちで読み込むならTextureのFinalize()を呼ぶこと
	return true;
}
void Seihyouki::toIce() {
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->hit(*this))
		{
			if ((*id)->GetState() == Water::State::LIQUID)
			{
				changeStateCnt++;
				if (changeStateCnt >= maxChangeTime)
				{
					(*id)->SetState(Water::State::SOLID);
					changeStateCnt = 0;
					break;
				}
			}
		}
	}
}
void Seihyouki::changeActive() {
	this->active = !this->active;
}
void Seihyouki::SetTexture(Texture* tex)
{
	this->coldImg = tex;
}
Seihyouki::SP Seihyouki::Create(Vec2& pos, Vec2 range, Seihyouki::Angle ang, bool active, bool flag_) {
	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, range, ang, active))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}


//bool Seihyouki::Initialize(Vec2& pos)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	this->taskName = "Seihyouki";	//検索時に使うための名を登録する
//	__super::Init(taskName);		//TaskObject内の処理を行う
//
//	movetime = 0;
//	hitBace.CreateObject(Cube, pos, Vec2(64, 64), 0);
//	this->GetFlag();
//	cout << "製氷機　初期化" << endl;
//	return true;
//}
//bool Seihyouki::Initialize(Vec2& pos ,std::shared_ptr<Switch> &target)
//{
//	//-----------------------------
//	//生成時に処理する初期化処理を記述
//	//-----------------------------
//	this->taskName = "Seihyouki";	//検索時に使うための名を登録する
//	__super::Init(taskName);		//TaskObject内の処理を行う
//
//	movetime = 0;
//	hitBace.CreateObject(Cube, pos, Vec2(64,64), 0);
//	this->SetSwitchFlag(target);
//	cout << "製氷機　初期化" << endl;
//	return true;
//}
//void Seihyouki::GetFlag()
//{
//	if (target != nullptr)
//	{
//		switchflag = target->isON();
//	}
//	else
//	{
//		switchflag = true;
//	}
//}
//void Seihyouki::SetSwitchFlag(std::shared_ptr<Switch>&obj)
//{
//	if (obj != nullptr)
//	{
//		target = obj;
//	}
//}
//bool Seihyouki::GetSwitchFlag()
//{
//	return switchflag;
//}
//void Seihyouki::UpDate()
//{
//	//--------------------
//	//更新時に行う処理を記述
//	//--------------------
//	this->GetFlag();
//
//	if (GetSwitchFlag())
//	{
//		toIce();
//	}
//}
//
//void Seihyouki::Render2D()
//{
//	//--------------------
//	//描画時に行う処理を記述
//	//--------------------
//}
//
//bool Seihyouki::Finalize()
//{
//	//-----------------------------------------
//	//このオブジェクトが消滅するときに行う処理を記述
//	//-----------------------------------------
//	//次のタスクを作るかかつアプリケーションが終了予定かどうか
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		
//	}
//	return true;
//}
//void Seihyouki::toIce()
//{
//	auto waters = OGge->GetTasks<Water>("water");
//	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
//	{
//		if ((*id)->hit(hitBace))
//		{
//			if ((*id)->GetState() == Water::State::SOLID)
//			{
//				while (true)
//				{
//					movetime++;
//					if (movetime >= movetime_ice)
//					{
//						(*id)->SetState(Water::State::LIQUID);
//						movetime = 0;
//						break;
//					}
//				}
//			}
//			if ((*id)->GetState() == Water::State::LIQUID)
//			{
//				while (true)
//				{
//					movetime++;
//					if (movetime >= movetime_ice)
//					{
//						(*id)->SetState(Water::State::SOLID);
//						movetime = 0;
//						break;
//					}
//				}
//			}
//		}
//	}
//}
////----------------------------
////ここから下はclass名のみ変更する
////ほかは変更しないこと
////----------------------------
//Seihyouki::Seihyouki()
//{
//	cout << "製氷機　生成" << endl;
//}
//
//Seihyouki::~Seihyouki()
//{
//	this->Finalize();
//	cout << "製氷機　解放" << endl;
//}
//Seihyouki::SP Seihyouki::Create(Vec2& pos,bool flag_)
//{
//	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
//Seihyouki::SP Seihyouki::Create(Vec2& pos,std::shared_ptr<Switch>&target,bool flag_)
//{
//	Seihyouki::SP to = Seihyouki::SP(new Seihyouki());
//	if (to)
//	{
//		to->me = to;
//		if (flag_)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos , target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}