#include "OGsystem.h"
//3D描画確認用
int Box3D::IsOdd(int n, int a, int b) {
	if (n % 2 == 0) {
		return a;
	}
	return b;
}
int Box3D::InOdd(int n, int a, int b) {
	if ((n / 2) % 2 == 0) {
		return a;
	}
	return b;
}
int Box3D::IfOdd(int n, int a, int b) {
	if ((n / 4) % 2 == 0) {
		return a;
	}
	return b;
}
void Box3D::LinesDraw(Box3D &b) {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	GLfloat linebox[] = { b.x,b.y,b.z,b.w,b.h,b.d };
	for (int i = 0; i < 8; ++i) {
		glVertex3f(linebox[IsOdd(i, 0, 3)], linebox[InOdd(i, 1, 4)], linebox[IfOdd(i, 2, 5)]);
	}
	for (int i = 0; i < 8; ++i) {
		glVertex3f(linebox[IfOdd(i, 0, 3)], linebox[InOdd(i, 1, 4)], linebox[IsOdd(i, 2, 5)]);
	}
	for (int i = 0; i < 8; ++i) {
		glVertex3f(linebox[InOdd(i, 0, 3)], linebox[IsOdd(i, 1, 4)], linebox[IfOdd(i, 2, 5)]);
	}
	glEnd();
	glFlush();
}
//長方形×長方形
bool CollisionBox::hitBox(CollisionBox b)
{
	//頂点情報のセット
	Vec2 _ver[4] = {
		{ b.hitBase.x,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.h - 1 },
		{ b.hitBase.x,b.hitBase.h - 1 }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
		{ hitBase.w - 1,hitBase.y },
		{ hitBase.w - 1,hitBase.h - 1 },
		{ hitBase.x,hitBase.h - 1 }
	};
	//回転の適用
	OG::_Rotate(angle, _v);
	OG::_Rotate(b.angle, _ver);
	//どちらかの範囲内に相手の頂点が存在する場合TRUEを返す
	for (int i = 0; i < 4; ++i) {
		if ((((_v[1].x - _v[0].x)*(_ver[i].y - _v[0].y)) - ((_ver[i].x - _v[0].x)*(_v[1].y - _v[0].y))) >= 0 &&
			(((_v[2].x - _v[1].x)*(_ver[i].y - _v[1].y)) - ((_ver[i].x - _v[1].x)*(_v[2].y - _v[1].y))) >= 0 &&
			(((_v[3].x - _v[2].x)*(_ver[i].y - _v[2].y)) - ((_ver[i].x - _v[2].x)*(_v[3].y - _v[2].y))) >= 0 &&
			(((_v[0].x - _v[3].x)*(_ver[i].y - _v[3].y)) - ((_ver[i].x - _v[3].x)*(_v[0].y - _v[3].y))) >= 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 4; ++i) {
		if ((((_ver[1].x - _ver[0].x)*(_v[i].y - _ver[0].y)) - ((_v[i].x - _ver[0].x)*(_ver[1].y - _ver[0].y))) >= 0 &&
			(((_ver[2].x - _ver[1].x)*(_v[i].y - _ver[1].y)) - ((_v[i].x - _ver[1].x)*(_ver[2].y - _ver[1].y))) >= 0 &&
			(((_ver[3].x - _ver[2].x)*(_v[i].y - _ver[2].y)) - ((_v[i].x - _ver[2].x)*(_ver[3].y - _ver[2].y))) >= 0 &&
			(((_ver[0].x - _ver[3].x)*(_v[i].y - _ver[3].y)) - ((_v[i].x - _ver[3].x)*(_ver[0].y - _ver[3].y))) >= 0)
		{
			return true;
		}
	}
	return false;
}
//長方形×円
bool CollisionBox::hitCircle(CollisionCircle b)
{
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ b.hitBase.CenterX,b.hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
		{ hitBase.w - 1,hitBase.y },
		{ hitBase.w - 1,hitBase.h - 1 },
		{ hitBase.x,hitBase.h - 1 }
	};
	//Box型の回転の適用
	OG::_Rotate(angle, _v);
	//円の中に頂点が存在する場合TRUEを返す
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= b.hitBase.r*b.hitBase.r)
	{
		return true;
	}
	//円の中に線分が存在する場合TRUEを返す
	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<b.hitBase.r)
			return true;
	}
	return false;
}
//円×長方形
bool CollisionCircle::hitBox(CollisionBox b)
{
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ hitBase.CenterX,hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ b.hitBase.x,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.h - 1 },
		{ b.hitBase.x,b.hitBase.h - 1 }
	};
	//Box型の回転の適用
	OG::_Rotate(b.angle, _v);
	//円の中に頂点が存在する場合TRUEを返す
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= hitBase.r*hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= hitBase.r*hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= hitBase.r*hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= hitBase.r*hitBase.r)
	{
		return true;
	}
	//円の中に線分が存在する場合TRUEを返す
	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<hitBase.r)
			return true;
	}
	return false;
}
//円×円
bool CollisionCircle::hitCircle(CollisionCircle b)
{
	//円の範囲内に相手の円の範囲が存在する場合TRUEを返す
	if (((b.hitBase.CenterX - this->hitBase.CenterX)*
		(b.hitBase.CenterX - this->hitBase.CenterX)) +
		((b.hitBase.CenterY - this->hitBase.CenterY)*
		(b.hitBase.CenterY - this->hitBase.CenterY)) <=
			(b.hitBase.r + this->hitBase.r)*(b.hitBase.r + this->hitBase.r))
	{
		return true;
	}
	return false;
}
//描画確認用(多分使わない)
void CollisionBox::hitdraw() {

}

