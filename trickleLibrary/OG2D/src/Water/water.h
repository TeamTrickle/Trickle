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
	 
public:
	explicit Water();
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

	bool active;

private:
	Texture tex;
	std::map<State, Box2D> drawRange;
	State currentState;
};
#endif