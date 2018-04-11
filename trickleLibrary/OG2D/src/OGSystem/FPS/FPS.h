#pragma once
#include "OGSystem\_OGsystem.h"
class FPS {
public:
	void Initialize();
	void Update();
private:
	float lastTime;
	int count;
	GLfloat fps;
};
