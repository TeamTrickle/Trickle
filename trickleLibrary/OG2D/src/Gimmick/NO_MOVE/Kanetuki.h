#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <vector>
#include "VolumeControl\volumeControl.h"


class Kanetuki : public GameObject, public TaskObject {
public:
	enum Angle {
		UP,
		LEFT,
		RIGHT,
		BOTTOM,
	};

private:
	std::string taskName;
	int changeStateCnt;				//水を水蒸気にするまでの時間カウンタ
	const int maxChangeTimeLiquid;	//水が水蒸気になるフレーム数
	const int maxChangeTimeSolid;	//氷が水になるフレーム数
	GameObject hitBase;				//水との当たり判定用
	bool active;					//稼働中かどうか
	//サウンドのファイル名格納
	std::string startsoundname;
	std::string stopsoundname;
	std::string soundname;
	Texture* hotImg;			//画像データ
	int animCnt;				//アニメーションカウント
	int hotNum;				//横幅によって増える画像の数
	unsigned short timeCnt;		//起動時のタイム計測
	const unsigned short maxCnt;	//最大計測数	
	std::vector<Box2D> draw;
	Angle angle;
	float texRotaAng;

	bool Initialize(Vec2&, Vec2 range, Angle ang, bool active);		//初期化処理
	void UpDate();				//更新処理
	void Render2D();			//描画処理
	bool Finalize();			//解放処理
	void toSteam();				//水蒸気にする

	Kanetuki();

public:
	~Kanetuki();
	typedef std::shared_ptr<Kanetuki> SP;
	static Kanetuki::SP Create(Vec2& pos, Vec2 range, Angle ang, bool active, bool flag = true);

	void changeActive();				//自身の稼働状態を反転させる

	//サウンドの生成
	Sound soundstart;
	Sound sound;
	Sound soundstop;

	VolumeControl volControl;
	
	bool startflag;       //サウンドを再生していいかのフラッグ
	bool nowplay;
	void SetTexture(Texture*);
};





//class Kanetuki : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//各自で制作するときに使用するものはここに記述する
//	//-------------------------------------------
//public:
//	std::shared_ptr<Switch> target;
//private:
//	bool switchflag;
//	//------------------
//	//固定化されている処理
//	//-----------------
//	std::string taskName;
//	typedef std::shared_ptr<Kanetuki> SP;
//	Kanetuki();
//	//-------------
//	//変更しないこと
//	//-------------
//	bool Initialize(Vec2&);
//	bool Initialize(Vec2&, std::shared_ptr<Switch>&);
//	//初期化処理
//	void UpDate();			//更新処理
//	void Render2D();		//描画処理
//	bool Finalize();		//解放処理
//	void GetFlag();
//private:
//	const int Fire_time_LIQUID = 10;	//加熱する時間 液体
//	const int Fire_time_SOLID = 5;	    //加熱する時間 個体
//	int Fire_movetime;					//燃やす時間を格納する
//										//サウンドファイル名の格納
//	std::string startsoundname;
//	std::string soundname;
//
//	//状態遷移
//	void toSteam();						//水から水蒸気にする
//										//指定スイッチのフラグを代入する
//	void SetSwitchFlag(std::shared_ptr<Switch>&);
//	bool GetSwitchFlag();
//	void Fire_MovetimeReset();
//public:
//	virtual ~Kanetuki();
//	static Kanetuki::SP Create(Vec2& pos, bool = true);
//	static Kanetuki::SP Create(Vec2& pos, std::shared_ptr<Switch>& swith, bool = true);
//
//	Sound soundstart;
//	Sound sound;
//	bool startflag;       //サウンドを再生していいかのフラッグ
//	bool nowplay;
//public:
//};