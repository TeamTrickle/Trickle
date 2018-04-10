#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__


/**
 * @brief 当たり判定全般管理
 * @date 2018-03-27
 * @author Heewon Kim
 */

#include <array>
#include <vector>
#include "Object\Object.h"

class CollisionManager {

public:
	explicit CollisionManager();
	virtual ~CollisionManager();
	
	/**
	 * @brief 当たり判定を行いたいオブジェクトを登録します
	 * @param Object* オブジェクトのアドレス
	 */
	void AddChild(Object*);

	/**
	 * @brief 当たり判定を実際に行う部分
	 * @note Updateで呼ぶこと
	 */
	void Run();

	void Destroy();

	bool operator-(const Object*);

	void operator+=(Object*);

private:
	std::vector<Object*> objs;
};

#endif