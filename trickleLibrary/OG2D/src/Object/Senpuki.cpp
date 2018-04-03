#include "Senpuki.h"

using namespace std;

//11番配置座標(今回のは上)

const int IMAGE_SIZE_X = 64;                                       //画像サイズ_X
const int IMAGE_SIZE_Y = 64;                                       //画像サイズ_Y

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
	Wall_flag = false;                      //壁との当たり判定フラグの設定
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
	parent_Wall = nullptr;
	for (int i = 0; i < 2; ++i)              //Switchの数によってループ回数を変化させる
	{
		switch_pointa[i] = nullptr;          //現在あるSwitchの文をnullptrとして返す
	}
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
		if (o_.objectTag == "Water")                                 //扇風機の当たり判定（本来は水で判定を取る）
		{
			this->Water_flag = true;                                 //flagをtrueにする

			if (Water_flag)                                          //水と接触判定したら・・・
			{
				cout << "作動" << endl;
				if (((Water&)o_).GetState() == Water::State::GAS)      //水蒸気の状態ならば・・・
				{
					const_cast<Object&>(o_).position = Water_Move((Water&)o_);      //constを外してVec2の動きを渡す
				}
			}
		}
		else
		{
			this->Water_flag = false;                               //他のオブジェクトでは水との当たり判定フラグをfalseにする
		}
	};
}
bool Senpuki::HasParent()const                                      //nullptrではないか確認する関数
{
	return parent_Wall != nullptr;
}
void Senpuki::SetParent(Switch* obj, int value)                     //当たり判定に必要なオブジェクトを(Switch*)に代入する
{
	switch_pointa[value] = obj;
}
void Senpuki::SetParent(Object* obj)                                 //当たり判定に必要なオブジェクトのアドレス値を格納する
{

}
void Senpuki::SetParent(Map* obj)
{
	parent_Wall = obj;                                               //当たり判定に必要なオブジェクトのアドレス値を格納する
}
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //扇風機を切り替えるときに座標値も切り替える関数
{
	return position = pos;                                           //切り替える時にVec2で戻り値を渡す
}
void Senpuki::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);                                              //座標値をVectorに渡す
}
void Senpuki::Switch_Swap(Switch& s_)
{
	//_____________________________________________________________________________________________|//
	//|                                                                                            |//
	//|スイッチの切り替えフラグによって座標値を入れ替える処理です。                                |//
	//|座標値についてはvectorで保存した配列によって値を貰ってきます。                              |//
	//|なので、現在ではTask_Gameのところで座標値をvectorに入れる方式になります。                   |//
	//|____________________________________________________________________________________________|//
	if (!s_.switch_ON_OFF)                              //スイッチの切り替えフラグがtrueの時
	{
		Switch_On_or_Off_pos(Pos[0]);                                  //当たり判定の座標値を変更する 上の座標値
	}
	else
	{
		Switch_On_or_Off_pos(Pos[1]);                                  //当たり判定の座標値を変更する 下の座標値
	}
}
Vec2 Senpuki::Water_Move(Object& o_)
{
	if (Water_flag)                               //水関係の当たり判定フラグがtureなら・・・
	{
		if (((Water&)o_).GetState() == Water::State::GAS)       //水蒸気ならば・・・
		{
			while (Wall_flag == false)                           //壁との当たり判定フラグがtrueになるまで
			{
				o_.position.x++;                                 //x座標の移動をする
				for (int y = 0; y < parent_Wall->mapSize.y; ++y) //マップのy値の値までループ変数yを増加
				{
					for (int x = 0; x < parent_Wall->mapSize.x; ++x) //マップのx値までループ変数xを増加
					{
						if (parent_Wall->hitBase[y][x].objectTag == "Floor") //マップのオブジェクトタグが床ならば・・・
						{
							if (parent_Wall->MapHitCheck(o_))        //マップと水の当たり判定関数を呼び出す
							{
								Wall_flag = true;                    //接触をしたらtrueを返す
								cout << "接触成功" << endl;          //動きを確認したら出力
								break;                               //for文を抜け出す
							}
						}
					}
					break;              //for文を抜け出す
				}
				break;        //while文を抜け出す
			}
		}
		Wall_flag = false;    //水蒸気以外はすべてfalseにする
	}
	return o_.position;       //変更したベクトルを返す
}
