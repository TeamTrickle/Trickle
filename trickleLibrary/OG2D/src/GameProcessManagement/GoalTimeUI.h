#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class GoalTimeUI : public GameObject, public TaskObject
{
private:
	//タスク関連
	std::string taskName;
	
	//struct Mat3x3
	//{
	//	enum MatFormat
	//	{
	//		Unix,	//単位
	//		Rotate,	//回転
	//		Scale,	//拡大縮小
	//		Move,	//移動
	//	};
	//	float mat[9];
	//	Mat3x3 Create(float mat[], MatFormat);
	//};


	//画像関連
	Texture image;
	//const Box2D Src = {0,0,227,90};
	const Box2D Src = { 0,64 * 3,640,768 / 12 };

	//拡大機能
	Vec2  Center;			//描画中央固定座標
	Vec2  ReSize;			//新しくリサイズしたScale
	Vec2  ScaleVolume;		//拡大率
	Vec2  PreSize;			//前回のデータを取っておく

	//Mat3x3 mat;

private:
	bool Initialize(Vec2&);
	bool Finalize();
	void UpDate();
	void Render2D();
	GoalTimeUI();

	//拡大機能関連
	void MoveVolume();		  //拡大率を少しずつ上昇させていきます
	void ResetVolume();	      //拡大率を上げるための初期化を行う
	void ResetCenter();		  //中央値の再計算をします（1フレームで計算をして終了をさせること）

public:
	typedef std::shared_ptr<GoalTimeUI> SP;
	static GoalTimeUI::SP Create(Vec2& pos, bool = true);
	virtual ~GoalTimeUI();

};