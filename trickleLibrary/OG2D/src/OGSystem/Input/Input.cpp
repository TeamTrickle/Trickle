#include "Input.h"
//--------------------------------------------------
//@:Input::GamePadclass									
//--------------------------------------------------
void Input::GamePad::Initialize()
{
	this->GPadData[Pad::BUTTON_A] = GLFW_JOYSTICK_1;
	this->GPadData[Pad::BUTTON_B] = GLFW_JOYSTICK_2;
	this->GPadData[Pad::BUTTON_X] = GLFW_JOYSTICK_3;
	this->GPadData[Pad::BUTTON_Y] = GLFW_JOYSTICK_4;
	this->GPadData[Pad::BUTTON_L1] = GLFW_JOYSTICK_5;
	this->GPadData[Pad::BUTTON_R1] = GLFW_JOYSTICK_6;
	this->GPadData[Pad::BUTTON_BACK] = GLFW_JOYSTICK_7;
	this->GPadData[Pad::BUTTON_START] = GLFW_JOYSTICK_8;
	this->GPadData[Pad::BUTTON_L3] = GLFW_JOYSTICK_9;
	this->GPadData[Pad::BUTTON_R3] = GLFW_JOYSTICK_10;
	this->GPadData[Pad::BUTTON_U] = GLFW_JOYSTICK_11;
	this->GPadData[Pad::BUTTON_R] = GLFW_JOYSTICK_12;
	this->GPadData[Pad::BUTTON_D] = GLFW_JOYSTICK_13;
	this->GPadData[Pad::BUTTON_L] = GLFW_JOYSTICK_14;
}
bool Input::GamePad::isPresent() const
{
	return (glfwJoystickPresent(this->id_) == GLFW_TRUE) ? true : false;
}
Input::GamePad::GamePad(const int id) :
	id_(id),
	axis_button(false),
	axis_button_on(AXIS_BUTTON_NUM),
	axis_button_down(AXIS_BUTTON_NUM),
	axis_button_up(AXIS_BUTTON_NUM)
{
	glfwGetJoystickButtons(id_, &button_num);
	glfwGetJoystickAxes(id_, &axis_num);
	std::cout << "GamePadID: " << id_ << " button:" << button_num << " axis:" << axis_num << std::endl;
	button_on.resize(button_num);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(button_num);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(button_num);
	std::fill(std::begin(button_up), std::end(button_up), 0);
	axis_value.resize(axis_num);
	std::fill(std::begin(axis_value), std::end(axis_value), 0.0f);
}
void Input::GamePad::Reset()
{
	std::fill(std::begin(button_on), std::end(button_on), 0);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	std::fill(std::begin(button_up), std::end(button_up), 0);
	std::fill(std::begin(axis_value), std::end(axis_value), 0.0f);
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
}
std::vector<Input::GamePad> Input::initGamePad()
{
	std::vector<Input::GamePad> gamepad_;
	for (int id = GLFW_JOYSTICK_1; id <= GLFW_JOYSTICK_LAST; ++id)
	{
		if (glfwJoystickPresent(id) == GLFW_TRUE)
		{
			gamepad_.emplace_back(id);
		}
	}
	return gamepad_;
}
int Input::GamePad::buttons() const
{
	return button_num;
}
int Input::GamePad::axes() const
{
	return axis_num;
}
bool Input::GamePad::on(const int index)
{
	return button_on[index];
}
bool Input::GamePad::down(const int index)
{
	return button_down[index];
}
bool Input::GamePad::up(const int index)
{
	return button_up[index];
}
float Input::GamePad::axis(const int index)
{
	return axis_value[index];
}
bool Input::GamePad::registAxisButton(const int x_index, const int y_index, const float axis_threshold_)
{
	// 軸番号が範囲外の場合は設定しない
	if ((x_index >= axis_num) || (y_index >= axis_num)) return false;
	axis_button = true;
	axis_threshold = axis_threshold_;
	axis_x_index = x_index;
	axis_y_index = y_index;
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
	return true;
}
void Input::GamePad::upDate()
{
	int button_num_;
	const auto* buttons_ = glfwGetJoystickButtons(id_, &button_num_);
	if (button_num_ > 0)
	{
		for (int i = 0; i < button_num_; ++i)
		{
			button_down[i] = !button_on[i] && buttons_[i];
			button_up[i] = button_on[i] && !buttons_[i];
			button_on[i] = buttons_[i];
		}
	}
	int axis_num;
	const auto* axes = glfwGetJoystickAxes(id_, &axis_num);
	if (axis_num > 0) {
		for (int i = 0; i < axis_num; ++i) {
			axis_value[i] = axes[i];
		}
		if (axis_button) {
			// 簡易ボタン向けの処理
			u_char buttons[AXIS_BUTTON_NUM];
			std::fill(std::begin(buttons), std::end(buttons), 0);
			// 簡易ボタンのpress状態を作成
			// それぞれ軸の値が閾値を超えたらPressとみなす
			// TIPS:右側の比較式の結果(true / false)をそのまま利用
			buttons[AXIS_RIGHT_Y] = axis_value[axis_x_index] > axis_threshold;
			buttons[AXIS_RIGHT_X] = axis_value[axis_x_index] < -axis_threshold;
			buttons[AXIS_LEFT_Y] = axis_value[axis_y_index] > axis_threshold;
			buttons[AXIS_LEFT_X] = axis_value[axis_y_index] < -axis_threshold;
			for (int i = 0; i < AXIS_BUTTON_NUM; ++i) {
				// ボタンの Press / Push / Pull 情報を生成
				// Pushは押した瞬間、Pullは離した瞬間だけtrueになる
				axis_button_down[i] = !axis_button_on[i] && buttons[i];
				axis_button_up[i] = axis_button_on[i] && !buttons[i];
				axis_button_on[i] = buttons[i];
			}
		}
	}
}
void ResetGamePad(std::vector<Input::GamePad>& gamepad_)
{
	for (auto& id : gamepad_)
	{
		if (id.isPresent())
		{
			id.Reset();
		}
	}
}
//--------------------------------------------------
//@:Input::KeyBoardclass									
//--------------------------------------------------
Input::KeyBoard::KeyBoard()
{
	//仮想キーとの組み合わせ
	this->KeyData[Key::A] = GLFW_KEY_A;
	this->KeyData[Key::B] = GLFW_KEY_B;
	this->KeyData[Key::C] = GLFW_KEY_C;
	this->KeyData[Key::D] = GLFW_KEY_D;
	this->KeyData[Key::E] = GLFW_KEY_E;
	this->KeyData[Key::F] = GLFW_KEY_F;
	this->KeyData[Key::G] = GLFW_KEY_G;
	this->KeyData[Key::H] = GLFW_KEY_H;
	this->KeyData[Key::I] = GLFW_KEY_I;
	this->KeyData[Key::J] = GLFW_KEY_J;
	this->KeyData[Key::K] = GLFW_KEY_K;
	this->KeyData[Key::L] = GLFW_KEY_L;
	this->KeyData[Key::N] = GLFW_KEY_N;
	this->KeyData[Key::M] = GLFW_KEY_M;
	this->KeyData[Key::O] = GLFW_KEY_O;
	this->KeyData[Key::P] = GLFW_KEY_P;
	this->KeyData[Key::Q] = GLFW_KEY_Q;
	this->KeyData[Key::R] = GLFW_KEY_R;
	this->KeyData[Key::S] = GLFW_KEY_S;
	this->KeyData[Key::T] = GLFW_KEY_T;
	this->KeyData[Key::U] = GLFW_KEY_U;
	this->KeyData[Key::V] = GLFW_KEY_V;
	this->KeyData[Key::W] = GLFW_KEY_W;
	this->KeyData[Key::X] = GLFW_KEY_X;
	this->KeyData[Key::Y] = GLFW_KEY_Y;
	this->KeyData[Key::Z] = GLFW_KEY_Z;
	this->KeyData[Key::SPACE] = GLFW_KEY_SPACE;
	this->KeyData[Key::ENTER] = GLFW_KEY_ENTER;
	this->KeyData[Key::UP] = GLFW_KEY_UP;
	this->KeyData[Key::DOWN] = GLFW_KEY_DOWN;
	this->KeyData[Key::RIGHT] = GLFW_KEY_RIGHT;
	this->KeyData[Key::LEFT] = GLFW_KEY_LEFT;
	this->KeyData[Key::ESCAPE] = GLFW_KEY_ESCAPE;

	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	this->isPresent = true;
}
Input::KeyBoard Input::initkeyBoard()
{
	KeyBoard keyBoard_;
	keyBoard_.isPresent = true;
	return keyBoard_;
}
void Input::KeyBoard::SetWindow(GLFWwindow* w)
{
	this->nowWindow = w;
}
bool Input::KeyBoard::down(const int index)
{
	return button_down[index];
}
bool Input::KeyBoard::on(const int index)
{
	return button_on[index];
}
bool Input::KeyBoard::up(const int index)
{
	return button_up[index];
}
void Input::KeyBoard::upDate()
{
	for (int i = 0; i < 256; ++i)
	{
		int state = glfwGetKey(this->nowWindow, this->KeyData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = state;
	}
}
void ResetKeyBoard(Input::KeyBoard& keyboard)
{
	std::fill(std::begin(keyboard.button_on), std::end(keyboard.button_on), 0);
	std::fill(std::begin(keyboard.button_down), std::end(keyboard.button_down), 0);
	std::fill(std::begin(keyboard.button_up), std::end(keyboard.button_up), 0);
}
//--------------------------------------------------
//@:Inputclass									
//--------------------------------------------------
void Input::Inputinit(GLFWwindow *w)
{
	//キーボードの初期化
	this->key = this->initkeyBoard();
	this->key.SetWindow(w);
	//ゲームパッドの初期化
	this->pad = this->initGamePad();
	//ゲームパッドが１つ以上存在している場合
	this->Pad_Connection = false;
	for (int i = 0; i < this->pad.size(); ++i)
	{
		this->pad[i].Initialize();
		this->Pad_Connection = true;
	}
	//ゲームパッドとの紐づけ
	{
		this->inputdata[B1].button = Input::GamePad::Pad::BUTTON_A;
		this->inputdata[B2].button = Input::GamePad::Pad::BUTTON_B;
		this->inputdata[B3].button = Input::GamePad::Pad::BUTTON_X;
		this->inputdata[B4].button = Input::GamePad::Pad::BUTTON_Y;

		this->inputdata[L1].button = Input::GamePad::Pad::BUTTON_L1;
		this->inputdata[R1].button = Input::GamePad::Pad::BUTTON_R1;

		this->inputdata[D1].button = Input::GamePad::Pad::BUTTON_BACK;
		this->inputdata[D2].button = Input::GamePad::Pad::BUTTON_START;

		this->inputdata[SL].button = Input::GamePad::Pad::BUTTON_L3;
		this->inputdata[SR].button = Input::GamePad::Pad::BUTTON_R3;

		this->inputdata[CU].button = Input::GamePad::Pad::BUTTON_U;
		this->inputdata[CR].button = Input::GamePad::Pad::BUTTON_R;
		this->inputdata[CD].button = Input::GamePad::Pad::BUTTON_D;
		this->inputdata[CL].button = Input::GamePad::Pad::BUTTON_L;
	}
	//キーボードとの紐づけ
	{
		this->inputdata[B1].key = Input::KeyBoard::Key::Z;
		this->inputdata[B2].key = Input::KeyBoard::Key::X;
		this->inputdata[B3].key = Input::KeyBoard::Key::C;
		this->inputdata[B4].key = Input::KeyBoard::Key::V;

		this->inputdata[L1].key = Input::KeyBoard::Key::Q;
		this->inputdata[R1].key = Input::KeyBoard::Key::E;

		this->inputdata[D1].key = Input::KeyBoard::Key::ENTER;
		this->inputdata[D2].key = Input::KeyBoard::Key::SPACE;

		this->inputdata[SL].key = Input::KeyBoard::Key::B;
		this->inputdata[SR].key = Input::KeyBoard::Key::N;

		this->inputdata[CU].key = Input::KeyBoard::Key::UP;
		this->inputdata[CR].key = Input::KeyBoard::Key::RIGHT;
		this->inputdata[CD].key = Input::KeyBoard::Key::DOWN;
		this->inputdata[CL].key = Input::KeyBoard::Key::LEFT;
	}
}
void Input::upDate()
{
	for (int i = 0; i < this->pad.size(); ++i)
	{
		this->pad[i].upDate();
	}
	this->key.upDate();
}
bool Input::down(int index, int padNum)
{
	//選択された番号のゲームパッドが存在しない場合
	if (!this->Pad_Connection)
	{
		return this->key.down(this->inputdata[index].key);
	}
	return this->key.down(this->inputdata[index].key) || this->pad[padNum].down(this->inputdata[index].button);
}
bool Input::on(int index, int padNum)
{
	//選択された番号のゲームパッドが存在しない場合
	if (!this->Pad_Connection)
	{
		return this->key.on(this->inputdata[index].key);
	}
	return this->key.on(this->inputdata[index].key) || this->pad[padNum].on(this->inputdata[index].button);
}
bool Input::up(int index, int padNum)
{
	//選択された番号のゲームパッドが存在しない場合
	if (!this->Pad_Connection)
	{
		return this->key.up(this->inputdata[index].key);
	}
	return this->key.up(this->inputdata[index].key) || this->pad[padNum].up(this->inputdata[index].button);
}
void Input::ResetInputData()
{
	ResetGamePad(this->pad);
	ResetKeyBoard(this->key);
}