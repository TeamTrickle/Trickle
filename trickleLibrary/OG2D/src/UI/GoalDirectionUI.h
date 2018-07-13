#pragma once
#include "OGSystem/OGsystem.h"
#include "Object/Object.h"

/*
*  ゴールの進行方向を示すUIクラスです
*/
class GoalDirection : public GameObject , public TaskObject
{
	enum DrawPattrn
	{
		ULeft,
		URight,
		UCenter,
		CLeft,
		CRight,
		CCenter,
		DLeft,
		DRight,
		DCenter,
	};
public:
	//メンバ変数

	typedef std::shared_ptr<GoalDirection> SP;
	DrawPattrn drawPattrn;

	//メンバ関数
	GoalDirection();
	virtual ~GoalDirection();
	static GoalDirection::SP Create(std::shared_ptr<GameObject>, bool = true);
	bool Initialize(std::shared_ptr<GameObject>);

	void SetTextrue(Texture*);
private:
	//メンバ変数
	std::string taskName;

	std::shared_ptr<GameObject> target;

	Texture* image;
	const Box2D srcbase = {0,0,256,256};

	//メンバ関数

	bool Finalize();
	void UpDate()override;
	void Render2D()override;

	void SetPos(Vec2&);
	
	bool WindowOuterCheck();
	void TargetDirecition();
	void CameraPosUpDate();
	float ToDeg(float radian);
};
