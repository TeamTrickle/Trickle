#pragma once

#include "OGSystem\OGsystem.h"

class Back : public TaskObject
{
	Texture backImg;
	Vec2 size;
	bool isScroll;
	Vec2* mapSize;
	void Init(const std::string&);
	Vec2* texPos;
	float* Center;
	float* Xsize;
	float* Tsize;
public:
	Back(const std::string&,Vec2&);
	Back(const std::string&, float, float);
	Back(const std::string&, int, int);
	void UpDate() override;
	void Render2D() override;
	typedef std::shared_ptr<Back> SP;
	static SP Create(const std::string&, Vec2&, bool = true);
	static SP Create(const std::string&, float, float, bool = true);
	static SP Create(const std::string&, int, int, bool = true);
	void SetScroll(bool = true);
	virtual ~Back();
};