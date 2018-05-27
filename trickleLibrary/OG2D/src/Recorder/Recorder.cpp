#include "Recorder.h"


void Recorder::printLog(const std::string& logmsg) {
	if (isLogging)
		std::cout << logmsg << std::endl;
}

Recorder* Recorder::Create(const std::string& fName, const bool& isLogging = false) {
	auto ret = new Recorder();
	if (!ret->Initialize(fName)) {
		delete ret;
		return nullptr;
	}
	ret->isLogging = isLogging;
	return ret;
}

void Recorder::Destroy() {
	gameTimer.Stop();
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

bool Recorder::Initialize(const std::string& fName) {
	fileName = fName;
	fileWriter.open(fName, std::ios::binary | std::ios::out);
	if (!fileWriter.is_open()) {
		return false;
	}
	recThread = std::thread(&Recorder::Recorde, this);
	return true;
}

void Recorder::Recorde() {
	gameTimer.Start();
	while (gameTimer.isplay()) {
		printLog(std::to_string(gameTimer.GetTime()));
	}
}