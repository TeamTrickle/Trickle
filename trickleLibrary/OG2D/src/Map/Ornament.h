#pragma once
#include "Object\Object.h"
#include "OGSystem\Texture\Texture.h"
#include "OGSystem\OGsystem.h"

class Ornament : public TaskObject{
public:
	Ornament();
	~Ornament();
	typedef std::shared_ptr<Ornament> SP;
	static SP Create(bool flag_ = true);


private:
	struct Info {
		Box2D draw;
		int angle;
	};
	Info pipe;
	//Info gear;
	Texture pipeTex;
	Texture gearTex;
	Texture pipeBoxTex;
	std::vector<Info> gear;
	std::vector<Info> gear_nomove;
	std::vector<Info> pipeBox;
	Box2D pipeSrc;
	Box2D gearSrc;
	Box2D pipeBoxSrc;

	bool Initialize();
	void UpDate();
	void Render2D();
	void Finalize();
};

