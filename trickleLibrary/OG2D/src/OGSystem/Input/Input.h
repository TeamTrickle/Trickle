#pragma once
#include "OGSystem\_OGsystem.h"
//簡易引数用
namespace In
{
	enum
	{
		//仮装コントローラの入力設定
		BUTTON_A,		//1
		BUTTON_B,		//2
		BUTTON_X,		//3
		BUTTON_Y,		//4
		BUTTON_L1,		//5
		BUTTON_R1,		//6
		BUTTON_BACK,	//7
		BUTTON_START,	//8
		BUTTON_L3,		//9
		BUTTON_R3,		//10
		BUTTON_U,		//11
		BUTTON_R,		//12
		BUTTON_D,		//13
		BUTTON_L,		//14
	};
	enum AXIS
	{
		AXIS_LEFT_X,		//左スティックX値
		AXIS_LEFT_Y,		//左スティックY値
		AXIS_RIGHT_X,		//右スティックX値
		AXIS_RIGHT_Y,		//右スティックY値
		AXIS_BUTTON_NUM,
	};
	enum
	{
		LSTICK_LEFT,
		LSTICK_RIGHT,
		LSTICK_UP,
		LSTICK_DOWN,
		RSTICK_LEFT,
		RSTICK_RIGHT,
		RSTICK_UP,
		RSTICK_DOWN,
		STICK_NUM,
	};
	enum
	{
		//仮想入力
		B1,
		B2,
		B3,
		B4,
		CD,
		CU,
		CR,
		CL,
		L1,
		R1,
		D1,
		D2,
		SR,
		SL,
		LD,
		LU,
		LR,
		LL,
		RD,
		RU,
		RR,
		RL,
	};
	enum
	{
		//キーボードの仮装キー設定
		A, S, D, W, Q, E, Z, X, C, R, F, V, T,
		G, B, Y, H, N, U, J, M, I, K, O, L, P,
		SPACE, ENTER, ESCAPE,
		UP, DOWN, LEFT, RIGHT,
	};
}
//マウス用簡易引数
namespace Mouse
{
	enum
	{
		LEFT,
		RIGTH,
		CENTER,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
	};
}