void CollisionBox::Rotate(float _angle) {
	//回転の値を格納
	this->angle = _angle;
}

KeyInput::KeyInput()
{
	//入力タイムの初期化
	for (int i = 0; i < 256; ++i) {
		this->KeyInputDownTime[i] = 0;
		this->KeyInputOnTime[i] = 0;
		this->KeyInputUpTime[i] = 0;
	}
}
bool KeyInput::KeyInputDown(GLFWwindow *w, int key) {
	if (glfwGetKey(w, key)) {
		this->KeyInputDownTime[key]++;
	}
	else if (this->KeyInputDownTime[key] != 0) {
		this->KeyInputDownTime[key] = 0;
	}
	if (this->KeyInputDownTime[key] == 1) {
		return true;
	}
	return false;
}
bool KeyInput::KeyInputOn(GLFWwindow *w, int key) {
	if (glfwGetKey(w, key)) {
		this->KeyInputOnTime[key]++;
		return true;
	}
	else if (this->KeyInputOnTime[key] != 0) {
		this->KeyInputOnTime[key] = 0;
	}
	if (this->KeyInputOnTime[key] == 1) {
	}
	return false;
}
bool KeyInput::KeyInputUp(GLFWwindow *w, int key) {
	if (glfwGetKey(w, key)) {
		this->KeyInputUpTime[key]++;
	}
	else if (this->KeyInputUpTime[key] != 0) {
		this->KeyInputUpTime[key] = 0;
		return true;
	}
	if (this->KeyInputUpTime[key] == 1) {
	}
	return false;
}

