#include "Recorder.h"
using namespace RecDef;

void Recorder::printLog(const std::string& logmsg) {
	if (isLogging)
		std::cout << logmsg << std::endl;
}

Recorder* Recorder::Create(const std::string& fName, const bool& isLogging = false) {
	auto ret = new Recorder();
	ret->isLogging = isLogging;
	if (!ret->Initialize(fName)) {
		delete ret;
		return nullptr;
	}
	return ret;
}

void Recorder::Destroy() {
	gameTimer->Stop();
	if (recThread.joinable())
		recThread.join();
	fileWriter.close();
	if (fileWriter.is_open()) {
		printLog(fileName + "ファイル記録に問題がありました");
	}
	else {
		printLog(fileName + "ファイルの記録を中止します");
	}
	delete this;
}

bool Recorder::isKeyListenable() const {
	return
		inputListener &&
		!watchKeys.empty();
}

bool Recorder::Initialize(const std::string& fName) {
	fileName = fName;
	fileWriter.open(fName, std::ios::out | std::ios::binary);
	if (!fileWriter.is_open()) {
		return false;
	}
	return true;
}

bool Recorder::isAlreadyRecorded(const WatchKey& key, const KeyState& status) const {
	return key.second == status;
}

void Recorder::WriteRecord(const std::string& msg) {
	inputQueue.push(msg);
}

void Recorder::ActivateKeyRecord(Input* in) {
	inputListener = in;
}

void Recorder::AddKeyInputWatchList(const Input::in& key) {
	watchKeys.push_back(WatchKey::pair(key, KeyState::Idle));
}

void Recorder::operator>>(const Input::in& key) {
	AddKeyInputWatchList(key);
}

void Recorder::RecordStart() {
	recThread = std::thread(&Recorder::Recorde, this);
}

void Recorder::RecordJoysticks() {
	isRecordSticks = true;
}

void Recorder::Recorde() {
	Time localTimer;
	gameTimer = &localTimer;
	localTimer.Start();
	while (localTimer.isplay()) {
		if (!inputQueue.empty()) {
			std::string act = inputQueue.front();
			std::string curTime = std::to_string(localTimer.GetTime());
			std::string msg = curTime + " / " + act;
			fileWriter << msg.c_str() << std::endl;
			printLog(msg);
			inputQueue.pop();
		}
		if (isKeyListenable())
			RecordeButton();
		if (isRecordSticks)
			RecordeSticks();
	}
}

void Recorder::RecordeButton() {
	for (auto& k : watchKeys) {
		bool isRecordable = false;
		if (inputListener->down(k.first) && !isAlreadyRecorded(k, KeyState::PRESS))		{ isRecordable = true;	k.second = KeyState::PRESS; }
		if (inputListener->up(k.first)	 && !isAlreadyRecorded(k, KeyState::RELEASE))	{ isRecordable = true;	k.second = KeyState::RELEASE; }
		if (isRecordable) {
			std::string curTime = std::to_string(gameTimer->GetTime());
			std::string button  = std::to_string(k.first);
			std::string status	= std::to_string(k.second);
			std::string msg = curTime + "/" + button + "/" + status;
			fileWriter << msg.c_str() << std::endl;
			printLog(msg);
		}
	}
}

void Recorder::RecordeSticks() {
	auto isRecordeable = [&](const In::AXIS& b) -> bool {
		return inputListener->axis(b) != 0.f;
	};

	for (auto& s : sticks) {
		if (isRecordeable(s)) {
			std::string curTime = std::to_string(gameTimer->GetTime());
			std::string stickName = sticksName[s];
			std::string tilt = std::to_string(inputListener->axis(s));
			std::string msg = curTime + "/" + "StickInput/" + stickName + "/" + tilt;
			fileWriter << msg.c_str() << std::endl;
			printLog(msg);
		}
	}
}
