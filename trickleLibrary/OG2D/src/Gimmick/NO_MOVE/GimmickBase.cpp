#include "GimmickBase.h"



GimmickBase::GimmickBase(Vec2 pos, Vec2 range, Dir dir, bool active)
	:
	range_(range),
	dir_(dir),
	active_(active)
{
	position = pos;
}


GimmickBase::~GimmickBase() {
}

std::shared_ptr<GimmickBase> GimmickBase::Create(Vec2 pos, Vec2 range, Dir dir, bool active) {
	std::shared_ptr<GimmickBase> obj(new GimmickBase(pos, range, dir, active));
	if(obj){
		obj->me = obj;
		OGge->SetTaskObject(obj);
		if(!obj->Initialize(pos, range, dir, active)){
			obj->Kill();
		}
		return obj;
	}
	return nullptr;
}

bool GimmickBase::Initialize(Vec2 pos, Vec2 range, Dir dir, bool active) {
	return true;
}

void GimmickBase::setTaskName(const std::string& name) {
	taskName_ = name;
	__super::Init(taskName_);
}

void GimmickBase::setHitBase(Vec2 pos, Vec2 range) {
	hitBase_.CreateObject(Cube, pos, range);
}

GameObject GimmickBase::getHitBase() {
	return hitBase_;
}

void GimmickBase::changeActive() {
	active_ = !active_;
}

void GimmickBase::affectWater() {}

void GimmickBase::setDirection(Dir d) {
	dir_ = d;
}

GimmickBase::Dir GimmickBase::getDirection() {
	return dir_;
}

void GimmickBase::setActive(bool a) {
	active_ = a;
}

bool GimmickBase::isActive() {
	return active_;
}
