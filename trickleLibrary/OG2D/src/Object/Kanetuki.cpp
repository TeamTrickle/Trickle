#include "Kanetuki.h"
using namespace std;

const int POS_X = 600;
const int POS_Y = 100;			

const int IMAGE_SIZE_X = 32;	//画像サイズX座標
const int IMAGE_SIZE_Y = 32;	//画像サイズY座標

const int HOTTIME = 1;			//水蒸気になるまでの時間
const int HOT_TIME = 180;		//水蒸気に変化する時間

//☆☆☆☆//-----------------------------------------------------------------------------
Kanetuki::Kanetuki(/*EnemyHitTest* e_pointa*/)
{
	//player_pointa = p_pointa;

	//EnemyHitTestクラスの情報を取得する
	//enemy_pointa = e_pointa;     

	_filePath = "prototype.png";	
	position = Vec2(POS_X, POS_Y);
	flag = false;
	Count = 0;
	objectTag = "Kanetuki";
}

//☆☆☆☆//-----------------------------------------------------------------------------
Kanetuki::~Kanetuki()
{
	//delete player_pointa;
	//delete enemy_pointa;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::Initialize()
{
	/*_filePath = "Kanetuki.jpg";
	position = Vec2(POS_X, POS_Y);
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE, IMAGE_SIZE), 0);
	flag = false;
	Count = 0;*/
	image.TextureCreate(_filePath);
	CreateObject(Objform::Cube, position, Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::UpDate()
{
	//collisionCube.hitBase = Box2D((int)position.x + 100, (int)position.y /2 + 128, IMAGE_SIZE, IMAGE_SIZE);

	// ___________________________________________________ //
	//| Playerに当たり一定の時間が立つと水蒸気に変化します|//
	//|___________________________________________________|//

}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	draw.OffsetSize();
	Box2D src(IMAGE_SIZE_X * 10, 0, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	image.Draw(draw, src);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::Finalize()
{
	image.Finalize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
//  関数  //-----------------------------------------------------------------------------
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::CheckHit()
{
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Water")
		{
			flag = true;
			if (flag)								//Playerと接してるとき
			{
				if (((Water&)o_).GetState() == Water::State::SOLID)
				{
					Count += HOTTIME;				//加熱カウンタを増やす

					if (Count >= HOT_TIME)			//加熱カウンタが上限に達したら
					{
						//水蒸気の状態にする
						((Water&)o_).SetState(Water::State::GAS);
					}
				}
			}
			else
			{
				//cout << "false" << endl;
				Count = 0;							//加熱カウンタを元に戻す
			}
		}
		else
		{
			flag = false;
		}
	};
}