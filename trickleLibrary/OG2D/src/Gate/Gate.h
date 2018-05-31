#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class Gate : public GameObject, public TaskObject
{
	Texture* image;
	Box2D draw;
	Box2D src;
	unsigned __int8 ID;
	bool isOpen;
	bool preIsOpen;
	int AnimCnt;
	int Sense;
public:
	Gate(const Vec2&);
	virtual ~Gate();
	void UpDate();
	void Render2D();
	typedef std::shared_ptr<Gate> SP;
	static SP Create(const Vec2&, bool = true);
	static SP Create(const float, const float, bool = true);
	void SetTexture(Texture*);
	unsigned __int8 GetID() const;
	bool ToOpen();
	bool ToClose();
};