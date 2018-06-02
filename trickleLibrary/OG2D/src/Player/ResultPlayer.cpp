#include "ResultPlayer.h"

#include "GameProcessManagement\ClearUI.h"

bool ResultPlayer::Initialize(Vec2& pos,Vec2& speed)
{
	//タスク登録
	this->taskName = "ResultPlayer";
	this->Init(taskName);
	
	//基本情報
	this->CreateObject(Cube, pos, Vec2(64, 64), 0);
	this->moveVec = speed;
	
	//アニメーションの設定
	this->animetion.Reset();

	//画像関連
	std::string filePath = "walk.png";
	image.Create(filePath);
	this->SetDrawOrder(1.0f);

	//リザルト画面に関連する関数
	this->ResetWalkStop();

	std::cout << "リザルト時プレイヤ　初期化" << std::endl;
	return true;
}
bool ResultPlayer::Finalize()
{
	image.Finalize();
	return true;
}
void ResultPlayer::Think()
{
	Vec2 camerasize = OGge->camera->GetSize();
	Vec2 windowsize = OGge->window->GetSize();

	auto clearui = OGge->GetTask<ClearUI>("ClearUI");

	ResultPlayer::State nm = this->animetion.motion;
	switch (nm)
	{
	case ResultPlayer::Normal:
		break;
	case ResultPlayer::Walk:
		if(this->position.x >= camerasize.x * 25 / 100)
		{
			this->walkstop = true;		//リザルト画面への情報フラグ
			nm = Stop;
		}
		break;
	case ResultPlayer::Smail:
		break;
	case ResultPlayer::Stop:
		if (clearui != nullptr)
		{
			nm = Walk;
		}
		break;
	default:
		break;
	}
	animetion.MotionChenge(nm);
}
void ResultPlayer::Motion()
{
	ResultPlayer::State nm = this->animetion.motion;
	switch (nm)
	{
	case ResultPlayer::Normal:
		break;
	case ResultPlayer::Walk:
		this->Move();
		break;
	case ResultPlayer::Smail:
		break;
	default:
		break;
	}
}
void ResultPlayer::UpDate()
{
	Think();
	Motion();
}

void ResultPlayer::Move()
{
	auto clearui = OGge->GetTask<ClearUI>("ClearUI");
	if (clearui != nullptr)
	{
		this->moveVec.x = 8;
	}

	Vec2 camerasize = OGge->camera->GetSize();
	if(position.x <= camerasize.x)
	{
		this->animetion.animetionCnt++;
		position.x += moveVec.x;
	}
	else
	{
		Kill();
	}
}
void ResultPlayer::Render2D()
{
	Box2D draw(position, Scale);
	draw.OffsetSize();
	Box2D src = this->Src;
	src = this->animetion.ReturnSrc(src,this->animetion.motion);
	src.OffsetSize();

	int temp = src.w;
	src.w = src.x;
	src.x = temp;
	image.Draw(draw, src);
}
void ResultPlayer::Animetion::Reset()
{
	this->animetionCnt = 0;
	this->motion = Walk;
	this->smailflag = false;
}
void ResultPlayer::Animetion::ResetAnimetionCnt()
{
	this->animetionCnt = 0;
}
Box2D ResultPlayer::Animetion::ReturnSrc(Box2D Src, State motion)
{
	Box2D src = Src;
	switch (motion)
	{
	case ResultPlayer::Normal:
		src.x = 0;
		break;
	case ResultPlayer::Walk:
		src.x = this->animetionCnt / 3 % 9 * src.w;
		break;
	case ResultPlayer::Smail:
		src.x = 0;
		break;
	}
	return src;
}
void ResultPlayer::Animetion::MotionChenge(State state)
{
	this->motion = state;
}
bool ResultPlayer::Animetion::SmailChangeCheck()
{
	this->toSmailCnt++;
	//喜ぶモーションに切り替えても良いか？ ☆の演出が終了したら・・・
	if (toSmailCnt >= 300)
	{
		return true;
	}
	return false;
}
void ResultPlayer::Animetion::SmailMotion()
{
	//クリアが表示され拡大がされたあとにフラグを返す方法が一番良い
	auto clearUI = OGge->GetTask<ClearUI>("ClearUI");
	if (clearUI != nullptr)
	{
		//拡大がされたら・・・喜ぶモーションカウンタを回す
		this->animetionCnt++;
		if (animetionCnt >= 500)
		{
			this->ResetAnimetionCnt();
			this->smailflag = true;
		}
	}
}
void ResultPlayer::ResetWalkStop()
{
	this->walkstop = false;
}
bool ResultPlayer::GetResetWalkStop()
{
	return this->walkstop;
}
ResultPlayer::ResultPlayer()
{
	std::cout << "リザルト時プレイヤ　生成" << std::endl;
}
ResultPlayer::~ResultPlayer()
{
	std::cout << "リザルト時プレイヤ　解放" << std::endl;
}
ResultPlayer::SP ResultPlayer::Create(Vec2 pos,Vec2 speed,bool flag)
{
	ResultPlayer::SP to = ResultPlayer::SP(new ResultPlayer());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,speed))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}