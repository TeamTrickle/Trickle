#include "Ornament.h"



Ornament::Ornament()
{
	this->pipe.tex.Create("pipe.png");
	this->gear.tex.Create("gear.png");
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
		//歯車
		gear.angle = 0;
		gear.draw = Box2D(64 * 4, 64 * 22, 128, 128);
		gear.draw.OffsetSize();
		gear.src = Box2D(0, 0, 195, 195);
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
	gear.angle++;
	if (gear.angle >= 360) { gear.angle = 0; }
}
void Ornament::Render2D() {
	pipe.tex.Draw(pipe.draw, pipe.src);
	gear.tex.Rotate(this->gear.angle);
	gear.tex.Draw(gear.draw, gear.src);

}
void Ornament::Finalize() {
	pipe.tex.Finalize();
}