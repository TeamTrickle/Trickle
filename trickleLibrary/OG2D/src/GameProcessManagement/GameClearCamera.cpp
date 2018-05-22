#include "GameClearCamera.h"

#include "Goal\Goal.h"
bool GameClearCamera::Initialize()
{
	this->taskName = "GameClearCamera";
	this->Init(taskName);
	this->Flag_Reset();
	this->Set_CameraSpeed(Vec2(3, 3));
	this->SetCameraSize();
	std::cout << "ゴールカメラ　初期化" << std::endl;
	return true;
}
void GameClearCamera::Flag_Reset()
{
	this->cameraMovefinish = false;
	this->active = false;
	this->Move = false;
	moveCnt = 0;
}
void GameClearCamera::Set_CameraSpeed(Vec2& moveVec)
{
	cameraMove = moveVec;
}
void GameClearCamera::SetCameraPos()
{
	if (!Move)
	{
		cameraPos = OGge->camera->GetPos();
	}
}
bool GameClearCamera::GetCameraMoveFinish()
{
	return cameraMovefinish;
}
bool GameClearCamera::Finalize()
{
	return true;
}
void GameClearCamera::UpDate()
{
	SetCameraPos();
	CameraMove();
}
void GameClearCamera::Render2D()
{

}
void GameClearCamera::CameraMove()
{
	auto goal = OGge->GetTask<Goal>("Goal");
	if (goal)
	{
		if (goal->cleared)
		{
			Move = true;
			active = true;
			if (cameraPos.x <= goal->position.x - cameraSize.x / 2)
			{
				cameraPos.x += cameraMove.x;
				OGge->camera->SetPos(cameraPos);
			}
			else if (cameraPos.y <= goal->position.y + goal->Scale.y - cameraSize.y)
			{
				cameraPos.y += cameraMove.y;
				OGge->camera->SetPos(cameraPos);
			}
			else
			{
				OGge->camera->SetPos(goal->position);
				//カメラのサイズを合わせる
				OGge->camera->SetSize(goal->Scale);
				moveCnt++;
				if (moveCnt >= 90)
				{
					this->cameraMovefinish = true;
					return;
				}
			}
		}
	}
	if (OGge->in->key.down(Input::KeyBoard::S))
	{
		std::cout << cameraPos.x << "   " << cameraPos.y << std::endl;
	}
}
void GameClearCamera::SetCameraSize()
{
	cameraSize = OGge->camera->GetSize();
}
GameClearCamera::GameClearCamera()
{
	std::cout << "ゴールカメラ　生成" << std::endl;
}
GameClearCamera::~GameClearCamera()
{
	std::cout << "ゴールカメラ　解放" << std::endl;
}
GameClearCamera::SP GameClearCamera::Create(bool flag)
{
	GameClearCamera::SP to = GameClearCamera::SP(new GameClearCamera());
	if (to)
	{
		to->me = to;
		if (flag)
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