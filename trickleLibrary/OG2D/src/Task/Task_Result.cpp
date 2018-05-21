#include "Task_Result.h"
using namespace std;
//別タスクや別オブジェクトを生成する場合ここにそのclassの書かれたhをインクルードする
#include "Task_Title.h"
#include "GameProcessManagement\FlagUI.h"
#include "Player\ResultPlayer.h"
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

	SetDrawOrder(0.0f);
	{
		Vec2 windowsize = OGge->window->GetSize();
		auto player = ResultPlayer::Create(Vec2(0, (int)windowsize.y - 200),Vec2(3,0));
	}
	for (int i = 0; i < 3; ++i)
	{
		auto ster = FlagUI::Create(Vec2(100 * (i + 1), 100),1 << 0);
	}
	cout << "結果画面処理　初期化" << endl;
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
	{
		Box2D draw(Vec2(0, 0), OGge->window->GetSize());
		draw.OffsetSize();
		Box2D src(Vec2(0, 0), Vec2(1280, 720));
		src.OffsetSize();
		image.Draw(draw, src);
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
		auto player = OGge->GetTask<ResultPlayer>("ResultPlayer");
		auto ster = OGge->GetTasks<FlagUI>("Ster");
		for (auto id = (*ster).begin(); id != (*ster).end(); ++id)
		{
			(*id)->Kill();
		}
		if (player)
		{
			player->Kill();
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
		cout << "Goal" << endl;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//フラグ２を持っている
		active = true;
		cout << "30秒以内にゴールをした" << endl;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//フラグ３を持っている
		cout << "60秒以内にゴールをした" << endl;
		active = true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//フラグ４を持っている
		cout << "普通にゴールをした" << endl;
		active = true;
	}
	if (Flag & 0x0F)
	{
		cout << "マスタークリア" << endl;
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
void Result::Flag_Judge_Clear()
{
	Flag &= ~Flag;
}
void Result::Result_DataInput()
{
	string GameFalg;			//ゲームフラグ
								//データの読み込み
	ifstream fin(TimeFilePath);

	if (!fin)
	{
		return;
	}
	//読み込んだデータを入れておく変数
	string line;
	//改行か終了時点までの文字の文字列をlineに入れる
	getline(fin, line);
	//文字列を操作するための入力クラス、直接アクセスする
	istringstream _fin(line);
	//一字書き込み変数
	string text;
	//_finに入っている文字列から','までの文字をtextにいれる
	getline(_fin, text, ',');
	//textのデータを変数にいれる
	(stringstream)text >> FrameTime;
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
	getline(_fin, text, ',');
	(stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//ゲームがクリア
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//時間の計算
	int sec, min, hour;
	sec = FrameTime % 60;
	min = FrameTime / 60;
	hour = min / 60;
	cout << hour << "時間" << min << "分" << sec << "秒" << endl;

	fin.close();


}
//----------------------------
//ここから下はclass名のみ変更する
//ほかは変更しないこと
//----------------------------
Result::Result()
{
	cout << "結果画面処理　生成" << endl;
	//カメラ座標を元に戻す
	OGge->camera->SetPos(Vec2(0, 0));
	FrameTime = 0;
	Flag_Judge_Clear();
}

Result::~Result()
{
	this->Finalize();
	cout << "結果画面処理　解放" << endl;
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