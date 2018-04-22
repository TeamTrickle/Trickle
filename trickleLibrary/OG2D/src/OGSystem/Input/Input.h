#pragma once
#include "OGSystem\_OGsystem.h"
class Input
{
public:
	//enum
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
	};
	//class
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
		explicit GamePad(const int id);
		bool on(const int index);
		bool down(const int index);
		bool up(const int index);
		float axis(const int index);
		void upDate();
		void Initialize();
		void Reset();
		bool isPresent() const;
	private:
		bool registAxisButton(const int x_index, const int y_index, const float axis_threshold_);
		int id_;
		int button_num;
		int axis_num;
		int GPadData[14];
		std::vector<float> axis_value;
		bool axis_button;
		float axis_threshold;
		int axis_x_index;
		int axis_y_index;
		std::vector<u_char> button_on;
		std::vector<u_char> button_down;
		std::vector<u_char> button_up;
		std::vector<u_char> axis_button_on;
		std::vector<u_char> axis_button_down;
		std::vector<u_char> axis_button_up;
		int buttons() const;
		int axes() const;
	};
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
		KeyBoard();
		bool up(const int index);
		bool down(const int index);
		bool on(const int index);
		void upDate();
		void SetWindow(GLFWwindow* w);
		GLFWwindow* nowWindow;
		bool isPresent;
		std::vector<u_char> button_on;
		std::vector<u_char> button_down;
		std::vector<u_char> button_up;
	private:
		int KeyData[256];
	};
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
		Vec2 position;
		GLFWwindow* nowWindow;
		Mouse();
		~Mouse();
		void upDate();
		void SetWindow(GLFWwindow *w);
		Vec2 GetPos() const;
		bool on(const int index);
		bool down(const int index);
		bool up(const int index);
		bool isPresent;
		std::vector<u_char> button_on;
		std::vector<u_char> button_down;
		std::vector<u_char> button_up;
	private:
		int MouseData[256];
	};
	struct InputData
	{
		int button;		//ゲームパッドのボタン
		int key;		//キーボードのキー
	};
	//class宣言
	std::vector<GamePad> pad;
	KeyBoard key;
	Mouse mouse;
	//変数
	bool Pad_Connection;
	//関数
	void Inputinit(GLFWwindow *w);
	bool on(int in_, int padNum = 0);
	bool down(int in_, int padNum = 0);
	bool up(int in_, int padNum = 0);
	void upDate();
private:
	void ResetInputData();
	int inputData[256];
	std::vector<Input::GamePad> initGamePad();
	KeyBoard initkeyBoard();
	Mouse initMouse();
	InputData inputdata[14];
};
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
	enum
	{
		AXIS_LEFT_X,		//左スティックX値
		AXIS_LEFT_Y,		//左スティックY値
		AXIS_RIGHT_X,		//右スティックX値
		AXIS_RIGHT_Y,		//右スティックY値
		AXIS_BUTTON_NUM,
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