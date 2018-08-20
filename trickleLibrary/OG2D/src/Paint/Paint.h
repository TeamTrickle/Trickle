#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
/**
*@brief	:絵具オブジェクト
*/
class Paint final: public GameObject, public TaskObject
{
public:
	/**
	*enum PaintColor
	*絵具用のカラー色
	*/
	enum PaintColor
	{
		//!	赤
		Red,
		//!	青
		Blue,
		//!	紫
		Purple,
		//! 無地
		Normal,
	};
private:
	//!	色情報
	PaintColor* color;
	//!	画像の情報
	Texture* image;
	//! 描画位置
	Box2D draw;
	//!	描画画像位置
	Box2D src;
	//!	スマートポインタ
	typedef std::shared_ptr<Paint> SP;
	/**
	*@brief	:描画位置を指定する
	*/
	void Setsrc();
	/**
	*@brief	:水との当たり判定
	*@return:当たっていればtrue
	*/
	bool WaterHit();
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@bried	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:constructor
	*@param	:Vec2 pos 生成位置
	*@param	:Vec2 size 大きさ
	*@param	:PaintColor color_ 色情報
	*/
	explicit Paint(const Vec2 & pos, const Vec2 & size, const PaintColor & color_);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Paint();
	/**
	*@brief	:タスク生成
	*@param	:Vec2 pos 生成位置
	*@param	:Vec2 size 大きさ
	*@param	:PaintColor color_ 色情報
	*@return:生成に失敗した場合nullptr
	*/
	static SP Create(const Vec2& pos, const Vec2& size, const PaintColor& color_);
	/**
	*@brief	:使用画像を登録する
	*@param	:Texture* tex 画像情報
	*/
	void SetTexture(Texture* tex);
};