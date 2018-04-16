#include "Switch.h"
using namespace std;

//ジャスティン風
//const int IMAGE_SIZE_X = 64;                    //画像サイズ_X
//const int IMAGE_SIZE_Y = 64;                    //画像サイズ_Y
//
//const int POS_X = IMAGE_SIZE_X * 19;            //初期座標値（現在使用はしていません）
//const int POS_Y = IMAGE_SIZE_Y * 8;             //初期座標値（現在使用はしてません）
//
//												//☆☆☆☆//-----------------------------------------------------------------------------
//Switch::Switch()                                //コンストラクタ（引数なし）                      
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//Switch::Switch(Vec2 pos)                        //コンストラクタ（Vec2　初期座標値）           
//{
//	position = pos;                             //初期座標値をSwicthの座標値に代入する
//	Pos.push_back(pos);                         //引数で受け取った座標値をvectorに保存する
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//Switch::~Switch()                               //デストラクタ　現在は特になし
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Switch::Initlaize()
//{
//	for (int i = 0; i < 2; ++i)                //スイッチの設置分ループさせる
//	{
//		switch_ON_OFF[i] = false;
//		hitBace[i].CreateObject(Objform::Cube, Pos[i], Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);         //当たり判定矩形を生成する
//	}
//	CheakHit();
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Switch::UpDate()                      //更新処理                      
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Switch::Finalize()                    //解放処理
//{
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Switch::Render()                      //描画処理
//{
//
//}
////追加変数//-----------------------------------------------------------------------------
//void Switch::CheakHit()                                 //当たり判定の処理をまとめた関数
//{
//	hitBace[0].CollisionProcess = [&](const Object& o_)                                                          //当たり判定処理                
//	{
//		if (o_.objectTag == "PlayerFoot" || o_.objectTag == "PlayerLeft" || o_.objectTag == "PlayerRight")
//		{
//			if (gameEngine->in.down(Input::KeyBoard::Q))
//			{
//				if (switch_ON_OFF[0])
//				{
//					cout << "OFF" << endl;
//					switch_ON_OFF[0] = false;
//				}
//				else
//				{
//					cout << "ON" << endl;
//					switch_ON_OFF[0] = true;
//				}
//				((Senpuki&)o_).Switch_Swap(this, 0);
//			}
//		}
//	};
//
//	hitBace[1].CollisionProcess = [&](const Object& o_)                                                          //当たり判定処理                
//	{
//		if (o_.objectTag == "PlayerFoot" || o_.objectTag == "PlayerLeft" || o_.objectTag == "PlayerRight")
//		{
//			if (gameEngine->in.down(Input::KeyBoard::Q))
//			{
//				if (switch_ON_OFF[1])
//				{
//					cout << "OFF" << endl;
//					switch_ON_OFF[1] = false;
//				}
//				else
//				{
//					cout << "ON" << endl;
//					switch_ON_OFF[1] = true;
//				}
//				//((Senpuki&)o_).Switch_Swap(this, 1); アクセス違反の原因になっています。
//			}
//		}
//	};
//}
//void Switch::Set_Pos(const Vec2 pos)
//{
//	Pos.push_back(pos);                                 //引数の座標値を追加する
//}



//横田さん風
void Switch::Initialize(Vec2 pos) {
	position = pos;
	CreateObject(Cube, position, Vec2(64, 64), 0.0f);
	objectTag = "Switch";
	is_on = false;
}
void Switch::Update() {

}
void Switch::Finalize() {
	targets.clear();
	image.Finalize();
}
void Switch::Render() {

}
bool Switch::isON() {
	return is_on;
}
void Switch::ON_OFF() {
	is_on = !is_on;
	//スイッチのONOFFが切り替わった時だけターゲットのChangeState()を呼び出す
	for (auto t : targets) {
		if (t->objectTag == "Fan") {
			((Fan*)t)->ChangeState();
		}
	}
}
void Switch::SetTarget(Object* t) {
	//あとで加熱器と製氷機のタグも追加すること
	if (t->objectTag != "Fan") { return; }
	targets.push_back(t);
}