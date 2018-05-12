#pragma once


/**
 * @brief ’その’バケッツ
 * @author Heewon Kim
 * @date 2018-03-30
 */

#include "Water\water.h"
#include "Map\Map.h"

class Bucket : public GameObject,public TaskObject {

private:
	const Box2D BUCKET_NOTHING = Box2D(0, 0, 64, 64);
	const Box2D BUCKET_WATER = Box2D(64, 0, 64, 64);
	Box2D GetSpriteCrop() const;

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

	void SetParent(GameObject*);
	bool HasParent() const;
	void CheckMove(Vec2 &e_, Map &map, Bucket &bucket);

	bool WaterHit(Water*);
	void HoldCheck(bool = true);
	bool GetHold() const;

	/**
	 * @brief	バケッツから水をこぼします
	 * @return	バケッツの中にあった量だけの水のアドレス地
	 * @note	new使ったので必ず消してください
	 */
	Water* Spill();
	float capacity;
	Vec2 gravity;      //重力
	bool hold;         //プレイヤがバケツを持っているかの判断
private:
	GameObject * parent;
	Texture tex;
};