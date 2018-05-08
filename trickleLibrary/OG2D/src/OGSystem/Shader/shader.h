#pragma once
//必要ファイルのインクルード
#include "OGSystem\_OGsystem.h"

//シェーダーのセットアップ

namespace Shader {
	//コンパイル
	GLuint compile(GLuint type, const std::string &text);
	//準備
	void setup(const GLuint program, const std::string &v_source, const std::string &f_source);
	//読み込み
	GLuint read(const std::string &file);
	//シェーダー内アトリビュート変数の識別子を取得
	GLint attrib(const GLint program, const std::string &name);
	//シェーダー内ユニフォーム変数の識別子を取得
	GLint uniform(const GLuint program, const std::string &name);
	//シェーダープログラムの使用開始
	void use(const GLuint program);
}