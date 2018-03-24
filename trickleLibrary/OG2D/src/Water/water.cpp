#include "water.h"



Water::Water() {

}

Water::~Water() {

}


bool Water::Initialize() {
	return true;
}

void Water::Update() {
	
}

void Water::Render() {
	Box2D src = drawRange[currentState];
	Box2D draw(0.f, 0.f, src.w, src.h);
	draw.Offset(Object::position.x, Object::position.y);
	tex.Draw(draw, src);
}

void Water::Finalize() {
	tex.Finalize();
}

void Water::SetState(const State& s_) {
	this->currentState = s_;
}

Water::State Water::GetState() const {
	return currentState;
}