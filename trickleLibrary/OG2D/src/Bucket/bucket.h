#pragma once


/**
* @brief ’その’バケッツ
* @author Heewon Kim
* @date 2018-03-30
*/

#include "OGSystem\OGSystem.h"
#include "Object\Object.h"
#include "Paint\Paint.h"	//カラー使用をするため

class Bucket : public GameObject, public TaskObject {

private:
	const Box2D BUCKET_NOTHING = Box2D(0, 0, 256, 256);
	const Box2D BUCKET_WATER = Box2D(256, 0, 256, 256);
	const Box2D BUCKET_WATERMAX = Box2D(512, 0, 256, 256);
	Paint::PaintColor* color;
	GameObject WaterHitObj;
	Box2D GetSpriteCrop() const;
	bool BucketWaterCreate();
	bool isObjectCollided();
	bool IsOutCheck;
	unsigned int WaterOutTime;
public:
	explicit Bucket();
	explicit Bucket(Vec2& pos);
	virtual ~Bucket();

	typedef std::shared_ptr<Bucket> SP;
	static SP Create(Vec2&, bool = true);
	bool Initialize(Vec2& pos);
	void UpDate();
	void Render2D();
	bool Finalize();
	

	void CheckMove(Vec2 &);

	void HoldCheck(bool = true);
	bool GetHold() const;
	void WaterIsHitCheck();
	/**
	* @brief	バケッツから水をこぼします
	* @return	バケッツの中にあった量だけの水のアドレス地
	* @note	new使ったので必ず消してください
	*/
	float capacity;
	Vec2 gravity;			//重力
	bool hold;				//プレイヤがバケツを持っているかの判断
	int invi;				//無敵時間(水との判定を行わない時間)

	//サウンドの生成について
	Sound soundP;
	Sound soundD;
	Sound sound;
	bool putsoundplay;


private:
	Texture tex;

	std::string putsoundname;     //バケツを置く音
	std::string dropsoundname;    //水をこぼす音
	std::string soundname;
};