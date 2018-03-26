#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
//登録するギミックをここに記述する//

//#include "Player\Player.h"
//#include "Player\EnemyHitTest.h"
#include "Object\Kanetuki.h"
#include "Object\Senpuki.h"
//______________________________//
//|動くギミック  制御クラス    |//
//|履歴：2018/03/26 横尾	   |//
//|　                          |//
//|  クラスの宣言で使用可能____|//
#include "Object\Switch.h"

//class Player;
//class EnemyHitTest;
class Kanetuki;
class Senpuki;
class Switch;

class GIMMICK_Control
{
public:
	GIMMICK_Control();
	~GIMMICK_Control();
	void Initialize();
	TaskFlag UpDate();
	void Finalize();
	void Render2D();
public:
	//Player* _p_pointa;
	EnemyHitTest* _e_pointa;
	Kanetuki*     _ka_pointa;
	Senpuki*      _sen_pointa;
	Switch*		  _swi_pointa;
};

