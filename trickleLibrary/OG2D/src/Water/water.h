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
	};

public:
	explicit Water(Vec2 pos);
	virtual ~Water();

	bool Initialize();
	void Update();
	void Render();
	void Finalize();

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

	bool active;
	//水量
	float volume;
	//無敵時間
	int invi;
private:
	Texture tex;
	std::map<State, Box2D> drawRange;
	State currentState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	int setTime;
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
};
#endif