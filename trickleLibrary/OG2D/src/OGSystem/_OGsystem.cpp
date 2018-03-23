#include "_OGsystem.h"
namespace OG {
	float ToRadian(const  float  degree_)
	{
		return  degree_ * PI / 180.0f;
	}
	void MulitMatrixf(GLfloat*src1, GLfloat*src2, GLfloat*dst) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				dst[y * 4 + x] = src2[y * 4] * src1[x] + src2[y * 4 + 1] * src1[x + 4] + src2[y * 4 + 2] * src1[x + 8] + src2[y * 4 + 3] * src1[x + 12];
			}
		}
	}
	void Normalize(GLfloat *v) {
		float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		if (m > 0.0f) { m = 1.0f / m; }
		else { m = 0.0f; }
		v[0] *= m;
		v[1] *= m;
		v[2] *= m;
	}
	void Cross(float* src1, float* src2, float* dst) {
		dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
		dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
		dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
	}
	float inner(Vec2 _v1, Vec2 _v2) {
		return ((_v1.x * _v2.x) + (_v1.y*_v2.y));
	}
	float inner(float _x1, float _y1, float _x2, float _y2) {
		return ((_x1 * _x2) + (_y1*_y2));
	}
	float inner(int _x1, int _y1, int _x2, int _y2) {
		return (float)((_x1 * _x2) + (_y1*_y2));
	}
	float cross(Vec2 _v1, Vec2 _v2) {
		return ((_v1.x * _v2.x) - (_v1.y*_v2.y));
	}
	float cross(float _x1, float _y1, float _x2, float _y2) {
		return ((_x1 * _x2) - (_y1*_y2));
	}
	float cross(int _x1, int _y1, int _x2, int _y2) {
		return (float)((_x1 * _x2) - (_y1*_y2));
	}
	float doubleinner(Vec2 _v) {
		return inner(_v, _v);
	}
	float doubleinner(float _x, float _y) {
		return inner(_x, _y, _x, _y);
	}
	float doubleinner(int _x, int _y) {
		return inner(_x, _y, _x, _y);
	}
	void LineHitDraw(Vec2 _b[4]) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex2f(_b[0].x, _b[0].y);
		glVertex2f(_b[1].x, _b[1].y);

		glVertex2f(_b[1].x, _b[1].y);
		glVertex2f(_b[2].x, _b[2].y);

		glVertex2f(_b[2].x, _b[2].y);
		glVertex2f(_b[3].x, _b[3].y);

		glVertex2f(_b[3].x, _b[3].y);
		glVertex2f(_b[0].x, _b[0].y);
		glEnd();
	}
	float get_distance(float x, float y, float x1, float y1, float x2, float y2) {
		float dx, dy, a, b, t, tx, ty;
		float distance;
		dx = (x2 - x1);
		dy = (y2 - y1);
		a = dx*dx + dy*dy;
		b = dx * (x1 - x) + dy * (y1 - y);
		t = -b / a;
		if (t < 0) t = 0;
		if (t > 1) t = 1;
		tx = x1 + dx * t;
		ty = y1 + dy * t;
		distance = sqrt((x - tx)*(x - tx) + (y - ty)*(y - ty));
		return distance;
	}
	void _Rotate(float _ang, Vec2 _b[4])
	{
		//ラジアンの値に変更
		float tora = OG::ToRadian(_ang);
		//原点を指定
		Vec2 Center((_b[2].x + _b[0].x) / 2, (_b[2].y + _b[0].y) / 2);
		//回転軸の原点の値を導く
		GLfloat v[]
		{
			_b[0].x - Center.x,_b[0].y - Center.y,
			_b[1].x - Center.x,_b[1].y - Center.y,
			_b[2].x - Center.x,_b[2].y - Center.y,
			_b[3].x - Center.x,_b[3].y - Center.y,
		};
		//回転行列の生成
		GLfloat ma[4] = {
			cosf(tora),-sinf(tora),
			sinf(tora),cosf(tora),
		};
		//回転行列の計算
		_b[0].x = (v[0] * ma[0]) + (v[1] * ma[1]);
		_b[0].y = (v[0] * ma[2]) + (v[1] * ma[3]);

		_b[1].x = (v[2] * ma[0]) + (v[3] * ma[1]);
		_b[1].y = (v[2] * ma[2]) + (v[3] * ma[3]);

		_b[2].x = (v[4] * ma[0]) + (v[5] * ma[1]);
		_b[2].y = (v[4] * ma[2]) + (v[5] * ma[3]);

		_b[3].x = (v[6] * ma[0]) + (v[7] * ma[1]);
		_b[3].y = (v[6] * ma[2]) + (v[7] * ma[3]);

		//回転軸の原点の移動した分を元に戻す
		_b[0].x = _b[0].x + Center.x;
		_b[0].y = _b[0].y + Center.y;

		_b[1].x = _b[1].x + Center.x;
		_b[1].y = _b[1].y + Center.y;

		_b[2].x = _b[2].x + Center.x;
		_b[2].y = _b[2].y + Center.y;

		_b[3].x = _b[3].x + Center.x;
		_b[3].y = _b[3].y + Center.y;
	}
}
void FPS::Initialize() {
	fps = 0.f;
	glfwSetTime(0.0);
	count = 0;
	lastTime = (float)glfwGetTime();
}
void FPS::Update() {
	if (count == 60) {
		fps = count / ((float)glfwGetTime() - lastTime);
		std::cout << fps << std::endl;
		count = 0;
		lastTime = (float)glfwGetTime();
	}
	count++;
}
Window::Window()
{
	this->_widht = 640;
	this->_height = 480;
	this->_Screen = false;
	this->_Name = "NoName";
}
Window::Window(int wi, int he, char* name, bool screen) 
	:_widht(wi)
	, _height(he)
	, _Name(name)
	, _Screen(screen)
	{
	if (_Screen) {
		window = glfwCreateWindow(_widht, _height, _Name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(_widht, _height, _Name, NULL, NULL);
	}
	if (!window) {
		glfwTerminate();
		return;
	}
}
Window::~Window()
{

}

void Window::createWindow(int wi, int he, char* name, bool screen)
{
	this->_widht = wi;
	this->_height = he;
	this->_Name = name;
	this->_Screen = screen;
	if (this->_Screen) {
		this->window = glfwCreateWindow(this->_widht, this->_height, this->_Name, glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		this->window = glfwCreateWindow(this->_widht, this->_height, this->_Name, NULL, NULL);
	}
	if (!this->window) {
		glfwTerminate();
		return;
	}
}