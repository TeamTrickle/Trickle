#pragma once
//_____________________________
//|ゲームオブジェクト            
//|履歴：2018/03/20   
//|____________________________
#include "OGSystem\OGlib.h"
#include "OGSystem\Collision\Collision.h"
#include "OGSystem\TaskObject.h"
/**
*enum Objform
*オブジェクトの形
*/
enum Objform
{
	//! 無
	Non,
	//!	円
	Ball,
	//! 矩形
	Cube,
};
/**
*@brief	:ゲームで使用するオブジェクト用class
*/
class GameObject 
{
	//! 当たり判定を行う有無
	bool isCheck;
public:
	//! オブジェクトの状態
	Objform objform;
	//! 位置
	Vec2 position;
	//! サイズ
	Vec2 Scale;
	//! 半径
	Vec2 Radius;
	//! 回転度
	float angle;
	//! 矩形当たり判定
	CollisionBox collisionCube;
	//! 円当たり判定
	CollisionCircle collisionBall;
	//! 重力の有無
	bool Gravity;
	//! 質量
	float mass;
	//! オブジェクトのタグ名
	std::string objectTag;
	/**
	*@brief	:GameObject同士の当たり判定
	*@param	:GameObject o 相手のオブジェクト
	*@return:bool 当たっていればtrue
	*/
	bool hit(GameObject& o);
	/**
	*@fn
	*回転を行わない当たり判定
	*@brief	:矩形Object同士の簡易当たり判定
	*@param	:GameObject o 相手のオブジェクト
	*@return:bool 当たっていればtrue
	*/
	bool CubeHit(GameObject& o);
	/**
	*@brief	:constructor
	*/
	GameObject();
	/**
	*@brief	:constructor
	*@param	:Objform form オブジェクトの形
	*@param	:Vec2 _posi 位置
	*@param	:Vec2 _Sca 大きさ
	*@param	:float _ang	回転値
	*/
	GameObject(
		const Objform& form,
		const Vec2& _posi,
		const Vec2& _Sca,
		float _ang = 0.0f
	);
	/**
	*@brief	:destructor
	*/
	~GameObject();
	/**
	*@brief	:オブジェクトの情報を登録する
	*@param	:Objform form オブジェクトの形
	*@param	:Vec2 _posi 位置
	*@param	:Vec2 _Sca 大きさ
	*@param	:float _ang	回転値
	*/
	void CreateObject(
		const Objform& form,
		const Vec2& _posi,
		const Vec2& _Sca,
		const float _ang = 0.0f
	);
	/**
	*@brief	:当たり判定に線を引く
	*/
	void LineDraw();
	/**
	*@brief	:当たり判定を付ける
	*@param	:bool flag 当たり判定を行う設定
	*/
	void HitCheck(bool flag = true);
	/**
	*@brief	:当たり判定を行う範囲かを返す
	*@param	:Vec2 pos 相手の位置
	*@param	:Vec2 size 相手の大きさ
	*@return:bool 判定内であればtrue
	*/
	bool IsObjectDistanceCheck(const Vec2& pos, const Vec2& size);
	/**
	*@brief	:大きな判定範囲を表示する
	*/
	void LineDistanceDraw();
	/**
	*@brief	:初期設定移動処理(未実装)
	*/
	virtual void Move();
	/**
	*@brief	:初期設定重力処理(未実装)
	*/
	virtual void Friction();
private:
};