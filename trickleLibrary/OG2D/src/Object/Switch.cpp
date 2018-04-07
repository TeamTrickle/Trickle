#include "Switch.h"
using namespace std;
typedef Input::KeyBoard It;                     //クラスの名前空間の省略

const int IMAGE_SIZE_X = 64;                    //画像サイズ_X
const int IMAGE_SIZE_Y = 64;                    //画像サイズ_Y

const int POS_X = IMAGE_SIZE_X * 19;            //初期座標値（現在使用はしていません）
const int POS_Y = IMAGE_SIZE_Y * 8;             //初期座標値（現在使用はしてません）

//☆☆☆☆//-----------------------------------------------------------------------------
Switch::Switch()                                //コンストラクタ（引数なし）                      
{

}
//☆☆☆☆//-----------------------------------------------------------------------------
Switch::Switch(Vec2 pos)                        //コンストラクタ（Vec2　初期座標値）           
{
	position = pos;                             //初期座標値をSwicthの座標値に代入する
	Pos.push_back(pos);                         //引数で受け取った座標値をvectorに保存する
}
//☆☆☆☆//-----------------------------------------------------------------------------
Switch::~Switch()                               //デストラクタ　現在は特になし
{
	
}
//☆☆☆☆//-----------------------------------------------------------------------------
bool Switch::Initlaize(Vec2 pos,Switch* s_)
{
	switch_pointa = s_;                           //switch_pointaに当たり判定矩形を生成する 
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);         //当たり判定矩形を生成する
	objectTag = "Switch";
	CheakHit(*switch_pointa);              //当たり判定関数を呼び出す
	return true;                           //関数処理無事に終了したことをtrueで返す
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::UpDate()                      //更新処理                      
{

}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Finalize()                    //解放処理
{
	player_pointa = nullptr;
	senpuki_pointa = nullptr;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Render()                      //描画処理
{
	
}
//追加変数//-----------------------------------------------------------------------------
void Switch::CheakHit(Switch& s_)                                 //当たり判定の処理をまとめた関数
{	
	Object::CollisionProcess = [&](const Object& o_)                                                          //当たり判定処理                
	{
		if (player_pointa->hit(s_))                          //Playerとの接触判定が合ったら・・・  //エラー箇所                                                             
		{
			Hitflag = true;                                  //当たり判定フラグをtrue
		}
		else                                                 //Playerではなかった場合・・・
		{
			Hitflag = false;                                 //当たり判定フラグをfalse
		}
		if (Hitflag)                                         //当たり判定フラグがtrueなら・・・
		{
			if (gameEngine->input.keyboard.down(It::Q))          //かつキーボード操作『Q』押されたら・・・
			{
				if (switch_ON_OFF)                                   //この時にスイッチの切り替えフラグがtrueなら・・・
				{
					switch_ON_OFF = false;                               //スイッチの切り替えフラグをfalseにする
					cout << "スイッチoff" << endl;                       //出力
				}
				else                                                 //falseだったら・・・
				{
					switch_ON_OFF = true;                                //スイッチの切り替えフラグをtrueにする
					cout << "スイッチon" << endl;                        //出力
				}
			}
			senpuki_pointa->Switch_Swap(*this);              //Switchの情報を貰って参照する
		}
	};
}

bool Switch::HasParent()const
{
	return player_pointa != nullptr;                    //Player*はnullptrになっていないか？ 
}

void Switch::SetParent(Player* player)
{
	player_pointa = player;                             //引数からPlayer*に代入する
}

void Switch::SetParent(Senpuki* sen)
{
	senpuki_pointa = sen;                               //引数で受け取ったアドレス値をsenpuki_pointaに代入する
}

void Switch::Set_Pos(const Vec2 pos)
{
	Pos.push_back(pos);                                 //引数の座標値を追加する
}
