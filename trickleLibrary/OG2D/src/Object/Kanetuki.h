//______________________________//
//|動くギミック  加熱機        |//
//|履歴：2018/03/27 横尾	   |//
//|　                          |//
//|____________________________|//
#pragma once
#include "Object.h"

//#include "Player\Player.h"
//#include "Player\EnemyHitTest.h"

//class Player;
//class EnemyHitTest;

class Kanetuki : public Object
{
public:
	void Initialize();
	void UpDate();
	void Finalize();
	void Render();
	Kanetuki(/*EnemyHitTest* e_pointa*/);
	~Kanetuki();
private:
	int  Count;
	bool flag;
	void CheckHit(Object* objhit);
	//EnemyHitTest* enemy_pointa;
	Texture image;
	std::string _filePath;
};