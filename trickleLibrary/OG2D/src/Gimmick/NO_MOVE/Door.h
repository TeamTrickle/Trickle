///Game中用のswitchに連動した開閉を行うclass
///constructor	pos = 位置,size = 大きさ,isOpen = 開いているか(true = 開いている,false = 閉じている)
///ToOpenで開(成功true,失敗false)、ToCloseで閉(成功true,失敗false)、IsOpen(開true,閉false)で開いているかを返す
///GetIDでDoorに設定されているIDを返す、IDは生成時に決定される
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:ゲーム中の扉オブジェクト
*/
class Door :public GameObject, public TaskObject
{
public:
	/**
	*@enum Direction
	*扉の向き
	*/
	enum Direction
	{
		//!	横
		WIDTH,
		//!	縦
		HEIGHT,
	};
private:
	//!	個別ID
	unsigned __int8 id;
	//! 開いているかどうか
	bool isOpen;
	//! 移動中かどうか
	bool isMove;
	//! 前回の開き状態
	bool preIsOpen;
	//! 経過時間
	float timeCnt;
	//!	原点位置
	Vec2 originPos;
	//! 使用画像のポインタ
	Texture* image;
	//! 描画位置
	Box2D draw;
	//! 描画画像位置
	Box2D src;
	//! 向き
	Direction direction;
	//!	オブジェクトの位置を計算するのに必要となる値のアドレスを保管
	float* ch_Value[3];
	//! 描画用回転値
	float rotate;
	//! スマートポインタ
	typedef std::shared_ptr<Door> SP;
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:constructor
	*@param	:Vec2 pos	位置
	*@param	:Vec2 size	大きさ
	*@param	:bool isOpen	開閉状態
	*@param	:Direction dire	向き
	*/
	Door(const Vec2& pos, const Vec2& size, const bool isOpen, const Direction& dire);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Door();
	/**
	*@brief	:タスク生成
	*@param	:Vec2 pos	位置
	*@param	:Vec2 size	大きさ
	*@param	:bool isOpen	開閉状態
	*@param	:Direction dire	向き
	*@return:Door 生成に失敗した場合nullptr
	*/
	static SP Create(const Vec2& pos,const Vec2& size,const bool isOpen,const Direction& dire);
	/**
	*@brief	:扉を開ける
	*@return:bool 成功した場合true
	*/
	bool ToOpen();
	/**
	*@brief	:扉を閉める
	*@return:bool 成功した場合true
	*/
	bool ToClose();
	/**
	*@brief	:扉の状態を反転にする
	*@return:bool 変更後の状態
	*/
	bool changeIsOpen();
	/**
	*@brief	:現在の開閉状態を返す
	*@return:bool 開閉状態
	*/
	bool IsOpen() const;
	/**
	*@brief	:現在動いているかを返す
	*@return:bool 動いている場合true
	*/
	bool IsMove() const;
	/**
	*@brief	:使用画像を登録する
	*@param	:Texture* tex	画像のポインタ
	*/
	void SetTexture(Texture* tex);
	/**
	*@brief	:個別IDを返す
	*@return:unsgined __int8 個別ID
	*/
	unsigned __int8 GetID() const;
};