void Input::Initialize(GLFWwindow *w)
{
	//入力タイムの初期化
	for (int i = 0; i < 256; ++i) {
		Input::KeyInputDownTime[i] = 0;
		Input::KeyInputOnTime[i] = 0;
		Input::KeyInputUpTime[i] = 0;
	}
	//仮想キーとの組み合わせ
	Input::nowWindow = w;
	Input::KeyData[Input::A] = GLFW_KEY_A;
	Input::KeyData[Input::B] = GLFW_KEY_B;
	Input::KeyData[Input::C] = GLFW_KEY_C;
	Input::KeyData[Input::D] = GLFW_KEY_D;
	Input::KeyData[Input::E] = GLFW_KEY_E;
	Input::KeyData[Input::F] = GLFW_KEY_F;
	Input::KeyData[Input::G] = GLFW_KEY_G;
	Input::KeyData[Input::H] = GLFW_KEY_H;
	Input::KeyData[Input::I] = GLFW_KEY_I;
	Input::KeyData[Input::J] = GLFW_KEY_J;
	Input::KeyData[Input::K] = GLFW_KEY_K;
	Input::KeyData[Input::L] = GLFW_KEY_L;
	Input::KeyData[Input::N] = GLFW_KEY_N;
	Input::KeyData[Input::M] = GLFW_KEY_M;
	Input::KeyData[Input::O] = GLFW_KEY_O;
	Input::KeyData[Input::P] = GLFW_KEY_P;
	Input::KeyData[Input::Q] = GLFW_KEY_Q;
	Input::KeyData[Input::R] = GLFW_KEY_R;
	Input::KeyData[Input::S] = GLFW_KEY_S;
	Input::KeyData[Input::T] = GLFW_KEY_T;
	Input::KeyData[Input::U] = GLFW_KEY_U;
	Input::KeyData[Input::V] = GLFW_KEY_V;
	Input::KeyData[Input::W] = GLFW_KEY_W;
	Input::KeyData[Input::X] = GLFW_KEY_X;
	Input::KeyData[Input::Y] = GLFW_KEY_Y;
	Input::KeyData[Input::Z] = GLFW_KEY_Z;
	Input::KeyData[Input::SPACE] = GLFW_KEY_SPACE;
	Input::KeyData[Input::ENTER] = GLFW_KEY_ENTER;
	Input::KeyData[Input::UP] = GLFW_KEY_UP;
	Input::KeyData[Input::DOWN] = GLFW_KEY_DOWN;
	Input::KeyData[Input::RIGHT] = GLFW_KEY_RIGHT;
	Input::KeyData[Input::LEFT] = GLFW_KEY_LEFT;
	Input::KeyData[Input::ESCAPE] = GLFW_KEY_ESCAPE;
}
bool Input::KeyInputDown(Key key) {
	if (glfwGetKey(Input::nowWindow, Input::KeyData[key])) {
		Input::KeyInputDownTime[key]++;
	}
	else if (Input::KeyInputDownTime[key] != 0) {
		Input::KeyInputDownTime[key] = 0;
	}
	if (Input::KeyInputDownTime[key] == 1) {
		return true;
	}
	return false;
}
bool Input::KeyInputOn(Key key) {
	if (glfwGetKey(Input::nowWindow, Input::KeyData[key])) {
		Input::KeyInputOnTime[key]++;
		return true;
	}
	else if (Input::KeyInputOnTime[key] != 0) {
		Input::KeyInputOnTime[key] = 0;
	}
	if (Input::KeyInputOnTime[key] == 1) {
	}
	return false;
}
bool Input::KeyInputUp(Key key) {
	if (glfwGetKey(Input::nowWindow, Input::KeyData[key])) {
		Input::KeyInputUpTime[key]++;
	}
	else if (Input::KeyInputUpTime[key] != 0) {
		Input::KeyInputUpTime[key] = 0;
		return true;
	}
	if (Input::KeyInputUpTime[key] == 1) {
	}
	return false;
}
void Input::Finalize()
{
	
}

