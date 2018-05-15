#pragma once
#include "OGSystem\_OGsystem.h"

class Texture {
public:
	Texture();							//コンストラクタ
	~Texture();							//デストラクタ	
	bool Create(std::string&);			//画像データの生成
	void Draw(							//描画処理
		Box2D, 
		Box2D, 
		Color = { 1.0f,1.0f,1.0f,1.0f });
	bool Finalize();					//解放処理
	void Rotate(float);				//回転の適応
private:
	GLuint _TexId;						//テクスチャのID
	Vec2 TextureSize;					//画像サイズ
	Vec2 _materix[4];					//頂点情報
	const std::string FileName = "./data/image/";//画像ファイルパス
	void _Rotate(float,					//頂点座標を回転させる
				GLfloat*);
	float angle;						//回転値
};