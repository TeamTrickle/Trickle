#include "FrameTime.h"

#include "Task\Task_Result.h"
bool FrameTimeUI::Initialize(Vec2& pos,int digitselect,int& resulttime)
{
	//タスク関連
	this->taskName = "FrameTimeUI";
	this->Init(taskName);

	//数字の桁数を計算する
	this->getframetime = resulttime;			//リザルトから取得したタイムを代入する
	this->DigitNumberReset();					//桁数の初期化
	this->SetFrameTime();						//桁数の計算
	this->digitSelectnumber = digitselect;		//数字を割り当てるための変数
	this->SetVector();							//数字桁数を取得したものを1桁ずつVectorに格納する

	//基本の情報
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->active = false;
	
	//画像関連
	image.Create((std::string)"../font/math.png");
	this->SetDrawOrder(0.1f);

	//Easing関連
	easingX.ResetTime();
	easingX.Init();
	this->PrePos = position;
	this->easingEnd = false;

	std::cout << "フレームタイムUI　初期化" << std::endl;
	return true;
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
	this->digitnumberLength = SetDigitNumber();
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
void FrameTimeUI::TargetTime()
{
	int Count = 0;
	for (auto it = frametime.begin(); it != frametime.end(); ++it)
	{
		if (Count == digitSelectnumber)
		{
			this->digitSelectnumber =  *it;
			return;
		}
		++Count;
	}
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
	if (!active)
	{
		TargetTime();
		active = true;
	}
	if (easingX.isplay())
	{
		position.x = easingX.linear.In(10, 0, this->PrePos.x, easingX.Time(10));
	}
	else
	{
		this->easingEnd = true;
	}
}
bool FrameTimeUI::GetEasingEnd()
{
	return this->easingEnd;
}
void FrameTimeUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.x = src.w * digitSelectnumber;
	src.OffsetSize();
	image.Draw(draw, src);
}
FrameTimeUI::FrameTimeUI()
{
	std::cout << "フレームタイムUI　生成" << std::endl;
}
FrameTimeUI::~FrameTimeUI()
{
	this->Finalize();
	std::cout << "フレームタイムUI　解放" << std::endl;
}
FrameTimeUI::SP FrameTimeUI::Create(Vec2& pos,int digitselect,int& resulttime,bool flag)
{
	FrameTimeUI::SP to = FrameTimeUI::SP(new FrameTimeUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,digitselect,resulttime))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}