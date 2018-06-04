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
	bool isCheck;
public:
	Objform objform;								//オブジェクトの状態
	Vec2 position;									//位置
	Vec2 Scale;										//サイズ
	Vec2 Radius;									//半径
	float angle;									//回転度
	CollisionBox collisionCube;						//矩形当たり判定
	CollisionCircle collisionBall;					//円当たり判定
	bool Gravity;									//重力の有無
	float mass;										//質量
	bool hit(GameObject& o);						//GameObject同士の当たり判定
	GameObject();									//コンストラクタ	
	GameObject(										//コンストラクタ
		const Objform& form, 
		const Vec2& _posi, 
		const Vec2& _Sca, 
		float _ang = 0.0f
	);
	~GameObject();									//デストラクタ
	void CreateObject(								//GameObjectの情報を登録
		const Objform& form,
		const Vec2& _posi,
		const Vec2& _Sca,
		const float _ang = 0.0f
	);
	std::string objectTag;							//タグ名
	void LineDraw();								//当たり判定をラインを引いて確認用
	void CheckON();									//当たり判定を起動する
	bool IsObjectDistanceCheck(const Vec2& pos, const Vec2& size);	//当たり判定を行う範囲内かどうかを返します。
	void LineDistanceDraw();
private:
};