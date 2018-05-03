//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|____________________________|//
#pragma once
#include "Object\Object.h"
#include "Senpuki.h"


//横田さん風

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
	//オブジェクトなのでオブジェクトを継承している限りはスイッチが切り替える
	std::vector<Object*> targets;
	Texture image;
	std::string path;
	bool is_on;

};