void Texture::TextureCreate(std::string path)
{
	GLuint id;
	this->TextureID = 1;
	//テクスチャをサイズ分だけ生成する
	glGenTextures(this->TextureID, &id);
	//テクスチャをバインドする
	glBindTexture(GL_TEXTURE_2D, id);
	//画像を読み込む
	int width;
	int height;
	int comp;
	std::string filepath = FileName + path;
	//画像データを読み込む
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &comp, 0);
	//データ形式を選ぶ
	GLint type = (comp == 3) ? GL_RGB : GL_RGBA;
	//画像データをOpenGLへ送る
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data);
	TextureSize = Vec2(width, height);
	//元データの破棄
	stbi_image_free(data);
	//表示用設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	this->_TexId = id;
	_materix[0] = { 0,0 };
	_materix[1] = { width,0 };
	_materix[2] = { width,height };
	_materix[3] = { 0,height };
	angle = 0.f;
}
Texture::Texture()
{

}
void Texture::Draw(Box2D draw, Box2D src) {
	//座標
	GLfloat vtx[] = {
		draw.x,draw.h,
		draw.w,draw.h,
		draw.w,draw.y,
		draw.x,draw.y,
	};
	_Rotate(angle, &vtx[0]);
	glVertexPointer(2, GL_FLOAT, 0, vtx);
	//画像座標
	const GLfloat texuv[] = {
		src.x / TextureSize.x,src.h / TextureSize.y,
		src.w / TextureSize.x,src.h / TextureSize.y,
		src.w / TextureSize.x,src.y / TextureSize.y,
		src.x / TextureSize.x,src.y / TextureSize.y,
	};
	//0.1以下のカラーを表示しない、これで透過されてる部分を切り抜くことで透過された画像になる
	glAlphaFunc(GL_GREATER, (GLclampf)0.1);
	glTexCoordPointer(2, GL_FLOAT, 0, texuv);
	//OpenGLに登録されているテクスチャを紐づけ
	glBindTexture(GL_TEXTURE_2D, _TexId);
	//描画
	//glMatrixMode(GL_TEXTURE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
void Texture::Finalize()
{
	glDeleteTextures(1, &this->_TexId);
}
void Texture::Rotate(float radian)
{
	this->angle = radian;
}
void Texture::_Rotate(float radian, GLfloat *_mate)
{
	//ラジアンの値に変更
	float tora = OG::ToRadian(radian);
	//原点を指定
	Vec2 Center((*(_mate + 2) + *(_mate)) / 2, (*(_mate + 5) + *(_mate + 1)) / 2);
	//回転軸の原点の値を導く
	GLfloat v[]
	{
		*(_mate)-Center.x,*(_mate + 1) - Center.y,
		*(_mate + 2) - Center.x,*(_mate + 3) - Center.y,
		*(_mate + 4) - Center.x,*(_mate + 5) - Center.y,
		*(_mate + 6) - Center.x,*(_mate + 7) - Center.y,
	};
	//回転行列の生成
	GLfloat ma[4] = {
		cosf(tora),-sinf(tora),
		sinf(tora),cosf(tora),
	};
	//回転行列の計算
	*(_mate) = (v[0] * ma[0]) + (v[1] * ma[1]);
	*(_mate + 1) = (v[0] * ma[2]) + (v[1] * ma[3]);

	*(_mate + 2) = (v[2] * ma[0]) + (v[3] * ma[1]);
	*(_mate + 3) = (v[2] * ma[2]) + (v[3] * ma[3]);

	*(_mate + 4) = (v[4] * ma[0]) + (v[5] * ma[1]);
	*(_mate + 5) = (v[4] * ma[2]) + (v[5] * ma[3]);

	*(_mate + 6) = (v[6] * ma[0]) + (v[7] * ma[1]);
	*(_mate + 7) = (v[6] * ma[2]) + (v[7] * ma[3]);

	//回転軸の原点の移動した分を元に戻す
	*(_mate) = *(_mate)+Center.x;
	*(_mate + 1) = *(_mate + 1) + Center.y;

	*(_mate + 2) = *(_mate + 2) + Center.x;
	*(_mate + 3) = *(_mate + 3) + Center.y;

	*(_mate + 4) = *(_mate + 4) + Center.x;
	*(_mate + 5) = *(_mate + 5) + Center.y;

	*(_mate + 6) = *(_mate + 6) + Center.x;
	*(_mate + 7) = *(_mate + 7) + Center.y;
}
Texture::~Texture()
{
	glDeleteTextures(1, &this->_TexId);
}

Camera2D::Camera2D(Box2D pos)
{
	this->cameraPos = pos;
	this->position = { 0,0 };
	this->width = 0;
	this->height = 0;
}
Camera2D::~Camera2D()
{

}
void Camera2D::Initialize(Box2D pos)
{
	this->cameraPos = pos;
	this->position = { 0,0 };
	this->width = 0;
	this->height = 0;
}
void Camera2D::CameraUpDate()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Box2D _camera(cameraPos);
	_camera.x += this->position.x;
	_camera.y += this->position.y;
	_camera.OffsetSize();
	glOrtho(_camera.x, _camera.w, _camera.h + this->width, _camera.y + this->height, -1.0f, 1.0f);
}
void Camera2D::Move(Vec2 est)
{
	this->position += est;
}

Camera2D::SP Camera2D::Create(Box2D pos)
{
	return Camera2D::SP(new Camera2D(pos));
}

EngineSystem::EngineSystem()
{
	
}

EngineSystem::EngineSystem(int widht, int height, char* name, bool screen)
{
	this->w_he = widht;
	this->w_he = height;
	this->w_na = name;
	this->w_sc = screen;
}

void EngineSystem::Initialize()
{
	gameEngine->camera = Camera2D::Create(Box2D(0, 0, 960, 540));
	gameEngine->keyinput = KeyInput::Create();
}

void EngineSystem::UpDate()
{
	gameEngine->camera->CameraUpDate();
}

EngineSystem* gameEngine;

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
