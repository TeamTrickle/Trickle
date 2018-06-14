#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Task\Task_Result.h"
class FlagUI : public GameObject, public TaskObject
{
public:
	
private:
	//フラグ関連
	int Resultflag;
	int targetflag;
	bool flagactive;

	//Easing関連
	//Vec2 PrePos;
	//Easing easingX;


	//画像関連
	Texture image[2];
	const Box2D Src = Box2D(0, 0, 78, 79);
	bool effectEnd;

	//拡大機能
	bool isScaleed;
	Vec2  Center;			//描画中央固定座標
	Vec2  ReSize;			//新しくリサイズしたScale
	Vec2  ScaleVolume;		//拡大率
	Vec2  PreSize;			//前回のデータを取っておく
	Vec2  PrePos;			//描画調整用

	//他のクラスへ送るため変数
	Vec2  SendPos;			//Effectの位置を決める
	
private:
	//フラグ関係
	void SetResultflag();
	void FalgJudge(int);

	//拡大機能
	void MoveVolume();		  //拡大率を少しずつ上昇させていきます
	void ResetVolume();	      //拡大率を上げるための初期化を行う
	void ResetCenter();		  //中央値の再計算をします（1フレームで計算をして終了をさせること）

	//他のクラスへデータ送る関数への準備をする関数
	void SetSendPos(Box2D&);  //DrawのPosをエフェクトと同じにする
public:
	std::string taskName;
	virtual ~FlagUI();
	typedef std::shared_ptr<FlagUI> SP;
	static FlagUI::SP Create(Vec2& pos,int targetflag,bool = true);
	FlagUI();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos,int&);//初期化処理
	void UpDate();					//更新処理
	void Render2D();				//描画処理
	bool Finalize();				//解放処理

	//リザルトタスクで使用する関数
	bool GetEffectEnd();			//エフェクト演出が終わったかを判定します

	//エフェクトに必要な関数
	bool GetFlag();					//フラグを返す
	bool is_Scale();				//拡大が終了したかを返す
	void SetEffectEnd();			//エフェクトが終了したらエフェクトの方で変更させる
	Vec2 GetPos();					//エフェクトの生成時に送るPos
};