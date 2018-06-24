#include "GameProcessManagement.h"
#include "Goal\Goal.h"
#include "Task\Task_Game.h"
#include "Task\Task_Result.h"
#include "Task\StageSelect.h"
GameManager::GameManager()
{
	this->Seconds = 0;
	this->Minute = 0;
	this->timeCnt = 0;
	this->isclear = false;
	for (int i = 0; i < 3; ++i)
	{
		this->M_flag[i] = false;
	}
	this->time = 0;
	__super::Init((std::string)"GM");
}
GameManager::~GameManager()
{
	if (this->isclear)
	{
		if (*MapNum == 5 || *MapNum == 6)
		{
			OGge->ChengeTask();
			Result::Create();
		}
		else
		{
			if (*MapNum < 4)
			{
				*MapNum = *MapNum + 1;
				auto next = Game::Create();
			}
			//次にチュートリアルを控えているものは次のチュートリアルへ移動
			else if (*MapNum == 4)
			{
				//チュートリアル終了でセレクトに戻る
				auto next = StageSelect::Create();
			}
		}
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
		if (this->time > 180)
		{
			//クリア処理
			//データの保存
			auto game = OGge->GetTask<Game>("game");
			if (game)
			{
				game->Kill();
				//現在の記録を保存
				this->OutData();
				//現在の最大記録との比較
				this->ComparisonData();
			}
			this->isclear = true;
		}
		else
		{
			this->time++;
		}
	}
}
void GameManager::ResetData()
{
	for (int i = 1; i <= 6; ++i)
	{
		std::ofstream ofs("./data/Result/data" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
		ofs.open("./data/Result/save" + std::to_string(i) + ".bin", std::ios::out | std::ios::binary);
		ofs << -1 << std::endl;
		ofs.close();
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
	std::string path = "./data/Result/save" + std::to_string((int)*MapNum) + ".bin";
	std::ofstream ofs(path, std::ios::out | std::ios::binary);
	if (!ofs)
	{
		std::cout << "ファイルが存在しません" << std::endl;
	}
	//クリアしている場合
	if (this->isClear())
	{
		//時間の保存
		ofs << this->Minute << "," << this->Seconds << std::endl;
		switch (*MapNum)
		{
		case 1:
			//とりあえず読み込み時にエラーを吐かないように仮の値をいれておく
			for(int i = 0;i < 3;++i)
			{
				ofs << "t,";
				this->M_flag[i] = true;
			}
			break;
		case 2:
			for (int i = 0; i < 3; ++i)
			{
				ofs << "t,";
				this->M_flag[i] = true;
			}
			break;
		case 3:
			for (int i = 0; i < 3; ++i)
			{
				ofs << "t,";
				this->M_flag[i] = true;
			}
			break;
		case 4:
			for (int i = 1; i <= 3; ++i)
			{
				std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
				if (!ifs)
				{
					ofs << "f,";
				}
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i] = true;
				}
				else
				{
					ofs << "f,";
				}
				delete is;
				ifs.close();
			}
			break;
		case 5:
			//ステージ１のミッション
			if (this->Minute * 60 + this->Seconds <= 120)
			{
				ofs << "t,";
				this->M_flag[0] = true;
			}
			else
			{
				ofs << "f," ;
			}

			if (this->Minute * 60 + this->Seconds <= 90)
			{
				ofs << "t,";
				this->M_flag[1] = true;
			}
			else
			{
				ofs << "f,";
			}

			if (this->Minute * 60 + this->Seconds <= 60)
			{
				ofs << "t," ;
				this->M_flag[2] = true;
			}
			else
			{
				ofs << "f," ;
			}
			break;
		case 6:
		{
			//ステージ２のミッション
			auto goals = OGge->GetTasks<Goal>("Goal");
			unsigned __int8 i = 0;
			for (auto id = goals->begin(); id != goals->end(); ++id)
			{
				if ((*id)->ColorCheck())
				{
					ofs << "t," ;
					this->M_flag[i] = true;
				}
				else
				{
					ofs << "f," ;
				}
				++i;
			}
		}
			break;
		default:
			break;
		}
	}
	else
	{
		//それ以外(例外処理)
		ofs << -1 << std::endl;
	}
	ofs.close();
	if (*MapNum >= 1 && *MapNum <= 3)
	{
		ofs.open("./data/Result/save4.bin", std::ios::out | std::ios::binary);
		ofs << -2 << "," << -2 << std::endl;
		for (int i = 1; i <= 3; ++i)
		{
			std::ifstream ifs("./data/Result/save" + std::to_string(i) + ".bin", std::ios::in | std::ios::binary);
			if (!ifs)
			{
				ofs << "f,";
			}
			else
			{
				std::string line;
				std::getline(ifs, line);
				std::istringstream* is = new std::istringstream(line);
				std::string text;
				int timer;
				std::getline(*is, text, ',');
				(std::stringstream)text >> timer;
				if (timer != -1)
				{
					ofs << "t,";
					this->M_flag[i - 1] = true;
				}
				else
				{
					ofs << "f,";
					this->M_flag[i - 1] = false;
				}
				delete is;
			}
			ifs.close();
		}
		ofs.close();
	}
	return true;
}
bool GameManager::ComparisonData()
{
	//前の結果を入れる箱
	int time[2] = { 0,0 };
	bool flag[3] = { false,false,false };
	switch (*MapNum)
	{
	case 5:
	case 6:
	{
		std::ifstream ifs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> time[i];
				if (time[i] == -1)
				{
					//読み込んだデータが-1の場合エラーなのでファイルが存在しなかった時同様ファイルを今回のデータで上書きする
					this->OutFileData();
					delete is;
					return true;
				}
			}
			std::getline(ifs, line);
			delete is;
			is = new std::istringstream(line);
			for (int i = 0; i < 3; ++i)
			{
				std::getline(*is, text, ',');
				if (text == "t")
				{
					flag[i] = true;
				}
			}
			delete is;
		}
		else
		{
			//ファイルが存在しない場合
			OutFileData();
			return true;
		}
		//正常時の最大記録保持の書き込み処理
		std::ofstream ofs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
		if (this->isClear())
		{
			//チュートリアル４用処理
			if (time[0] == -2 && time[1] == -2)
			{
				ofs << this->Minute << "," << this->Seconds << std::endl;
			}
			//タイムの早い方を保存する
			else if ((int)this->Minute * 60 + (int)this->Seconds < time[0] * 60 + time[1])
			{
				ofs << this->Minute << "," << this->Seconds << std::endl;
			}
			else
			{
				ofs << time[0] << "," << time[1] << std::endl;
			}
			for (int i = 0; i < 3; ++i)
			{
				//前回か今回でクリアしてたらtを書き込む
				if (this->M_flag[i] || flag[i])
				{
					ofs << "t,";
				}
				else
				{
					ofs << "f,";
				}
			}
		}
		else
		{
			//エラー時-1をいれておく
			ofs << -1 << std::endl;
		}
		ofs.close();
	}
	break;
	case 1:
	case 2:
	case 3:
		break;
	}
	

	if (*MapNum >= 1 && *MapNum <= 4)
	{
		//セーブに入ってるタイムとflagを持ってくる
		std::ifstream ifs("./data/Result/save4.bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> time[i];
			}
			std::getline(ifs, line);
			delete is;
			is = new std::istringstream(line);
			for (int i = 0; i < 3; ++i)
			{
				std::getline(*is, text, ',');
				if (text == "t")
				{
					flag[i] = true;
				}
				else
				{
					flag[i] = false;
				}
			}
			delete is;
			std::cout << std::endl;
		}
		int timers[2] = { 0,0 };
		bool flags[3] = { false,false,false };
		ifs.close();
		ifs.open("./data/Result/data4.bin", std::ios::in | std::ios::binary);
		if (ifs)
		{
			std::string line;
			std::getline(ifs, line);
			std::istringstream* is = new std::istringstream(line);
			std::string text;
			for (int i = 0; i < 2; ++i)
			{
				std::getline(*is, text, ',');
				(std::stringstream)text >> timers[i];
				if (timers[0] == -1)
				{
					std::ofstream ofs("./data/Result/data4.bin", std::ios::out | std::ios::binary);
					ofs << time[0] << "," << time[1] << std::endl;
					for (int i = 0; i < 3; ++i)
					{
						if (flag[i])
						{
							ofs << "t,";
						}
						else
						{
							ofs << "f,";
						}
					}
					ifs.close();
					ofs.close();
					delete is;
					return true;
				}
			}
			std::getline(ifs, line);
			delete is;
			is = new std::istringstream(line);
			for (int i = 0; i < 3; ++i)
			{
				std::getline(*is, text, ',');
				if (text == "t")
				{
					flags[i] = true;
				}
				else
				{
					flags[i] = false;
				}
			}
			delete is;
		}
		ifs.close();
		std::ofstream ofs("./data/Result/data4.bin", std::ios::out | std::ios::binary);
		if (time[0] == -2 && time[1] == -2)
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else if (timers[0] == -2 && timers[1] == -2)
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		else if (timers[0] * 60 + timers[1] < time[0] * 60 + time[1])
		{
			ofs << timers[0] << "," << timers[1] << std::endl;
		}
		else
		{
			ofs << time[0] << "," << time[1] << std::endl;
		}
		for (int i = 0; i < 3; ++i)
		{
			if (flag[i] || flags[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
		ofs.close();
		
	}
	return true;
}
void GameManager::OutFileData()
{
	//最大記録保持用の書き込み動作
	//※ここはファイルが存在しないまたはファイルデータがエラーの場合のみ
	std::ofstream ofs("./data/Result/data" + std::to_string(*MapNum) + ".bin", std::ios::out | std::ios::binary);
	if (this->isClear())
	{
		//時間の保存
		ofs << this->Minute << "," << this->Seconds << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			if (this->M_flag[i])
			{
				ofs << "t,";
			}
			else
			{
				ofs << "f,";
			}
		}
	}
	else
	{
		ofs << -1 << std::endl;
	}
	ofs.close();
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

