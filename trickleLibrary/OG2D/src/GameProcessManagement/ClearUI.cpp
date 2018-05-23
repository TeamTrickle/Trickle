#include "ClearUI.h"
bool ClearUI::Initialize(Vec2& pos)
{
	this->taskName = "ClearUI";
	this->Init(taskName);
	std::cout << "クリアUI　初期化" << std::endl;

	CreateObject(Cube, pos, Vec2(512, 96), 0);
	this->SetDrawOrder(0.1f);
	image.Create((std::string)"ClearUI.png");
	return true;
}
bool ClearUI::Finalize()
{
	image.Finalize();
	return true;
}
void ClearUI::UpDate()
{

}
void ClearUI::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src.OffsetSize();
	image.Draw(draw, src);
}
ClearUI::ClearUI()
{
	std::cout << "クリアUI　生成" << std::endl;
}
ClearUI::~ClearUI()
{
	this->Finalize();
	std::cout << "クリアUI　解放" << std::endl;
}
ClearUI::SP ClearUI::Create(Vec2& pos, bool flag)
{
	ClearUI::SP to = ClearUI::SP(new ClearUI());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}