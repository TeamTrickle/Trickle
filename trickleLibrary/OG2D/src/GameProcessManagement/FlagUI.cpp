#include "FlagUI.h"


bool FlagUI::Initialize(Vec2& pos,int& target)
{
	std::cout << "ミッション達成エフェクト　初期化" << std::endl;
	this->taskName = "Ster";
	this->Init(taskName);
	CreateObject(Cube, pos, Vec2(64, 64), 0);
	//フラグ代入を格納する
	Resultflag = 0;
	//ターゲットフラグの設定
	targetflag = target;
	//画像判定に必要なフラグ
	flagactive = false;
	SetDrawOrder(0.1f);
	image[0].Create((std::string)"Ster.png");
	image[1].Create((std::string)"SterB.png");
	return true;
}
void FlagUI::UpDate()
{
	//フラグを代入する
	this->SetResultflag();
	this->FalgJudge(targetflag);
}
void FlagUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	if (flagactive)
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
	auto result = OGge->GetTask<Result>("Result");
	Resultflag = result->Get_Flag();
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
