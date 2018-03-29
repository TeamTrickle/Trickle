//______________________________//
//|動くギミック  扇風機        |//
//|履歴：2018/03/29 横尾	   |//
//|　                          |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Player\EnemyHitTest.h"

//#include "Player\Player.h"

//class Player;
class EnemyHitTest;

class Senpuki : public Object
{
public:
	void Initialize();
	void UpDate();
	void Finalize();
	void Render();
	Senpuki(/*EnemyHitTest* e_pointa*/);
	//Senpuki(Player* p_pointa);
	~Senpuki();
private:
	//Player* player_pointa;

	//EnemyHitTest* enemy_pointa;
	bool flag;							//当たり判定格納変数
	Texture senimg;						//画像イメージ
	Texture collbox;					//画像イメージ
	std::string _filePath;				//ファイルパス
	std::string _hitbox;				//ファイルパス
	CollisionBox range;				    //視野範囲
public:
	void CheckHit(int);
};