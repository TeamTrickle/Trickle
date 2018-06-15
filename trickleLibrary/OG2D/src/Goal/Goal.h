#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"

class Goal : public GameObject, public TaskObject
{
	class CameraAnim
	{
		Vec2 startPos;
		Vec2 endPos;
		unsigned int time;
		Easing easing_x;
		Easing easing_y;
	public:
		void Set(const Vec2& start, const Vec2& end, const unsigned int time);
		Vec2 Move();
		bool isPlay();
	};
	enum Mode
	{
		Non,	//‰Šú
		Form1,	//ƒJƒƒ‰ˆÚ“®
		Form2,	//‰Ôç‚«
		Form3,	//ƒJƒƒ‰–ß‚è
		End,	//I—¹
	};
	bool isClear;
	bool isCheck;
	bool cameraLock;
	unsigned int animCnt;
	unsigned int ID;
	Texture* image;
	GameObject foot;
	Box2D draw;
	Box2D src;
	Paint::PaintColor color;
	Paint::PaintColor termsColor;
	Mode mode;
	CameraAnim cm_Pos;
	CameraAnim cm_Size;
	Vec2* precmPos;
	Vec2* precmSize;
	bool isGoalCheck();
public:
	explicit Goal(const Vec2& pos);
	virtual ~Goal();
	void SetColor(Paint::PaintColor&);
	bool ColorCheck() const;
	void UpDate() override;
	void Render2D() override;
	bool GetClear() const;
	void SetTexture(Texture*);
	bool WaterHit();
	bool GetLock() const;
	unsigned int GetID() const;
	typedef std::shared_ptr<Goal> SP;
	static SP Create(const Vec2& pos, bool = true);
};