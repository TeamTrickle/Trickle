#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GameClearCamera : public GameObject , public TaskObject
{
private:
	std::string taskName;
	bool cameraMovefinish;
	bool active;			//Œ»İƒJƒƒ‰‚ªˆÚ“®’†‚©H
	Vec2 cameraPos;
private:
	void CameraMove();
	void Flag_Reset();
private:
	bool Finalize();
	void UpDate();
	void Render2D();
public:
	bool GetCameraMoveFinish();
public:
	typedef std::shared_ptr<GameClearCamera> SP;
	GameClearCamera();
	virtual ~GameClearCamera();
	static GameClearCamera::SP Create(bool = true);
	bool Initialize();
};