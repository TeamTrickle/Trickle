
#include "Senpuki.h"

using namespace std;

//ジャスティン風
//
////11番配置座標(今回のは上)
//
//const int IMAGE_SIZE_X = 64;                                       //画像サイズ_X
//const int IMAGE_SIZE_Y = 64;                                       //画像サイズ_Y
//
//const float WIND = 1.5f;				                           //風力（風の強さ）
//
//																   //☆☆☆☆//-----------------------------------------------------------------------------
//Senpuki::Senpuki()                                                 //コンストラクタ（なし）
//{
//
//}
//Senpuki::Senpuki(Vec2 pos)                                         //コンストラクタ（Vec2　初期座標）
//{
//	position = pos;                                                //送られた座標値を扇風機の座標データに代入させる
//	Pos.push_back(pos);                                            //送られた座標値を保存する（スイッチの切り替え時に必要だから）
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//Senpuki::~Senpuki()                                                //デストラクタ　※現在は何もありません
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//
//bool Senpuki::Initialize(Vec2 pos)
//{
//	range.objectTag = "Senpuuki";                 //オブジェクトタグ名を生成する
//
//												  //当たり判定の矩形を用意する
//	CreateObject(Objform::Cube, Vec2(position.x + 64, position.y), Vec2(IMAGE_SIZE_X * 6, IMAGE_SIZE_Y), 0);
//	range.CreateObject(Objform::Cube, Vec2(position.x + 64, position.y), Vec2(IMAGE_SIZE_X * 6, IMAGE_SIZE_Y), 0); //もう一つの当たり判定矩形を生成する
//	cout << "判定座標(" << position.x + IMAGE_SIZE_X << "," << position.y + IMAGE_SIZE_Y << endl;		//デバッグ機能での当たり判定の表示
//																									//
//	Water_flag = false;						//当たり判定初期フラグの設定
//	Wall_flag = false;                      //壁との当たり判定フラグの設定
//	Range_Flag = false;                     //視野範囲との当たり判定
//	CheakHit();								//当たり判定を行う
//	return true;
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::UpDate()
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::Finalize()
//{
//	parent_Wall = nullptr;
//	for (int i = 0; i < 2; ++i)              //Switchの数によってループ回数を変化させる
//	{
//		switch_pointa[i] = nullptr;          //現在あるSwitchの文をnullptrとして返す
//	}
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::Render()
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
////  関数  //-----------------------------------------------------------------------------
////☆☆☆☆//-----------------------------------------------------------------------------
//
//void Senpuki::CheakHit()                                             //当たり判定の処理
//{
//	this->range.CollisionProcess = [&](const Object& o_)             //全てのローカルでのクラスを参照する？
//	{
//		if (o_.objectTag == "Water")       //Playerとの当たり判定
//		{
//			this->Water_flag = true;                                 //flagをtrueにする
//
//			if (Water_flag)
//			{
//				if (((Water&)o_).GetState() == Water::State::GAS)   //この水は水蒸気であるか？
//				{
//					Range_Flag = Cheak_Water(o_);                   //当たり判定の戻り値を返す
//					if (Range_Flag)                                 //当たり判定がtrueを返してきたら・・・                        
//					{
//						const_cast<Object&>(o_).position = Water_Move((Water&)o_);      //constを外してVec2の動きを渡す
//					}
//				}
//			}
//		}
//		else
//		{
//			this->Water_flag = false;                               //他のオブジェクトでは水との当たり判定フラグをfalseにする
//		}
//	};
//}
//bool Senpuki::HasParent()const                                      //nullptrではないか確認する関数
//{
//	return parent_Wall != nullptr;
//}
//void Senpuki::SetParent(Switch* obj, int value)                     //当たり判定に必要なオブジェクトを(Switch*)に代入する
//{
//	switch_pointa[value] = obj;
//}
//void Senpuki::SetParent(Object* obj)                                 //当たり判定に必要なオブジェクトのアドレス値を格納する
//{
//
//}
//void Senpuki::SetParent(Map* obj)
//{
//	parent_Wall = obj;                                               //当たり判定に必要なオブジェクトのアドレス値を格納する
//}
//Vec2 Senpuki::Switch_On_or_Off_pos(const Vec2 pos)                   //扇風機を切り替えるときに座標値も切り替える関数
//{
//	return position = pos;                                           //切り替える時にVec2で戻り値を渡す
//}
//void Senpuki::Set_Pos(Vec2 pos)
//{
//	Pos.push_back(pos);                                              //座標値をVectorに渡す
//}
//void Senpuki::Switch_Swap(Switch* s_, int value)
//{
//	//_____________________________________________________________________________________________|//
//	//|                                                                                            |//
//	//|スイッチの切り替えフラグによって座標値を入れ替える処理です。                                |//
//	//|座標値についてはvectorで保存した配列によって値を貰ってきます。                              |//
//	//|なので、現在ではTask_Gameのところで座標値をvectorに入れる方式になります。                   |//
//	//|____________________________________________________________________________________________|//
//	if (s_->switch_ON_OFF[value])                              //スイッチの切り替えフラグがtrueの時
//	{
//		range.position.x = Pos[0].x - 64 * 6;
//	}
//	else
//	{
//		range.position.y = Pos[1].x + 64;
//	}
//}
//Vec2 Senpuki::Water_Move(Object& o_) //見直しが必要！！
//{
//	if (Water_flag)                               //水関係の当たり判定フラグがtureなら・・・
//	{
//		if (((Water&)o_).GetState() == Water::State::GAS)       //水蒸気ならば・・・
//		{
//			while (Wall_flag == false)                          //壁との当たり判定フラグがtrueになるまで
//			{
//				if (range.position.x == Pos[0].x + 64)         //本当はスイッチのフラグにしますが、バグるので無理やり対応        
//				{
//					o_.position.x++;                           //x座標値の移動
//				}
//				else
//				{
//					o_.position.x--;                           //x座標値の移動
//				}
//				for (int y = 0; y < parent_Wall->mapSize.y; ++y) //マップのy値の値までループ変数yを増加
//				{
//					for (int x = 0; x < parent_Wall->mapSize.x; ++x) //マップのx値までループ変数xを増加
//					{
//						if (parent_Wall->hitBase[y][x].objectTag == "Floor") //マップのオブジェクトタグが床ならば・・・
//						{
//							if (parent_Wall->MapHitCheck(o_))        //マップと水の当たり判定関数を呼び出す
//							{
//								Wall_flag = true;                    //接触をしたらtrueを返す
//								cout << "接触成功" << endl;          //動きを確認したら出力
//								break;                               //for文を抜け出す
//							}
//						}
//					}
//					break;              //for文を抜け出す
//				}
//				break;        //while文を抜け出す
//			}
//		}
//		Wall_flag = false;    //水蒸気以外はすべてfalseにする
//	}
//	return o_.position;       //変更したベクトルを返す
//}
//bool Senpuki::Cheak_Water(const Object& o_)
//{
//	if (range.hit(const_cast<Object&>(o_)))                        //視野範囲と水との当たり判定
//	{
//		return true;
//	}
//	return false;
//}




//横田さん風
void Fan::Initialize(Vec2 pos, float r, Fan::Dir d, bool activ) {
	position = pos;
	objectTag = "Fan";
	range = r;
	dir = d;
	active = activ;
	if (dir == Fan::Dir::LEFT) {
		CreateObject(Cube, Vec2(position.x - 64.0f*range, position.y), Vec2(64.0f * range, 64.0f), 0.0f);
		strength = -1;
	}
	else {
		CreateObject(Cube, Vec2(position.x + 64.0f, position.y), Vec2(64.0f*range, 64.0f), 0.0f);
		strength = 1;
	}
	Object::CollisionProcess = [&](const Object& o_) {
		if (active) {
			if (o_.objectTag == "Water") {
				if (((Water&)o_).GetSituation() == Water::Situation::Normal && ((Water&)o_).GetState() == Water::State::GAS) {
					const_cast<Object&>(o_).position.x += strength;
				}
			}
		}
	};
}
void Fan::AddSwitch(Switch* swit) {
	switches.push_back(swit);
}
void Fan::ChangeState(){
	active = !active;
}
void Fan::Finalize() {
	switches.clear();
	image.Finalize();
}
void Fan::Render(){}