#include "Input.h"
//--------------------------------------------------
//@:Input::GamePadclass									
//--------------------------------------------------
void Input::GamePad::Initialize()
{
	//入力値をenumと配列で管理
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
	//Joystickが存在するかどうか
	return (glfwJoystickPresent(this->id_) == GLFW_TRUE) ? true : false;
}
Input::GamePad::GamePad(const int id) :
	id_(id)
{
	//GamePadが存在するかどうか、ボタン数スティック数はいくつかの計測とその分の要素の確保
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
	axis_button_on.resize(STICK_NUM);
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	axis_button_down.resize(STICK_NUM);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	axis_button_up.resize(STICK_NUM);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
	axis_threshold = 1.f;
}
void Input::GamePad::Reset()
{
	//確保した要素の初期化
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
	//GamePadが存在する分だけ生成する
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
bool Input::GamePad::on(const int index) const
{
	return button_on[index];
}
bool Input::GamePad::down(const int index) const
{
	return button_down[index];
}
bool Input::GamePad::up(const int index) const
{
	return button_up[index];
}
float Input::GamePad::axis(const int index) const
{
	return axis_value[index];
}
bool Input::GamePad::axis_on(const int index) const
{
	return this->axis_button_on[index];
}
bool Input::GamePad::axis_down(const int index) const
{
	return this->axis_button_down[index];
}
bool Input::GamePad::axis_up(const int index) const
{
	return this->axis_button_up[index];
}
bool Input::GamePad::registAxisButton(const float axis_threshold_)
{
	axis_threshold = axis_threshold_;
	return true;
}
void Input::GamePad::upDate()
{
	//現在の入力状況と1回前の入力状況からtrueかfalseをいれる
	int button_num_;
	//GamePadのButtonの状況を取得
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
	//GamePadのJoyStickの状態を取得
	const auto* axes = glfwGetJoystickAxes(id_, &axis_num);
	if (axis_num > 0) {
		for (int i = 0; i < axis_num; ++i) {
			axis_value[i] = axes[i];
		}
		u_char buttons[STICK_NUM];
		std::fill(std::begin(buttons), std::end(buttons), 0);
		buttons[LSTICK_LEFT] = axis_value[AXIS_LEFT_X] <= -axis_threshold;
		buttons[LSTICK_RIGHT] = axis_value[AXIS_LEFT_X] >= axis_threshold;
		buttons[LSTICK_UP] = axis_value[AXIS_LEFT_Y] >= axis_threshold;
		buttons[LSTICK_DOWN] = axis_value[AXIS_LEFT_Y] <= -axis_threshold;

		buttons[RSTICK_LEFT] = axis_value[AXIS_RIGHT_X] <= -axis_threshold;
		buttons[RSTICK_RIGHT] = axis_value[AXIS_RIGHT_X] >= axis_threshold;
		buttons[RSTICK_UP] = axis_value[AXIS_RIGHT_Y] >= axis_threshold;
		buttons[RSTICK_DOWN] = axis_value[AXIS_RIGHT_Y] <= -axis_threshold;
		for (int i = 0; i < STICK_NUM; ++i)
		{
			axis_button_down[i] = !axis_button_on[i] && buttons[i];
			axis_button_up[i] = axis_button_on[i] && !buttons[i];
			axis_button_on[i] = buttons[i];
		}
	}
}
void ResetGamePad(std::vector<Input::GamePad>& gamepad_)
{
	//入力状況を初期化する
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
	//キーボードを１つ生成
	KeyBoard keyBoard_;
	keyBoard_.isPresent = true;
	return keyBoard_;
}
void Input::KeyBoard::SetWindow(GLFWwindow* w)
{
	this->nowWindow = w;
}
bool Input::KeyBoard::down(const int index) const
{
	return button_down[index];
}
bool Input::KeyBoard::on(const int index) const
{
	return button_on[index];
}
bool Input::KeyBoard::up(const int index) const
{
	return button_up[index];
}
void Input::KeyBoard::upDate()
{
	for (int i = 0; i < 256; ++i)
	{
		//キーボードの入力状況を取得
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
//@:Mouseclass									
//--------------------------------------------------
Input::Mouse::Mouse()
{
	this->MouseData[Mouse_::LEFT] = GLFW_MOUSE_BUTTON_1;
	this->MouseData[Mouse_::RIGHT] = GLFW_MOUSE_BUTTON_2;
	this->MouseData[Mouse_::CENTER] = GLFW_MOUSE_BUTTON_3;
	this->MouseData[Mouse_::BUTTON_4] = GLFW_MOUSE_BUTTON_4;
	this->MouseData[Mouse_::BUTTON_5] = GLFW_MOUSE_BUTTON_5;
	this->MouseData[Mouse_::BUTTON_6] = GLFW_MOUSE_BUTTON_6;
	this->MouseData[Mouse_::BUTTON_7] = GLFW_MOUSE_BUTTON_7;
	this->MouseData[Mouse_::BUTTON_8] = GLFW_MOUSE_BUTTON_8;
	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	this->isPresent = true;
}
Input::Mouse Input::initMouse()
{
	Mouse mouse_;
	mouse_.isPresent = true;
	return mouse_;
}
void Input::Mouse::SetWindow(GLFWwindow* w)
{
	this->nowWindow = w;
}
bool Input::Mouse::on(const int index) const
{
	return button_on[index];
}
bool Input::Mouse::down(const int index) const
{
	return button_down[index];
}
bool Input::Mouse::up(const int index) const
{
	return button_up[index];
}
void Input::Mouse::upDate()
{
	for (int i = 0; i < 256; ++i)
	{
		//マウスの入力状況を取得
		int state = glfwGetMouseButton(this->nowWindow, this->MouseData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = state;
	}
}
Vec2 Input::Mouse::GetPos() const
{
	double x, y;
	glfwGetCursorPos(this->nowWindow, &x, &y);
	return Vec2((float)x, (float)y);
}
void ResetMouse(Input::Mouse& mouse)
{
	std::fill(std::begin(mouse.button_on), std::end(mouse.button_on), 0);
	std::fill(std::begin(mouse.button_down), std::end(mouse.button_down), 0);
	std::fill(std::begin(mouse.button_up), std::end(mouse.button_up), 0);
}
//--------------------------------------------------
//@:Inputclass									
//--------------------------------------------------
void Input::Inputinit(GLFWwindow *w)
{
	//キーボードの初期化
	this->key = this->initkeyBoard();
	this->key.SetWindow(w);
	//マウスの初期化
	this->mouse = this->initMouse();
	this->mouse.SetWindow(w);
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

		this->inputdata[LU].button = Input::GamePad::AXISBUTTON::LSTICK_UP;
		this->inputdata[LD].button = Input::GamePad::AXISBUTTON::LSTICK_DOWN;
		this->inputdata[LL].button = Input::GamePad::AXISBUTTON::LSTICK_LEFT;
		this->inputdata[LR].button = Input::GamePad::AXISBUTTON::LSTICK_RIGHT;

		this->inputdata[RU].button = Input::GamePad::AXISBUTTON::RSTICK_UP;
		this->inputdata[RD].button = Input::GamePad::AXISBUTTON::RSTICK_DOWN;
		this->inputdata[RL].button = Input::GamePad::AXISBUTTON::RSTICK_LEFT;
		this->inputdata[RR].button = Input::GamePad::AXISBUTTON::RSTICK_RIGHT;
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

		this->inputdata[LU].key = Input::KeyBoard::Key::W;
		this->inputdata[LD].key = Input::KeyBoard::Key::S;
		this->inputdata[LL].key = Input::KeyBoard::Key::A;
		this->inputdata[LR].key = Input::KeyBoard::Key::D;

		this->inputdata[RU].key = Input::KeyBoard::Key::I;
		this->inputdata[RD].key = Input::KeyBoard::Key::K;
		this->inputdata[RL].key = Input::KeyBoard::Key::J;
		this->inputdata[RR].key = Input::KeyBoard::Key::L;
	}
}
void Input::upDate()
{
	for (int i = 0; i < this->pad.size(); ++i)
	{
		this->pad[i].upDate();
	}
	this->key.upDate();
	this->mouse.upDate();
}
bool Input::down(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key.down(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key.down(this->inputdata[index].key) || this->pad[padNum].down(this->inputdata[index].button);
	}
	return this->key.down(this->inputdata[index].key) || this->pad[padNum].axis_down(this->inputdata[index].button);
	//return this->key.down(this->inputdata[index].key) || index < 14 ? this->pad[padNum].down(this->inputdata[index].button) : this->pad[padNum].axis_down(this->inputdata[index].button);
}
bool Input::on(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key.on(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key.on(this->inputdata[index].key) || this->pad[padNum].on(this->inputdata[index].button);
	}
	return this->key.on(this->inputdata[index].key) || this->pad[padNum].axis_on(this->inputdata[index].button);
	//return this->key.on(this->inputdata[index].key) || index < 14 ? this->pad[padNum].on(this->inputdata[index].button) : this->pad[padNum].axis_on(this->inputdata[index].button);
}
bool Input::up(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key.up(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key.up(this->inputdata[index].key) || this->pad[padNum].up(this->inputdata[index].button);
	}
	return this->key.up(this->inputdata[index].key) || this->pad[padNum].axis_up(this->inputdata[index].button);
	//return this->key.up(this->inputdata[index].key) || index < 14 ? this->pad[padNum].up(this->inputdata[index].button) : this->pad[padNum].axis_up(this->inputdata[index].button);
}
float Input::axis(const int index, const int padNum) const
{
	float ang = 0.f;
	switch (index)
	{
	case In::AXIS::AXIS_LEFT_X:
		if (this->key.on(KeyBoard::A))
		{
			ang -= 1.0f;
		}
		if (this->key.on(KeyBoard::D))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_LEFT_Y:
		if (this->key.on(KeyBoard::W))
		{
			ang += 1.0f;
		}
		if (this->key.on(KeyBoard::S))
		{
			ang -= 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_X:
		if (this->key.on(KeyBoard::J))
		{
			ang -= 1.0f;
		}
		if (this->key.on(KeyBoard::L))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_Y:
		if (this->key.on(KeyBoard::I))
		{
			ang += 1.0f;
		}
		if (this->key.on(KeyBoard::K))
		{
			ang -= 1.0f;
		}
		break;
	default:
		break;
	}
	if (glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		if (this->pad[padNum].axis(index) != 0.f)
		{
			ang = this->pad[padNum].axis(index);
		}
	}
	return ang;
}
void Input::ResetInputData()
{
	ResetGamePad(this->pad);
	ResetKeyBoard(this->key);
	ResetMouse(this->mouse);
}
void Input::registAxis(const float regist)
{
	for (auto id = this->pad.begin(); id != this->pad.end(); ++id)
	{
		id->registAxisButton(regist);
	}
}