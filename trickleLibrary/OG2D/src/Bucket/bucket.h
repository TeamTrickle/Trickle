#ifndef __BUCKET_H__
#define __BUCKET_H__


/**
 * @brief ’その’バケッツ
 * @author Heewon Kim
 * @date 2018-03-30
 */

#include "Water\water.h"
#include "Map\Map.h"

class Bucket : public Object {

private:
	const Box2D BUCKET_NOTHING = Box2D(0, 0, 64, 64);
	const Box2D BUCKET_WATER = Box2D(64, 0, 64, 64);
	Box2D GetSpriteCrop() const;

public:
	explicit Bucket();
	explicit Bucket(Vec2 pos);
	virtual ~Bucket();

	bool Initialize(Vec2 pos);
	void Update(Map &map, Bucket &bucket);
	void Render();
	void Finalize();

	void SetParent(Object*);
	bool HasParent() const;
	void CheckMove(Vec2 &e_, Map &map, Bucket &bucket);

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
	Object * parent;
	Texture tex;
};



#endif