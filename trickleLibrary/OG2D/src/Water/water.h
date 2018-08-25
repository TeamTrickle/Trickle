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
/**
*状態遷移するオブジェクト管理class
*/
class Water : public GameObject,public TaskObject {

public:
	/**
	*enum State
	* 状態の値
	*/
	enum class State : int {
		LIQUID = 0,			//　液体
		SOLID,				//　個体
		GAS					//　気体
	};
	/**
	*enum Situation
	* 現状状態
	*/
	enum class Situation : int
	{
		Newfrom,			//出現中
		Normal,				//通常
		Deleteform,			//削除中
		CreaDelete,			//削除
		Rainfrom			//雨状態
	};
private:
	//! 落下最大速度
	const float maxFall;
	//! 重力加速度
	const float gravity;
	//! 摩擦
	float finSpeed;
	//! 雨発生時間
	const unsigned __int8 rainTime;
	//! 画像情報
	Texture* tex;
	//! 現在の状態
	State currentState;
	//! 前の状態
	State preState;
	//! 現在の状態
	Situation nowSituation;
	//! 最低サイズ
	Vec2 minSize;
	//! 最大サイズ
	Vec2 maxSize;
	//! 移動値
	Vec2 move;
	//! 1フレームでの移動値
	Vec2 nowMove;
	//! 左側の当たり判定
	GameObject* left;
	//! 右側の当たり判定
	GameObject* right;
	//! 自分の色情報
	Paint::PaintColor color;
	//! 状態の変化タイム
	int setTime;
	//! 自分の所持状態
	bool hold;
	//! 個別ID
	unsigned int id;
	//! サウンドのファイル名格納
	std::string soundname; 
	//! 描画用カラー値
	Color color_a;
	//! 炎に当たっているタイム
	unsigned int fireCnt;
	//! 氷に当たっているタイム
	unsigned int iceCnt;
	//! スマートポインタ
	typedef std::shared_ptr<Water> SP;
public:
	//! 水量
	float volume;
	//! 無敵時間
	int invi;
	//! カウント時間
	int nowTime;
	//! サウンドの生成
	bool soundplay;
	Sound sound;
	VolumeControl volControl;
private:
	/**
	*@brief	:生成時処理
	*@return:Situation 次の状態
	*/
	Situation UpNewform();
	/**
	*@brief	:削除時処理
	*@return:Situation 次の状態
	*/
	Situation UpDeleteform();
	/**
	*@brief	:更新処理
	*@return:Situation 次の状態
	*/
	Situation UpNormal();
	/**
	*@brief	:重力処理
	*/
	void Friction();
	/**
	*@brief	:足元処理
	*@param	:string name 判定を行いたいオブジェクト名
	*@param	:int id 相手の当たり判定ID
	*@return:bool 当たっていればtrue
	*/
	bool FootCheck(const std::string& name, const int id = 0);
	/**
	*@brief	:頭上処理
	*@param	:string name 判定を行いたいオブジェクト名
	*@param	:int id 相手の当たり判定ID
	*@return:bool 当たっていればtrue
	*/
	bool HeadCheck(const std::string& name, const int id = 0);
	/**
	*@brief	:足元氷判定処理
	*@return:bool 当たっていればtrue
	*/
	bool FootSolidCheck();
	/**
	*@brief	:頭上氷判定処理
	*@return:bool 当たっていればtrue
	*/
	bool HeadSolidCheck();
	/**
	*@brief	:水の移動処理
	*@param	:Vec2 move 移動値
	*/
	void MoveWATERCheck(Vec2& move);
	/**
	*@brief	:雲の移動処理
	*@param	:Vec2 move 移動値
	*/
	void MoveGASCheck(Vec2& move);
	/**
	*@brief	:氷の移動処理
	*@param	:Vec2 move 移動値
	*/
	void MoveSOILDCheck(Vec2& move);
	/**
	*@brief	:状態確認
	*/
	void CheckState();
	/**
	*@brief	:氷の押し出し処理
	*@return:bool 押し出しを行った場合true
	*/
	bool SolidExtrusion();
	/**
	*@brief	:初期化処理
	*@return:bool 成功true
	*/
	bool Initialize();
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:解放処理
	*@return:bool 成功true
	*/
	bool Finalize();
	/**
	*@brief	:constructor
	*@param	:Vec2 pos 生成位置
	*/
	explicit Water(const Vec2& pos);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Water();
	/**
	*@brief	:画像を登録する
	*@param	:Texture* texture 画像データのポインタ
	*/
	void SetTexture(Texture* texture);
	/**
	 * @brief	状態転移します。
	 * @see	外で使うとこにはWater::State::Liquid こんな形に
	 */
	void SetState(const State&);
	/**
	*@brief	:現在の状態を返す
	*@return:State 現在状態
	*/
	State GetState() const;
	/**
	*@brief	:オブジェクトの移動処理
	*@param	:Vec2 move 移動値
	*/
	void MovePos(const Vec2& move);
	/**
	*@brief	:オブジェクトのX移動値
	*@param	:float move 移動値
	*/
	void MovePos_x(const float move);
	/**
	*@brief	:移動値の取得
	*@return:Vec2 移動値
	*/
	Vec2 GetMove() const;
	/**
	*@brief	:状態を更新する
	*@param	:Situation s 状態
	*/
	void SetSituation(const Situation& s);
	/**
	*@brief	:状態を取得する
	*@return:Situation 現在状態
	*/
	Situation GetSituation() const;
	/**
	*@brief	:押し出された移動処理
	*@param	:Vec2 move 移動量
	*@return:Vec2 移動できなかった値
	*/
	Vec2 MoveSolid(const Vec2& move);
	/**
	*@brief	:水量を移動する
	*@return:float 水量
	*/
	float waterMove();
	/**
	*@brief	:水量を外部から上書きする
	*@param	:float value 水量
	*/
	void SetWaterVolume(const float value);
	/**
	*@brief	:水量を取得
	*@return:float 水量
	*/
	float GetWaterVolume() const;
	/**
	*@brief	:バケツとの判定を行うかどうか
	*@return:bool 行う場合true
	*/
	bool IsBucket();
	/**
	*@brief	:色の設定
	*@param :Paint::PaintColor color 色情報
	*@return:bool 成功でtrue
	*/
	bool SetColor(const Paint::PaintColor& color);
	/**
	*@brief	:色の取得
	*@return:Paint::PaintColor 色情報
	*/
	Paint::PaintColor GetColor() const;
	/**
	*@brief	:タスク生成
	*@param	:Vec2 pos 位置情報
	*@return:Water 生成に失敗したらnullptr
	*/
	static SP Create(const Vec2& pos);
	/**
	*@brief	:最大サイズを登録
	*@param	:Vec2 maxSize サイズ
	*/
	void SetMaxSize(const Vec2& maxSize);
	/**
	*@brief	:自身が持たれているか返す
	*@return:bool 所持状態
	*/
	bool GetHold() const;
	/**
	*@brief :所持状態を指定する
	*@param :bool flag 所持状態
	*/
	void HoldCheck(const bool flag);
	/**
	*@brief	:移動値をリセットする
	*/
	void ResetMove();
	/**
	*@brief	:自身が溶けた時の処理
	*/
	void SolidMelt();
	/**
	*@brief	:自身のサイズの変更を行う
	*@param :Vec2 scale サイズ
	*/
	void SetScale(const Vec2& scale);
	/**
	*@brief	:個別IDを返す
	*@return:unsigned int 個別ID
	*/
	unsigned int GetID() const;
	/**
	*@brief	:炎カウントを設定する
	*@param	:unsigned int cnt カウント
	*/
	void SetFireCnt(const unsigned int& cnt);
	/**
	*@brief	:炎カウントを返す
	*@return:unsigned int 現在カウント
	*/
	unsigned int GetFireCnt() const;
	/**
	*@brief	:氷カウントを設定する
	*@param	:unsigned int cnt カウント
	*/
	void SetIceCnt(const unsigned int& cnt);
	/**
	*@brief	:氷カウントを返す
	*@return:unsigned int 現在カウント
	*/
	unsigned int GetIceCnt() const;
};