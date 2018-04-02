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
	void Update(Map &map, Block &block);
	void Render();
	void Finalize();

	void SetParent(Object*);
	bool HasParent() const;


	//マップとの当たり判定に使用
	void CreateFoot();
	void CreateHead();
	void CreateLeft();
	void CreateRight();

	//プレイヤとの当たり判定に使用
	void PlCheckHitR(Object &p);
	void PlCheckHitL(Object &p);
	void PlCheckHitH(Object &p);
	void PlCheckHitF(Object &p);

	//プレイヤとの当たり判定用フラッグ
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//マップとの当たり判定用フラッグ
	bool maphitR;
	bool maphitL;
	bool maphitH;
	bool maphitF;

	//めり込まない処理
	void CheckMove(Vec2 &e_, Map &map , Block &bock);

	//オブジェクトを生成するため
	Object footBase;
	Object headBase;
	Object leftBase;
	Object rightBase;

private:
	Object * parent;
	Texture tex;
};

#endif