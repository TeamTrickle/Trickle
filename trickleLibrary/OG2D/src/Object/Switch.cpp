#include "Switch.h"
using namespace std;

const int POS_X = 500;
const int POS_Y = 270;

const int IMAGE_SIZE_X = 32;		//画像サイズ
const int IMAGE_SIZE_Y = 32;		//画像サイズ
//☆☆☆☆//-----------------------------------------------------------------------------
Switch::Switch(/*EnemyHitTest* e_pointa*/)
{
	//player_pointa = p_pointa;
	//enemy_pointa = e_pointa;
	_filePath = "prototype.png";
	flag = false;
	switchflag = false;
}
//☆☆☆☆//-----------------------------------------------------------------------------
Switch::~Switch()
{
	//delete player_pointa;
	//delete enemy_pointa;
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Initlaize()
{
	/*_filePath = "Switch.bmp";
	flag = false;
	switchflag = false;*/

	image.TextureCreate(_filePath);
	//collisionCube.hitBase = Box2D((int)position.x, (int)position.y, 32, 32);
	CreateObject(Objform::Cube, Vec2(POS_X, POS_Y), Vec2(IMAGE_SIZE_X, IMAGE_SIZE_Y), 0);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::UpDate()
{
	//CheakHit(enemy_pointa);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Finalize()
{
	image.Finalize();
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	draw.OffsetSize();
	Box2D src(IMAGE_SIZE_X * 8,0, IMAGE_SIZE_X,IMAGE_SIZE_Y);
	image.Draw(draw, src);
}
//☆☆☆☆//-----------------------------------------------------------------------------
void Switch::CheakHit()
{
	//flag = collisionCube.hitBox(objhit->collisionCube);

	//スイッチが押せる場所にいるかどうか？
	Object::CollisionProcess = [&](const Object& o_)
	{
		if (o_.objectTag == "Player")
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
		if (flag)
		{
			//cout << "true" << endl;
			// Sキーを押してSwitchをON/OFFの切り替えをする
			if (Input::KeyInputDown(Input::S))
			{
				if (switchflag)
				{
					switchflag = false;
					cout << "スイッチoff" << endl;
				}
				else
				{
					switchflag = true;
					cout << "スイッチon" << endl;
				}
			}
		}
	};
}