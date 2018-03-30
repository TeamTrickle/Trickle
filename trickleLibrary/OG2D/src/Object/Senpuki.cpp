#include "Senpuki.h"

using namespace std;

//11番配置座標

const int IMAGE_SIZE_X = 64;			//画像サイズ
const int IMAGE_SIZE_Y = 64;			//画像サイズ

const int INITIALCOORDINATE_X = IMAGE_SIZE_X * 11;	//初期座標
const int INITIALCOORDINATE_Y = IMAGE_SIZE_Y * 7;	//初期座標

const float WIND = 1.5f;				//風力（風の強さ）

//☆☆☆☆//-----------------------------------------------------------------------------
Senpuki::Senpuki()
{

}
Senpuki::Senpuki(Vec2 pos)
{
	position = pos;
}
//☆☆☆☆//-----------------------------------------------------------------------------
Senpuki::~Senpuki()
{

}
//☆☆☆☆//-----------------------------------------------------------------------------

//初期化をするところ(Vec2 初期座標)
bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";

	//当たり判定の矩形を用意する
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);								//当たり判定矩形を生成する
	cout << "判定座標(" << position.x + IMAGE_SIZE_X << "," << position.y + IMAGE_SIZE_Y << endl;		//デバッグ機能での当たり判定の表示
	//
	flag = false;							//当たり判定初期フラグの設定
	CheakHit();								//当たり判定を行う
	return true;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{
	
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::Finalize()
{
	delete parent;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::Render()
{

}
//☆☆☆☆//-----------------------------------------------------------------------------
//  関数  //-----------------------------------------------------------------------------
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::CheakHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		cout << "ラムダ式の処理中なう" << endl;
		if (parent->hit(*this))			//Playerの当たり判定（本来は水で判定を取る）
		{
			flag = true;				//Playerと接している
			cout << "当たっています" << endl;
			if (flag)
			{
				//flag = collisionCube.hitBox(objhit->collisionCube); //自機との当たり判定
				if (((Water&)o_).GetState() == Water::State::GAS)//Playerが水蒸気の状態ならば・・・
				{
					//風を送りx座標に送ることで風が吹いているように見せる
					//o_.position.x -= WIND;
					cout << "風が吹きます" << endl;
				}
			}
		}
		else
		{
			flag = false;
		}
	};
}
bool Senpuki::HasParent()const
{
	return parent != nullptr;
}
void Senpuki::SetParent(Object* obj) 
{
	parent = obj;
}