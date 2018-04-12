#include "Senpuki.h"

using namespace std;

//const int INITIALCOORDINATE_X = 400;	//初期座標
//const int INITIALCOORDINATE_Y = 200;	//初期座標
//const int IMAGE_SIZE = 128;			    //画像サイズ
//const float WIND = 1.5f;				//風力（風の強さ）
//
////☆☆☆☆//-----------------------------------------------------------------------------
//Senpuki::Senpuki(/*EnemyHitTest* e_pointa*/)
//{
//	//player_pointa = p_pointa;
//	//enemy_pointa = e_pointa;
//	
//	position.x = INITIALCOORDINATE_X;
//	position.y = INITIALCOORDINATE_Y;
//	_filePath = "test.png";
//	_hitbox = "Collision.png";
//	flag = false;
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//Senpuki::~Senpuki()
//{
//
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::Initialize()
//{
//	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE, IMAGE_SIZE), 0);
//	/*position.x = INITIALCOORDINATE_X;
//	position.y = INITIALCOORDINATE_Y;
//	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE, IMAGE_SIZE), 0);
//	_filePath = "test.png";
//	_hitbox = "Collision.png";
//	flag = false;*/
//
//	//画像関連//
//	senimg.TextureCreate(_filePath);		//画像パス指定をする
//	collbox.TextureCreate(_hitbox);
//	//collisionCube.hitBase = Box2D((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
//	//range.hitBase = Box2D((int)position.x / 2, (int)position.y / 2, IMAGE_SIZE + (int)position.x / 4, IMAGE_SIZE + (int)position.y / 4);
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::UpDate()
//{
//	//CheckHit(enemy_pointa,1);
//	if (flag)
//	{
//
//		if (true)//Playerが水蒸気の状態ならば・・・
//		{
//			//風を送りx座標に送ることで風が吹いているように見せる
//
//			//enemy_pointa->position.x -= WIND;
//		}
//	}
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::Finalize()
//{
//	senimg.Finalize();				
//	collbox.Finalize();
//}
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::Render()
//{
//	//扇風機
//	Box2D draw((int)position.x , (int)position.y,IMAGE_SIZE,IMAGE_SIZE);
//	draw.OffsetSize();
//	Box2D src(0, 0, IMAGE_SIZE, IMAGE_SIZE);
//	//当たり判定の描画（デバッグ時のみ適応）
//	/*
//	Box2D Colldraw(draw);
//	Colldraw.OffsetSize();
//	Box2D Collsrc(src);*/
//	senimg.Draw(draw, src);
//	//collbox.Draw(draw, src);
//}
////☆☆☆☆//-----------------------------------------------------------------------------
////  関数  //-----------------------------------------------------------------------------
////☆☆☆☆//-----------------------------------------------------------------------------
//void Senpuki::CheckHit(Object* objhit , int value = 0)
//{
//	//valueによって当たり判定を変える（デバッグ用）
//	switch (value)
//	{
//	case 0:
//		//flag = collisionCube.hitBox(objhit->collisionCube); //自機との当たり判定
//		flag = hit(*objhit);
//		break;
//	case 1:
//		flag = range.hitBox(objhit->collisionCube);         //視野範囲との当たり判定
//		break;
//	}
//}


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