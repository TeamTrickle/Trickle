#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"

class Goal : public GameObject, public TaskObject
{
	bool isClear;
	unsigned int animCnt;
	Texture* image;
	GameObject foot;
	Box2D draw;
	Box2D src;
	Paint::PaintColor color;
public:
	explicit Goal(const Vec2& pos);
	virtual ~Goal();
	void UpDate() override;
	void Render2D() override;
	bool GetClear() const;
	void SetTexture(Texture*);
	bool WaterHit();
	typedef std::shared_ptr<Goal> SP;
	static SP Create(const Vec2& pos, bool = true);
};