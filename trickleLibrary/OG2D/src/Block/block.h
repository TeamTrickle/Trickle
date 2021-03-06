#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Bucket\bucket.h"

class Block : public GameObject, public TaskObject {

private:
	/**
	@author Heewon Kim
	@brief 当たり判定関連全体的な判定を行います
	@return 何かにぶつかったのかの判定
	*/
	bool isCollideSomething();
	bool footCheck();

	//サウンドのファイルネーム格納
	std::string soundname;
public:
	explicit Block();
	explicit Block(Vec2& pos);
	virtual ~Block();

	typedef std::shared_ptr<Block> SP;
	static SP Create(Vec2&, bool = true);

	//bool HitMap;
	//float speed;
	Vec2 speed;
	Vec2 gravity;
	GameObject foot;
	unsigned __int8 Cnt;
	bool Initialize(Vec2&);
	void UpDate();
	void Render2D();
	bool Finalize();

	//めり込まない処理
	void CheckMove(Vec2 &e_);
	//プレイヤーとブロックの当たった時の処理
	void PlCheckHit(GameObject &p);
	//プレイヤーとブロックの当たり判定フラッグ
	bool plhit;
	//押されているかつ壁に当たっていないならtrue	
	bool isPushed;



	//プレイヤ側から、移動する量を持ってくる
	Vec2 GetMove(Vec2& move);
	//プレイヤーに移動不可分の値を返す
	Vec2 BackMove();

	Vec2 backmove;

	//サウンドを生成する
	Sound sound;
	bool soundstart;

	//プレイヤとの当たり判定に使用　　使わなくなった
	void PlCheckHitR(GameObject &p);
	void PlCheckHitL(GameObject &p);
	void PlCheckHitH(GameObject &p);
	void PlCheckHitF(GameObject &p);
	//プレイヤとの当たり判定用フラッグ 使わなくなった
	bool plhitR;
	bool plhitL;
	bool plhitH;
	bool plhitF;
	//オブジェクトを生成するため 使わなくなった
	GameObject footBase;
	GameObject headBase;
	GameObject leftBase;
	GameObject rightBase;

private:
	Texture* tex;
};