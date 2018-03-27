#include "CollisionManager.h"

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

void CollisionManager::AddChild(Object* obj) {
	objs.push_back(obj);
}

void CollisionManager::Run() {
	for (auto& i : objs) 
		for (auto& j : objs) {
			if (i == j) continue;
			if (i->hit(*j))
				i->Collide(*j);
		}
}