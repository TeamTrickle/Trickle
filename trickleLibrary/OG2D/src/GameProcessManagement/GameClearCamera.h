#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GameClearCamera : public GameObject , public TaskObject
{
private:
	std::string taskName;	//タスク名
	bool cameraMovefinish;	//カメラの移動が終了している？
	bool active;			//現在カメラが移動中か？
	bool Move;				//動く準備をする
	Vec2 cameraPos;			//カメラの座標値
	Vec2 cameraMove;		//カメラの移動量
	Vec2 cameraSize;		//カメラのサイズ
	int  moveCnt;
private:
	void CameraMove();
	void Flag_Reset();
	void Set_CameraSpeed(Vec2& moveVec);
	void NowCameraPos();
private:
	bool Finalize();
	void UpDate();
	void Render2D();
public:
	bool GetCameraMoveFinish();
	void SetCameraSize();	//カメラの座標値をOGから代入する
public:
	typedef std::shared_ptr<GameClearCamera> SP;
	GameClearCamera();
	virtual ~GameClearCamera();
	static GameClearCamera::SP Create(bool = true);
	bool Initialize();
};