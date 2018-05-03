#include "Switch.h"
using namespace std;

void Switch::Initialize(Vec2 pos) 
{
	//座標の設定
	position = pos;
	//当たり判定の実装
	CreateObject(Cube, position, Vec2(64, 64), 0.0f);
	//オブジェクトタグの追加
	objectTag = "Switch";
	//スイッチの切り替えフラグをONにする
	is_on = false;
}
void Switch::Update() 
{
	//何もなし
}
void Switch::Finalize() 
{
	targets.clear();
	image.Finalize();
}
void Switch::Render() 
{
	//csvがあるので描画の機能はなし
}
bool Switch::isON() 
{
	//切り替えフラグを返す
	return is_on;
}
void Switch::ON_OFF() 
{
	//trueとfalseの切り替えフラグを切り替える
	is_on = !is_on;
	//スイッチのONOFFが切り替わった時だけターゲットのChangeState()を呼び出す
	for (auto t : targets) 
	{
		if (t->objectTag == "Fan") 
		{
			//スイッチを押すと・・・
			((Fan*)t)->ChangeState();
		}
	}
}
void Switch::SetTarget(Object* t) 
{
	//あとで加熱器と製氷機のタグも追加すること
	if (t->objectTag != "Fan") { return; }
	targets.push_back(t);
}