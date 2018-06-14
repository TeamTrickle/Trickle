#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
#include "Task/StageSelect.h"

bool GameProcessManagement::Initialize()
{
	//タスク関連
	this->taskName = "GameProcessManagement";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//フラグ関連
	gameclear_flag = false;                 //初期値はfalseにしておく
	pause_flag = false;
	this->mission.Flag = 0;

	timer = Timer::Create();



	cout << "進行管理クラス　初期化" << endl;
	return true;
}
void GameProcessManagement::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	Goal_Check();                        //ゴールを全てしているのかどうか？
	Goal_Event();
}

void GameProcessManagement::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
}
GameManager::GameManager()
{
	this->Seconds = 0;
	this->Minute = 0;
	this->timeCnt = 0;
	__super::Init((std::string)"GM");
}
GameManager::~GameManager()
{
	if (*MapNum == 5 || *MapNum == 6)
	{
		Result::Create();
	}
}
void GameManager::UpDate()
{
	if (!this->isClear())
	{
		//時間をプラスする
		//60秒を超えたら分をプラスし秒をリセット
		if (!this->isMaxTime())
		{
			this->timeCnt++;
			if (this->timeCnt >= 60)
			{
				this->Seconds++;
				this->timeCnt = 0;
				if (this->Seconds >= 60)
				{
					if (this->Minute < 59)
					{
						this->Seconds = 0;
						this->Minute++;
					}
				}
			}
		}
	}
	else
	{
		//クリア処理
		//データの保存
		auto game = OGge->GetTask<Game>("game");
		if (game)
		{
			game->Kill();
			if (*MapNum == 5 || *MapNum == 6)
			{
				this->OutData();
			}
		}
		//クリアしていないときはタイマーを動かす
		//timer->Frame_Set();
		goalCheck.clear();
	}
}
bool GameManager::isMaxTime()
{
	return this->Seconds >= 59 && this->Minute >= 59 ? true : false;
}
unsigned int GameManager::SecondsTime() const
{
	return this->Seconds;
}
unsigned int GameManager::MinuteTime() const
{
	return this->Minute;
}
bool GameManager::isClear()
{
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = goals->begin(); id != goals->end(); ++id)
	{
		//１つでもクリアしていないのならfalseを返す
		if (!(*id)->GetClear())
		{
			return false;
		}
	}
	return true;
}
bool GameManager::OutData()
{
	ofstream fin(TimeFilePath);							//ファイルのパスの指定
	fin << timer->Get_frame() << "," << std::endl;		//タイマーのフレーム数を書き込み
	if (gameclear_flag)
	{
		switch (*MapNum)
		{
		case 5:
			fin << "Stage1";
			fin << ",";
			//各自の達成項目について判定をしてフラグを代入させる
			this->Flag_Judge(*MapNum,fin);
			break;
		case 6:
			fin << "Stage2";
			fin << ",";
			//各自の達成項目について判定をしてフラグを代入させる
			this->Flag_Judge(*MapNum,fin);
			break;
		}
	}
	fin.close();							//ファイルを閉じる
}
bool GameProcessManagement::isAllGoal()
{
	return this->gameclear_flag;
}
int GameProcessManagement::GetFlag()
{
	return this->mission.Flag;
}
void GameProcessManagement::Mission::Flag_Input(GameProcessManagement::Achievement flag)
{
	this->Flag |= flag;
}
void GameProcessManagement::Mission::Flag_Judge_Clear()
{
	this->Flag &= ~this->Flag;
}
void GameProcessManagement::Flag_Judge(unsigned short& mapnumber, std::ofstream& fin)
{
	//条件を書く　IF
	//フラグを代入する
	//ファイルにデータを書く
	int cleartime = this->timer->GetTime();

	switch (mapnumber)
	{
	case 5:
		//条件をここに入力する
		//フラグ１の条件 30秒以内にゴールをした
		if (cleartime <= 30)
		{
			fin << "Flag1" << ",";
			this->mission.Flag_Input(Achievement::Flag1);
			fin << "Flag2" << ",";
			this->mission.Flag_Input(Achievement::Flag2);
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
		//フラグ２の条件 60秒以内にゴールをした
		if (cleartime <= 60)
		{
			fin << "Flag2" << ",";
			this->mission.Flag_Input(Achievement::Flag2);
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
		//フラグ３の条件 120秒以内にゴールをした
		if (cleartime <= 120)
		{
			fin << "Flag3" << ",";
			this->mission.Flag_Input(Achievement::Flag3);
			fin << std::endl;
		}
		break;
	case 6:
		//条件をここに入力する

		break;
	default:
		break;
	}
}
GameProcessManagement::GameProcessManagement()
{
	cout << "進行管理クラス　生成" << endl;
}

GameProcessManagement::~GameProcessManagement()
{
	this->Finalize();
	cout << "進行管理クラス　解放" << endl;
}
GameManager::SP GameManager::Create(bool flag)
{
	GameManager::SP to = GameManager::SP(new GameManager());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}

