#include "Ornament.h"



Ornament::Ornament()
{
	this->pipeTex.Create("pipe.png");
	this->gearTex.Create("gear.png");
	this->pipeBoxTex.Create("pipeornament.png");
	__super::Init((std::string)"Ornament");
	__super::SetDrawOrder(0.3f);
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
	switch (*MapNum) {
	case 1:
		//スタートの水が垂れるパイプ
		pipe.draw = Box2D(64 * 5, 64 * 13, 256, 170);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(0, 0, 768, 512);
		//回る歯車
		gear.push_back({ Box2D(64 * 4, 64 * 21, 128, 128),Box2D(0, 0, 195, 195), 0 });
		gear.push_back({ Box2D(64 * 3,64 * 21 + 16,170,170),Box2D(0,0,195,195),0 });
		gear.push_back({ Box2D(-100, 64 * 5,390,390),Box2D(0,0,195,195),0 });
		gear.push_back({ Box2D(64 * 21, 64 * 22 - 50,170,170),Box2D(0,0,195,195),0 });
		for (int i = 0; i < gear.size(); ++i) {
			gear[i].draw.OffsetSize();
		}
		//回らない歯車
		gear_nomove.push_back({ Box2D(64 * 36,64 * 22,390,390),Box2D(0,0,195,195),0 });
		gear_nomove.push_back({ Box2D(64 * 36,64 * 20,195,195),Box2D(0,0,195,195),0 });
		for (int i = 0; i < gear_nomove.size(); ++i) {
			gear_nomove[i].draw.OffsetSize();
		}
		//箱付きパイプ
		pipeBox.push_back({ Box2D(64 * 5 - 342,64 * 17,342,256),Box2D(0,0,1024,768),0 });
		pipeBox.push_back({ Box2D(64 * 33,64 * 9,512,384),Box2D(0,0,1024,768),180 });
		for (int i = 0; i < pipeBox.size(); ++i) {
			pipeBox[i].draw.OffsetSize();
		}
		break;
	case 2:
		pipe.draw = Box2D(64 * 6, 64 * 8, 256, 170);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(0, 0, 768, 512);
		break;
	case 3:
		pipe.draw = Box2D(64 * 4, 64 * 10, 256, 170);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(0, 0, 768, 512);
		break;
	case 4:
		pipe.draw = Box2D(64 * 3, 64 * 2, 256, 170);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(0, 0, 768, 512);

		break;
	case 5:
		pipe.draw = Box2D(64 * 2, 64 * 1, 256, 170 - 64);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(0, 193, 768, 512 - 192);
		pipe.src.OffsetSize();
		break;
	case 6:
		pipe.draw = Box2D(64 * 8, 64 * 2, 256, 170 - 64);
		pipe.draw.OffsetSize();
		pipe.src = Box2D(20, 192, 768 - 20, 512 - 192);
		pipe.src.OffsetSize();
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
	pipeTex.Draw(pipe.draw, pipe.src);
	for (int i = 0; i < gear.size(); ++i) {
		gearTex.Rotate(gear[i].angle);
		gearTex.Draw(gear[i].draw, gear[i].src);
	}
	for (int i = 0; i < gear_nomove.size(); ++i) {
		gearTex.Rotate(gear_nomove[i].angle);
		gearTex.Draw(gear_nomove[i].draw, gear_nomove[i].src);
	}
	for (int i = 0; i < pipeBox.size(); ++i) {
		pipeBoxTex.Rotate(pipeBox[i].angle);
		pipeBoxTex.Draw(pipeBox[i].draw, pipeBox[i].src);
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