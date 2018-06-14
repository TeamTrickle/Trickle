//#include "ResultPlayer.h"
//
//#include "GameProcessManagement\ClearUI.h"
//#include "Effect\SterEffect.h"
//
//bool ResultPlayer::Initialize(Vec2& pos,Vec2& speed)
//{
//	//タスク登録
//	this->taskName = "ResultPlayer";
//	this->Init(taskName);
//	
//	//基本情報
//	this->CreateObject(Cube, pos, Vec2(96, 96), 0);
//	this->moveVec = speed;
//
//	this->keyflag = false;
//	
//	//アニメーションの設定
//	this->animetion.Reset();
//
//	//画像関連
//	std::string filePath = "player.png";
//	image.Create(filePath);
//	this->SetDrawOrder(1.0f);
//
//	//リザルト画面に関連する関数
//	this->ResetWalkStop();
//
//	std::cout << "リザルト時プレイヤ　初期化" << std::endl;
//	return true;
//}
//bool ResultPlayer::Finalize()
//{
//	image.Finalize();
//	return true;
//}
//void ResultPlayer::Think()
//{
//	Vec2 camerasize = OGge->camera->GetSize();
//	Vec2 windowsize = OGge->window->GetSize();
//
//	auto clearui = OGge->GetTask<ClearUI>("ClearUI");
//	auto sterEffect = OGge->GetTasks<SterEffect>("SterEffect");
//
//	ResultPlayer::State nm = this->animetion.motion;
//	switch (nm)
//	{
//	case ResultPlayer::Normal:
//
//		break;
//	case ResultPlayer::Walk:
//		if (!this->animetion.SmailMotionIsPlay())
//		{
//			if (this->position.x >= camerasize.x * 25 / 100)
//			{
//				this->walkstop = true;		//リザルト画面への情報フラグ
//				nm = Stop;
//			}
//		}
//		break;
//	case ResultPlayer::Smail:
//		//アニメーションカウントが一定時間まで経過したら・・・
//		if (this->animetion.SmailMotionIsPlay())
//		{
//			if (OGge->in->down(In::B2))
//			{
//				nm = Walk;
//			}
//		}
//		break;
//	case ResultPlayer::Stop:
//		//クリアUIが表示された場合歩きだす（拡大までが終了したら）
//		if (clearui != nullptr)
//		{
//			if (clearui->GetVolumeFlag())
//			{
//				this->animetion.ResetAnimetionCnt();
//				nm = Smail;
//			}
//		}
//		break;
//	}
//	animetion.MotionChenge(nm);
//}
//void ResultPlayer::Motion()
//{
//	ResultPlayer::State nm = this->animetion.motion;
//	switch (nm)
//	{
//	case ResultPlayer::Normal:
//		break;
//	case ResultPlayer::Walk:
//		this->Move();
//		break;
//	case ResultPlayer::Smail:
//		//特になし
//		this->animetion.AnimetionMove();
//		break;
//	case ResultPlayer::Stop:
//		break;
//	}
//}
//void ResultPlayer::UpDate()
//{
//	Think();
//	Motion();
//}
//
//void ResultPlayer::Move()
//{
//	auto clearui = OGge->GetTask<ClearUI>("ClearUI");
//	if (clearui != nullptr)
//	{
//		this->moveVec.x = 8;
//	}
//
//	Vec2 camerasize = OGge->camera->GetSize();
//
//	//Playerが解放されるまで
//	if(position.x <= camerasize.x)
//	{
//		this->animetion.AnimetionMove();
//		position.x += moveVec.x;
//	}
//	else
//	{
//		Kill();
//	}
//}
//void ResultPlayer::Render2D()
//{
//	Box2D draw(position, Scale);
//	draw.OffsetSize();
//	Box2D src = this->Src;
//	src = this->animetion.ReturnSrc(src,this->animetion.motion);
//	src.OffsetSize();
//
//	int temp = src.w;
//	src.w = src.x;
//	src.x = temp;
//	image.Draw(draw, src);
//}
//void ResultPlayer::Animetion::Reset()
//{
//	this->animetionCnt = 0;
//	this->motion = Walk;
//}
//void ResultPlayer::Animetion::ResetAnimetionCnt()
//{
//	this->animetionCnt = 0;
//}
//bool ResultPlayer::Animetion::SmailMotionIsPlay()
//{
//	return this->animetionCnt >= this->toSmailCnt ? true : false;
//}
//void ResultPlayer::Animetion::AnimetionMove()
//{
//	this->animetionCnt++;
//}
//Box2D ResultPlayer::Animetion::ReturnSrc(Box2D Src, State motion)
//{
//	Box2D src = Src;
//	switch (motion)
//	{
//	case ResultPlayer::Normal:
//		src.x = 0;
//		break;
//	case ResultPlayer::Walk:
//		src.x = this->animetionCnt / 3 % 9 * src.w;
//		break;
//	case ResultPlayer::Smail:
//		if (animetionCnt % 60 >= 30)
//		{
//			src.x = 5 * src.h;
//			src.y = 5 * src.w;
//		}
//		else
//		{
//			src.x = 0;
//			src.y = 0;
//		}
//		break;
//	case ResultPlayer::Stop:
//		src.x = 0;
//		src.y = 0;
//		break;
//	}
//	return src;
//}
//void ResultPlayer::Animetion::MotionChenge(State state)
//{
//	this->motion = state;
//}
//void ResultPlayer::Animetion::ResetSrc(Box2D& src)
//{
//	src.x = 0;
//	src.y = 0;
//}
//void ResultPlayer::ResetWalkStop()
//{
//	this->walkstop = false;
//}
//bool ResultPlayer::GetResetWalkStop()
//{
//	return this->walkstop;
//}
//ResultPlayer::ResultPlayer()
//{
//	std::cout << "リザルト時プレイヤ　生成" << std::endl;
//}
//ResultPlayer::~ResultPlayer()
//{
//	std::cout << "リザルト時プレイヤ　解放" << std::endl;
//}
//ResultPlayer::SP ResultPlayer::Create(Vec2 pos,Vec2 speed,bool flag)
//{
//	ResultPlayer::SP to = ResultPlayer::SP(new ResultPlayer());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos,speed))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}