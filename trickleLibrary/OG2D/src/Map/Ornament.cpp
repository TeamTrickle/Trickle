#include "Ornament.h"



Ornament::Ornament()
{
	this->pipeTex.Create("pipe.png");
	this->gearTex.Create("gear.png");
	this->pipeBoxTex.Create("pipeornament.png");
	this->gearSrc = Box2D(0, 0, 195, 195);
	this->pipeBoxSrc = Box2D(0, 0, 1024, 768);
	__super::Init((std::string)"Ornament");
	__super::SetDrawOrder(0.5f);
}


Ornament::~Ornament()
{
	this->Finalize();
}

Ornament::SP Ornament::Create(bool flag_)
{
	auto to = Ornament::SP(new Ornament());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;

}

bool Ornament::Initialize() {
	float x = 0;
	switch (*MapNum) {
	case 1:
		//スタートの水が垂れるパイプ
		pipe.draw = Box2D(64 * 5, 64 * 13, 256, 170);
		this->pipeSrc = Box2D(0, 0, 768, 512);
		pipe.draw.OffsetSize();
		//回る歯車
		gear.push_back({ Box2D(64 * 4, 64 * 21, 128, 128), 0 });
		gear.push_back({ Box2D(64 * 3,64 * 21 + 16,170,170),0 });
		gear.push_back({ Box2D(-100, 64 * 5,390,390),0 });
		gear.push_back({ Box2D(64 * 21, 64 * 22 - 50,170,170),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 36,64 * 22,390,390),0 });
		gear_nomove.push_back({ Box2D(64 * 36,64 * 20,195,195),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		pipeBox.push_back({ Box2D(64 * 5 - 342,64 * 17,342,256),0 });
		pipeBox.push_back({ Box2D(64 * 33,64 * 9,512,384),180 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 2:
		pipe.draw = Box2D(64 * 6, 64 * 8, 256, 170);
		pipe.draw.OffsetSize();
		this->pipeSrc = Box2D(0, 0, 768, 512);
		//回る歯車
		gear.push_back({ Box2D(64 * 10 - 32,64 * 6,170,170),0 });
		gear.push_back({ Box2D(64 * 8,64 * 7,100,100),0 });
		gear.push_back({ Box2D(64 * 27,64 * 19,350,350),0 });
		gear.push_back({ Box2D(64 * 26,64,300,300),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 24,64 * 19,120,120),0 });
		gear_nomove.push_back({ Box2D(64 * 23,64 * 20,200,200),0 });
		gear_nomove.push_back({ Box2D(64 * 2,64 * 21,150,150),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		pipeBox.push_back({ Box2D(64 * 7,64 * 17,512,384),90 });
		pipeBox.push_back({ Box2D(-64 * 2,64 * 16,410,307),180 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 3:
		pipe.draw = Box2D(64 * 4, 64 * 10, 256, 170);
		pipe.draw.OffsetSize();
		this->pipeSrc = Box2D(0, 0, 768, 512);
		//回る歯車
		gear.push_back({ Box2D(64 * 6 - 32,64 * 4,170,170),0 });
		gear.push_back({ Box2D(64 * 2,0,300,300),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 23,64 * 18,200,200),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		pipeBox.push_back({ Box2D(-64 * 2 - 10,64 * 16,410,307),180 });
		pipeBox.push_back({ Box2D(64 * 27,0,410,307),0 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 4:
		pipe.draw = Box2D(64 * 3, 64 * 2, 256, 170);
		pipe.draw.OffsetSize();
		this->pipeSrc = Box2D(0, 0, 768, 512);
		//回る歯車
		gear.push_back({ Box2D(64 * 7,64 * 9,100,100),0 });
		gear.push_back({ Box2D(64 * 26 - 20,64 * 19,350,350),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 23,64 * 21 - 40,200,200),0 });
		gear_nomove.push_back({ Box2D(0,20,300,300),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		pipeBox.push_back({ Box2D(64 * 6,64 * 19,512,384),90 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 5:
		pipe.draw = Box2D(64 * 2, 64 * 1, 256, 170 - 64);
		pipe.draw.OffsetSize();
		pipeSrc = Box2D(0, 193, 768, 512 - 192);
		pipeSrc.OffsetSize();
		//回る歯車
		gear.push_back({ Box2D(-15,64*2,200,200),0 });
		gear.push_back({ Box2D(-30,64,150,150),0 });
		gear.push_back({ Box2D(64 * 31,64 * 14,380,380),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(-100,64*13,250,250),0 });
		gear_nomove.push_back({ Box2D(64*16,-64,180,180),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		x = pipeBoxSrc.x;
		pipeBoxSrc.x = pipeBoxSrc.w;
		pipeBoxSrc.w = x;
		pipeBox.push_back({ Box2D(64*21,64 * 10,256,192),0});
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 6:
		pipe.draw = Box2D(64 * 8, 64 * 2, 256, 170 - 64);
		pipe.draw.OffsetSize();
		pipeSrc = Box2D(20, 192, 768 - 20, 512 - 192);
		pipeSrc.OffsetSize();
		//回る歯車
		gear.push_back({ Box2D(64 * 10,64 * 31 + 32,180,180),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 38 + 32,64 * 6,200,200),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		pipeBox.push_back({ Box2D(-180,64*3,512,384),180 });
		pipeBox.push_back({ Box2D(64*18,64*14-32,256,192),-90 });
		pipeBox.push_back({ Box2D(64 * 40,64 * 30,512,384),90 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	default:
		break;
	}

	return true;
}
void Ornament::UpDate() {
	for (int i = 0; i < gear.size(); ++i) {
		++gear[i].angle;
		if (gear[i].angle >= 360) {
			gear[i].angle = 0;
		}
	}
}
void Ornament::Render2D() {
	//pipeTex.Draw(pipe.draw, pipeSrc);
	for (int i = 0; i < gear.size(); ++i) {
		gearTex.Rotate((float)gear[i].angle);
		//gearTex.Draw(gear[i].draw, gearSrc);
	}
	for (int i = 0; i < gear_nomove.size(); ++i) {
		gearTex.Rotate((float)gear_nomove[i].angle);
		//gearTex.Draw(gear_nomove[i].draw, gearSrc);
	}
	for (int i = 0; i < pipeBox.size(); ++i) {
		pipeBoxTex.Rotate((float)pipeBox[i].angle);
		//pipeBoxTex.Draw(pipeBox[i].draw, pipeBoxSrc);
	}
}
void Ornament::Finalize() {
	gear.clear();
	gear_nomove.clear();
	pipeBox.clear();
	pipeTex.Finalize();
	gearTex.Finalize();
	pipeBoxTex.Finalize();
}