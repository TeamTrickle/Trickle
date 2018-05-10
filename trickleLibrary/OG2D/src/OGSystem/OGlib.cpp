#include "OGlib.h"
Circle::Circle()
	:center_x(0.f), center_y(0.f), r(0.f)
{}
Circle::Circle(float _x, float _y, float _r)
	:r(_r), center_x(_x), center_y(_y)
{}
Circle::Circle(int _x, int _y, int _r)
	:r((float)_r), center_x((float)_x), center_y((float)_y)
{}
Circle::Circle(Circle&_c)
	:r(_c.r), center_x(_c.center_x), center_y(_c.center_y)
{}
Vec3::Vec3()
	:x(0.f), y(0.f), z(0.f)
{}
Vec3::Vec3(float ex, float ey, float ez)
	:x(ex), y(ey), z(ez)
{}
Vec3::Vec3(int ex, int ey, int ez)
	:x((float)ex), y((float)ey), z((float)ez)
{}
Vec2::Vec2()
	:x(0.f), y(0.f)
{}
Vec2::Vec2(float ex, float ey)
	:x(ex), y(ey)
{}
Vec2::Vec2(int ex, int ey)
	:x((float)ex), y((float)ey)
{}
//Vec2::Vec2(Vec2& v)
//	:x(v.x),y(v.y)
//{}
void Vec2::Normalize() {
	float len = this->GetLength();
	if (len == 0) { return; }
	x /= len;
	y /= len;
}
float Vec2::GetLength() {
	return powf(x*x + y * y, 0.5f);
}
Vec2 Vec2::operator+(Vec2& v) { return Vec2(x + v.x, y + v.y); }
Vec2 Vec2::operator-(Vec2& v) { return Vec2(x - v.x, y - v.y); }
Vec2 Vec2::operator*(float n) { return Vec2(x*n, y*n); }
void Vec2::operator+=(Vec2& v) { x += v.x; y += v.y; }
void Vec2::operator*=(float n) { x *= n; y *= n; }
void Vec2::operator-=(Vec2& v) { x -= v.x; y -= v.y; }

Mat4::Mat4(float ex, float ey, float ez, float ew)
{
	mat4[0] = ex;
	mat4[1] = ey;
	mat4[2] = ez;
	mat4[3] = ew;
}
Mat4::Mat4(int ex, int ey, int ez, int ew)
{
	mat4[0] = (float)ex;
	mat4[1] = (float)ey;
	mat4[2] = (float)ez;
	mat4[3] = (float)ew;
}

Mat4x4::Mat4x4(float ex, float ey, float ez, float ew,
	float sx, float sy, float sz, float sw,
	float dx, float dy, float dz, float dw,
	float rx, float ry, float rz, float rw) {
	mat4[0] = ex;
	mat4[1] = ey;
	mat4[2] = ez;
	mat4[3] = ew;
	mat4[4] = sx;
	mat4[5] = sy;
	mat4[6] = sz;
	mat4[7] = sw;
	mat4[8] = dx;
	mat4[9] = dy;
	mat4[10] = dz;
	mat4[11] = dw;
	mat4[12] = rx;
	mat4[13] = ry;
	mat4[14] = rz;
	mat4[15] = rw;
}
Mat4x4::Mat4x4(int ex, int ey, int ez, int ew,
	int sx, int sy, int sz, int sw,
	int dx, int dy, int dz, int dw,
	int rx, int ry, int rz, int rw) {
	mat4[0] = (float)ex;
	mat4[1] = (float)ey;
	mat4[2] = (float)ez;
	mat4[3] = (float)ew;
	mat4[4] = (float)sx;
	mat4[5] = (float)sy;
	mat4[6] = (float)sz;
	mat4[7] = (float)sw;
	mat4[8] = (float)dx;
	mat4[9] = (float)dy;
	mat4[10] = (float)dz;
	mat4[11] = (float)dw;
	mat4[12] = (float)rx;
	mat4[13] = (float)ry;
	mat4[14] = (float)rz;
	mat4[15] = (float)rw;
}

Box3D::Box3D()
	:x(0.f), y(0.f), z(0.f), w(0.f), h(0.f), d(0.f)
{}
Box3D::Box3D(float ex, float ey, float ez, float ew, float eh, float ed)
	:x(ex), y(ey), z(ez), w(ew), h(eh), d(ed)
{}
Box3D::Box3D(const Box3D &_e)
	:x(_e.x), y(_e.y), z(_e.z), w(_e.w), h(_e.h), d(_e.d)
{}
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

