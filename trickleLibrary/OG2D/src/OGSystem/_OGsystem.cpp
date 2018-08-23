#include "_OGsystem.h"
//--------------------------------------------------
//@:OGspace							
//--------------------------------------------------
namespace OG {
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
	void LineHitDraw(Vec2* _b, const Color& color_) {
		glColor4f(color_.red, color_.green, color_.blue, color_.alpha);
		glBegin(GL_LINES);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);

		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glVertex2f((_b + 2)->x, (_b + 2)->y);

		glVertex2f((_b + 2)->x, (_b + 2)->y);
		glVertex2f((_b + 3)->x, (_b + 3)->y);

		glVertex2f((_b + 3)->x, (_b + 3)->y);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineHitDraw(Vec2* _b) {
		glBegin(GL_LINES);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);

		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glVertex2f((_b + 2)->x, (_b + 2)->y);

		glVertex2f((_b + 2)->x, (_b + 2)->y);
		glVertex2f((_b + 3)->x, (_b + 3)->y);

		glVertex2f((_b + 3)->x, (_b + 3)->y);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineHitDraw(Box2D* _b)
	{
		glBegin(GL_LINES);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b)->w, (_b)->y);

		glVertex2f((_b)->w, (_b)->y);
		glVertex2f((_b)->w, (_b)->h);

		glVertex2f((_b)->w, (_b)->h);
		glVertex2f((_b)->x, (_b)->h);

		glVertex2f((_b)->x, (_b)->h);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void _Rotate(const float _ang, Vec2* _b)
	{
		//ラジアンの値に変更
		float tora = OG::ToRadian(_ang);
		//原点を指定
		Vec2 Center(((_b + 2)->x + (_b)->x) / 2, ((_b + 2)->y + (_b)->y) / 2);
		//回転軸の原点の値を導く
		GLfloat v[]
		{
			_b->x - Center.x,_b->y - Center.y,
			(_b + 1)->x - Center.x,(_b + 1)->y - Center.y,
			(_b + 2)->x - Center.x,(_b + 2)->y - Center.y,
			(_b + 3)->x - Center.x,(_b + 3)->y - Center.y,
		};
		//回転行列の生成
		GLfloat ma[4] = {
			cosf(tora),-sinf(tora),
			sinf(tora),cosf(tora),
		};
		//回転行列の計算
		(_b)->x = (*(v) * *(ma)) + (*(v + 1)* *(ma + 1));
		(_b)->y = (*(v) * *(ma + 2)) + (*(v + 1)* *(ma + 3));

		(_b + 1)->x = (*(v + 2)* *(ma)) + (*(v + 3)* *(ma + 1));
		(_b + 1)->y = (*(v + 2)* *(ma + 2)) + (*(v + 3)* *(ma + 3));

		(_b + 2)->x = (*(v + 4)* *(ma)) + (*(v + 5)* *(ma + 1));
		(_b + 2)->y = (*(v + 4)* *(ma + 2)) + (*(v + 5)* *(ma + 3));

		(_b + 3)->x = (*(v + 6)* *(ma)) + (*(v + 7)* *(ma + 1));
		(_b + 3)->y = (*(v + 6)* *(ma + 2)) + (*(v + 7)* *(ma + 3));

		//回転軸の原点の移動した分を元に戻す
		(_b)->x = (_b)->x + Center.x;
		(_b)->y = (_b)->y + Center.y;

		(_b + 1)->x = (_b + 1)->x + Center.x;
		(_b + 1)->y = (_b + 1)->y + Center.y;

		(_b + 2)->x = (_b + 2)->x + Center.x;
		(_b + 2)->y = (_b + 2)->y + Center.y;

		(_b + 3)->x = (_b + 3)->x + Center.x;
		(_b + 3)->y = (_b + 3)->y + Center.y;
	}
}
void OG::BackColor(const Color& color)
{
	glClearColor((GLclampf)color.red, (GLclampf)color.green, (GLclampf)color.blue, (GLclampf)color.alpha);
}
void OG::BackColor(const float& red, const float& green, const float& blue, const float& alpha)
{
	glClearColor((GLclampf)red, (GLclampf)green, (GLclampf)blue, (GLclampf)alpha);
}
int OG::mbclen(const char* c)
{
	if ((*c & 0xc0) == 0x80)
	{
		return 2;
	}
	else if ((*c & 0x80) == 0)
	{
		return 1;
	}
	return 0;
}
void OG::cout(const Box2D& b)
{
	std::cout << "x " << b.x << ":y " << b.y << ":w " << b.w << ":h " << b.h << "\n";
}
void OG::cout(const Vec2& v)
{
	std::cout << "x " << v.x << ":y " << v.y << "\n";
}
void OG::cout(const Color& c)
{
	std::cout << "red " << c.red << ":green " << c.green << ":blue " << c.blue << ":alpha " << c.alpha << "\n";
}