#pragma once
#include "OGSystem\OGSystem.h"
/**
*@brief	:タスク変更時に行うロード用のタスク
*/
class Load : public TaskObject
{
public:
	/**
	*enum Fead
	*インとアウトを分けるため
	*/
	enum Fead
	{
		//!	ロゴのフェードイン
		LogoIn,
		//!	ロゴのフェードアウト
		LogoOut,
		//! 背景のフェードイン
		BackIn,
		//! 背景のフェードアウト
		BackOut,
	};
private:
	//!	ロゴデータ
	Texture* logoimage;
	//! 背景データ
	Texture* backimage;
	//! 描画位置
	Box2D draw;
	//!	描画画像位置
	Box2D src;
	//! 背景の色データ
	Color* backcolor;
	//! ロゴの色データ
	Color* logocolor;
	//! 現在のモード
	Fead mode;
	//! フェードアウトのタイム
	const float feadOutTime;
	//! フェードインのタイム
	const float feadInTime;
	//!	削除を行うタスクの文字列
	std::vector<std::string> deleteObjectName;
	//!	スマートポインタ
	typedef std::shared_ptr<Load> SP;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:ポーズ処理
	*/
	void PauseUpDate() override;
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:constructor
	*/
	Load();
	/**
	*@brief	:ロゴフェードアウト処理
	*/
	void FeadLogoOutUpDate();
	/**
	*@brief	:ロゴフェードイン処理
	*/
	void FeadLogoInUpDate();
	/**
	*@brief	:背景フェードアウト処理
	*/
	void FeadBackOutUpDate();
	/**
	*@brief	:背景フェードイン処理
	*/
	void FeadBackInUpDate();
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Load();
	/**
	*@brief	:タスク生成
	*/
	static SP Create();
	/**
	*@brief	:登録されている画像を強制的に描画させる
	*/
	void Draw();
	/**
	*@brief	:行うフェードを指定する
	*/
	void SetFead(const Fead&);
	/**
	*@brief	:全てのタスクの更新を止める
	*@param	:bool flag 止めるtrue,解除false
	*/
	void ALLTaskUpDateStop(const bool flag = true);
	/**
	*@brief	:現在のフェードを取得する
	*@return:Fead 現在のフェード
	*/
	Fead Get() const;
	/**
	*@brief	:削除したいオブジェクトの文字列を登録する
	*@param	:string name オブジェクトの文字列
	*/
	void AddDeleteObjectName(const std::string& name);
};