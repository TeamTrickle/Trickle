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
	Switch_Hitflag = false;                 //最初は上の扇風機が動いている状態
	CheakHit();								//当たり判定を行う
	return true;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Senpuki::UpDate()
{
	if (Switch_Hitflag)                     //スイッチとの当たり判定があるとき・・・
	{
		cout << "スイッチと接触中" << endl;
	}
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
		//cout << "ラムダ式の処理中なう" << endl;                      //出力
		if (o_.objectTag == "Water")                                 //Playerの当たり判定（本来は水で判定を取る）
		{
			this->Water_flag = true;                                 //flagをtrueにする
			//cout << "当たっています" << endl;                        //出力
			if (Water_flag)                                          //水と接触判定したら・・・
			{
				if (((Water&)o_).GetState() == Water::State::GAS)    //水蒸気の状態ならば・・・
				{
					//cout << "風が吹きます" << endl;
				}
				if (((Water&)o_).GetState() == Water::State::LIQUID) //液体の状態ならば・・・
				{
					
				}
			}
		}
		else
		{
			this->Water_flag = false;
		}

		//_____________________________________________________________________________________________|//
		//|                                                                                            |//
		//|扇風機とSwitchとの当たり判定処理内容オブジェクトタグを使用してでの当たり判定を採用しました。|//
		//|今後フラグが多くなる場合はint型でのflagを利用してビット演算で行う予定です。                 |//
		//|____________________________________________________________________________________________|//
		if (o_.objectTag == "Switch")              //objectTagがSwitchだったら・・・
		{
			this->Switch_Hitflag = true;           //trueにして下のボタンに切り替える
		}
		else
		{
			this->Switch_Hitflag = false;          //スイッチではない場合はfalseを返す
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
Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //扇風機を切り替えるときに座標値も切り替える関数を
{
	return position = pos;
}


//|__________________________________________________________________________________|//
//|未実装　                                                                          |//
//|・スイッチの情報を受け取ってスイッチの切り替え処理と扇風機が切り替わる処理を実行中|//
//|                                                                                  |//
//|__________________________________________________________________________________|//