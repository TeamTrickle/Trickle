#pragma once
#include "OGSystem\OGsystem.h"
#include <fstream>
#include <array>




class StageInfoRes {
private:
	typedef std::pair<Box2D, bool> Achievement;

	static std::vector<std::string> SplitString(const std::string&, const char&);
	static Box2D stringToBox2D(const std::string&);
	Texture* loadFromTexture(std::string&);

public:
	 StageInfoRes(const std::string&);
	~StageInfoRes();

public:
	const static int MAX_ACHIEVEMENT = 3;
	Texture*									atlas;
	Texture*									mapInfo;
	Box2D										title;
	std::array<Achievement, MAX_ACHIEVEMENT>	achievement;

private:
	std::string									atlasFileName;
	std::string									mapInfoFileName;
};