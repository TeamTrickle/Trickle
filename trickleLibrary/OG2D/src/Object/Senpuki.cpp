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
	position = pos;                                                //送られた座標値を扇風機の座標データに代入させる
	Pos.push_back(pos);                                            //送られた座標値を保存する（スイッチの切り替え時に必要だから）
}
//☆☆☆☆//-----------------------------------------------------------------------------
Senpuki::~Senpuki()                                                //デストラクタ　※現在は何もありません
{

}
//☆☆☆☆//-----------------------------------------------------------------------------

bool Senpuki::Initialize(Vec2 pos)
{
	objectTag = "Senpuuki";                 //オブジェクトタグ名を生成する

	//当たり判定の矩形を用意する
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);								//当たり判定矩形を生成する
	cout << "判定座標(" << position.x + IMAGE_SIZE_X << "," << position.y + IMAGE_SIZE_Y << endl;		//デバッグ機能での当たり判定の表示
	//
	Water_flag = false;						//当たり判定初期フラグの設定
	CheakHit();								//当たり判定を行う
	Switch_Swap();                          //スイッチの切り替えフラグによって座標値の再設定をします。
	return true;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{

}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::Finalize()
{
	parent = nullptr;
	switch_pointa = nullptr;
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
		if (o_.objectTag == "Water")                                 //Playerの当たり判定（本来は水で判定を取る）
		{
			this->Water_flag = true;                                 //flagをtrueにする

			if (Water_flag)                                          //水と接触判定したら・・・
			{
				if (((Water&)o_).GetState() == Water::State::GAS)      //水蒸気の状態ならば・・・
				{
					const_cast<Object&>(o_).position = Water_Move((Water&)o_);      //constを外してVec2の動きを渡す
				}
			}
		}
		else
		{
			this->Water_flag = false;
		}
	};
}
bool Senpuki::HasParent()const                                       //nullptrではないか確認する関数
{
	return parent != nullptr;
}
void Senpuki::SetParent(Switch* obj)                                 //当たり判定に必要なオブジェクトを(Switch*)に代入する
{
	switch_pointa = obj;
}
void Senpuki::SetParent(Object* obj)                                 //当たり判定に必要なオブジェクトのアドレス値を格納する
{
	parent = obj;
}
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //扇風機を切り替えるときに座標値も切り替える関数
{
	return position = pos;
}
void Senpuki::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);
}
void Senpuki::Switch_Swap()
{
	//_____________________________________________________________________________________________|//
	//|                                                                                            |//
	//|スイッチの切り替えフラグによって座標値を入れ替える処理です。                                |//
	//|座標値についてはvectorで保存した配列によって値を貰ってきます。                              |//
	//|なので、現在ではTask_Gameのところで座標値をvectorに入れる方式になります。                   |//
	//|____________________________________________________________________________________________|//

	if (!switch_pointa->switch_ON_OFF)                                 //スイッチの切り替えフラグがtrueの時
	{
		Switch_On_or_Off_pos(Pos[0]);                                  //当たり判定の座標値を変更する 上の座標値
	}
	else
	{
		Switch_On_or_Off_pos(Pos[1]);                                  //当たり判定の座標値を変更する 下の座標値
	}
	cout << this->position.x << " , " << this->position.y << endl;     //変更した座標値の出力する
}
Vec2 Senpuki::Water_Move(Water& o_)
{
	if (Water_flag)                               //水関係の当たり判定フラグがtureなら・・・
	{
		if (o_.GetState() == Water::State::GAS)       //水蒸気ならば・・・
		{
			o_.position.x++;                          //x座標の移動をする
		}
	}
	return o_.position;
}
template<typename T>
T& Senpuki::const_off(T& obj)
{
	return const_cast<T&>(obj);
}
//|__________________________________________________________________________________|//
//|未実装　                                                                          |//
//|                                                                                  |//
//|・スイッチを複数当たり判定対象にすること                                          |//
//|・水の移動（アクセスする方法に苦戦)                                               |//
//|・風を発生される（壁まで風を送る）                                                |//
//|__________________________________________________________________________________|//