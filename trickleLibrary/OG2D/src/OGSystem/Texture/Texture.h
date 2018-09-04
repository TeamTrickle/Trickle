/**
*画像の読み込み、表示を行うclass
*/
#pragma once
#include "OGSystem\_OGsystem.h"
#include <opencv2/imgcodecs.hpp>

class Texture {
public:
	/**
	*@brief	:constructor
	*/
	Texture();
	/**
	*@brief	:constructor
	*@param	:string path ファイルパス
	*/
	Texture(const std::string& path);
	/**
	*@brief	:destructor
	*/
	~Texture();
	/**
	*@brief	:画像データの生成
	*@param	:string path ファイルパス
	*/
	bool Create(const std::string& path);

	bool Create(const cv::Mat&);			//画像データの生成

	/**
	*@brief	:描画処理
	*@param	:Box2D draw 描画範囲
	*@param	:Box2D src 画像範囲
	*@param	:Color color 描画色
	*/
	void Draw(
		const Box2D& draw,
		const Box2D& src,
		const Color& color = { 1.0f,1.0f,1.0f,1.0f });
	/**
	*@brief	:解放処理
	*@return:解放成功true
	*/
	bool Finalize();
	/**
	*@brief	:回転の適用
	*@param	:float angle 回転値
	*/
	void Rotate(const float angle);
	/**
	*@brief	:読み込んだ画像のサイズを返す
	*@return:Vec2 画像の大きさ
	*/
	Vec2 GetTextureSize() const;
	/**
	*@brief	:登録されているIDを返す
	*@return:GLuint ID
	*/
	GLuint GetID() const;
	/**
	*@brief	:テクスチャIDを生成する
	*@param	:GLsizei size 生成数
	*@return:GLuint ID
	*/
	GLuint CreateID(const GLsizei& size);
	/**
	*@brief	:テクスチャIDを削除する
	*@param	:GLsizei size 削除数
	*/
	void DeleteID(const GLsizei& size);
	/**
	*@brief	:テクスチャをバインドする
	*@param	:GLuint id バインドするID
	*0指定で対象を無にする
	*/
	void Bind(const GLuint& id);
private:
	//! テクスチャのID
	GLuint _TexId;
	//! 画像サイズ
	Vec2 TextureSize;
	//! 頂点情報
	Vec2 _materix[4];
	//! 画像ファイルパス
	const std::string FileName;
	/**
	*@brief	:頂点座標を回転させる
	*@param :float angle 回転値
	*@param	:GLfloat* materix 行列配列
	*/
	void _Rotate(const float angle,
		GLfloat* materix);
	//! 回転値
	float angle;
};