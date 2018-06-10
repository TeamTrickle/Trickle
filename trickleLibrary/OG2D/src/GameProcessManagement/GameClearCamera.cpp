#include "GameClearCamera.h"

#include "Goal\Goal.h"
bool GameClearCamera::Initialize()
{
	//タスク関連
	this->taskName = "GameClearCamera";
	this->Init(taskName);

	//カメラ関連
	this->Flag_Reset();
	this->Set_CameraSpeed(Vec2(3, 3));
	this->SetCameraSize();

	std::cout << "ゴールカメラ　初期化" << std::endl;
	return true;
}
void GameClearCamera::Flag_Reset()
{
	this->cameraMovefinish = false;
	this->Move = false;
	moveCnt = 0;
}
void GameClearCamera::NowCameraPos()
{
	//カメラが動かない間
	if (!Move)
	{
		cameraPos = OGge->camera->GetPos();
	}
}
void GameClearCamera::Set_CameraSpeed(Vec2& moveVec)
{
	cameraMove = moveVec;
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
	NowCameraPos();
	CameraMove();
	this->isGoal();
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
				//カメラ調整が終わったら花が咲くアニメーションのカウントを増やす
				goal->goal_anim = true;
				if (moveCnt >= 90)
				{
					this->cameraMovefinish = true;
					return;
				}
			}
		}
	}	
}
bool GameClearCamera::isGoal()
{
	auto goal = OGge->GetTasks<Goal>("Goal");
	//ゴール判定を格納するVectorを用意する
	std::vector<bool> goalCheck;
	//ゴール判定を格納するVectorにデータを入れる
	for (auto id = (*goal).begin(); id != (*goal).end(); ++id)
	{
		goalCheck.push_back((*id)->cleared);
	}

	//要素を調べる
	return std::all_of(goalCheck.begin(), goalCheck.end(), [](bool flag){return flag == true;});
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