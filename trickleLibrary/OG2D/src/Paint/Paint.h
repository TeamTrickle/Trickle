#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Paint final: public GameObject, public TaskObject
{
public:
	enum PaintColor
	{
		Red,
		Blue,
		Purple,
		Normal,
	};
private:
	PaintColor* color;
	Texture* image;
	Box2D draw;
	Box2D src;
	void Setsrc();
	bool WaterHit();
public:
	explicit Paint(const Vec2 & pos, const Vec2 & size, const PaintColor & color_);
	virtual ~Paint();
	typedef std::shared_ptr<Paint> SP;
	static SP Create(const Vec2& pos, const Vec2& size, const PaintColor& color_, bool = true);
	void SetTexture(Texture* tex);
	void UpDate();
	void Render2D();
};