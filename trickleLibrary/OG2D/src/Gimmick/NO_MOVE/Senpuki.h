//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾       |//
//|履歴：2018/03/30 横尾　     |//
//|履歴：2018/03/31 横尾       |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/06 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|履歴：2018/05/03 横尾       |//
//|____________________________|//

#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Water\water.h"

class Switch;

class Fan :public Object 
{
	std::vector<Switch*> switches;		//自身の稼働にかかわっているスイッチ一覧
public:
	enum Dir 
	{
		LEFT,
		RIGHT,
	};
	explicit Fan();
	explicit Fan(Vec2);
	virtual ~Fan();
	void Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void Finalize();
	void Render();
private:
	Dir dir;
	Texture image;
	float range;
	float movePos;
	bool active;
};

