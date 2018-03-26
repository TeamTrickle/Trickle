//______________________________//
//|メインシステム               |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/03/23金子翔       |//
//|____________________________|//
#define _USE_MATH_DEFINES
//小数点誤差修正
#define _OX_EPSILON_ 0.0000001f
#define STB_IMAGE_IMPLEMENTATION
#include "ft2build.h"
#include FT_FREETYPE_H
#include "OGSystem\OGTask.h"
//------------------
//class定義
//------------------
FPS fps;
_OGTK OGTK;
//------------------
//タスクシステム
//------------------
void TaskSystem()
{
	OGTK._myGameUpDate();
}
void TaskRender()
{
	OGTK._myGameRender2D();
	OGTK._myGameRender3D();
}
void TaskFinalize()
{
	OGTK._myGameFinalize();
}
//------------------
//初期化
//------------------
void Initialize() {
	fps.Initialize();
	Input::Initialize(OGTK._window.window);
}
//------------------
//解放
//------------------
void Finalize()
{
	Input::Finalize();
}
//------------------
//更新
//------------------
bool Update() {
	if (Input::KeyInputDown(Input::ESCAPE))
	{
		TaskFinalize();
		//ウィンドウの破棄
		glfwDestroyWindow(OGTK._window.window);
		return true;
	}
	fps.Update();
	return false;
}
//------------------
//メイン
//------------------
int main() {
	//FWの初期化
	if (!glfwInit()) {
		return -1;
	}
	OGTK._myGameInitialize();
	//使用OpenGLのVersion指定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//使用するウィンドウを設定する
	glfwMakeContextCurrent(OGTK._window.window);
	//同期(ダブルバッファの入れ替えタイミングの指定)
	glfwSwapInterval(1);
#if defined(_MSC_VER)
	//GLEW初期化
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}
#endif
	// 透視変換行列を設定
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, OGTK._window._widht, OGTK._window._height);
	glLoadIdentity();
	gameEngine = new EngineSystem();
	gameEngine->Initialize();
	// 操作対象の行列をモデリングビュー行列に切り替えておく
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//ウインドウの座標の巻線に基づいてポリゴンをカリングする
	glEnable(GL_CULL_FACE);
	//深さの比較を行い、深度バッファを更新する
	glEnable(GL_DEPTH_TEST);
	//法線ベクトルの設定、正規化
	glEnable(GL_NORMALIZE);
	//背景color
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	//初期化処理
	Initialize();
	while (!glfwWindowShouldClose(OGTK._window.window)) {
		gameEngine->UpDate();
		glMatrixMode(GL_MODELVIEW);
		//バッファをクリアして値を設定する
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//有効になっている場合、計算されたフラグメントカラー値をカラーバッファの値とブレンドします。
		glEnable(GL_BLEND);
		//ピクセル演算を指定する
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//更新処理
		if (Update()) { break; }
		TaskSystem();
		//描画処理
		TaskRender();
		//指定したウィンドウのダブルバッファを行う
		glfwSwapBuffers(OGTK._window.window);
		//ウィンドウ、マウス、キーボードの入力の状態をアップデートする
		glfwPollEvents();
	}
	//解放
	Finalize();
	//ゲームエンジンの内容を解放
	delete gameEngine;
	//GLFWのライブラリを終了する
	glfwTerminate();
}