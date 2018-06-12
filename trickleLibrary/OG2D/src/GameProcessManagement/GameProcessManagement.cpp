#include "GameProcessManagement.h"
using namespace std;
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Goal\Goal.h"
#include "Task\Task_Result.h"
#include "Task/StageSelect.h"

bool GameProcessManagement::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "GameProcessManagement";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	gameclear_flag = false;                 //初期値はfalseにしておく
	pause_flag = false;
	timer = Timer::Create();
	timer->Start();							//タイマーをスタートさせる

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

bool GameProcessManagement::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (timer != nullptr)
	{
		timer->Kill();
	}
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		//ゴールをしている
		if (gameclear_flag)
		{//ポーズ処理を行っていない
			if (!pause_flag)
			{
				//順番が違うとリザルト画面の表示ができません
				//チュートリアルでは表示しない
				if (*MapNum == 5 || *MapNum == 6)
				{
					auto result = Result::Create();
					pause_flag = true;
				}
			}
		}
	}
	return true;
}
void GameProcessManagement::Goal_Check()
{
	if (!gameclear_flag)
	{
		auto goal = OGge->GetTasks<Goal>("Goal");
		//ゴール判定を格納するVectorを用意する
		std::vector<bool> goalCheck;
		//ゴール判定を格納するVectorにデータを入れる
		for (auto id = (*goal).begin(); id != (*goal).end(); ++id)
		{
			goalCheck.push_back((*id)->isGoal());
		}

		//要素を調べる
		if (std::all_of(goalCheck.begin(), goalCheck.end(), [](bool flag) {return flag == true; }))
		{
			timer->Pause();
			gameclear_flag = true;
			goalCheck.clear();
			return;
		}
		//クリアしていないときはタイマーを動かす
		timer->Frame_Set();
		goalCheck.clear();
	}
}
void GameProcessManagement::Goal_Event()
{
	//ゴールをしたら・・・
	if (gameclear_flag)						//ゲームフラグがtrueになったら・・・
	{
		File_Writing();						//フレームを書き込み
		timer->Stop();						//タイマーの時間を元に戻す
	}
}
void GameProcessManagement::File_Writing()
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
			this->mission.Flag_Judge(*MapNum,fin);
			fin << "," << std::endl;
			break;
		case 6:
			fin << "Stage2";
			fin << ",";
			//各自の達成項目について判定をしてフラグを代入させる
			this->mission.Flag_Judge(*MapNum,fin);
			fin << "," << std::endl;
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
void GameProcessManagement::Mission::Flag_Judge(unsigned short& mapnumber , std::ofstream& fin)
{
	//条件を書く　IF
	//フラグを代入する
	//ファイルにデータを書く
	switch (mapnumber)
	{
	case 5:
		//条件をここに入力する

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

GameProcessManagement::SP GameProcessManagement::Create(bool flag_)
{
	GameProcessManagement::SP to = GameProcessManagement::SP(new GameProcessManagement());
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