//______________________________//
//|動くギミック  スイッチ      |//
//|履歴：2018/03/29 横尾	   |//
//|履歴：2018/03/31 横尾　     |//
//|履歴：2018/04/01 横尾       |//
//|履歴: 2018/04/02 横尾       |//
//|履歴: 2018/04/03 横尾       |//
//|履歴：2018/04/07 横尾       |//
//|履歴：2018/05/24 横尾		|//
//|履歴：2018/5/31　横田
//|____________________________|//
#pragma once
//必要読み込みファイル
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
#include "Senpuki.h"
#include "Kanetuki.h"
#include "Seihyouki.h"


//----------------
//方針
//スイッチは自身のオンオフを持つ
//スイッチを操作するのはプレイヤ(Player.cppでスイッチのオンオフを切り替える関数を呼ぶ)
//切り替わった瞬間、管理しているギミックに切り替えの情報を送る(PostMsg)
//----------------
class Switch : public GameObject, public TaskObject {
public:
	enum class TargetType {
		Heater,
		IceMachine,
		Fan,
	};
private:
	Texture image;
	std::string soundname;		//サウンドのファイル名格納
	std::string taskName;		//検索用
	bool isON_;					//稼働中かどうか
	Box2D draw;
	Box2D srcbase;
	TargetType ttype;
	int animCnt;
	bool play_switch;

	Switch();
	bool Initialize(Vec2& pos, std::vector<std::shared_ptr<GameObject>> target, TargetType ttype);
	void Update();
	void Render2D();
	bool Finalize();

	std::vector<std::shared_ptr<GameObject>> targets_;		
	bool PostMsg(std::shared_ptr<GameObject> receiver);
public:

	Sound sound;

	bool isON();				//自分のオンオフを返す、オンならtrue
	void ChangeON_OFF();		//オンオフを切り替える
	TargetType getTargetType();

	typedef std::shared_ptr<Switch> SP;
	static Switch::SP Create(Vec2& pos, std::vector<std::shared_ptr<GameObject>> targets, TargetType ttype, bool = true);

	~Switch();
};
//
//class Switch : public GameObject, public TaskObject
//{
//	//-------------------------------------------
//	//各自で制作するときに使用するものはここに記述する
//	//-------------------------------------------
//public:
//	bool GetisON();
//private:
//	Texture image;
//	const Box2D Src = { 0,0,256,256 };
//	std::shared_ptr<Switch>targetswitch;
//
//	std::string soundname;      //サウンドのファイル名格納
//
//	bool is_on;
//	//------------------
//	//固定化されている処理
//	//------------------
//private:
//	void UpDate();				//更新処理
//	void Render2D();			//描画処理
//	bool Finalize();			//解放処理
//public:
//	std::string taskName;
//	virtual ~Switch();
//	typedef std::shared_ptr<Switch> SP;
//	//通常時
//	//あるスイッチとフラグを切り替えるスイッチを生成する場合
//	static Switch::SP Create(Vec2& pos, bool = true);
//	static Switch::SP Create(Vec2& pos, Switch::SP target,bool = true);
//	Switch();
//	//-------------
//	//変更しないこと
//	//-------------
//	bool Initialize(Vec2& pos, Switch::SP target);
//	bool Initialize(Vec2& pos);
//
//	Sound sound;
//	void ON_OFF();
//private:	
//	void TargetSwitchChenge();			//ターゲットのスイッチとフラグを入れ替える
//	void SetTarget(Switch::SP target);
//};