class Input
{
public:
	//enum
	//入力用仮想入力
	enum in {
		B1,
		B2,
		B3,
		B4,
		CD,
		CU,
		CR,
		CL,
		L1,
		R1,
		D1,
		D2,
		SR,
		SL,
		LD,
		LU,
		LR,
		LL,
		RD,
		RU,
		RR,
		RL,
	};
	//class
	//ゲームパッド
	class GamePad
	{
	public:
		enum Pad
		{
			//仮装コントローラの入力設定
			BUTTON_A,		//1
			BUTTON_B,		//2
			BUTTON_X,		//3
			BUTTON_Y,		//4
			BUTTON_L1,		//5
			BUTTON_R1,		//6
			BUTTON_BACK,	//7
			BUTTON_START,	//8
			BUTTON_L3,		//9
			BUTTON_R3,		//10
			BUTTON_U,		//11
			BUTTON_R,		//12
			BUTTON_D,		//13
			BUTTON_L,		//14
		};
		enum AXIS {
			AXIS_LEFT_X,		//左スティックX値
			AXIS_LEFT_Y,		//左スティックY値
			AXIS_RIGHT_X,		//右スティックX値
			AXIS_RIGHT_Y,		//右スティックY値
			AXIS_BUTTON_NUM,
		};
		enum AXISBUTTON
		{
			LSTICK_LEFT,
			LSTICK_RIGHT,
			LSTICK_UP,
			LSTICK_DOWN,
			RSTICK_LEFT,
			RSTICK_RIGHT,
			RSTICK_UP,
			RSTICK_DOWN,
			STICK_NUM,
		};
		explicit GamePad(const int id);		//コンストラクタ
		bool on(const int index) const;		//indexのonのboolを返す
		bool down(const int index) const;	//indexのdownのboolを返す
		bool up(const int index) const;		//indexのupのboolを返す
		float axis(const int index) const;	//indexのスティックの値を返す(0~1)
		bool axis_on(const int index) const;
		bool axis_down(const int index) const;
		bool axis_up(const int index) const;
		bool isPresent() const;				//ゲームパッドの有無
		void upDate();						//入力状況の更新
		void Initialize();					//初期化処理
		void Reset();						//入力状況のリセット
	private:
		bool registAxisButton(				//スティックの範囲外処理
			const float axis_threshold_);
		int id_;							//ゲームパッド複数個に対応させるために１つ１つにidを振り分ける
		int button_num;						//ゲームパッドのボタン数
		int axis_num;						//ゲームパッドのスティック数
		int GPadData[14];					//入力データを格納する変数
		std::vector<float> axis_value;		//スティック情報を格納する変数
		float axis_threshold;				//スティックの頂点値z
		std::vector<u_char> button_on;		//buttonのonを格納する変数
		std::vector<u_char> button_down;	//buttonのdownを格納する変数
		std::vector<u_char> button_up;		//buttonのupを格納する変数
		std::vector<u_char> axis_button_on;	//axisのonを格納する変数
		std::vector<u_char> axis_button_down;//axisのdownを格納する変数
		std::vector<u_char> axis_button_up;	//axisのupを格納する変数
		int buttons() const;				//ボタン数を返す関数
		int axes() const;					//スティック数を返す関数
	};
	//キーボード
	class KeyBoard
	{
	public:
		enum Key
		{
			//キーボードの仮装キー設定
			A, S, D, W, Q, E, Z, X, C, R, F, V, T,
			G, B, Y, H, N, U, J, M, I, K, O, L, P,
			SPACE, ENTER, ESCAPE,
			UP, DOWN, LEFT, RIGHT,
		};
		explicit KeyBoard();				//コンストラクタ
		bool up(const int index) const;		//indexのupのboolを返す
		bool down(const int index) const;	//indexのdownのboolを返す
		bool on(const int index) const;		//indexのonのboolを返す
		void upDate();						//入力状況の更新
		void SetWindow(GLFWwindow* w);		//反映させるWindowを登録する
		bool isPresent;						//キーボードの有無(おそらく必要ないがパッドにあるので一応こちらでも準備しておく)
		std::vector<u_char> button_on;		//buttonのonを格納する変数
		std::vector<u_char> button_down;	//buttonのdownを格納する変数
		std::vector<u_char> button_up;		//buttonのupを格納する変数
	private:
		int KeyData[256];					//入力データを格納する変数
		GLFWwindow* nowWindow;				//Window情報を格納する
	};
	//マウス
	class Mouse
	{
	public:
		enum Mouse_
		{
			LEFT,
			RIGHT,
			CENTER,
			BUTTON_4,
			BUTTON_5,
			BUTTON_6,
			BUTTON_7,
			BUTTON_8,
		};
		
		explicit Mouse();					//コンストラクタ
		void upDate();						//入力状況の更新
		void SetWindow(GLFWwindow *w);		//反映させるWindowを登録する
		Vec2 GetPos() const;				//Windowの0,0座標から見た位置を返す
		bool on(const int index) const;		//indexのonのboolを返す
		bool down(const int index) const;	//indexのdownのboolを返す
		bool up(const int index) const;		//indexのupのboolを返す
		bool isPresent;						//マウスの有無の情報
		std::vector<u_char> button_on;		//buttonのonを格納する変数
		std::vector<u_char> button_down;	//buttonのdownを格納する変数
		std::vector<u_char> button_up;		//buttonのupを格納する変数
	private:
		int MouseData[8];					//MauseButtonデータ
		Vec2 position;						//マウスの座標を保存する変数
		GLFWwindow* nowWindow;				//Windowの情報を格納する
	};
	//ゲームパッドとキーボードを区別する
	struct InputData
	{
		int button;		//ゲームパッドのボタン
		int key;		//キーボードのキー
	};
	//class宣言
	//ゲームパッド配列
	std::vector<GamePad> pad;
	//キーボード
	KeyBoard key;
	//マウス
	Mouse mouse;
	//変数
	bool Pad_Connection;				//ゲームパッドの存在有無
	//関数
	void Inputinit(GLFWwindow *w);		//入力初期化
	bool on(const int in_, const int padNum = 0) const;		//押してるとき
	bool down(const int in_, const int padNum = 0) const;	//押したとき
	bool up(const int in_, const int padNum = 0) const;		//あげたとき
	float axis(const int in_, const int padNum = 0) const;
	void upDate();						//入力情報更新
private:
	void ResetInputData();				//入力状態をリセット
	int inputData[256];					//入力データ
	std::vector<Input::GamePad> initGamePad();//ゲームパッド初期化
	KeyBoard initkeyBoard();			//キーボード初期化
	Mouse initMouse();					//マウス初期化
	InputData inputdata[22];			//in分のデータ
};
