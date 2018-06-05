#pragma once
#include "Object\Object.h"
#include "OGSystem\OGsystem.h"
class Paint final: public GameObject, public TaskObject
{
	Color color;
	Texture image;
public:
	explicit Paint();
	virtual ~Paint();
};