#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"


class Seihyouki : public GameObject, public TaskObject
{
public:
	enum Angle
	{
		RIGHT,
		LEFT,
		UP
	};
private:
	std::string taskName;
	int changeStateCnt;			//水を氷にするまでの時間カウンタ
	const int maxChangeTime;	//水が氷になるフレーム数
	GameObject hitBase;			//水との当たり判定用	なぜ加熱器はないのに製氷機にはあるのか……後に描画もこのクラスで行うことを考えて一応残す
	bool active;				//稼働中かどうか
	Texture* coldImg;			//画像データ
	int animCnt;				//アニメーションカウント
	int coldNum;				//横幅によって増える画像の数
	std::vector<Box2D> draw;	//氷の画像
	unsigned short timeCnt;		//起動時のタイム計測
	const unsigned short maxCnt;	//最大計測数	

	bool Initialize(Vec2& , Vec2 range, Angle ang, bool active);		//初期化処理
	void UpDate();				//更新処理
	void Render2D();			//描画処理
	bool Finalize();			//解放処理
	void toIce();				//氷にする

	Seihyouki();

public:
	Angle angle;
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, Vec2 range, Angle, bool active, bool flag = true);
	void SetTexture(Texture*);

	void changeActive();				//自身の稼働状態を反転させる
};




//class Seihyouki : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//各自で制作するときに使用するものはここに記述する
//	//-------------------------------------------
//private:
//	void toIce();							//氷にする
//	void SetSwitchFlag(std::shared_ptr<Switch>&);
//	void GetFlag();
//	bool GetSwitchFlag();
//private:
//	GameObject hitBace;
//	bool switchflag;
//	//------------------
//	//固定化されている処理
//	//------------------
//public:
//	std::string taskName;
//	std::shared_ptr<Switch> target;
//	virtual ~Seihyouki();
//	typedef std::shared_ptr<Seihyouki> SP;
//	static Seihyouki::SP Create(Vec2& pos, bool = true);
//	static Seihyouki::SP Create(Vec2& pos,std::shared_ptr<Switch>& target,bool = true);
//	Seihyouki();
//	//-------------
//	//変更しないこと
//	//-------------
//	bool Initialize(Vec2&);		//初期化処理
//	bool Initialize(Vec2&,std::shared_ptr<Switch>& target);		//初期化処理
//	void UpDate();			//更新処理
//	void Render2D();		//描画処理
//	bool Finalize();		//解放処理
//
//private:
//	int movetime;					//氷にするまでの格納するフレーム数
//	const int movetime_ice = 20;	//氷にするまで・・・
//};