#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Seihyouki : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	void HitGeneration(Vec2&, Vec2&);		//座標値　当たり判定サイズ
	
	void toIce();							//氷にする
private:
	Texture sampleImage;
	GameObject hitBace;
	//------------------
	//固定化されている処理
	//------------------
public:
	std::string taskName;
	virtual ~Seihyouki();
	typedef std::shared_ptr<Seihyouki> SP;
	static Seihyouki::SP Create(Vec2& pos, Vec2& scale,bool = true);
	Seihyouki();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2&,Vec2&);		//初期化処理
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理

private:
	int movetime;					//氷にするまでの格納するフレーム数
	const int movetime_ice = 20;	//氷にするまで・・・
};