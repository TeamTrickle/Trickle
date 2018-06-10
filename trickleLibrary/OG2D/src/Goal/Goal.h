#ifndef __GOAL_H__
#define __GOAL_H__

//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

class Goal : public GameObject, public TaskObject
{
public:
	enum CameraMode
	{
		//動いていない
		NON,
		//起動中
		Play,
		//終了した
		End,		
	};
private:
	//タスク関連
	std::string taskName;

	//基本の情報
	bool cleared;

	//画像関連
	Texture tex;

	//アニメーション関連
	bool isanimetion;
	bool isanimetionfinish;
	int  animCnt;

	//ゴールカメラ関連
	CameraMode cameramode;
	bool iscameraPlay;			//カメラが起動しているか起動したかを返します
	Vec2 cameraPos;				//カメラの座標値
	Vec2 cameraMove;			//カメラの移動量
	Vec2 cameraSize;			//カメラのサイズ
	Vec2 PreCameraPos;			//保存しておくカメラの座標
	Vec2 PreCameraSize;			//保存しておくカメラのサイズ
	Vec2 inside;				//ゴール直後のPlayerとゴールの距離を格納します
	bool camerafinish;			//カメラの動きが終了した

private:
	//タスク関連
	void UpDate();			//更新処理
	void Render2D();		//描画処理
	bool Finalize();		//解放処理

	//基本の情報
	bool ClearCheck();			//ゴールの判定を返します


	//アクセサメソッド関連
	void ResetisGoal();			//ゴール判定の初期化を行います

	void ResetAnimetion();		//アニメーションの初期化

	void ResetCameraMode();		//カメラのモードを初期化します
	void ResetisCameraPlay();	//カメラの起動するフラグを初期化します
	void ResetCameraVec();		//Vectorクラスの初期化
	void ResetCamera();			//ゴールカメラ関連をまとめて初期化します
	void ResetCameraCnt();		//ゴールのカウンタを初期化します

	//カメラ関連
	void Camera_Think();
	void Camera_Motion();
	void Camera_Play();			//カメラを動かす
public:
	virtual ~Goal();
	typedef std::shared_ptr<Goal> SP;
	static Goal::SP Create(bool);
	static Goal::SP Create(bool,Vec2&);
	Goal();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize();		//初期化処理
	bool Initialize(Vec2&);	//初期化処理
	
	//他のクラスで使用できるメソッド

	//フラグ関係
	bool isGoal();						//ゴールをしているかどうかを返す
	bool isAnimetion();					//アニメーションが終了しているかを返す

	//カメラモード関連
	CameraMode GetCameraMode();		//カメラモードを返す
	void SetCameraMode(CameraMode);	//カメラモードを変更します
	void SetCameraSpeed(Vec2&);		//カメラを動かすスピードを変更します
};

#endif