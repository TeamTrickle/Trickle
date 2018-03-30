#include "Senpuki.h"

using namespace std;

//11番配置座標(今回のは上)

const int IMAGE_SIZE_X = 64;                                       //画像サイズ_X
const int IMAGE_SIZE_Y = 64;                                       //画像サイズ_Y

const int INITIALCOORDINATE_X = IMAGE_SIZE_X * 11;	               //初期座標_X
const int INITIALCOORDINATE_Y = IMAGE_SIZE_Y * 7;	               //初期座標_Y

const float WIND = 1.5f;				                           //風力（風の強さ）

//☆☆☆☆//-----------------------------------------------------------------------------
Senpuki::Senpuki()                                                 //コンストラクタ（なし）
{
	
}
Senpuki::Senpuki(Vec2 pos)                                         //コンストラクタ（Vec2　初期座標）
{
	position = pos;
}
//☆☆☆☆//-----------------------------------------------------------------------------
Senpuki::~Senpuki()                                                //デストラクタ　※現在は何もありません
{

}
//☆☆☆☆//-----------------------------------------------------------------------------

//初期化をするところ(Vec2 初期座標)
bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";                 //オブジェクトタグ名を生成する

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
void Senpuki::CheakHit()                                             //当たり判定の処理
{
	Object::CollisionProcess = [&](const Object& o_)                 //全てのローカルでのクラスを参照する？
	{
		cout << "ラムダ式の処理中なう" << endl;                      //出力
		if (o_.objectTag == "Water")                                 //Playerの当たり判定（本来は水で判定を取る）
		{
			flag = true;                                             //flagをtrueにする
			cout << "当たっています" << endl;                        //出力
			if (flag)                                                //水と接触判定したら・・・
			{
				if (((Water&)o_).GetState() == Water::State::GAS)    //水蒸気の状態ならば・・・
				{
					cout << "風が吹きます" << endl;
				}
				if (((Water&)o_).GetState() == Water::State::LIQUID) //液体の状態ならば・・・
				{
					cout << "液体の状態" << endl;
				}
			}
		}
		else
		{
			flag = false;
		}
	};
}
bool Senpuki::HasParent()const                                       //nullptrではないか確認する関数
{
	return parent != nullptr;
}
void Senpuki::SetParent(Object* obj)                                 //当たり判定に必要なオブジェクトをObject* parent に代入する
{
	parent = obj;
}