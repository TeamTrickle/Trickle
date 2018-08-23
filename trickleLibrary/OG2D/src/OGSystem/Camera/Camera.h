/**
*GL機能を使用し2D上でのカメラを扱うclass
*既存GameEngineを使用している場合は内部で宣言されている
*使用しない場合は2Dの描画のために１つ生成する必要がある
*/
#pragma once
#include "OGSystem\_OGsystem.h"
/**
*@brief	:カメラ2D
*/
class Camera2D
{
public:
	/**
	*@brief	:constructor
	*/
	Camera2D();
	/**
	*@brief	:constructor
	*@param	:Box2D b 位置とサイズ
	*/
	Camera2D(const Box2D& b);
	/**
	*@brief	:destructor
	*/
	~Camera2D();
	/**
	*@brief	:初期化処理
	*@param	:Box2D b 位置とサイズ
	*/
	void Initialize(const Box2D& b);
	/**
	*@brief	:更新処理
	*/
	void UpDate() const;
	/**
	*@brief	:位置を移動させる
	*@param :Vec2 move 移動値
	*/
	void MovePos(Vec2& move);
	/**
	*@brief	:位置を設定する
	*@param	:Vec2 pos 位置
	*/
	void SetPos(Vec2& pos);
	/**
	*@brief	:サイズを設定する
	*@param	:Vec2 size 大きさ
	*/
	void SetSize(Vec2& size);
	/**
	*@brief	:サイズを動かす
	*@param	:Vec2 move 移動値
	*/
	void MoveSize(Vec2& move);
	/**
	*@brief	:カメラ位置のX座標を設定する
	*@param	:float x 座標値
	*/
	void SetPos_x(const float& x);
	/**
	*@brief	:カメラ位置のY座標を設定する
	*@param	:float y 座標値
	*/
	void SetPos_y(const float& y);
	/**
	*@brief	:カメラの横サイズを変える
	*@param	:float w 横サイズ
	*/
	void SetSize_w(const float& w);
	/**
	*@brief	:カメラの縦サイズを変える
	*@param	:float w 縦サイズ
	*/
	void SetSize_h(const float& h);
	/**
	*@brief	:カメラの位置を返す
	*@return:Vec2 カメラ位置
	*/
	Vec2 GetPos() const;
	/**
	*@brief	:カメラのサイズを返す
	*@return:Vec2 カメラの大きさ
	*/
	Vec2 GetSize() const;
private:
	//!	実際位置
	Box2D cameraPos;
	//!	位置
	Vec2 position;
	//! サイズ
	Vec2 Scale;
};