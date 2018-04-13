//______________________________//
//|メインシステム               |//
//|履歴：2018/03/20金子翔       |//
//|履歴：2018/03/23金子翔       |//
//|____________________________|//
#define _USE_MATH_DEFINES
//小数点誤差修正
#define _OX_EPSILON_ 0.0000001f

#include "OGSystem\OGTask.h"
//------------------
//class定義
//------------------
_OGTK OGTK;
void test()
{
	std::cout << "testnow" << std::endl;
}
//------------------
//タスクシステム
//------------------
void TaskSystem()
{
	OGTK._myGameUpdate();
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

}
//------------------
//解放
//------------------
void Finalize()
{
	
}
//------------------
//更新
//------------------
bool Update() {
	if (gameEngine->in.key.down(In::ESCAPE))
	{
		TaskFinalize();
		//ウィンドウの破棄
		glfwDestroyWindow(gameEngine->window->window);
		return true;
	}
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
	gameEngine = new EngineSystem();
	OGTK._myGameInitialize();
	gameEngine->Initialize();
	//使用OpenGLのVersion指定
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//使用するウィンドウを設定する
	glfwMakeContextCurrent(gameEngine->window->window);
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
	//描画範囲の指定
	glViewport(0, 0, gameEngine->window->_widht, gameEngine->window->_height);
	//行列の初期化
	glLoadIdentity();
	// 操作対象の行列をモデリングビュー行列に切り替えておく
	glMatrixMode(GL_MODELVIEW);
	//行列の初期化
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
	//ウィンドウの生成位置の指定
	glfwSetWindowPos(gameEngine->window->window, 1920 - gameEngine->window->_widht, 50);
	//ウィンドウが存在する場合ループ
	while (!glfwWindowShouldClose(gameEngine->window->window)) {
		//エンジン内の更新処理
		gameEngine->Update();
		//捜査対象の行列をモデルビュー行列に変更
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
		glfwSwapBuffers(gameEngine->window->window);
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