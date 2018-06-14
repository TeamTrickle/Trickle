//#include "ClearUI.h"
//bool ClearUI::Initialize(Vec2& pos)
//{
//	//タスク関連
//	this->taskName = "ClearUI";
//	this->Init(taskName);
//
//	//基本の情報
//	CreateObject(Cube, pos, Vec2(256, 96), 30.f);
//
//
//	//画像関連
//	this->SetDrawOrder(0.1f);
//	image.Create((std::string)"ClearUI.png");
//	//拡大機能関連
//	this->ResetVolume();
//
//	std::cout << "クリアUI　初期化" << std::endl;
//	return true;
//}
//void ClearUI::ResetVolume()
//{
//	this->Volumefinish = false;
//	this->PreSize = this->Scale;
//	this->ReSize = {};
//	this->ScaleVolume = {};
//}
//void ClearUI::SetVolumeFlag(bool flag)
//{
//	this->Volumefinish = flag;
//}
//bool ClearUI::GetVolumeFlag()
//{
//	return this->Volumefinish;
//}
//bool ClearUI::Finalize()
//{
//	image.Finalize();
//	return true;
//}
//void ClearUI::UpDate()
//{
//	this->MoveVolume();
//}
//void ClearUI::ResetCenter() 
//{
//	//倍率を加算する 元のサイズ　×　倍率
//	this->ReSize.x = this->Scale.x *  this->ScaleVolume.x;
//	this->ReSize.y = this->Scale.y *  this->ScaleVolume.y;
//
//	//座標値に影響をさせる　(リサイズ　－　前回行ったリサイズ) * 2
//	this->position.x -= (this->ReSize.x - this->PreSize.x) * 2;
//	this->position.y -= (this->ReSize.y - this->PreSize.y) * 2;
//
//	//全体を求める	座標　－　リサイズ
//	this->Center = this->position + this->ReSize;
//
//	//座標の中央値を求める
//	this->Center.x = this->Center.x / 2.f;
//	this->Center.y = this->Center.y / 2.f;
//
//	//リサイズデータを保存しておく
//	this->PreSize = this->ReSize;
//}
//void ClearUI::MoveVolume()
//{
//	this->ScaleVolume.x += 0.033f;
//	this->ScaleVolume.y += 0.033f;
//	if (this->ScaleVolume.x >= 1.0f)
//	{
//		this->ScaleVolume.x = 1.0f;
//	}
//	if (this->ScaleVolume.y >= 1.0f)
//	{
//		this->ScaleVolume.y = 1.0f;
//	}
//	if (this->ScaleVolume.x >= 1.0f && this->ScaleVolume.y >= 1.0f)
//	{
//		this->SetVolumeFlag(true);
//	}
//	//再計算をする
//	this->ResetCenter();
//}
//void ClearUI::Render2D()
//{
//	//少し調整
//	Box2D draw(this->Center.x + this->Scale.x - 20, this->Center.y + this->Scale.y , this->Scale.x * this->ScaleVolume.x, this->Scale.y * this->ScaleVolume.y);
//	draw.OffsetSize();
//
//	//拡大機能
//	Box2D src = this->Src;
//	src.OffsetSize();
//
//	image.Draw(draw, src);
//}
//ClearUI::ClearUI()
//{
//	std::cout << "クリアUI　生成" << std::endl;
//}
//ClearUI::~ClearUI()
//{
//	this->Finalize();
//	std::cout << "クリアUI　解放" << std::endl;
//}
//ClearUI::SP ClearUI::Create(Vec2& pos, bool flag)
//{
//	ClearUI::SP to = ClearUI::SP(new ClearUI());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}