#pragma once

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

/**
* @brief 背景に流れる雲クラス
* @author 横田
* @date 2018.8.10
*/
class Cloud : public GameObject, public TaskObject {
	//! 雲のテクスチャ
	Texture cloudImg;
	//! 雲画像の表示位置
	Vec2 cloudPos[2];
	//! 移動スピード
	float speed;
public:
	Cloud(const std::string& path, float speed);
	~Cloud();
	static std::shared_ptr<Cloud> Create(const std::string& path, float speed);

	void Initialize(const std::string& path, float speed);
	void UpDate() override;
	void Render2D() override;
};


/**
*@brief	:背景描画とスクロールを行うclass
*/
class Back : public TaskObject
{
	//!	背景画像データ
	Texture backImg;
	//!	描画するサイズ
	Vec2 size;
	//!	スクロールを行う背景かどうか
	bool isScroll;
	//!	マップサイズの縦横値
	Vec2* mapSize;
	//!	描画する画像の位置
	Vec2* texPos;
	//!	マップの中心値
	float* Center;
	//!	マップの位置と端の位置の差
	float* Xsize;
	//!	端の位置と画像の位置の差
	float* Tsize;
	//!	スマポ宣言
	typedef std::shared_ptr<Back> SP;
	/**
	*@brief	:画像の読み込みと変数の初期化
	*/
	void Init(const std::string&);
	/**
	*@brife	:constructor
	*@param	:string	ファイル名
	*@param	:Vec2	描画時の縦サイズと横サイズ
	*/
	Back(const std::string&, const Vec2&);
	/**
	*@brife	:constructor
	*@param	:string	ファイル名
	*@param	:float size_x	描画時の横サイズ
	*@param :float size_y	描画時の縦サイズ
	*/
	Back(const std::string&, float, float);
	/**
	*@brife	:constructor
	*@param	:string	ファイル名
	*@param	:int size_x	描画時の横サイズ
	*@param :int size_y	描画時の縦サイズ
	*/
	Back(const std::string&, int, int);
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:画像の描画位置の設定
	*@return:bool	設定に成功したらtrue
	*/
	bool TexturePositionConfig();
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Back();
	/**
	*@brief	:タスク生成
	*@param	:string path	ファイル名
	*@param	:Vec2 size	描画時の縦サイズと横サイズ
	*@reutrn:Back	生成に失敗した場合はnullptr
	*/
	static SP Create(const std::string& path, const Vec2& size);
	/**
	*@brief	:タスク生成
	*@param	:string path	ファイル名
	*@param	:float size_x	描画時の横サイズ
	*@param :float size_y	描画時の縦サイズ
	*@reutrn:Back	生成に失敗した場合はnullptr
	*/
	static SP Create(const std::string& path, float size_x, float size_y);
	/**
	*@brief	:タスク生成
	*@param	:string path	ファイル名
	*@param	:int size_x	描画時の横サイズ
	*@param :int size_y	描画時の縦サイズ
	*@reutrn:Back	生成に失敗した場合はnullptr
	*/
	static SP Create(const std::string& path, int size_x, int size_y);
	/**
	*@brief	:スクロールを行う背景かを設定する
	*@param	:bool flag	スクロールを行う有無
	*/
	void SetScroll(bool flag = true);
};