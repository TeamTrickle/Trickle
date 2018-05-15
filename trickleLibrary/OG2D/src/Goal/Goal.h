#ifndef __GOAL_H__
#define __GOAL_H__

//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Goal : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	bool Initialize(Vec2&);
	bool cleared;
	
	//void AddWater();
	//bool DeleteWater();
	bool ClearCheck();
private:
	Texture tex;

	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Goal();
	typedef std::shared_ptr<Goal> SP;
	static Goal::SP Create(bool);
	static Goal::SP Create(bool,Vec2&);
	Goal();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理
};

#endif