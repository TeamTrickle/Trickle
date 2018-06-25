#pragma once


/**
 * @brief	水関連処理です
 * @date	2018-03-24
 * @author	Heewon Kim
 */

#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include <algorithm>
#include "VolumeControl\volumeControl.h"
#include "Paint\Paint.h"

class Water : public GameObject,public TaskObject {

public:
	enum class State : int {
		LIQUID = 0,			//　液体
		SOLID,				//　個体
		GAS					//　気体
	};
	
	enum class Situation : int
	{
		Newfrom,			//出現中
		Normal,				//通常
		Deleteform,			//削除中
		CreaDelete,			//削除
		Rainfrom			//雨状態
	};
private:
	const float MAX_FALL;								//落下最大速度
	const float GRAVITY;		//重力加速度
	float FIN_SPEED;								//摩擦
	const unsigned __int8 RAIN_TIME;
	Texture* tex;
	State currentState;
	State preState;
	Situation nowSituation;
	Vec2 minSize;
	Vec2 maxSize;
	Vec2 move;
	Vec2 nowMove;
	Paint::PaintColor color;
	int setTime;
	bool hold;
	unsigned int id;
	std::string soundname;      //サウンドのファイル名格納
	Color color_a;
public:
	bool active;
	//水量
	float volume;
	//無敵時間
	int invi;
	//カウント時間
	int nowTime;
	//サウンドの生成
	bool soundplay;
	Sound sound;
	VolumeControl volControl;
private:
	Situation UpNewform();
	Situation UpDeleteform();
	Situation UpNormal();
	void Friction();
	bool FootCheck(std::string&, int = 0);
	bool FootSolidCheck();
	bool HeadSolidCheck();
	void MoveWATERCheck(Vec2&);
	void MoveGASCheck(Vec2&);
	void MoveSOILDCheck(Vec2&);
	bool HeadCheck(std::string&, int = 0);
	void CheckState();
public:
	explicit Water(Vec2 pos);
	virtual ~Water();
	bool Initialize();
	void UpDate();
	void Render2D();
	bool Finalize();
	void SetTexture(Texture* texture);
	/**
	 * @brief	状態転移します。
	 * @see	外で使うとこにはWater::State::Liquid こんな形に
	 */
	void SetState(const State&);
	State GetState() const;
	void MovePos(Vec2&);
	void MovePos_x(float);
	Vec2 GetMove() const;
	void SetSituation(const Situation&);
	Situation GetSituation() const;
	Vec2 MoveSolid(const Vec2&);									//氷を押し出す処理(未実装)
	//水量の移動
	float waterMove();
	//水量を外部から上書きする
	void SetWaterVolume(float);
	//水量のチェック
	float GetWaterVolume() const;
	bool IsBucket();
	//色関連
	bool SetColor(const Paint::PaintColor&);
	Paint::PaintColor GetColor() const;
	typedef std::shared_ptr<Water> SP;
	static SP Create(Vec2&, bool = true);
	void SetMaxSize(Vec2&);
	bool GetHold() const;
	void HoldCheck(bool);
	void ResetMove();
	bool SolidMelt();
};