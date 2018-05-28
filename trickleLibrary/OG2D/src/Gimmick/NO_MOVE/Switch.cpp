#include "Switch.h"
using namespace std;

//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
bool Switch::Initialize(Vec2& pos)
{
	taskName = "Switch";
	//タグ検索を検知可能にする
	this->Init(taskName);			//TaskObject内の処理を行う
									//当たり判定の実装
	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	image.Create((std::string)"switch.png");
	cout << "通常スイッチ　初期化" << endl;
	return true;
}
bool Switch::Initialize(Vec2& pos, Switch::SP target)
{
	if (target)
	{
		cout << "スイッチを検知" << endl;
	}
	else
	{
		cout << "スイッチ代入失敗" << endl;
	}
	taskName = "Switch";
	//タグ検索を検知可能にする
	this->Init(taskName);			//TaskObject内の処理を行う
	//当たり判定の実装
	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	//ターゲットを代入する
	SetTarget(target);
	image.Create((std::string)"switch.png");
	cout << "ターゲットスイッチ　初期化" << endl;
	return true;
}
void Switch::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	//このスイッチのフラグと対象に反転させる
	if (targetswitch != nullptr)
	{
		this->TargetSwitchChenge();
	}
}
void Switch::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	if (this->GetisON())
	{
		int temp = src.x;
		src.x = src.w;
		src.w = temp;
	}
	image.Draw(draw, src);
}

bool Switch::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
bool Switch::GetisON()
{
	//切り替えフラグを返す
	return is_on;
}
void Switch::ON_OFF()
{
	//trueとfalseの切り替えフラグを切り替える
	is_on = !is_on;
}
void Switch::SetTarget(Switch::SP target)
{
	if (target != nullptr)
	{
		this->targetswitch = target;
		this->is_on = !this->targetswitch->GetisON();
	}
}
void Switch::TargetSwitchChenge()
{
	if (targetswitch != nullptr)
	{
		this->is_on = !this->targetswitch->GetisON();
	}		
}
Switch::Switch()
{
	cout << "スイッチ　生成" << endl;
}

Switch::~Switch()
{
	this->Finalize();
	cout << "スイッチ　解放" << endl;
}
Switch::SP Switch::Create(Vec2& pos, Switch::SP target,bool flag)
{
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
Switch::SP Switch::Create(Vec2& pos, bool flag)
{
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag)
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