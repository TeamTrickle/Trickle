#pragma once

#include "OGSystem\OGsystem.h"

class Back : public TaskObject
{
	Texture backImg;
	Vec2 size;
public:
	Back(std::string&,Vec2&);
	Back(std::string&, float, float);
	Back(std::string&, int, int);
	void Render2D();
	typedef std::shared_ptr<Back> SP;
	static SP Create(std::string&, Vec2&, bool = true);
	static SP Create(std::string&, float, float, bool = true);
	static SP Create(std::string&, int, int, bool = true);
	virtual ~Back();
};