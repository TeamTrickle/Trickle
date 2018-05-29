#include "RecPlayer.h"

RecPlayer* RecPlayer::Create(const std::string& fName, const bool& dbgFlag = false) {
	auto ret = new RecPlayer();
	if (!ret->Initialize()) {
		delete ret;
		return nullptr;
	}
	return ret;
}

bool RecPlayer::Initialize(const std::string& fName) {
	fileName = fName;
	return true;
}

void RecPlayer::Destroy() {
	
	delete this;
}