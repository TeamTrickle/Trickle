#include "FlagUI.h"

#include "Effect\SterEffect.h"
#include "GameProcessManagement.h"
bool FlagUI::Initialize(Vec2& pos,int& target)
{
	//タスク関連
	this->taskName = "Ster";
	this->Init(taskName);

	//基本の情報
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	//フラグ代入を格納する
	Resultflag = 0;
	//ターゲットフラグの設定
	targetflag = target;

	//Easing関連
	easingX.ResetTime();
	easingX.Init();
	this->PrePos = position;

	//画像関連
	flagactive = false;			//画像を変更する際に判定を比較する
	SetDrawOrder(0.1f);
	image[0].Create((std::string)"Ster.png");
	image[1].Create((std::string)"SterB.png");

	//エフェクト関連
	this->effectEnd = false;

	std::cout << "ミッション達成エフェクト　初期化" << std::endl;
	return true;
}
void FlagUI::UpDate()
{
	//フラグを代入する
	this->SetResultflag();
	this->FalgJudge(targetflag);
	this->EasingMove();
}
void FlagUI::EasingMove()
{
	position.x = this->easingX.back.Out(15, 0, this->PrePos.x, easingX.Time(15));
}
bool FlagUI::EasingEnd()
{
	return !easingX.isplay();
}
void FlagUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	
	if (flagactive && effectEnd)
	{
		image[0].Draw(draw, src);
	}
	else
	{
		image[1].Draw(draw, src);
	}
}
bool FlagUI::Finalize()
{
	for (int i = 0; i < 2; ++i)
	{
		image[i].Finalize();
	}
	return true;
}
void FlagUI::SetResultflag()
{
	if (auto gameProcess = OGge->GetTask<GameProcessManagement>("GameProcessManagement"))
	{
		this->Resultflag = gameProcess->GetFlag();
	}
}
void FlagUI::FalgJudge(int judge)
{
	int flag = 0;
	flag |= Resultflag;
	if ((flag & judge) == judge)
	{
		flagactive = true;
	}
}
bool FlagUI::GetFlag()
{
	return this->flagactive;
}
void FlagUI::SetEffectEnd()
{
	this->effectEnd = true;
}
bool FlagUI::GetEffectEnd()
{
	return this->effectEnd;
}
FlagUI::FlagUI()
{
	std::cout << "ミッション達成エフェクト　生成" << std::endl;
}
FlagUI::~FlagUI()
{
	this->Finalize();
	std::cout << "ミッション達成エフェクト　解放" << std::endl;
}
FlagUI::SP FlagUI::Create(Vec2& pos,int target,bool flag_)
{
	FlagUI::SP to = FlagUI::SP(new FlagUI());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
