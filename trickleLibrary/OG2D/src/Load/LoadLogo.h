#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
	Texture image;	//‰æ‘œ
	Box2D draw;		//–ˆ‰ñéŒ¾‚·‚é‚æ‚è‚±‚±‚É‘‚¢‚Ä‚ ‚é•û‚ªˆ—‚ªŒy‚­‚È‚é‚Ì‚Å‚Í‚ÌŒŸØ‚ğ‚µ‚Ä‚¢‚Ü‚·B
	Box2D src;		//
public:
private:
	void UpDate();
	void Render2D();
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//‹­§•`‰æ‚ğs‚¤

};