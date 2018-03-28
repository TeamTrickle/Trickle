#include "CollisionManager.h"

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

void CollisionManager::AddChild(Object* obj) {
	objs.push_back(obj);
}

void CollisionManager::Run() {
	for (auto& i : objs) {
		i->isCollided = false;
		for (auto& j : objs) {
			if (i == j || i->CollisionProcess == nullptr) continue;
			if (i->hit(*j)) {
				i->CollisionProcess(*j);
				
			}
		}
	}
}