//______________________________//
//|動くギミック  扇風機        |//
//|履歴：2018/03/27 横尾	   |//
//|　                          |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Player\EnemyHitTest.h"
#include "Water\water.h"

//#include "Player\Player.h"
//
////class Player;
//class EnemyHitTest;
//
//class Senpuki : public Object
//{
//public:
//	void Initialize();
//	void UpDate();
//	void Finalize();
//	void Render();
//	Senpuki(/*EnemyHitTest* e_pointa*/);
//	//Senpuki(Player* p_pointa);
//	~Senpuki();
//private:
//	//Player* player_pointa;
//
//	//EnemyHitTest* enemy_pointa;
//	bool flag;							//当たり判定格納変数
//	Texture senimg;						//画像イメージ
//	Texture collbox;					//画像イメージ
//	std::string _filePath;				//ファイルパス
//	std::string _hitbox;				//ファイルパス
//	CollisionBox range;				    //視野範囲
//public:
//	void CheckHit(Object* objhit , int value);
//};


class Fan :public Object {
	std::vector<Switch*> switches;		//自身の稼働にかかわっているスイッチ一覧
public:
	enum Dir {
		LEFT,
		RIGHT,
	};

	void Initialize(Vec2 pos, float r, Dir d, bool activ);
	void AddSwitch(Switch* swit);
	void ChangeState();
	void Finalize();
	void Render();
private:
	Dir dir;
	Texture image;
	float range;
	float strength;
	bool active;


};