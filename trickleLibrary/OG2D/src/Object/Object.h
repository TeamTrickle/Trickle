#pragma once
//_____________________________
//|ゲームオブジェクト            
//|履歴：2018/03/20   
//|____________________________
#include "OGSystem\OGlib.h"
#include "OGSystem\Collision\Collision.h"
enum Objform
{
	Non,											//無
	Ball,											//円
	Cube,											//矩形
};
class GameObject
{
public:
	Objform objform;								//オブジェクトの状態
	Vec2 position;									//位置
	Vec2 Scale;										//サイズ
	float angle;									//回転度
	CollisionBox collisionCube;						//矩形当たり判定
	CollisionCircle collisionBall;					//円当たり判定
	bool Gravity;									//重力の有無
	float mass;										//質量
	bool hit(GameObject& o);						//GameObject同士の当たり判定
	GameObject();									//コンストラクタ	
	GameObject(										//コンストラクタ
		Objform form, 
		Vec2 _posi, 
		Vec2 _Sca, 
		float _ang
	);
	~GameObject();									//デストラクタ
	void CreateObject(								//GameObjectの情報を登録
		Objform form,
		Vec2 _posi,
		Vec2 _Sca,
		float _ang
	);
	std::string objectTag;							//タグ名
	void LineDraw();								//当たり判定をラインを引いて確認用
private:
};