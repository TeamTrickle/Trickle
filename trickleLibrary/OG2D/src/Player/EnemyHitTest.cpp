#include "EnemyHitTest.h"

const int INITIALCOORDINATE_X = 100;	//初期座標
const int INITIALCOORDINATE_Y = 100;	//初期座標

const int IMAGE_SIZE = 128;				//画像サイズ
const int SPEED = 3;					//ENEMY SPEED

EnemyHitTest::EnemyHitTest()
{
	position.x = INITIALCOORDINATE_X;
	position.y = INITIALCOORDINATE_Y;
	state = State::Frieze;
}
EnemyHitTest::~EnemyHitTest()
{

}
void EnemyHitTest::Initialize()
{
	collisionCube.hitBase = Box2D((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE); //当たり判定を設定する
	_filePath = "player.png";
	image.TextureCreate(_filePath);
}
void EnemyHitTest::Finalize()
{
	image.Finalize();

	
}
void EnemyHitTest::UpDate()
{
	Move();
}
void EnemyHitTest::Render()
{
	Box2D draw((int)position.x, (int)position.y, IMAGE_SIZE, IMAGE_SIZE);
	Box2D src(0, 0, IMAGE_SIZE, IMAGE_SIZE);
	draw.OffsetSize();							//座標値の再設定を行う
	image.Draw(draw, src);

}
void EnemyHitTest::Move()
{
	if (Input::KeyInputOn(Input::LEFT))
	{
		position.x -= SPEED;
	}
	if (Input::KeyInputOn(Input::RIGHT))
	{
		position.x += SPEED;
	}
	if (Input::KeyInputOn(Input::UP))
	{
		position.y -= SPEED;
	}
	if (Input::KeyInputOn(Input::DOWN))
	{
		position.y += SPEED;
	}
	//座標の更新
	collisionCube.hitBase.x = position.x;
	collisionCube.hitBase.y = position.y;
	std::cout << "現在のEnemy座標" << "(" << position.x << "," << position.y << ")" << std::endl;
}
