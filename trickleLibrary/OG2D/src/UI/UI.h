#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>
#include "Bucket\bucket.h"

class UImanager;

class UI :public GameObject,public TaskObject {
	Texture tex;
	Vec2 pos;		//座標
	int counter;	//時間はかる。
	int index;		//描画するsrc
	int num;		//画像分割数
	int life;		//寿命
	Box2D draw;
	std::vector<Box2D> srcTable;
	Vec2 maxWH;		//最大描画範囲
	Vec2 nowWH;		//現在の描画範囲
	Vec2 endPos;	//最大表示時の左上の座標
	Easing easeW;
	Easing easeH;
	int id_;

public:	
	bool active;	//生死
	int appeared;	//初期：-1、一度プレイヤと接触したら0、出たら1
	std::function<bool()> appear;
	std::function<bool()> vanish;

	struct UIinfo {
		Vec2 pos;
		Box2D hit;
		std::string path;
		int life;
		int picNum;
		std::function<bool()> appear;
		std::function<bool()> vanish;
	};

	UI();
	~UI();
	typedef std::shared_ptr<UI> SP;
	static SP Create(Vec2&, Box2D&, std::string&, int life, int num, int id, bool = true);
	static SP Create(UIinfo& info, int id, bool = true);

	bool Initialize(Vec2& p, Box2D& coll, std::string& path, int life, int id, std::function<bool()> appear, std::function<bool()> vanish, int num = 0);	//座標、ファイルパス、寿命、画像分割数
	void UpDate();
	void Move(Vec2 p);		//座標を動かすときに使う
	void Render2D();
	bool Finalize();
};

class UImanager :public GameObject, public TaskObject {
public:
	UImanager();
	~UImanager();

	bool Initialize(unsigned short& mapNum);
	void UpDate();

private:
	int maxNum;		//表示するUIの数、Initializeで指定、UI増やす時はこれも変えなきゃいけないクソ仕様
	std::vector<std::shared_ptr<UI>> UIlist_;
	std::vector<UI::UIinfo> uiInfo;

	int activeID;
};


//UIの出現、消滅条件に使う関数を定義しておくだけのクラス
class UIfunc {
public:
	UIfunc() {};
	bool getBucket();
	bool getWater();
	bool Hit(GameObject& me);
	bool NoHit(GameObject& me);
	bool playerPos();
	bool spoilWater();
};
extern std::unique_ptr<UIfunc> uifunc;