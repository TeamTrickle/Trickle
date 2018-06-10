#include "Goal.h"
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Water\water.h"
#include "Player/Player.h"
#include "Map/Map.h"
bool Goal::Initialize(Vec2& pos,Paint::PaintColor color) 
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
	this->selectcolor = color;
	this->SetColorTextrue();

	//基本の情報
	CreateObject(Objform::Cube, pos, Vec2(64, 64), 0.f);

	std::cout << "ゴール　初期化" << std::endl;
	return true;
}
void Goal::UpDate()
{
	this->Camera_Think();
	this->Camera_Motion();

	this->DebugGoalClear();
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
	tex[this->selectcolor].Draw(draw, src);
	this->LineDraw();
}

bool Goal::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	for (int i = 0; i < 4; ++i)
	{
		tex[i].Finalize();
	}
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
	this->camerafinish = false;
}
void Goal::ResetCameraVec()
{
	this->cameraPos = OGge->camera->GetPos();
	this->cameraSize = OGge->camera->GetSize();
	this->PreCameraSize = OGge->camera->GetSize();
}
void Goal::ResetCamera()
{
	this->ResetCameraMode();
	this->ResetisCameraPlay();
	this->ResetCameraVec();
	this->SetCameraSpeed(Vec2(2, 2));
}
void Goal::SetCameraSpeed(Vec2& speed)
{
	this->cameraMove = speed;
}
void Goal::SetColorTextrue()
{
	//花のモーションとゴールの札を設定する
	tex[Paint::Red].Create((std::string)"");
	tex[Paint::Blue].Create((std::string)"");
	tex[Paint::Purple].Create((std::string)"");
	tex[Paint::Normal].Create((std::string)"goal.png");
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
			}
		}
		else
		{
			this->iscameraPlay = true;
		}
		this->inside = (this->position - cameraPos);
		break;
	case Goal::Play:
		this->cameraPos = OGge->camera->GetPos();
		this->Camera_Play();
		break;
	case Goal::End:
		//カメラのサイズを元に戻す
		OGge->camera->SetPos(this->PreCameraPos);
		OGge->camera->SetSize(this->PreCameraSize);
		break;
	}
}
void Goal::Camera_Play()
{
	std::cout << "("  << this->inside.x << "  "<<this->inside.y << ")"<< std::endl;

	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		std::cout << "例外" << std::endl;
		return;
	}

	//Playerから見てゴールが左側にある場合
	if (inside.x < 0)
	{
		//マップ外処理
		if (this->cameraPos.x < 0)
		{
			if (this->cameraPos.x / 2 >= this->cameraPos.x / 2 + this->inside.x)
			{
				this->cameraPos.x -= this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Playerから見てゴールが右側にある場合
	else if (inside.x > 0)
	{
		//マップ外処理
		if (this->cameraPos.x + this->cameraSize.x < map->DrawSize.x * map->mapSize.x)
		{
			if (this->cameraPos.x / 2 <= this->cameraPos.x / 2 + this->inside.x)
			{
				this->cameraPos.x += this->cameraMove.x;
				OGge->camera->SetPos_x(this->cameraPos.x);
			}
		}
	}
	//Playerから見てゴールが上にある場合
	if (inside.y < 0)
	{
		//マップ外処理
		if (this->cameraPos.y < 0)
		{
			if (this->cameraPos.y >= this->cameraPos.y + this->inside.y)
			{
				cameraPos.y -= cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
	}
	//Playerから見てゴールが下にある場合
	else if (inside.y > 0)
	{
		//マップ外処理
		if (this->cameraPos.y + this->PreCameraSize.y < map->DrawSize.y * map->mapSize.y)
		{
			if (this->cameraPos.y < this->cameraPos.y + this->inside.y)
			{
				cameraPos.y += cameraMove.y;
				OGge->camera->SetPos_y(cameraPos.y);
			}
		}
		else
		{
			
		}
	}

	//デバッグ機能
	if (OGge->in->key.down(Input::KeyBoard::Q))
	{
		//カメラの移動を終了させる
		this->camerafinish = true;
	}

	if(this->camerafinish)
	{
		if (!this->isanimetion)
		{
			//アニメーションが終了したときにカメラの座標が戻れるように保存しておく
			this->PreCameraPos = OGge->camera->GetPos();
		}
		//花のアニメーションを開始
		this->isanimetion = true;

		//カメラの拡大
		OGge->camera->SetPos(this->position);
		OGge->camera->SetSize(this->Scale);
	}
}
bool Goal::ClearCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	if (waters != nullptr)
	{
		for (int i = 0; i < (*waters).size(); ++i)
		{//接触判定
			if ((*waters)[i]->hit(*this))
			{//水かどうかを調べる
				if ((*waters)[i]->GetSituation() == Water::Situation::Normal && (*waters)[i]->GetState() == Water::State::LIQUID)
				{//水の色がこのゴールの札を同じであるか
					if ((*waters)[i]->GetColor() == this->selectcolor)
					{
						return true;
					}
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
Goal::SP Goal::Create(bool flag_,Vec2& pos,Paint::PaintColor color)
{
	Goal::SP to = Goal::SP(new Goal());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos,color))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

void Goal::DebugGoalClear()
{
	if (OGge->in->key.down(Input::KeyBoard::Q))
	{
		this->cleared = true;
	}
}