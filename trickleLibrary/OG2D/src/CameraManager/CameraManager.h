
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:タイトルで使用するカメラの移動を行うclass
*/
class CameraManager
{
	//!	カメラを移動させる範囲
	Box2D Range;
	//!	現在の世界の大きさ
	Box2D Size;
	//!	カメラの実際値
	Box2D RealRange;
	//!	移動値
	Vec2 est;
	//!	ターゲットの位置とサイズ
	Box2D pretarget;
	//!	カメラをスクロールさせる対象
	GameObject* target;
	/**
	*@brief	:スクロールする範囲を指定する
	*@param	:Box2D range	範囲の位置とサイズ
	*/
	void SetRange(const Box2D& range);

public:
	/**
	*@brief	:内部値初期化
	*/
	CameraManager();
	/**
	*@brief	:内部値解放
	*/
	~CameraManager();
	/**
	*@brief	:ターゲットを登録
	*@param	:GameObject* taget	ターゲットのオブジェクトのポインタ
	*/
	void SetObject(GameObject* target);
	/**
	*@brief	:現在の世界のサイズを指定する
	*@param	:Box2D size	世界の大きさ
	*/
	void SetSize(const Box2D& size);
	/**
	*@brief	:カメラをターゲットに合わせる
	*/
	void move();
	/**
	*@brief	:ターゲットを解除する
	*/
	void DeleteObject();
};
/**
*@brief	:カメラの即移動防止のための拡張機能
*/
class CameraEasing
{
	//!	イージングのX用
	Easing easing_x;
	//! イージングのY用
	Easing easing_y;
	//!	開始位置のポインタ
	Vec2* start;
	//!	終了位置のポインタ
	Vec2* end;
public:
	/**
	*@brief	:内部値初期化
	*/
	CameraEasing();
	/**
	*@brief	:内部値解放
	*/
	~CameraEasing();
	/**
	*@brief	:カメラの移動の終了位置の登録
	*@param	:Vec2 end	終了位置
	*/
	void SetEndPos(const Vec2& end);
	/**
	*@brief	:カメラの移動
	*/
	void CameraMove();
	/**
	*@brief	:カメラを移動させているかどうか
	*@return:bool 動いている最中であればtrue
	*/
	bool IsPlay();
	/**
	*@brief	:カメラの移動を止める
	*/
	void MoveEnd();
};