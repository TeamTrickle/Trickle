#include "OGlib.h"
Circle::Circle()
	:center_x(0.f), center_y(0.f), r(0.f)
{}
Circle::Circle(const float _x, const float _y, const float _r)
	: r(_r), center_x(_x), center_y(_y)
{}
Circle::Circle(const int _x, const int _y, const int _r)
	: r((float)_r), center_x((float)_x), center_y((float)_y)
{}
Circle::Circle(const Circle&_c)
	: r(_c.r), center_x(_c.center_x), center_y(_c.center_y)
{}
Vec3::Vec3()
	: x(0.f), y(0.f), z(0.f)
{}
Vec3::Vec3(const float ex, const float ey, const float ez)
	: x(ex), y(ey), z(ez)
{}
Vec3::Vec3(const int ex, const int ey, const int ez)
	: x((float)ex), y((float)ey), z((float)ez)
{}
Vec2::Vec2()
	: x(0.f), y(0.f)
{}
Vec2::Vec2(const float ex, const float ey)
	: x(ex), y(ey)
{}
Vec2::Vec2(const int ex, const int ey)
	: x((float)ex), y((float)ey)
{}
void Vec2::Normalize() {
	float len = this->GetLength();
	if (len == 0) { return; }
	x /= len;
	y /= len;
}
float Vec2::GetLength() {
	return powf(x*x + y * y, 0.5f);
}
Vec2 Vec2::operator+(const Vec2& v) { return Vec2(x + v.x, y + v.y); }
//Vec2 Vec2::operator+(const Vec2& v) { this->x += v.x, this->y += v.y; return *this; }
Vec2 Vec2::operator-(const Vec2& v) { return Vec2(x - v.x, y - v.y); }
//Vec2 Vec2::operator-(const Vec2& v) { this->x -= v.x, this->y -= v.y; return *this; }
Vec2 Vec2::operator*(const float n) { return Vec2(x*n, y*n); }
//Vec2 Vec2::operator*(const float n) { this->x *= n, this->y *= n; return *this; }
void Vec2::operator+=(const Vec2& v) { x += v.x; y += v.y; }
void Vec2::operator*=(const float n) { x *= n; y *= n; }
void Vec2::operator-=(const Vec2& v) { x -= v.x; y -= v.y; }
bool Vec2::operator==(const Vec2& v) { return this->x == v.x && this->y == v.y; }

Mat4::Mat4(const float ex, const float ey, const float ez, const float ew)
{
	mat4[0] = ex;
	mat4[1] = ey;
	mat4[2] = ez;
	mat4[3] = ew;
}
Mat4::Mat4(const int ex, const int ey, const int ez, const int ew)
{
	mat4[0] = (float)ex;
	mat4[1] = (float)ey;
	mat4[2] = (float)ez;
	mat4[3] = (float)ew;
}

