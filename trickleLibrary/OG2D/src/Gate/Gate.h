#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:ステージセレクトで使用する扉オブジェクト
*/
class Gate : public GameObject, public TaskObject
{
	//!	使用画像ポインタ
	Texture* image;
	//!	描画位置
	Box2D draw;
	//!	テクスチャ位置
	Box2D src;
	//!	個別ID
	unsigned __int8 ID;
	//!	開いているかどうか
	bool isOpen;
	//!	前回の開き状況
	bool preIsOpen;
	//!	アニメーション用カウント
	int AnimCnt;
	//!	アニメーションが変わる間隔
	int Sense;
	//!	描画を切る範囲のX座標
	float door_x;
	//!	描画を切る範囲のW座標
	float door_w;
	//!	スマートポインタ
	typedef std::shared_ptr<Gate> SP;
	std::string soundclosename;     //サウンドのファイル名格納
	std::string soundopenname;
	/**
	*@brief	:constructor	値の初期化
	*/
	Gate(const Vec2&);
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
public:
	/**
	*@brief	:解放処理
	*/
	virtual ~Gate();
	/**
	*@brief	:タスク生成
	*@param	:Vec2 pos	生成位置
	*@return:Gate 生成に失敗した場合nullptr
	*/
	static SP Create(const Vec2& pos, bool = true);
	/**
	*@brief	:タスク生成
	*@param	:float pos_x	生成X位置
	*@param	:float pos_y	生成Y位置
	*@return:Gate 生成に失敗した場合nullptr
	*/
	static SP Create(const float pos_x, const float pos_y, bool = true);
	/**
	*@brief	:使用画像を登録
	*@param	:Texture* texture	使用画像のポインタ
	*/
	void SetTexture(Texture* texture);
	/**
	*@brief	:個別IDを取得
	*@return:unsigned __int8 個別ID
	*/
	unsigned __int8 GetID() const;
	/**
	*@brief	:ゲートを開放する
	*@return:bool 開放処理が開始された場合true
	*/
	bool ToOpen();
	/**
	*@brief	:ゲートを閉鎖する
	*@return:bool 閉鎖処理が開始された場合true
	*/
	bool ToClose();
	/**
	*@brief	:登録されている描画を切るX位置を返す
	*@return:float 位置のX座標
	*/
	float Get_Door_x() const;
	/**
	*@brief	:登録されている描画を切るW座標を返す
	*@return:float 位置のW座標
	*/
	float Get_Door_w() const;

	Sound soundOpen;
	Sound soundClose;
};