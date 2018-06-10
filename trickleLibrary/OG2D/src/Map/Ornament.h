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
		Texture tex;
		Box2D draw;
		Box2D src;
	};
	Info pipe;
	////スタートの水が垂れるパイプ
	//Texture pipeTex;

	bool Initialize();
	void Render2D();
	void Finalize();
};

