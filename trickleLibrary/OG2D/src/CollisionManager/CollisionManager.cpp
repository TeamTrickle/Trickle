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
			bool isCollided = i->isCollidedGlobal;
			if (i->hit(*j)) {
				if (!i->isCollidedGlobal && i->CollisionIn) {
					i->isCollidedGlobal = true;
					i->CollisionIn(*j);
				}
				else
					i->CollisionProcess(*j);
			}
			else {
				if (i->isCollidedGlobal && i->CollisionOut)
					i->CollisionOut(*j);
				i->isCollidedGlobal = false;
			}
		}
	}
}

void CollisionManager::Destroy() {
	while (!objs.empty())
		objs.pop_back();
}

bool CollisionManager::operator-(const Object* o_) {
	for (auto it = objs.begin(); it != objs.end(); it++)
		if ((*it) == o_) {
			objs.erase(it);
			return true;
		}
	return false;
}

void CollisionManager::operator+=(Object* o_) {
	this->AddChild(o_);
}