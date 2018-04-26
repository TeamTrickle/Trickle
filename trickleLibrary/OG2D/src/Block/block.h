#pragma once
#ifndef __BLOCK_H__          //これなに？
#define __BLOCK_H__


#include "Water\water.h"
#include "Map\Map.h"
#include "CollisionManager\CollisionManager.h"
//#include "Object\Object.h"

class Block : public Object {

public:
	explicit Block();
	explicit Block(Vec2 pos);
	virtual ~Block();

	//bool HitMap;
	//float speed;
	Vec2 speed;
	Vec2 gravity;
	bool Initialize(Vec2);
	void Update(Map &map, Block &block, Object& p);
	void Render();
	void Finalize();

	void SetParent(Object*);
	bool HasParent() const;

	//めり込まない処理
	void CheckMove(Vec2 &e_, Map &map, Block &bock);
	//プレイヤーとブロックの当たった時の処理
	void PlCheckHit(Object &p, Block &block);
	//プレイヤーとブロックの当たり判定フラッグ
	bool plhit;
	//プレイヤ側から、移動する量を持ってくる
	Vec2 GetMove(Vec2 move);
	//プレイヤーに移動不可分の値を返す
	Vec2 BackMove();

	Vec2 backmove;

	//プレイヤとの当たり判定に使用　　使わなくなった
	void PlCheckHitR(Object &p);
	void PlCheckHitL(Object &p);
	void PlCheckHitH(Object &p);
	void PlCheckHitF(Object &p);
	//プレイヤとの当たり判定用フラッグ 使わなくなった
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//オブジェクトを生成するため 使わなくなった
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;

private:
	Object * parent;
	Texture tex;
};

#endif