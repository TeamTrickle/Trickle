#pragma once
//_____________________________
//|システムクラス１             
//|履歴：2018/03/20       
//|____________________________

#if !defined (_DEBUG)
// Degub版のみコンソールを表示する設定
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

// Windows:GLEWをスタティックライブラリ形式で利用
#define GLEW_STATIC
// GLFWのヘッダ内で他のライブラリを取り込む	
#define GLFW_INCLUDE_GLEXT
#define GLFW_INCLUDE_GLU
#define GLM_FORCE_SWIZZLE

#pragma comment(lib, "OPENGL32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "Win64/OpenAL32.lib")
#pragma comment(lib, "opencv_core342.lib")
#pragma comment(lib, "opencv_videoio342.lib")
//#pragma comment(lib, "freetype.lib")

#if defined(_MSC_VER)
// Windows:外部ライブラリのリンク指定
#if defined (_DEBUG)
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#endif
#endif

#if defined(_MSC_VER)
//EWを先にインクルードする必要がある。
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "al\al.h"
#include "al\alc.h"

#include <memory>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>

#include "OGlib.h"
#include "randmais.h"

#define PI 3.1415926f
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;

namespace OG {
	//便利機能関数や数学計算
	void MulitMatrixf(GLfloat*, GLfloat*, GLfloat*);
	void Normalize(GLfloat*);
	void _Rotate(float _angle, Vec2*);
	void LineHitDraw(Vec2*);
	void LineHitDraw(Vec2*, Color&);
	void LineHitDraw(Box2D*);
	void BackColor(const Color& color);
	void BackColor(const float&red, const float&green, const float&blue, const float&alpha);
	int mbclen(const char* c);
	void cout(const Box2D&);
	void cout(const Vec2&);
	void cout(const Color&);
	bool Data_Cipher(const std::string& in_path, const std::string& out_path);
	std::string Data_Composite(std::ifstream& ifs);
	void OutDebugData(const std::string& out_path, const std::string& text);
	void DataClear(const std::string& path);
}