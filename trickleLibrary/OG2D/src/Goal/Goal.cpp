#include "Goal.h"
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"
#include "Player/Player.h"
#include "Map/Map.h"
bool Goal::Initialize()
{
	//タスク関連
	this->taskName = "Goal";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//ゴールフラグ関連
	this->ResetisGoal();

	//アニメーション関連
	this->ResetAnimetion();

	//カメラモード関連
	this->ResetCamera();

	//画像関連
	tex.Create((std::string)"goal.png");
	

	//基本の情報
	CreateObject(Objform::Cube, Vec2{}, Vec2(64, 64), 0.f);


	std::cout << "ゴール　初期化" << std::endl;
	return true;
}
bool Goal::Initialize(Vec2& pos) {
	//タスク関連
	this->taskName = "Goal";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//ゴールフラグ関連
	this->ResetisGoal();

	//アニメーション関連
	this->ResetAnimetion();

	//カメラモード関連
	this->ResetCamera();


	//画像関連
	tex.Create((std::string)"goal.png");

	//基本の情報
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);

	std::cout << "ゴール　初期化" << std::endl;
	return true;
}
void Goal::UpDate()
{
	this->Camera_Think();
	this->Camera_Motion();
}

void Goal::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src;
	if (this->cleared) 
	{
		//アニメーションフラグがtrueならば・・
		if (this->isanimetion && animCnt < 99) 
		{
			//拡大が終わったらアニメーション
			//(10カット*１０フレーム)-1になったら止める
			animCnt++;
		}
		if (animCnt >= 99)
		{
			this->isanimetionfinish = true;
		}
		src = Box2D(256*(animCnt / 10), 284, 256, 284);
	}
	else 
	{
		src = Box2D(0, 0, 256, 256);
	}
	
	src.OffsetSize();
	tex.Draw(draw, src);
	this->LineDraw();
}

bool Goal::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	tex.Finalize();
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
void Goal::ResetisGoal()
{
	this->cleared = false;
}
void Goal::ResetAnimetion()
{
	this->isanimetion = false;
	this->isanimetionfinish = false;
	this->animCnt = 0;
}
void Goal::ResetCameraMode()
{
	this->cameramode = CameraMode::NON;
}
void Goal::ResetisCameraPlay()
{
	this->iscameraPlay = false;
}
void Goal::ResetCameraCnt()
{
	
}
void Goal::ResetCameraVec()
{
	this->cameraPos = OGge->camera->GetPos();
	this->cameraSize = OGge->camera->GetSize();
}
void Goal::ResetCamera()
{
	this->ResetCameraMode();
	this->ResetisCameraPlay();
	this->ResetCameraVec();
	this->ResetCameraCnt();
	this->SetCameraSpeed(Vec2(2, 3));
}
void Goal::SetCameraSpeed(Vec2& speed)
{
	this->cameraMove = speed;
}
Goal::CameraMode Goal::GetCameraMode()
{
	return this->cameramode;
}
bool Goal::isGoal()
{
	return this->cleared;
}
bool Goal::isAnimetion()
{
	return this->isanimetion;
}
void Goal::SetCameraMode(CameraMode mode)
{
	this->cameramode = mode;
}
void Goal::Camera_Think()
{
	Goal::CameraMode nm = this->cameramode;
	switch (nm)
	{
	case Goal::NON:		//起動していない
		if (this->cleared)
		{
			nm = Play;
		}
		break;
	case Goal::Play:	//起動している
		if (this->isanimetionfinish)
		{
			nm = End;
		}
		break;
	case Goal::End:		//起動した
		//カメラのサイズを元に戻す

		break;
	}
	this->SetCameraMode(nm);
}
void Goal::Camera_Motion()
{
	auto player = OGge->GetTask<Player>("Player");

	switch (this->cameramode)
	{
	case Goal::NON:
		//クリアしていない場合だけクリア判定をチェックします
		if (!this->cleared)
		{
			if (this->ClearCheck())
			{
				this->cleared = true;
				this->iscameraPlay = true;
				this->inside = (this->position - player->position);
			}
		}
		break;
	case Goal::Play:
		break;
	case Goal::End:
		
		break;
	}
	this->cameraPos = OGge->camera->GetPos();
	this->Camera_Play();
}
void Goal::Camera_Play()
{
	auto player = OGge->GetTask<Player>("Player");
	auto map = OGge->GetTask<Map>("map");
	if (!player && !map)
	{
		std::cout << "例外" << std::endl;
		return;
	}

	//Playerから見てゴールが左側にある場合
	if (inside.x < 0)
	{
		if (this->cameraPos.x < 0)
		{
			if (this->cameraPos.x >= this->cameraPos.x + this->inside.x)
			{
				this->cameraPos.x -= this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Playerから見てゴールが右側にある場合
	else if (inside.x > 0)
	{
		if (this->cameraPos.x + this->cameraSize.x < map->DrawSize.x * map->mapSize.x)
		{
			if (this->cameraPos.x <= this->cameraPos.x + this->inside.x)
			{
				this->cameraPos.x += this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Playerから見てゴールが上にある場合
	else if (inside.y < 0)
	{
		if (this->cameraPos.y < 0)
		{
			if (this->cameraPos.y >= this->cameraPos.y + this->inside.y)
			{
				cameraPos.y -= cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
	}
	else if (inside.y > 0)
	{
		if (this->cameraPos.y + this->cameraSize.y < map->DrawSize.y * map->mapSize.y)
		{
			if (this->cameraPos.y <= this->cameraPos.y + this->inside.y)
			{
				cameraPos.y += cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
	}
	else
	{
		this->isanimetion = true;
	}
}
bool Goal::ClearCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	if (waters != nullptr)
	{
		for (int i = 0; i < (*waters).size(); ++i)
		{
			if ((*waters)[i]->hit(*this))
			{
				if ((*waters)[i]->GetSituation() == Water::Situation::Normal && (*waters)[i]->GetState() == Water::State::LIQUID)
				{
					return true;
				}
			}
		}
	}
	return false;
}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Goal::Goal()
{
	std::cout << "ゴール　生成" << std::endl;
}

Goal::~Goal()
{
	this->Finalize();
	std::cout << "ゴール　解放" << std::endl;
}

Goal::SP Goal::Create(bool flag_)
{
	Goal::SP to = Goal::SP(new Goal());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Goal::SP Goal::Create(bool flag_,Vec2& pos)
{
	Goal::SP to = Goal::SP(new Goal());
	if (to)
	{
		to->me = to;
		if (flag_)
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