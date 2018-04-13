#pragma once
#include "OGSystem\_OGsystem.h"
#include <functional>
class FPS {
public:
	FPS();
	~FPS();
	void Initialize();
	void Update();
	void SetData(void data_());
	void DeleteData();
	typedef std::shared_ptr<FPS> SP;
	static SP Create();
private:
	float lastTime;
	int count;
	GLfloat fps;
	std::vector<std::function<void()>> data;
	float Setfps;
	float setlast;
};
