#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class ClearUI : public GameObject, public TaskObject
{
private:
	//タスク関連
	std::string taskName;

	//画像関連
	Texture image;
	const Box2D Src = {0,0,269,85};

	//拡大機能変数
	float Volume;

private:
	//タスク関連
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	ClearUI();

	//拡大機能
	void ResetVolume();
	void MoveVolume();
public:
	virtual ~ClearUI();
	typedef std::shared_ptr<ClearUI> SP;
	static ClearUI::SP Create(Vec2& pos, bool = true);

	//リザルトで使用する関数

};