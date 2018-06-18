//<<<<<<< HEAD
////#include "GoalTimeUI.h"
////bool GoalTimeUI::Initialize(Vec2& pos)
//=======
//#include "GoalTimeUI.h"
//bool GoalTimeUI::Initialize(Vec2& pos)
//{
//	//タスク関連
//	this->taskName = "GoalTimeUI";
//	this->Init(taskName);
//
//	//基本の情報
//	CreateObject(Cube, pos, Vec2(450, 64), 0);
//
//
//	//画像関連
//	image.Create((std::string)"fontui.png");
//	this->SetDrawOrder(0.1f);
//
//
//	//拡大機能
//	this->ResetVolume();
//
//	std::cout << "ゴールタイムUI　初期化" << std::endl;
//	return true;
//}
//void GoalTimeUI::ResetVolume()
//{
//	this->ScaleVolume = {};
//	this->PreSize = this->Scale;
//	this->ReSize = {};
//}
//void GoalTimeUI::ResetCenter()
//{
//	//倍率を加算する 元のサイズ　×　倍率
//	this->ReSize.x = this->Scale.x *  this->ScaleVolume.x;
//	this->ReSize.y = this->Scale.y *  this->ScaleVolume.y;
//
//	//座標値に影響をさせる　(リサイズ　－　前回行ったリサイズ) * 2
//	this->position.x -= (this->ReSize.x - this->PreSize.x) * 1.5f;
//	this->position.y -= (this->ReSize.y - this->PreSize.y) * 1.5f;
//
//	//全体を求める	座標　－　リサイズ
//	this->Center = this->position + this->ReSize;
//	//座標の中央値を求める
//	this->Center.x = this->Center.x / 2.f;
//	this->Center.y = this->Center.y / 2.f;
//
//	//リサイズデータを保存しておく
//	this->PreSize = this->ReSize;
//}
//bool GoalTimeUI::Finalize()
//{
//	image.Finalize();
//	return true;
//}
//void GoalTimeUI::UpDate()
//{
//	this->MoveVolume();
//}
//void GoalTimeUI::MoveVolume()
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
//	//再計算をする
//	this->ResetCenter();
//}
////GoalTimeUI::Mat3x3 GoalTimeUI::Mat3x3::Create(float target[], MatFormat format)
//>>>>>>> develop
////{
////	//タスク関連
////	this->taskName = "GoalTimeUI";
////	this->Init(taskName);
////
////	//基本の情報
////	CreateObject(Cube, pos, Vec2(448, 90), 0);
////
////
////	//画像関連
////	image.Create((std::string)"TimeUI.png");
////	this->SetDrawOrder(0.1f);
////
////
////	//拡大機能
////	this->ResetVolume();
////
////	std::cout << "ゴールタイムUI　初期化" << std::endl;
////	return true;
////}
////void GoalTimeUI::ResetVolume()
////{
////	this->ScaleVolume = {};
////	this->PreSize = this->Scale;
////	this->ReSize = {};
////}
////void GoalTimeUI::ResetCenter()
////{
////	//倍率を加算する 元のサイズ　×　倍率
////	this->ReSize.x = this->Scale.x *  this->ScaleVolume.x;
////	this->ReSize.y = this->Scale.y *  this->ScaleVolume.y;
////
////	//座標値に影響をさせる　(リサイズ　－　前回行ったリサイズ) * 2
////	this->position.x -= (this->ReSize.x - this->PreSize.x) * 2;
////	this->position.y -= (this->ReSize.y - this->PreSize.y) * 2;
////
////	//全体を求める	座標　－　リサイズ
////	this->Center = this->position + this->ReSize;
////
////	//座標の中央値を求める
////	this->Center.x = this->Center.x / 2.f;
////	this->Center.y = this->Center.y / 2.f;
////
////	//リサイズデータを保存しておく
////	this->PreSize = this->ReSize;
////}
////bool GoalTimeUI::Finalize()
////{
////	image.Finalize();
////	return true;
////}
////void GoalTimeUI::UpDate()
////{
////	this->MoveVolume();
////}
////void GoalTimeUI::MoveVolume()
////{
////	this->ScaleVolume.x += 0.033f;
////	this->ScaleVolume.y += 0.033f;
////	if (this->ScaleVolume.x >= 1.0f)
////	{
////		this->ScaleVolume.x = 1.0f;
////	}
////	if (this->ScaleVolume.y >= 1.0f)
////	{
////		this->ScaleVolume.y = 1.0f;
////	}
////	//再計算をする
////	this->ResetCenter();
////}
//////GoalTimeUI::Mat3x3 GoalTimeUI::Mat3x3::Create(float target[], MatFormat format)
//////{
//////	float value[9] = {};
//////
//////	//単位行列にする
//////	for (int i = 0; i < 9; i += 4)
//////	{
//////		value[i] = 1.f;
//////	}
//////	Mat3x3 mat;
//////	for (int i = 0; i < 9; ++i)
//////	{
//////		mat.mat[i] = value[i];
//////		///1 0 0 
//////		///0 1 0
//////		///0 0 1
//////	}
//////
//////	switch (format)
//////	{
//////	case Unix://単位行列
//////		break;
//////	case Rotate:
//////		value[0] = target[0];	//cos
//////		value[1] = target[1];	//sin
//////		value[3] = target[2];	//-sin
//////		value[4] = target[3];	//cos
//////		break;
//////	case Scale:
//////		value[0] = target[0];	//Xa
//////		value[1] = target[1];	//Xb
//////		break;
//////	case Move:
//////		value[6] = target[0];	//x
//////		value[7] = target[1];	//y
//////		break;
//////	}
//////	return mat;
//////}
////void GoalTimeUI::Render2D()
////{
////	Box2D draw(this->Center.x - this->Center.x / 2, this->Center.y , this->Scale.x * this->ScaleVolume.x, this->Scale.y * this->ScaleVolume.y);
////	draw.OffsetSize();
////
////	//拡大機能
////	Box2D src = this->Src;
////	src.OffsetSize();
////
////	image.Draw(draw,src);
////}
////GoalTimeUI::GoalTimeUI()
////{
////	std::cout << "ゴールタイムUI　生成" << std::endl;
////}
////GoalTimeUI::~GoalTimeUI()
////{
////	this->Finalize();
////	std::cout << "ゴールタイムUI　解放" << std::endl;
////}
////GoalTimeUI::SP GoalTimeUI::Create(Vec2& pos, bool flag)
////{
////	GoalTimeUI::SP to = GoalTimeUI::SP(new GoalTimeUI());
////	if (to)
////	{
////		to->me = to;
////		if (flag)
////		{
////			OGge->SetTaskObject(to);
////		}
////		if (!to->Initialize(pos))
////		{
////			to->Kill();
////		}
////		return to;
////	}
//<<<<<<< HEAD
////	return nullptr;
////}
//=======
////	return mat;
////}
//void GoalTimeUI::Render2D()
//{
//	Box2D draw(this->Center.x + this->Scale.x - 450, this->Center.y + 40 , this->Scale.x * this->ScaleVolume.x, this->Scale.y * this->ScaleVolume.y);
//	draw.OffsetSize();
//
//	//拡大機能
//	Box2D src = this->Src;
//	src.OffsetSize();
//
//	image.Draw(draw,src);
//}
//GoalTimeUI::GoalTimeUI()
//{
//	std::cout << "ゴールタイムUI　生成" << std::endl;
//}
//GoalTimeUI::~GoalTimeUI()
//{
//	this->Finalize();
//	std::cout << "ゴールタイムUI　解放" << std::endl;
//}
//GoalTimeUI::SP GoalTimeUI::Create(Vec2& pos, bool flag)
//{
//	GoalTimeUI::SP to = GoalTimeUI::SP(new GoalTimeUI());
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
//>>>>>>> develop
