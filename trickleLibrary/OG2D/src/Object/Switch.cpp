#include "Switch.h"
using namespace std;
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
bool Switch::Initlaize(Vec2 pos)           //初期化処理　当たり判定・矩形の生成・フラグの初期化
{
	CreateObject(Objform::Cube, pos, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);                                    //当たり判定矩形を生成する
	CheakHit();                            //当たり判定関数を呼び出す
	return true;                           //関数処理無事に終了したことをtrueで返す
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::UpDate()                      //更新処理                      
{
	CheakHit();                            //当たり判定の処理をまとめた関数
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Finalize()                    //解放処理
{
	
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Render()                      //描画処理
{
	
}
//追加変数//-----------------------------------------------------------------------------
void Switch::CheakHit()                                 //当たり判定の処理をまとめた関数
{	
	Object::CollisionProcess = [&](const Object& o_)                                                          //当たり判定処理                
	{
		cout << "ラムダ式" << endl;
		if (player_pointa->hit(*this))                       //Playerとの接触判定が合ったら・・・                                                               
		{
			cout << "接触成功" << endl;                      //出力する
			Hitflag = true;                                  //当たり判定フラグをtrue
		}
		else                                                 //Playerではなかった場合・・・
		{
			cout << "接触なし　スイッチ" << endl;            //出力
			Hitflag = false;                                 //当たり判定フラグをfalse
		}
		if (Hitflag)                                         //当たり判定フラグがtrueなら・・・
		{
			if (Input::KeyInputDown(Input::S))                    //かつキーボード操作『S』押されたら・・・
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
