//#pragma once
//#include "OGSystem\OGsystem.h"
//#include "Object\Object.h"
//#include "OGSystem/_OGsystem.h"
//
//class ClearUI : public GameObject, public TaskObject
//{
//private:
//	//タスク関連
//	std::string taskName;
//
//	//画像関連
//	Texture image;
//	const Box2D Src = {0,0,269,85};
//
//	//拡大機能
//	Vec2  Center;			//描画中央固定座標
//	Vec2  ReSize;			//新しくリサイズしたScale
//	Vec2  ScaleVolume;		//拡大率
//	Vec2  PreSize;			//前回のデータを取っておく
//	bool  Volumefinish;
//
//private:
//	//タスク関連
//	bool Initialize(Vec2&);
//	bool Finalize();
//	void UpDate();
//	void Render2D();
//	ClearUI();
//
//	//拡大機能
//	void MoveVolume();		  //拡大率を少しずつ上昇させていきます
//	void ResetVolume();	      //拡大率を上げるための初期化を行う
//	void ResetCenter();		  //中央値の再計算をします（1フレームで計算をして終了をさせること）
//	void SetVolumeFlag(bool);
//public:
//	virtual ~ClearUI();
//	typedef std::shared_ptr<ClearUI> SP;
//	static ClearUI::SP Create(Vec2& pos, bool = true);
//
//	//リザルトで使用する関数
//	bool GetVolumeFlag();
//};