Mat4x4::Mat4x4(const float ex, const float ey, const float ez, const float ew,
	const float sx, const float sy, const float sz, const float sw,
	const float dx, const float dy, const float dz, const float dw,
	const float rx, const float ry, const float rz, const float rw) {
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
Mat4x4::Mat4x4(const int ex, const int ey, const int ez, const int ew,
	const int sx, const int sy, const int sz, const int sw,
	const int dx, const int dy, const int dz, const int dw,
	const int rx, const int ry, const int rz, const int rw) {
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
Box3D::Box3D(const float ex, const float ey, const float ez, const float ew, const float eh, const float ed)
	: x(ex), y(ey), z(ez), w(ew), h(eh), d(ed)
{}
Box3D::Box3D(const Box3D &_e)
	: x(_e.x), y(_e.y), z(_e.z), w(_e.w), h(_e.h), d(_e.d)
{}
int Box3D::IsOdd(const int n, const int a, const int b) {
	if (n % 2 == 0) {
		return a;
	}
	return b;
}
int Box3D::InOdd(const int n, const int a, const int b) {
	if ((n / 2) % 2 == 0) {
		return a;
	}
	return b;
}
int Box3D::IfOdd(const int n, const int a, const int b) {
	if ((n / 4) % 2 == 0) {
		return a;
	}
	return b;
}

Box2D::Box2D()
	:x(0), y(0), w(0), h(0)
{}
Box2D::Box2D(const float x_, const float y_, const float w_, const float h_)
	: x(x_), y(y_), w(w_), h(h_)
{}
Box2D::Box2D(const int x_, const int y_, const int w_, const int h_)
	: x((float)x_), y((float)y_), w((float)w_), h((float)h_)
{}
Box2D::Box2D(const Box2D& b_)
	: x(b_.x), y(b_.y), w(b_.w), h(b_.h)
{}
Box2D::Box2D(const Vec2& p, const Vec2& s)
	: x(p.x), y(p.y), w(s.x), h(s.y)
{}
void Box2D::Offset(const float x_, const float y_)
{
	x += x_;
	y += y_;
}
void Box2D::Offset(const int x_, const int y_)
{
	x += (float)x_;
	y += (float)y_;
}
void Box2D::OffsetSize()
{
	this->w = this->w + this->x;
	this->h = this->h + this->y;
}
//Box2D Box2D::operator+(const Box2D& b) { return Box2D(x += b.x, y += b.y, w += b.w, h += b.h); }
Box2D Box2D::operator+(const Box2D& b) { this->x += b.x, this->y += b.y, this->w += b.w, this->h += b.h; return *this; }
//Box2D Box2D::operator-(const Box2D& b) { return Box2D(x -= b.x, y -= b.y, w -= b.w, h -= b.h); }
Box2D Box2D::operator-(const Box2D& b) { this->x -= b.x, this->y -= b.y, this->w -= b.w, this->h -= b.h; return *this; }
//Box2D Box2D::operator*(const Box2D& b) { return Box2D(x *= b.x, y *= b.y, w *= b.w, h *= b.h); }
Box2D Box2D::operator*(const Box2D& b) { this->x *= b.x, this->y *= b.y, this->w *= b.w, this->h *= b.h; return *this; }
void Box2D::operator+=(const Box2D& b) { { x += b.x; y += b.y; w += b.w; h += b.h; } }
void Box2D::operator-=(const Box2D& b) { { x -= b.x; y -= b.y; w -= b.w; h -= b.h; } }
void Box2D::operator*=(const Box2D& b) { { x *= b.x; y *= b.y; w *= b.w; h *= b.h; } }
Color::Color()
	:red(0.f), green(0.f), blue(0.f), alpha(0.f)
{}
Color::Color(const float r, const float g, const float b, const float a)
	: red(r), green(g), blue(b), alpha(a)
{}
Color::Color(const int r, const int g, const int b, const int a)
	: red((float)r), green((float)g), blue((float)b), alpha((float)a)
{}
unsigned int Color::Getcolor() const
{
	unsigned char r = (unsigned char)(this->red * 255.0f);
	unsigned char g = (unsigned char)(this->green * 255.0f);
	unsigned char b = (unsigned char)(this->blue * 255.0f);
	unsigned char a = (unsigned char)(this->alpha * 255.0f);

	return (r) | (g << 8) | (b << 16) | (a << 24);
}
void Color::operator+=(const Color& b) { red += b.red; green += b.green; blue += b.blue; alpha += b.alpha; }
void Color::operator*=(const Color& b) { red *= b.red; green *= b.green; blue *= b.blue; alpha *= b.alpha; }
void Color::operator-=(const Color& b) { red -= b.red; green -= b.green; blue -= b.blue; alpha -= b.alpha; }
//Color Color::operator+(const Color& b) { return Color(red += b.red, green += b.green, blue += b.blue, alpha += b.alpha); }
//Color Color::operator-(const Color& b){ return Color(red -= b.red, green -= b.green, blue -= b.blue, alpha -= b.alpha); }
//Color Color::operator*(const Color& b){ return Color(red *= b.red, green *= b.green, blue *= b.blue, alpha *= b.alpha); }
Color Color::operator+(const Color& b) { this->red += b.red, this->green += b.green, this->blue += b.blue, this->alpha += b.alpha; return *this; }
Color Color::operator-(const Color& b) { this->red -= b.red, this->green -= b.green, this->blue -= b.blue, this->alpha -= b.alpha; return *this; }
Color Color::operator*(const Color& b) { this->red *= b.red, this->green *= b.green, this->blue *= b.blue, this->alpha *= b.alpha; return *this; }

float OG::ToRadian(const  float  degree_)
{
	return  degree_ * PI / 180.0f;
}
void OG::Cross(float* src1, float* src2, float* dst) {
	dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
	dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
	dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
float OG::inner(const Vec2& _v1, const Vec2& _v2) {
	return ((_v1.x * _v2.x) + (_v1.y*_v2.y));
}
float OG::inner(const float _x1, const float _y1, const float _x2, const float _y2) {
	return ((_x1 * _x2) + (_y1*_y2));
}
float OG::inner(const int _x1, const int _y1, const int _x2, const int _y2) {
	return (float)((_x1 * _x2) + (_y1*_y2));
}
float OG::cross(const Vec2& _v1, const Vec2& _v2) {
	return ((_v1.x * _v2.y) - (_v1.y*_v2.x));
}
float OG::cross(const float _x1, const float _y1, const float _x2, const float _y2) {
	return ((_x1 * _y2) - (_y1*_x2));
}
float OG::cross(const int _x1, const int _y1, const int _x2, const int _y2) {
	return (float)((_x1 * _y2) - (_y1*_x2));
}
float OG::doubleinner(const Vec2& _v) {
	return inner(_v, _v);
}
float OG::doubleinner(const float _x, const float _y) {
	return inner(_x, _y, _x, _y);
}
float OG::doubleinner(const int _x, const int _y) {
	return inner(_x, _y, _x, _y);
}
float OG::get_distance(const float x, const float y, const float x1, const float y1, const float x2, const float y2) {
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