Box2D::Box2D()
	:x(0), y(0), w(0), h(0)
{}
Box2D::Box2D(float x_, float y_, float w_, float h_)
	:x(x_), y(y_), w(w_), h(h_)
{}
Box2D::Box2D(int x_, int y_, int w_, int h_)
	:x((float)x_), y((float)y_), w((float)w_), h((float)h_)
{}
Box2D::Box2D(const Box2D& b_)
	:x(b_.x), y(b_.y), w(b_.w), h(b_.h)
{}
Box2D::Box2D(const Vec2& p, const Vec2& s)
	:x(p.x), y(p.y), w(s.x), h(s.y)
{}
void Box2D::Offset(float x_, float y_)
{
	x += x_;
	y += y_;
}
void Box2D::Offset(int x_, int y_)
{
	x += (float)x_;
	y += (float)y_;
}
void Box2D::OffsetSize()
{
	this->w = this->w + this->x;
	this->h = this->h + this->y;
}
Box2D Box2D::operator+(Box2D& b) { return Box2D(x += b.x, y += b.y, w += b.w, h += b.h); }
Box2D Box2D::operator-(Box2D& b) { return Box2D(x -= b.x, y -= b.y, w -= b.w, h -= b.h); }
Box2D Box2D::operator*(Box2D& b) { return Box2D(x *= b.x, y *= b.y, w *= b.w, h *= b.h); }
void Box2D::operator+=(Box2D& b){ { x += b.x; y += b.y; w += b.w; h += b.h; } }
void Box2D::operator-=(Box2D& b){ { x -= b.x; y -= b.y; w -= b.w; h -= b.h; } }
void Box2D::operator*=(Box2D& b){ { x *= b.x; y *= b.y; w *= b.w; h *= b.h; } }
Color::Color()
	:red(0.f), green(0.f), blue(0.f), alpha(0.f)
{}
Color::Color(const float r, const float g, const float b, const float a)
	:red(r), green(g), blue(b), alpha(a)
{}
Color::Color(const int r, const int g, const int b, const int a)
	:red((float)r), green((float)g), blue((float)b), alpha((float)a)
{}
unsigned int Color::Getcolor() const
{
	unsigned char r = (unsigned char)(this->red * 255.0f);
	unsigned char g = (unsigned char)(this->green * 255.0f);
	unsigned char b = (unsigned char)(this->blue * 255.0f);
	unsigned char a = (unsigned char)(this->alpha * 255.0f);

	return (r) | (g << 8) | (b << 16) | (a << 24);
}
void Color::operator+=(Color& b) { red += b.red; green += b.green; blue += b.blue; alpha += b.alpha; }
void Color::operator*=(Color& b) { red *= b.red; green *= b.green; blue *= b.blue; alpha *= b.alpha; }
void Color::operator-=(Color& b) { red -= b.red; green -= b.green; blue -= b.blue; alpha -= b.alpha; }
void Color::operator=(Color& b) { red = b.red; green = b.green; blue = b.blue; alpha = b.alpha; }

float OG::ToRadian(const  float  degree_)
{
	return  degree_ * PI / 180.0f;
}
void OG::Cross(float* src1, float* src2, float* dst) {
	dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
	dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
	dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
float OG::inner(Vec2& _v1, Vec2& _v2) {
	return ((_v1.x * _v2.x) + (_v1.y*_v2.y));
}
float OG::inner(float _x1, float _y1, float _x2, float _y2) {
	return ((_x1 * _x2) + (_y1*_y2));
}
float OG::inner(int _x1, int _y1, int _x2, int _y2) {
	return (float)((_x1 * _x2) + (_y1*_y2));
}
float OG::cross(Vec2& _v1, Vec2& _v2) {
	return ((_v1.x * _v2.x) - (_v1.y*_v2.y));
}
float OG::cross(float _x1, float _y1, float _x2, float _y2) {
	return ((_x1 * _x2) - (_y1*_y2));
}
float OG::cross(int _x1, int _y1, int _x2, int _y2) {
	return (float)((_x1 * _x2) - (_y1*_y2));
}
float OG::doubleinner(Vec2& _v) {
	return inner(_v, _v);
}
float OG::doubleinner(float _x, float _y) {
	return inner(_x, _y, _x, _y);
}
float OG::doubleinner(int _x, int _y) {
	return inner(_x, _y, _x, _y);
}
float OG::get_distance(float x, float y, float x1, float y1, float x2, float y2) {
	float dx, dy, a, b, t, tx, ty;
	float distance;
	dx = (x2 - x1);
	dy = (y2 - y1);
	a = dx * dx + dy * dy;
	b = dx * (x1 - x) + dy * (y1 - y);
	t = -b / a;
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	tx = x1 + dx * t;
	ty = y1 + dy * t;
	distance = sqrt((x - tx)*(x - tx) + (y - ty)*(y - ty));
	return distance;
}