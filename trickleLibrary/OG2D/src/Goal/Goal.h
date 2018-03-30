#ifndef __GOAL_H__
#define __GOAL_H__


//#include "Object\Object.h"
//#include "OGSystem\OGsystem.h"
#include "Water\water.h"

class Goal :public Object {
public:
	explicit Goal();
	virtual ~Goal();

	bool Initialize();
	void Update();
	void Render();
	void Finalize();

	bool cleared;

	Texture tex;
};

#endif