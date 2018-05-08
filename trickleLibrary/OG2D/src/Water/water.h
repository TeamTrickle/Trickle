#ifndef __WATER_H__
#define __WATER_H__


/**
 * @brief	水関連処理です
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include <map>
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <algorithm>

class Water : public Object {

public:
	enum class State : int {
		LIQUID = 0,			//　液体
		SOLID,				//　個体
		GAS					//　気体
	};
	
	enum class Situation : int
	{
		Newfrom,			//出現中
		Normal,				//通常
		Deleteform,			//削除中
		CreaDelete,			//削除
		Rainfrom			//雨状態
	};

public:
	explicit Water(Vec2 pos);
	virtual ~Water();

	bool Initialize();
	void Update();
	void Render();
	void Finalize();

	void SetTexture(Texture* texture);

	/**
	 * @brief	状態転移します。
	 * @see	外で使うとこにはWater::State::Liquid こんな形に
	 */
	void SetState(const State&);
	State GetState() const;

	void SetSituation(const Situation&);
	Situation GetSituation() const;

	//水量の移動
	float waterMove();
	//水量のチェック
	float GetWaterVolume() const;
	void AddObject(Object* obj_);								//オブジェクトを登録する
	bool DeleteObject(Object* obj_);							//指定オブジェクトを登録から削除する
	void AllDelete();											//全登録オブジェクトの削除
	//色関連
	bool SetColor(Color&);
	Color GetColor() const;
	bool active;
	//水量
	float volume;
	//無敵時間
	int invi;
	//カウント時間
	int nowTime;
private:
	const float MOVE_SPEED = 15.f;								//移動スピード
	const float JUMP_POWER = -20.f;								//ジャンプパワー
	const float MAX_FALL = 30.f;								//落下最大速度
	const float GRAVITY = (9.8f / 60.f / 60.f * 32) * 50;		//重力加速度
	const float FIN_SPEED = 0.5f;								//摩擦
	const int RAIN_TIME = 180;
	Texture* tex;
	std::vector<Object*> mapObj;
	std::map<State, Box2D> drawRange;
	State currentState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	Vec2 move;
	Color color;
	int setTime;
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
	void SetMapObject(Object* mapobj);
	std::vector<Object*> objects;
	void Friction();
	bool FootCheck(std::string&,int = 0);
	void MoveWATERCheck(Vec2&);
	void MoveGASCheck(Vec2&);
	void MoveSOILDCheck(Vec2&);
	bool HeadCheck(std::string&,int = 0);
};
#endif