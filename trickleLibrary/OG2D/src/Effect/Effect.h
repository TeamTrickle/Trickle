#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Effect : public TaskObject , public GameObject
{
	Texture image;
	Box2D draw;
	Box2D src;
public:
	explicit Effect();
	virtual ~Effect();
	void UpDate();
	void Render2D();
	typedef std::shared_ptr<Effect> SP;
	//static SP Create()
};