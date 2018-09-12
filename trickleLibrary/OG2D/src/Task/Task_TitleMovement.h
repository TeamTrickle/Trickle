#pragma once 
#include "OGSystem\OGsystem.h"
#include "CameraManager\CameraManager.h"

/**
 *	@brief	タイトルキャラの動き制作用
 *	@author	Heewon Kim (nabicore@icloud.com)
 */

class TitleMovement : public TaskObject {


public:
	explicit TitleMovement();
	virtual ~TitleMovement();

	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();

	typedef std::shared_ptr<TitleMovement> SP;
	static SP Create(bool = true);

private:
	Sound*				bgm;
	CameraManager		cm;
	Texture				*logo;
};