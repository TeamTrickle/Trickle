#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
public:
	enum Fead
	{
		In, Out
	};
private:
	Texture image;	//‰æ‘œ
	Box2D draw;		//–ˆ‰ñéŒ¾‚·‚é‚æ‚è‚±‚±‚É‘‚¢‚Ä‚ ‚é•û‚ªˆ—‚ªŒy‚­‚È‚é‚Ì‚Å‚Í‚ÌŒŸØ‚ğ‚µ‚Ä‚¢‚Ü‚·B
	Box2D src;		//
	Texture tex;
	Color* color;
	Fead mode;
	std::vector<std::string> deleteObject;
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//‹­§•`‰æ‚ğs‚¤
	void Render2D() override;
	void PauseUpDate() override;
	void UpDate() override;
	void Set(const Fead&);
	Fead Get() const;
	void AddObject(const std::string&);
};