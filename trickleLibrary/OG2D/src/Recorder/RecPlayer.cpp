#include "RecPlayer.h"

void RecPlayer::printLog(const std::string& logmsg) {
	if (isDbgMode)
		std::cout << logmsg << std::endl;
}

RecPlayer* RecPlayer::Create(const std::string& fName, const bool& dbgFlag = false) {
	auto ret = new RecPlayer();
	ret->isDbgMode = dbgFlag;
	if (!ret->Initialize(fName)) {
		delete ret;
		return nullptr;
	}
	return ret;
}

bool RecPlayer::Initialize(const std::string& fName) {
	fileName = fName;

	std::ifstream fileReader(fileName, std::ios::in | std::ios::binary);
	if (!fileReader.is_open()) {
		printLog("RecPlayer Error - No such file");
		return false;
	}

	printLog("=== File open : " + fileName + " ===");

	std::string buf;
	while (!fileReader.eof()) {
		fileReader >> buf;
		std::vector<std::string> commands = Split(buf, '/');

		float time = std::stof(commands[0]);

		// キー入力関連イベント
		if (commands.size() == 3) {
			Input::in key = (Input::in)std::stoi(commands[1]);
			RecDef::KeyState state = (RecDef::KeyState)std::stoi(commands[2]);
			recData.push(KeyEventTimeline::pair(time, RecDef::WatchKey::pair(key, state)));
			printLog("Read Successful - " + buf);
		}
	}
	fileReader.close();
	printLog("=== File closed ===");

	backupData = recData;
	timer.Start();

	return true;
}

bool RecPlayer::isPlayable() const {
	return timer.isplay();
}

bool RecPlayer::isEventExist(const KeyState& s) {
	return events.find(s) != events.end();
}

void RecPlayer::Reset() {
	recData = backupData;
	timer.Stop();
	timer.Start();
	printLog("RecPlayer --- Repeat!");
}

std::vector<std::string> RecPlayer::Split(const std::string& fullStr, const char& keyword)
{
	std::vector<std::string> ret;
	std::string buf = "";
	for (auto& c : fullStr) {
		if (c == keyword) {
			ret.push_back(buf);
			buf = "";
			continue;
		}
		buf += c;
	}
	if (!buf.empty())
		ret.push_back(buf);
	return ret;
}

void RecPlayer::Destroy() {
	try {
		delete this;
	}

	catch (std::exception) {}
}

void RecPlayer::Play() {
	if (!isEnded()) {
		if (isPlayable()) {
			float curTime = timer.GetTime();
			auto curActivity = recData.front();
			if (curTime >= curActivity.first) {
				printLog("Read from file - " +
					std::to_string(float(curActivity.first)) + " / " +
					std::to_string(int(curActivity.second.first)) + " / " +
					std::to_string(int(curActivity.second.second)));
				if (isEventExist(curActivity.second)) {
					events[curActivity.second]();
				}
				playerKeyState[curActivity.second.first] = curActivity.second.second;
				recData.pop();
			}
			for (auto& keyEvent : playerKeyState) {
				if (keyEvent.second == RecDef::KeyState::PRESS) {
					auto pressingKey = KeyState::pair(keyEvent.first, RecDef::KeyState::PRESS);
					if (isEventExist(pressingKey))
					events[pressingKey]();
				}
			}
		}
	}
	else if (isRepeat) {
		// Callback関数が存在する場合
		if (endCallback) {
			if (endCallback()) {
				Reset();
			}
		}
		// ないとただ繰り返す
		else {
			Reset();
		}
	}
}

void RecPlayer::AddKeyEvent(const Input::in& key,
							const RecDef::KeyState& state,
							const std::function<void()>& e) {
	events[KeyState::pair(key, state)] = e;
	playerKeyState[key] = RecDef::KeyState::Idle;
}

bool RecPlayer::isEnded() const {
	return recData.empty();
}

void RecPlayer::SetRepeat(const bool& r) {
	isRepeat = r;
}

void RecPlayer::SetEndCallback(const std::function<bool()>& cb) {
	endCallback = cb;
}

void RecPlayer::SetPause() {
	if (timer.isplay())
		timer.Pause();
}

void RecPlayer::SetPlay() {
	if (!timer.isplay())
		timer.Pause();
}
