#include "Task_StageAlert.h"
#include <fstream>

StageAlert::~StageAlert() {
	this->Finalize();
}

StageAlert::SP StageAlert::Create(bool flag_)
{
	auto to = StageAlert::SP(new StageAlert());
	if (to)
	{
		to->me = to;
		if (flag_) {
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize()) {
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool StageAlert::Initialize() {
	__super::Init((std::string)"stagealert");
	__super::SetDrawOrder(0.8f);
}

std::string StageAlert::GetSaveFilePath(const std::string& original) const {
	auto pathBeforeExtIdx = original.find('.');
	std::string ret = original.substr(0, pathBeforeExtIdx);
	ret += "_save.txt";
	return ret;
}

void StageAlert::UpDate() {

}

void StageAlert::Render2D() {

}

void StageAlert::Finalize() {

}



bool StageAlert::SetStageData(const std::string& fPath) {
	std::ifstream file(fPath, std::ios::in);
	if (file.is_open()) {
		file >> stageName;
		std::ifstream saveFile(GetSaveFilePath(fPath), std::ios::in);
		for (auto& a : achievements) {
			file >> a.first;
			if (saveFile.is_open()) {
				std::string buf;
				saveFile >> buf;
				a.second = (stoi(buf) != 0) ? true : false;
			}
			else {
				a.second = false;
			}
		}
		return true;
	}
	return false;
}