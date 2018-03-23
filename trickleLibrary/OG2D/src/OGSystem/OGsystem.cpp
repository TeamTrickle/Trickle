#include "OGsystem.h"
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
	OG::_Rotate(angle, _v);
	OG::_Rotate(b.angle, _ver);
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
	Vec2 _ver[1] = {
		{ b.hitBase.CenterX,b.hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
		{ hitBase.w - 1,hitBase.y },
		{ hitBase.w - 1,hitBase.h - 1 },
		{ hitBase.x,hitBase.h - 1 }
	};
	OG::_Rotate(angle, _v);
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= b.hitBase.r*b.hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= b.hitBase.r*b.hitBase.r)
	{
		return true;
	}

	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<b.hitBase.r)
			return true;
	}
	return false;
}
//円×長方形
bool CollisionCircle::hitBox(CollisionBox b)
{
	Vec2 _ver[1] = {
		{ hitBase.CenterX,hitBase.CenterY }
	};
	Vec2 _v[4] = {
		{ b.hitBase.x,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.y },
		{ b.hitBase.w - 1,b.hitBase.h - 1 },
		{ b.hitBase.x,b.hitBase.h - 1 }
	};
	OG::_Rotate(b.angle, _v);
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) <= hitBase.r*hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) <= hitBase.r*hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) <= hitBase.r*hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) <= hitBase.r*hitBase.r)
	{
		return true;
	}

	for (int i = 0; i<4; i++) {
		if (OG::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<hitBase.r)
			return true;
	}
	return false;
}
//円×円
bool CollisionCircle::hitCircle(CollisionCircle b)
{
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
	this->angle = _angle;
}

KeyInput::KeyInput()
{
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

void Key::Initialize(GLFWwindow *w)
{
	for (int i = 0; i < 256; ++i) {
		Key::KeyInputDownTime[i] = 0;
		Key::KeyInputOnTime[i] = 0;
		Key::KeyInputUpTime[i] = 0;
	}
	Key::nowWindow = w;
}
bool Key::KeyInputDown(int key) {
	if (glfwGetKey(Key::nowWindow, key)) {
		Key::KeyInputDownTime[key]++;
	}
	else if (Key::KeyInputDownTime[key] != 0) {
		Key::KeyInputDownTime[key] = 0;
	}
	if (Key::KeyInputDownTime[key] == 1) {
		return true;
	}
	return false;
}
bool Key::KeyInputOn(int key) {
	if (glfwGetKey(Key::nowWindow, key)) {
		Key::KeyInputOnTime[key]++;
		return true;
	}
	else if (Key::KeyInputOnTime[key] != 0) {
		Key::KeyInputOnTime[key] = 0;
	}
	if (Key::KeyInputOnTime[key] == 1) {
	}
	return false;
}
bool Key::KeyInputUp(int key) {
	if (glfwGetKey(Key::nowWindow, key)) {
		Key::KeyInputUpTime[key]++;
	}
	else if (Key::KeyInputUpTime[key] != 0) {
		Key::KeyInputUpTime[key] = 0;
		return true;
	}
	if (Key::KeyInputUpTime[key] == 1) {
	}
	return false;
}
void Key::Finalize()
{
	glfwDestroyWindow(Key::nowWindow);
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
		draw.x,draw.y,
		draw.w,draw.y,
		draw.w,draw.h,
		draw.x,draw.h,
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

//Font::Font()
//{
//
//}
//
//void Font::FontCreate()
//{
//
//}
//
//void Font::Draw()
//{
//
//}