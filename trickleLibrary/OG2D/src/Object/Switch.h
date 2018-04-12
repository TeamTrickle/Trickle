//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/27 横尾	   |//
//|　                          |//
//|____________________________|//
#pragma once
#include "Object.h"
#include "Object\Senpuki.h"
//#include "Player\Player.h"
//#include "Player\EnemyHitTest.h"

//class EnemyHitTest;
//class Player;

//class Switch : public Object
//{
//public:
//	Switch(/*EnemyHitTest* e_pointa*/);
//	~Switch();
//	void Initlaize();
//	void UpDate();
//	void Finalize();
//	void Render();
//
//	void CheakHit(Object* objhit);
//private:
//	Texture image;
//	std::string _filePath;
//	//Player* player_pointa;
//	//EnemyHitTest* enemy_pointa;
//
//	//今後はビット演算で行う
//
//	bool flag;//当たり判定
//	bool switchflag;//スイッチがONかOFFかを示す
//};




//注意！！！！
//プレイヤが二つ以上のスイッチに同時に接触するとエラー吐きます
//必ずスイッチを複数置くときは１マス以上離して配置
class Switch :public Object {
public:	
	void Initialize(Vec2 pos);
	void Update();
	void Finalize();
	void Render();
	bool isON();
	void ON_OFF();
	void SetTarget(Object* t);
private:
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};