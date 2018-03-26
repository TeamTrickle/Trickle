#include "Kanetuki.h"
using namespace std;

const int POS_X = 600;
const int POS_Y = 100;			//

const int IMAGE_SIZE = 128;		//画像サイズ

const int HOTTIME = 1;			//水蒸気になるまでの時間
const int HOT_TIME = 180;		//水蒸気に変化する時間

//☆☆☆☆//-----------------------------------------------------------------------------
Kanetuki::Kanetuki(EnemyHitTest* e_pointa)
{
	//player_pointa = p_pointa;

	//EnemyHitTestクラスの情報を取得する
	//enemy_pointa = e_pointa;     

	_filePath = "Kanetuki.jpg";	
	position = Vec2(POS_X, POS_Y);
	flag = false;
	Count = 0;
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
	image.TextureCreate(_filePath);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::UpDate()
{
	//当たり判定の座標がどこから出来ているか？分からないです。
	collisionCube.hitBase = Box2D((int)position.x + 100, (int)position.y /2 + 128, IMAGE_SIZE, IMAGE_SIZE);

	// ___________________________________________________ //
	//| Playerに当たり一定の時間が立つと水蒸気に変化します|//
	//|___________________________________________________|//

	/*CheckHit(enemy_pointa);
	if (flag)
	{
		cout << "true" << endl;
		if (enemy_pointa->state == State::Frieze)
		{
			Count += HOTTIME;
			if (Count >= HOT_TIME)
			{
				enemy_pointa->state = State::Hot;
			}
		}
	}
	else
	{
		//cout << "false" << endl;
		Count = 0;
	}*/
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Kanetuki::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
	draw.OffsetSize();
	Box2D src(0, 0, IMAGE_SIZE, IMAGE_SIZE);
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
void Kanetuki::CheckHit(Object* objhit)
{
	flag = collisionCube.hitBox(objhit->collisionCube);
}