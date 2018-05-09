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
	bool Initialize(Vec2&);
	void Update();
	void Render();
	void Finalize();

	bool cleared;
	std::vector<Water*> waters;
	void AddWater(Water*);
	bool DeleteWater(Water*);
	bool ClearCheck(Water&);
	Texture tex;
};

#endif