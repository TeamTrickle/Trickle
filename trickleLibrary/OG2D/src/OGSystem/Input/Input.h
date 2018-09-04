/**
*ゲームパッド、キーボード、マウスの入力を扱うclass
*既存GameEngineを使用している場合は自動で生成される
*/
#pragma once
#include "OGSystem\_OGsystem.h"
/**
*namespace In
*簡易引数用
*/
namespace In
{
	/**
	*enum
	*仮装コントローラの入力設定
	*/
	enum
	{
		//!	1
		BUTTON_A,
		//! 2
		BUTTON_B,
		//! 3
		BUTTON_X,
		//! 4
		BUTTON_Y,
		//! 5
		BUTTON_L1,
		//! 6
		BUTTON_R1,
		//! 7
		BUTTON_BACK,
		//! 8
		BUTTON_START,
		//! 9
		BUTTON_L3,
		//! 10
		BUTTON_R3,
		//! 11
		BUTTON_U,
		//! 12
		BUTTON_R,
		//! 13
		BUTTON_D,
		//! 14
		BUTTON_L,
	};
	enum AXIS
	{
		//! 左スティックX値
		AXIS_LEFT_X,
		//! 左スティックY値
		AXIS_LEFT_Y,
		//! 右スティックX値
		AXIS_RIGHT_X,
		//! 右スティックY値
		AXIS_RIGHT_Y,
		//!	R2
		AXIS_R2,
		//! L2
		AXIS_L2,
		AXIS_BUTTON_NUM,
	};
	enum
	{
		//! 左スティック左入力
		LSTICK_LEFT,
		//! 左スティック右入力
		LSTICK_RIGHT,
		//! 左スティック上入力
		LSTICK_UP,
		//! 左スティック下入力
		LSTICK_DOWN,
		//! 右スティック左入力
		RSTICK_LEFT,
		//! 右スティっク右入力
		RSTICK_RIGHT,
		//! 右スティック上入力	
		RSTICK_UP,
		//! 右スティック下入力
		RSTICK_DOWN,
		//! R2
		BUTTON_R2,
		//! L2
		BUTTON_L2,
		//! スティック数
		STICK_NUM,
	};
	/**
	*enum
	*仮想入力
	*/
	enum
	{
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
		L2,
		R2,
	};
	/**
	*enum
	*キーボード入力
	*/
	enum
	{
		A, S, D, W, Q, E, Z, X, C, R, F, V, T,
		G, B, Y, H, N, U, J, M, I, K, O, L, P,
		SPACE, ENTER, ESCAPE,
		UP, DOWN, LEFT, RIGHT,
	};
}
/**
*namespace Mouse
*マウス用簡易引数
*/
namespace Mouse
{
	enum
	{
		//! 左
		LEFT,
		//! 右
		RIGTH,
		//! 中心
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
	/**
	*enum in
	*入力用仮想入力
	*/
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
		L2,
		R2,
	};
	/**
	*@brief	:ゲームパッド入力
	*/
	class GamePad
	{
	public:
		/**
		*enum Pad
		*仮装コントローラの入力設定
		*/
		enum Pad
		{

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
		/**
		*enum AXIS
		*仮装コントローラの入力設定
		*/
		enum AXIS {
			//! 左スティックX値
			AXIS_LEFT_X,
			//! 左スティックY値
			AXIS_LEFT_Y,
			//! 右スティックX値
			AXIS_RIGHT_X,
			//! 右スティックY値
			AXIS_RIGHT_Y,
			//!	R2
			AXIS_R2,
			//! L2
			AXIS_L2,
			AXIS_BUTTON_NUM,
		};
		/**
		*enum AXISBUTTON
		*仮装コントローラの入力設定
		*/
		enum AXISBUTTON
		{
			//! 左スティック左入力
			LSTICK_LEFT,
			//! 左スティック右入力
			LSTICK_RIGHT,
			//! 左スティック上入力
			LSTICK_UP,
			//! 左スティック下入力
			LSTICK_DOWN,
			//! 右スティック左入力
			RSTICK_LEFT,
			//! 右スティっク右入力
			RSTICK_RIGHT,
			//! 右スティック上入力	
			RSTICK_UP,
			//! 右スティック下入力
			RSTICK_DOWN,
			//! R2
			BUTTON_R2,
			//! L2
			BUTTON_L2,
			//! スティック数
			STICK_NUM,
		};
		/**
		*@brief	:constructor
		*@param	:int id ゲームパッド番号
		*/
		explicit GamePad(const int id);
		/**
		*@brief	:押している判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	:押した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	:離した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	:全てのdown入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	:全てのon入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	:全てのup入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		/**
		*@brief	:指定値のスティックの傾きを返す
		*@param	:int index スティック指定
		*@return:float 傾き度(0~1)
		*/
		float axis(const int index) const;
		/**
		*@brief	:指定スティックの押し状態を返す
		*@param	:int index スティック指定
		*@return:bool 指定側に倒れていればtrue
		*/
		bool axis_on(const int index) const;
		/**
		*@brief	:指定スティックの押し状態を返す
		*@param	:int index スティック指定
		*@return:bool 指定側に倒された瞬間であればtrue
		*/
		bool axis_down(const int index) const;
		/**
		*@brief	:指定スティックの押し状態を返す
		*@param	:int index スティック指定
		*@return:bool 指定側から上がった瞬間であればtrue
		*/
		bool axis_up(const int index) const;
		/**
		*@brief	:ゲームパッドの有無を返す
		*@return:bool 存在すればtrue
		*/
		bool isPresent() const;
		/**
		*@brief	:入力状況の更新
		*/
		void upDate();
		/**
		*@brief	:各値の初期化
		*/
		void Initialize();
		/**
		*@brief	:入力状態のリセット
		*/
		void Reset();
		/**
		*@brief	:スティックの範囲外処理
		*@param	:float axis_threshold_ 区切る値
		*@return:成功true
		*/
		bool registAxisButton(
			const float axis_threshold_);
		/**
		*@brief	:ゲームパッド名を返す
		*@return:char* ゲームパッド名
		*/
		const char* GetName() const;
	private:
		//! ゲームパッド複数個に対応させるために１つ１つにidを振り分ける
		int id_;
		//! ゲームパッドのボタン数
		int button_num;
		//! ゲームパッドのスティック数
		int axis_num;
		//! 入力データを格納する変数
		int GPadData[14];
		//! スティック情報を格納する変数
		std::vector<float> axis_value;
		//! スティックの頂点値
		float axis_threshold;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//! buttonのupを格納する変数
		std::vector<u_char> button_up;
		//! axisのonを格納する変数
		std::vector<u_char> axis_button_on;
		//! axisのdownを格納する変数
		std::vector<u_char> axis_button_down;
		//! axisのupを格納する変数
		std::vector<u_char> axis_button_up;
		//! コントローラ名
		const char* name;
		/**
		*@brief	:ボタン数を返す
		*@return:int ボタン数
		*/
		int buttons() const;
		/**
		*@brief	:スティック数を返す
		*@return:スティック数
		*/
		int axes() const;
	};
	/**
	*@brief	:キーボード入力
	*/
	class KeyBoard
	{
	public:
		/**
		*enum Key
		*キーボードの仮装キー設定
		*/
		enum Key
		{
			A, S, D, W, Q, E, Z, X, C, R, F, V, T,
			G, B, Y, H, N, U, J, M, I, K, O, L, P,
			SPACE, ENTER, ESCAPE,
			UP, DOWN, LEFT, RIGHT,
		};
		/**
		*@brief	:constructor
		*/
		explicit KeyBoard();
		/**
		*@brief	:離した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	:押した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	:押している判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	:全てのdown入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	:全てのon入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	:全てのup入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		/**
		*@brief	:入力状況の更新
		*/
		void upDate();
		/**
		*@brief	:反映させるWindowを登録する
		*@param :GLFWWindow* w Windowのポインタ
		*/
		void SetWindow(GLFWwindow* w);
		//! キーボードの有無
		bool isPresent;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//!buttonのupを格納する変数
		std::vector<u_char> button_up;
	private:
		//! 入力データを格納する変数
		int KeyData[256];
		//! Window情報を格納する
		GLFWwindow* nowWindow;
	};
	/**
	*@brief	:マウス入力
	*/
	class Mouse
	{
	public:
		/**
		*enum Mouse_
		*マウスの入力設定
		*/
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
		/**
		*@brief	:constructor
		*/
		explicit Mouse();
		/**
		*@brief	:入力状況の更新
		*/
		void upDate();
		/**
		*@brief	:反映させるWindowを登録する
		*@param	:GLFWWindow* w Windowのポインタ
		*/
		void SetWindow(GLFWwindow *w);
		/**
		*@brief	:Windowからのマウスの位置を返す
		*@return:Vec2 マウスの位置
		*/
		Vec2 GetPos() const;
		/**
		*@brief	:押している判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	:押した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	:離した瞬間の判定を返す
		*@param :int index 判定を行いたい入力番号
		*@return:bool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	:全てのdown入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	:全てのon入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	:全てのup入力のうち１つでも判定があるか調べる
		*@return:1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		//! マウスの有無
		bool isPresent;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//! buttonのupを格納する変数
		std::vector<u_char> button_up;
	private:
		//! MauseButtonデータ
		int MouseData[8];
		//! マウスの座標を保存する変数
		Vec2 position;
		//! Windowの情報を格納する
		GLFWwindow* nowWindow;
	};
	/**
	*@brief	:ゲームパッドとキーボードを区別する
	*/
	struct InputData
	{
		//! ゲームパッドのボタン
		int button;
		//! キーボードのキー
		int key;
	};
	//class宣言
	//! ゲームパッド配列
	std::vector<GamePad> pad;
	//! キーボード
	KeyBoard key;
	//! マウス
	Mouse mouse;
	//変数
	//! ゲームパッドの存在有無
	bool Pad_Connection;
	//関数
	/**
	*@brief	:入力初期化
	*@param	:GLFWWindow* w 指定するWindowのポインタ
	*/
	void Inputinit(GLFWwindow *w);
	/**
	*@brief	:押している判定を返す
	*@param :int index 判定を行いたい入力番号
	*@param	:int padNum 判定を行うゲームパッドの番号
	*@return:bool 押していればtrue
	*/
	bool on(const int index, const int padNum = 0) const;
	/**
	*@brief	:押した瞬間の判定を返す
	*@param :int index 判定を行いたい入力番号
	*@param	:int padNum 判定を行うゲームパッドの番号
	*@return:bool 押した瞬間であればtrue
	*/
	bool down(const int index, const int padNum = 0) const;
	/**
	*@brief	:離した瞬間の判定を返す
	*@param :int index 判定を行いたい入力番号
	*@param	:int padNum 判定を行うゲームパッドの番号
	*@return:bool 離した瞬間であればtrue
	*/
	bool up(const int index, const int padNum = 0) const;
	/**
	*@brief	:指定値のスティックの傾きを返す
	*@param	:int index スティック指定
	*@param	:int padNum 判定を行うゲームパッドの番号
	*@return:float 傾き度(0~1)
	*/
	float axis(const int index, const int padNum = 0) const;
	/**
	*@brief	:全てのゲームパッドのスティックの傾き範囲を制限する
	*@param	:float regist 指定値
	*/
	void registAxis(const float regist);
	/**
	*@brief	:入力状況の更新
	*/
	void upDate();
	/**
	*@brief	:全てのdown入力のうち１つでも判定があるか調べる
	*@return:1つ以上入力されているとtrue
	*/
	bool EitherDown() const;
	/**
	*@brief	:全てのon入力のうち１つでも判定があるか調べる
	*@return:1つ以上入力されているとtrue
	*/
	bool EitherOn() const;
	/**
	*@brief	:全てのup入力のうち１つでも判定があるか調べる
	*@return:1つ以上入力されているとtrue
	*/
	bool EitherUp() const;
	/**
	*@brief	:入力状態をリセット
	*/
	void ResetInputData();
private:
	//! 入力データ
	int inputData[256];
	//! ゲームパッド初期化
	std::vector<Input::GamePad> initGamePad();
	//! キーボード初期化
	KeyBoard initkeyBoard();
	//! マウス初期化
	Mouse initMouse();
	//! in分のデータ
	InputData inputdata[24];
};
