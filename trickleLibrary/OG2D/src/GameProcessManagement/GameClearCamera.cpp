#include "GameClearCamera.h"

#include "Goal\Goal.h"
bool GameClearCamera::Initialize()
{
	this->taskName = "GameClearCamera";
	this->Init(taskName);
	this->Flag_Reset();
	std::cout << "ゴールカメラ　初期化" << std::endl;
	return true;
}
void GameClearCamera::Flag_Reset()
{
	this->cameraMovefinish = false;
	this->active = false;
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
			active = true;
			if (cameraPos.x < goal->position.x / 2)
			{
				cameraPos.x += 1;
				OGge->camera->MovePos(cameraPos);
			}
			else if (cameraPos.y < goal->position.y + 64)
			{
				cameraPos.y += 1;
				OGge->camera->MovePos(cameraPos);
			}
			else
			{
				this->cameraMovefinish = true;
			}		
		}
	}
	if (OGge->in->key.down(Input::KeyBoard::S))
	{
		std::cout << cameraPos.x << cameraPos.y << std::endl;
	}
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