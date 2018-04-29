#include "Task_Result.h"
using namespace std;
Result::Result()
{
	cout << "結果画面処理初期化" << endl;
}
Result::~Result()
{
	cout << "結果画面処理解放" << endl;
}
void Result::Initialize()
{
	Result_DataInput();
	Flag_Judge();
}
TaskFlag Result::Update()
{
	TaskFlag nowTask = TaskFlag::Task_Ruselt;
	if (gameEngine->in.key.down(Input::KeyBoard::S))
	{
		nowTask = Task_Title;
	}
	return nowTask;
}
void Result::Render()
{
	Box2D draw(Vec2(0,0),Vec2(0,0));
	draw.OffsetSize();
	Box2D src(Vec2(0, 0), Vec2(0, 0));
	src.OffsetSize();
	image.Draw(draw, src);
}
void Result::Finalize()
{
	image.Finalize();
}
void Result::Result_DataInput()
{
	int Frametime;				//タイムをフレーム格納する
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
	(stringstream)text >> Frametime;
	getline(_fin, text, ',');
	(stringstream)text >> GameFalg;
	if (GameFalg == "GameClear")		//ゲームがクリア
	{
		Flag_Input(Result::Achievement::Flag1);
	}
	//時間の計算
	int sec, min, hour;
	sec = Frametime % 60;
	min = Frametime / 60;
	hour = Frametime / 60 / 60;
	cout << hour << "時間" << min << "分" << sec << "秒" << endl;

	fin.close();

	
}
bool Result::Flag_Judge()
{
	if ((Flag & Result::Flag1 )== Result::Flag1)
	{
		//フラグ１を持っている
		cout << "Goal" << endl;
		return true;
	}
	if ((Flag & Result::Flag2) == Result::Flag2)
	{
		//フラグ２を持っている
		return true;
	}
	if ((Flag & Result::Flag3) == Result::Flag3)
	{
		//フラグ３を持っている
		return true;
	}
	if ((Flag & Result::Flag4) == Result::Flag4)
	{
		//フラグ４を持っている
		return true;
	}
	if (Flag & 0x0F)
	{
		//全部のフラグが成立している
		return true;
	}
	return false;
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
void Result::Set_pointa(Goal* obj)
{
	g_pointa = obj;
}