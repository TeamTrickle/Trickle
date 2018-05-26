//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|履歴：2018/05/24 横尾       |//
//|____________________________|//
#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"

#include "Player\Player.h"
class Switch : public GameObject, public TaskObject
{
	//-------------------------------------------
	//各自で制作するときに使用するものはここに記述する
	//-------------------------------------------
public:
	bool GetisON();
private:
	Texture image;
	const Box2D Src = { 0,0,256,256 };
	std::shared_ptr<Player>target;
	std::shared_ptr<Switch>targetswitch;
	bool is_on;
	//------------------
	//固定化されている処理
	//------------------
private:
	void UpDate();				//更新処理
	void Render2D();			//描画処理
	bool Finalize();			//解放処理
public:
	std::string taskName;
	virtual ~Switch();
	typedef std::shared_ptr<Switch> SP;
	//通常時
	static Switch::SP Create(Vec2& pos,Player::SP target,bool is_on,bool = true);
	//あるスイッチとフラグを切り替えるスイッチを生成する場合
	static Switch::SP Create(Vec2& pos, Switch::SP target,bool = true);
	Switch();
	//-------------
	//変更しないこと
	//-------------
	bool Initialize(Vec2& pos, Player::SP target,bool is_on);	//初期化処理
	bool Initialize(Vec2& pos, Switch::SP target);

	
private:
	bool CheckHit();
	void ON_OFF();
	void TargetSwitchChenge();			//ターゲットのスイッチとフラグを入れ替える
	void SetTarget(Player::SP target);
	void SetTarget(Switch::SP target);
};