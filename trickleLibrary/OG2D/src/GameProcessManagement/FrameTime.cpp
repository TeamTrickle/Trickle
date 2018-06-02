#include "FrameTime.h"

#include "Task\Task_Result.h"
bool FrameTimeUI::Initialize(Vec2& pos,int digitselect,int& resulttime)
{
	//タスク関連
	this->taskName = "FrameTimeUI";
	this->Init(taskName);

	//数字の桁数を計算する
	this->goaltime.Inputtime = resulttime;		//リザルトから取得したタイムを代入する
	this->digitSelectnumber = digitselect;		//数字を割り当てるための変数
	this->goaltime.InitTime();
	//基本の情報
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	
	//画像関連
	image.Create((std::string)"../font/math.png");
	this->SetDrawOrder(0.1f);
	//大きさ変更モーション
	this->ResetMoveCnt(this->ScaleanimetionCnt);
	//大きさを変更させるモーション
	if (this->goaltime.CoronnumberJudge(this->digitSelectnumber))
	{
		this->Scaleanimeflag = true;
	}
	else
	{
		this->Scaleanimeflag = false;
	}
	

	//Easing関連
	easingX.ResetTime();
	easingX.Init();
	this->PrePos = position;
	this->easingEnd = false;

	//ドラムロール関連
	this->ResetMoveCnt();
	this->ResetDramRollisPlay();
	this->randomSelectnumber = 0;
	this->dramrollisPlay = false;

	std::cout << "フレームタイムUI　初期化" << std::endl;
	return true;
}
bool FrameTimeUI::Finalize()
{
	image.Finalize();
	return true;
}
void FrameTimeUI::UpDate()
{
	if (easingX.isplay())
	{
		position.x = easingX.linear.In(10, 0, this->PrePos.x, easingX.Time(10));
	}
	else
	{
		this->easingEnd = true;
	}
	//コロン描画番号以外はドラムロールを行う
	if (!this->goaltime.CoronnumberJudge(this->digitSelectnumber))
	{
		this->DramRoll(300);
	}
	else
	{
		//データ代入のみ行う
		this->goaltime.SetCoron();
	}
}
bool FrameTimeUI::GetEasingEnd()
{
	return this->easingEnd;
}
void FrameTimeUI::Render2D()
{
	Box2D draw(position, Scale);
	if (this->GetDramRollIsPlay())
	{
		if (!this->Scaleanimeflag)
		{
			if (!this->MoveCntJudge(this->ScaleanimetionCnt, 6))
			{
				draw.w *= 1.5f;
				draw.h *= 1.5f;
			}
			else
			{
				this->Scaleanimeflag = true;
			}
		}
		else
		{
			draw.w = Scale.x;
			draw.h = Scale.y;
		}
	}
	draw.OffsetSize();
	Box2D src = this->Src;
	if (this->GetDramRollIsPlay())
	{
		src.x = src.w * this->goaltime.outputtime[this->digitSelectnumber];
	}
	else
	{
		src.x = src.w * this->randomSelectnumber;
	}
	if (this->goaltime.CoronnumberJudge(this->digitSelectnumber))
	{
		src.x = src.w * this->goaltime.outputtime[this->digitSelectnumber];
	}
	src.OffsetSize();
	image.Draw(draw, src);
}
std::string FrameTimeUI::Time::Set_toString(int& targettime)
{
	std::string value;
	std::ostringstream ss;
	ss << targettime;
	value += ss.str();
	return value;
}
void FrameTimeUI::Time::SetDigitLength(std::string& target)
{
	digit = target.size();
}
int FrameTimeUI::Time::toSecond()
{
	int value = 0;
	value = this->Inputtime;
	if (value / 60 >= 60 && this->GetMinutes() == 59)
	{
		value = 59;
	}
	else
	{
		value %= 60;
	}
	return value;
}
int FrameTimeUI::Time::toMinutes()
{
	int value = 0;
	value = this->Inputtime;
	if (value / 60 >= 60)
	{
		value = 59;
	}
	else
	{
		value /= 60;
	}
	return value;
}
void FrameTimeUI::Time::InitTime()
{
	this->minutes = this->toMinutes();
	this->second = this->toSecond();
}
int FrameTimeUI::Time::toInt(std::string& to_int, int loop)
{
	int value;
	value = std::stoi(to_int.substr(0 + loop, 1 + loop));
	return value;
}
void FrameTimeUI::Time::SetCoron()
{
	this->outputtime[this->CoronData] = this->Coronnumber;
}
int FrameTimeUI::Time::GetMinutes()
{
	return this->minutes;
}
int FrameTimeUI::Time::GetSecond()
{
	return this->second;
}
bool FrameTimeUI::Time::CoronnumberJudge(int& number)
{
	return number == this->CoronData ? true : false;
}
void FrameTimeUI::ResetMoveCnt()
{
	this->moveCnt = 0;
}
void FrameTimeUI::ResetMoveCnt(int& moveCnt)
{
	moveCnt = 0;
}
void FrameTimeUI::ResetDramRollisPlay()
{
	this->dramrollisPlay = false;
}
void FrameTimeUI::Time::SetTime()
{
	std::string min;

	//分を文字列にする
	min = this->Set_toString(this->minutes);
	//数字の桁数を数える
	this->SetDigitLength(min);


	//判定文 1桁だった場合・・・
	if (this->digit == 1)
	{
		//確定で０が入る
		this->outputtime[0] = 0;
		this->outputtime[1] = this->GetMinutes();
	}
	else
	{
		for (int i = 0; i < (int)this->digit; ++i)
		{
			outputtime[i] = this->toInt(min, i);
		}
	}

	//コロンをここで代入する
	this->outputtime[this->CoronData] = this->Coronnumber;

	min = this->Set_toString(this->second);
	this->SetDigitLength(min);

	if (this->digit == 1)
	{
		this->outputtime[3] = 0;
		this->outputtime[4] = this->GetSecond();
	}
	else
	{
		for (int i = 0; i < (int)this->digit; ++i)
		{
			this->outputtime[i + 3] = this->toInt(min, i);
		}
	}
}
int FrameTimeUI::Random()
{
	return random::GetRand(0, 9);
}
bool FrameTimeUI::MoveCntJudge(int& moveCnt ,int time)
{
	//アニメーションカウントを増加させる
	++moveCnt;
	if (moveCnt >= time)
	{
		this->ResetMoveCnt(moveCnt);
		return true;
	}
	return false;
}
void FrameTimeUI::DramRoll(int time)
{
	//ドラムロールをまだ行っていないか？
	if (!this->GetDramRollIsPlay())
	{
		//引数の時間を超えたらtrue
		if (MoveCntJudge(this->moveCnt, time))
		{
			this->goaltime.SetTime();
			this->dramrollisPlay = true;
		}
		else
		{
			this->randomSelectnumber = this->Random();
			this->dramrollisPlay = false;
		}
	}
}
bool FrameTimeUI::GetDramRollIsPlay()
{
	return this->dramrollisPlay;
}
bool FrameTimeUI::GetIsPlay()
{
	auto frametimeUI = OGge->GetTasks<FrameTimeUI>(this->taskName);
	int count = 0;
	for (auto id = (*frametimeUI).begin(); id != (*frametimeUI).end(); ++id)
	{
		//演出が最後まで終了したフラグがtrueになっているか？
		if ((*id)->Scaleanimeflag)
		{
			//カウントする
			++count;
		}
	}
	return count == 5 ? true : false;
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
