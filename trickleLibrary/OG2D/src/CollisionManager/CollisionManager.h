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

	template <typename T>
	void AddCollisionFunction(void (T::*function_)(std::vector<Object*>*), Object* obj_) {
		std::function<void(std::vector<Object*>*)> obj = std::bind(function_, std::placeholders::_1);
		collisionFunctions.push_back(obj);
	}	

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
	std::vector <std::function<void(std::vector<Object*>*)>> collisionFunctions;
};

#endif