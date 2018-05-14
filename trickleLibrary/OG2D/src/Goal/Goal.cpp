#include "Goal.h"
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"
bool Goal::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Goal";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	cleared = false;
	this->objectTag = "Goal";
	//テクスチャの読み込み
	tex.Create((std::string)"goal.png");
	//オブジェクトの生成
	CreateObject(Objform::Cube, Vec2(28 * 64, 14 * 64), Vec2(64, 64), 0.f);
	return true;
}
bool Goal::Initialize(Vec2& pos) {
	cleared = false;
	this->objectTag = "Goal";
	//テクスチャの読み込み
	tex.Create((std::string)"goal.png");
	//オブジェクトの生成
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);
	return true;
}

void Goal::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	if (this->ClearCheck())
	{
		cleared = true;
	}
}

void Goal::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) {
		src = Box2D(64, 0, 64, 64);
	}
	else {
		src = Box2D(0, 0, 64, 64);
	}
	src.OffsetSize();
	tex.Draw(draw, src);
}

bool Goal::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		tex.Finalize();
	}
	return true;
}
//void Goal::AddWater(Water* o)
//{
//	this->waters.push_back(o);
//}

//bool Goal::DeleteWater(Water* o)
//{
//	for (auto id = this->waters.begin(); id != this->waters.end(); ++id)
//	{
//		if ((*id) == o)
//		{
//			this->waters.erase(id);
//			return true;
//		}
//	}
//	return false;
//}

bool Goal::ClearCheck()
{
	auto waters = OGge->GetTasks<Water>("Water");
	if (waters == nullptr)
	{
		return false;
	}
	for (int i = 0; i < (*waters).size(); ++i)
	{
		if (!(*waters)[i]->hit(*this))
		{
			if ((*waters)[i]->GetSituation() == Water::Situation::Normal && (*waters)[i]->GetState() == Water::State::LIQUID)
			{
				return true;
			}
		}
	}
	return false;
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Goal::Goal()
{
	
}

Goal::~Goal()
{
	this->Finalize();
}

Goal::SP Goal::Create(bool flag_)
{
	Goal::SP to = Goal::SP(new Goal());
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

Goal::SP Goal::Create(bool flag_,Vec2& pos)
{
	Goal::SP to = Goal::SP(new Goal());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}