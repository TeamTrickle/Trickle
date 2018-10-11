/**
* @file Fan.h
* @brief 扇風機クラスを定義する
* @author yokota0717
* @date 2018.10.11
*/

#pragma once

#include "GimmickBase.h"
#include "VolumeControl\volumeControl.h"
#include "Effect\Effect.h"

/**
* @brief 扇風機クラス
* @details 水蒸気状態の水を横方向に移動させる
*/
class Fan : GimmickBase {
	Texture* image;
	Texture* windimage;      //風の画像
	Texture* windimage2;     //風の画像2
	Texture* windimage3;      //風の画像
	Texture* windimage4;      //風の画像
	Texture* windimage5;      //風の画像

	const Box2D Src = { 0,0,768 / 3,256 };
	float range;
	float movePos;
	int strength;
	float endpos;
	std::string soundname;      //サウンドのファイル名格納
	std::string taskName;		//検索用

	struct Animetion
	{
		int animetionframe;
		int speed;
		void AnimetionMove(bool flag);				//アニメーションフレームを動かす
		void AnimetionReset();						//アニメーションの数値をリセットする
		void AnimetionSrc(Box2D& src, bool flag);	//アニメーションフレームを描画に影響させる
	};
	Animetion animetion;

	virtual bool Initialize(Vec2 pos, Vec2 range, Dir dir, bool active) override;
public:
	Fan(Vec2 pos, Vec2 range, Dir dir, bool active);
	~Fan();

	//サウンド周りの情報
	bool startflag;
	Sound sound;
	VolumeControl volControl;
	//エフェクト周りの情報
	int effectCnt;
	int effectnum;       //エフェクトの画像をランダムで決定
	//! エフェクトの長さを設定する(もうちょっとどうにかしたい)
	void setEffectDist(float dist);

	void UpDate() override;			//更新処理
	void Render2D() override;		//描画処理
	bool Finalize();				//解放処理

	virtual void affectWater() override;
};
