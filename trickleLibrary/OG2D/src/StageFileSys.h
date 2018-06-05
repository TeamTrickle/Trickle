#pragma once
#include <string>

namespace Stage {
	std::string GetSaveFilePath(const std::string& original) {
		auto pathBeforeExtIdx = original.find('.');
		std::string ret = original.substr(0, pathBeforeExtIdx);
		ret += "_save.txt";
		return ret;
	}
}