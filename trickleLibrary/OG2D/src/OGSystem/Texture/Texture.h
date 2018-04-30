#pragma once
#include "OGSystem\_OGsystem.h"

class Texture {
public:
	Texture();
	~Texture();
	void TextureCreate(std::string _path);
	void Draw(Box2D draw, Box2D src, Color color_ = { 1.0f,1.0f,1.0f,1.0f });
	void Finalize();
	void Rotate(float radian);
	float angle;
private:
	GLuint _TexId;
	int TextureID;
	Box2D TexPos;
	Box2D Double;
	Vec2 TextureSize;
	GLfloat rotate[16];
	Vec2 _materix[4];
	const std::string FileName = "./data/image/";
	void _Rotate(float radian, GLfloat *mate);
};