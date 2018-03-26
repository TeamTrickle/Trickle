//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/26 横尾	   |//
//|　                          |//
//|____________________________|//
#pragma once
#include "Object.h"
//#include "Player\Player.h"
#include "Player\EnemyHitTest.h"

class EnemyHitTest;
//class Player;

class Switch : public Object
{
public:
	Switch(EnemyHitTest* e_pointa);
	~Switch();
	void Initlaize();
	void UpDate();
	void Finalize();
	void Render();
private:
	void CheakHit(Object* objhit);
	Texture image;
	std::string _filePath;
	//Player* player_pointa;
	//EnemyHitTest* enemy_pointa;

	//今後はビット演算で行う

	bool flag;//当たり判定
	bool switchflag;//スイッチがONかOFFかを示す
};