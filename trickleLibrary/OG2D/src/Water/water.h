#ifndef __WATER_H__
#define __WATER_H__


/**
 * @brief	…ŠÖ˜Aˆ—‚Å‚·
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include <map>
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Water : public Object {

public:
	enum class State : int {
		LIQUID = 0,
		SOLID,
		GAS
	};
	 
public:
	explicit Water();
	virtual ~Water();

	bool Initialize();
	void Update();
	void Render();
	void Finalize();

	void SetState(const State&);
	State GetState() const;
	
private:
	Texture tex;
	std::map<State, Box2D> draw;
	std::map<State, Box2D> src;
	State currentState;

};



#endif