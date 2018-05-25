#include "FrameTime.h"

#include "Task\Task_Result.h"
bool FrameTimeUI::Initialize(Vec2& pos,int digitselect)
{
	std::cout << "フレームタイムUI　初期化" << std::endl;
	this->taskName = "FrameTimeUI";
	this->getframetime = this->GetResultFrameTime();

	this->DigitNumberReset();
	this->SetFrameTime();
	this->SetVector();
	image.Create((std::string)"../font/math.png");
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->SetDrawOrder(0.1f);
	this->digitSelectnumber = digitselect;
	return true;
}
int FrameTimeUI::GetResultFrameTime()
{
	auto result = OGge->GetTask<Result>("Result");
	if (result)
	{
		return result->GetFrameTime();
	}
	return 0;
}
void FrameTimeUI::SetVector()
{
	int value = this->getframetime;
	for (int i = digitnumberLength; i > 0; --i)
	{
		value = this->getframetime % (int)pow(N, i);
		if (i != 1)
		{
			value = value / (int)pow(N, i - 1);
		}
		frametime.push_back(value);
	}
}
void FrameTimeUI::SetFrameTime()
{
	auto result = OGge->GetTask<Result>("Result");
	if (result)
	{
		this->digitnumberLength = SetDigitNumber();
	}
}
int FrameTimeUI::SetDigitNumber()
{
	int value = this->getframetime;
	int Count = 0;
	while (value != 0)
	{
		value /= N;
		++Count;
	}
	return Count;
}
void FrameTimeUI::DigitNumberReset()
{
	this->digitnumberLength = 0;
}
int FrameTimeUI::TargetTime()
{
	int Count = 0;
	for (auto it = frametime.begin(); it != frametime.end(); ++it)
	{
		if (Count == digitSelectnumber)
		{
			return *it;
		}
		++Count;
	}
	return 0;
}
int FrameTimeUI::GetDigitNumber()
{
	return this->digitnumberLength;
}
bool FrameTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void FrameTimeUI::UpDate()
{
	digitSelectnumber = TargetTime();
}
void FrameTimeUI::Render2D()
{
	{
		Box2D draw(position, Scale);
		draw.OffsetSize();
		Box2D src = this->Src;
		src.x = src.w * digitSelectnumber;
		src.OffsetSize();
		image.Draw(draw, src);
	}
}
FrameTimeUI::FrameTimeUI()
{
	std::cout << "フレームタイムUI　生成" << std::endl;
}
FrameTimeUI::~FrameTimeUI()
{
	std::cout << "フレームタイムUI　解放" << std::endl;
}
FrameTimeUI::SP FrameTimeUI::Create(Vec2& pos,int digitselect,bool flag)
{
	FrameTimeUI::SP to = FrameTimeUI::SP(new FrameTimeUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,digitselect))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}