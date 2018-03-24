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
	tex.Draw(draw[currentState],
		src[currentState]);
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