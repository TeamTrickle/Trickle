#include "Task_Result.h"
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Task_Title.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
#include "GameProcessManagement\ClearUI.h"
#include "GameProcessManagement\GoalTimeUI.h"
#include "GameProcessManagement\MissionUI.h"
#include "GameProcessManagement\FrameTime.h"
bool Result::Initialize()
{
	//-----------------------------
	//生成時に処理する初期化処理を記述
	//-----------------------------
	this->taskName = "Result";		//検索時に使うための名を登録する
	__super::Init(taskName);		//TaskObject内の処理を行う

	//生成例
	Result_DataInput();
	Flag_Judge();
	this->image.Create((std::string)"back.png");
	this->maptile.Create((std::string)"tile.jpg");

	SetDrawOrder(0.0f);
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto player = ResultPlayer::Create(Vec2(0, (int)windowsize.y - 50 - 64),Vec2(3,0));
	}
	{
		Vec2 windowsize = OGge->window->GetSize();
		for (int i = 0; i < 3; ++i)
		{
			auto ster = FlagUI::Create(Vec2(((int)windowsize.x / 2 - 200 ) + 100 * (i + 1), 130), 1 << 0);
		}
	}
	
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto clearUI = ClearUI::Create(Vec2(250,320));
		auto goaltime = GoalTimeUI::Create(Vec2(210,190));
		auto mission = MissionUI::Create(Vec2((int)windowsize.x / 2 - 200, 30));
		auto time = FrameTimeUI::Create(Vec2{},0);
	}
	std::cout << "結果画面処理　初期化" << std::endl;
	return true;
}

void Result::UpDate()
{
	//--------------------
	//更新時に行う処理を記述
	//--------------------
	//タイトルシーンへ遷移
	if (OGge->in->down(In::B2))
	{
		Kill();
	}
}
void Result::Render2D()
{
	//--------------------
	//描画時に行う処理を記述
	//--------------------
	Vec2 windowsize = OGge->window->GetSize();
	{
		Box2D draw(Vec2(0, 0), windowsize);
		draw.OffsetSize();
		Box2D src = this->backSrc;
		src.OffsetSize();
		image.Draw(draw, src);
	}
	{
		int count = 0;
		for (int y = windowsize.y - 50; y <= windowsize.y; y += 64)
		{
			for (int x = 0; x <= windowsize.x / 64; ++x)
			{
				Box2D draw(Vec2(x * 64, (int)windowsize.y - 50 + count * 64), Vec2(64, 64));
				draw.OffsetSize();
				Box2D src = this->maptileSrc;
				src.OffsetSize();
				maptile.Draw(draw, src);
			}
			count++;
		}
		
	}
}
bool Result::Finalize()
{
	//-----------------------------------------
	//このオブジェクトが消滅するときに行う処理を記述
	//-----------------------------------------
	//次のタスクを作るかかつアプリケーションが終了予定かどうか
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		image.Finalize();
		maptile.Finalize();

		auto player = OGge->GetTasks<ResultPlayer>("ResultPlayer");
		auto ster = OGge->GetTasks<FlagUI>("Ster");
		auto clear = OGge->GetTasks<ClearUI>("ClearUI");
		auto goaltime = OGge->GetTasks<GoalTimeUI>("GoalTimeUI");
		auto mission = OGge->GetTasks<MissionUI>("MissionUI");
		auto frametime = OGge->GetTasks<FrameTimeUI>("FrameTimeUI");

		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*player).begin(); id != (*player).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*clear).begin(); id != (*clear).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*goaltime).begin(); id != (*goaltime).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*mission).begin(); id != (*mission).end(); ++id)
		{
			(*id)->Kill();
		}
		for (auto id = (*frametime).begin(); id != (*frametime).end(); ++id)
		{
			(*id)->Kill();
		}
		auto title = Title::Create();
	}
	return true;
}
bool Result::Flag_Judge()
{
	bool active = false;
	if ((Flag & Result::Flag1) == Result::Flag1)
	{
		//フラグ１を持っている
		active = true;
		std::cout << "Goal" << std::endl;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//フラグ２を持っている
		active = true;
		std::cout << "30秒以内にゴールをした" << std::endl;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//フラグ３を持っている
		std::cout << "60秒以内にゴールをした" << std::endl;
		active = true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//フラグ４を持っている
		std::cout << "普通にゴールをした" << std::endl;
		active = true;
	}
	if (Flag & 0x0F)
	{
		std::cout << "マスタークリア" << std::endl;
	}
	return active;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2)
	{
		return true;
	}
	return false;
}
bool Result::Flag_Judge(Result::Achievement achive1, Result::Achievement achive2, Result::Achievement achive3)
{
	if ((Flag & achive1) == achive1 && (Flag & achive2) == achive2 && (Flag & achive3) == achive3)
	{
		return true;
	}
	return false;
}
void Result::Flag_Input(Result::Achievement achive)
{
	Flag |= achive;
}
int Result::Get_Flag()
{
	return Flag;
}
int Result::GetFrameTime()
{
	return FrameTime;
}
void Result::Flag_Judge_Clear()
{
	Flag &= ~Flag;
}
void Result::Result_DataInput()
{
	std::string GameFalg;			//ゲームフラグ
								//データの読み込み
	std::ifstream fin(TimeFilePath);

	if (!fin)
	{
		return;
	}
	//読み込んだデータを入れておく変数
	std::string line;
	//改行か終了時点までの文字の文字列をlineに入れる
	std::getline(fin, line);
	//文字列を操作するための入力クラス、直接アクセスする
	std::istringstream _fin(line);
	//一字書き込み変数
	std::string text;
	//_finに入っている文字列から','までの文字をtextにいれる
	std::getline(_fin, text, ',');
	//textのデータを変数にいれる
	(std::stringstream)text >> FrameTime;
	if (FrameTime <= 30)//30秒以内にゴール
	{
		Flag_Input(Result::Achievement::Flag2);
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else if (FrameTime <= 60)//60秒以内にゴール
	{
		Flag_Input(Result::Achievement::Flag3);
		Flag_Input(Result::Achievement::Flag4);
	}
	else
	{
		Flag_Input(Result::Achievement::Flag4);
	}
	std::getline(_fin, text, ',');
	(std::stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//ゲームがクリア
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//時間の計算
	int sec, min, hour;
	sec = FrameTime % 60;
	min = FrameTime / 60;
	hour = min / 60;
	std::cout << hour << "時間" << min << "分" << sec << "秒" << std::endl;

	fin.close();


}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Result::Result()
{
	std::cout << "結果画面処理　生成" << std::endl;
	//カメラ座標を元に戻す
	OGge->camera->SetPos(Vec2(0, 0));
	//カメラのサイズを元に戻す
	OGge->camera->SetSize(OGge->window->GetSize());
	FrameTime = 0;
	Flag_Judge_Clear();
}

Result::~Result()
{
	this->Finalize();
	std::cout << "結果画面処理　解放" << std::endl;
}

Result::SP Result::Create(bool flag_)
{

	Result::SP to = Result::SP(new Result());
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