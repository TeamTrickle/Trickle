//_____________________________
//|メインシステム               
//|履歴：2018/03/20       
//|履歴：2018/03/23
//|履歴：2018/04/26
//|____________________________
//数値演算定数
#define _USE_MATH_DEFINES
//小数点誤差修正
#define _OX_EPSILON_ 0.0000001f
#include "OGSystem\OGTask.h"
#include "OGSystem\Random\Random.h"
//#include "ft2build.h"
//#include FT_FREETYPE_H
//メモリリーク検知
#if (_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

OGTK* ogtk;
unsigned short* MapNum;
//------------------
//タスクシステム
//------------------
void TaskSystem()
{
	OGge->TaskGameUpDate();
}
void TaskRender()
{
	
}
void TaskFinalize()
{
	//解放処理
	OGge->SetDeleteEngine(true);
}
//------------------
//初期化
//------------------
bool Initialize() 
{
	random::Init();
	ogtk->StartTaskObject();
	return true;
}
//------------------
//解放
//------------------
bool Finalize()
{
	OGge->SetDeleteEngine(true);
	return true;
}
//------------------
//更新
//------------------
bool Update() {
	if (OGge->in->key.down(In::ESCAPE) || OGge->GetEnd())
	{
		TaskFinalize();
		//ウィンドウの破棄
		glfwDestroyWindow(OGge->window->GetWindow());
		return true;
	}
	return false;
}
//------------------
//メイン
//------------------
int main() {
	//メモリリーク検知
#if(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//FWの初期化
	if (!glfwInit()) {
		return -1;
	}
	//ゲームエンジンの生成
	OGge = new EngineSystem();
	ogtk = new OGTK();
	rm = new ResourceManager();
	MapNum = new unsigned short;
	//タスクの初期化処理
	ogtk->_myGameInitialize();
	//ゲームエンジンの初期化
	OGge->Initialize();
	//使用OpenGLのVersion指定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//使用するウィンドウを設定する
	glfwMakeContextCurrent(OGge->window->GetWindow());
	//同期(ダブルバッファの入れ替えタイミングの指定)
	glfwSwapInterval(1);
#if defined(_MSC_VER)
	//GLEW初期化
	if (glewInit() != GLEW_OK) {
		//ウィンドウとカーソルをすべて破棄しリソースを解放します。
		glfwTerminate();
		return -1;
	}
#endif
	// 透視変換行列を設定
	glMatrixMode(GL_PROJECTION);
	//描画範囲の指定
	glViewport(0, 0, (GLsizei)OGge->window->GetSize().x, (GLsizei)OGge->window->GetSize().y);
	//行列の初期化
	glLoadIdentity();
	// 操作対象の行列をモデリングビュー行列に切り替えておく
	glMatrixMode(GL_MODELVIEW);
	//行列の初期化
	glLoadIdentity();
	//ウインドウの座標の巻線に基づいてポリゴンをカリングする
	glEnable(GL_CULL_FACE);
	//深さの比較を行い、深度バッファを更新する(3D用)
	//glEnable(GL_DEPTH_TEST);
	//法線ベクトルの設定、正規化
	glEnable(GL_NORMALIZE);
	//背景color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//初期化処理
	Initialize();
	//ウィンドウが存在する場合ループ
	while (!glfwWindowShouldClose(OGge->window->GetWindow())) {
		//指定したウィンドウのダブルバッファを行う
		glfwSwapBuffers(OGge->window->GetWindow());
		//捜査対象の行列をモデルビュー行列に変更
		glMatrixMode(GL_MODELVIEW);
		//バッファをクリアして値を設定する
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//有効になっている場合、計算されたフラグメントカラー値をカラーバッファの値とブレンドします。
		glEnable(GL_BLEND);
		//ピクセル演算を指定する
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (OGge->fps->FrameCheck()) {
			glfwPollEvents();
			OGge->Update();
			if (Update()) {
				break;
			}
			TaskSystem();
		}
		OGge->Task_Render_AF();
		//エンジン内の更新処理
		//OGge->Update();
		//更新処理
		//if (Update()) { break; }
		//TaskSystem();
		//描画処理
		TaskRender();
		//ウィンドウ、マウス、キーボードの入力の状態をアップデートする
		//glfwPollEvents();
	}
	//解放
	Finalize();
	//ゲームエンジンの内容を解放
	delete MapNum;
	delete ogtk;
	delete OGge;
	delete rm;
	//GLFWのライブラリを終了する
	glfwTerminate();
}