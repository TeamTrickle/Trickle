#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Win\WinMain.h"

class GimmickC :public Object
{
public:
	Texture ContainerImg;
	std::string fileName = "Collision.png";
	float water;        //“ü‚Á‚Ä‚é…‚Ì—Ê
	float speed;        //ˆÚ“®‘¬“x
	bool hold;          //player‚ª—eŠí‚ğ‚Á‚Ä‚¢‚é‚©
	bool hitRight;
	bool hitLeft;
	bool hitBottom;

	void Initialize();
	TaskFlag UpDate();
	void Render();
	void Finalize();
};

