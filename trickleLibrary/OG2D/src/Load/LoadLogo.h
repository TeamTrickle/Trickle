#pragma once

#include "OGSystem\OGSystem.h"

class Load : public TaskObject
{
	class Param
	{
	public:
		std::mutex mutex;
		bool on;
		unsigned int animCnt;
	};
	std::shared_ptr<Param> param;
	Texture image;	//‰æ‘œ
	Box2D draw;		//–ˆ‰ñéŒ¾‚·‚é‚æ‚è‚±‚±‚É‘‚¢‚Ä‚ ‚é•û‚ªˆ—‚ªŒy‚­‚È‚é‚Ì‚Å‚Í‚ÌŒŸØ‚ğ‚µ‚Ä‚¢‚Ü‚·B
	Box2D src;		//
	Texture tex;
public:
private:
	void UpDate();
	static void Render(Texture* ,std::shared_ptr<Param>& param);
public:
	Load();
	virtual ~Load();
	typedef std::shared_ptr<Load> SP;
	static SP Create(bool = true);
	void Draw();		//‹­§•`‰æ‚ğs‚¤
	void Delete();
};