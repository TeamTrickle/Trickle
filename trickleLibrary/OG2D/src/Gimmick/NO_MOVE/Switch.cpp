#include "Switch.h"
using namespace std;

Switch::Switch()
{
	soundname = "switch.wav";
	this->taskName = "Switch";
	this->objectTag = "Switch";
	//タグ検索を検知可能にする
	this->Init(taskName);
	__super::SetDrawOrder(0.5f);
}

Switch::~Switch()
{
	this->Finalize();
}

bool Switch::Initialize(Vec2& pos, std::vector<std::shared_ptr<GameObject>> targets, TargetType ttype) {
	//当たり判定の実装
	this->CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	image.Create((std::string)"switch.png");
	//サウンド生成
	sound.create(soundname, false);
	sound.volume(1.0f);
	OGge->soundManager->SetSound(&sound);
	//描画関連
	draw = Box2D(pos.x, pos.y, 64.0f, 64.0f);
	draw.OffsetSize();
	animCnt = 0;
	isON_ = false;
	//ターゲット関連
	this->ttype = ttype;
	this->targets_ = targets;
	return true;

}
void Switch::Update() {

}
void Switch::Render2D() {

	if (this->isON_) {
		//スイッチがONならアニメーションをPLUS方向に
		if (this->animCnt < 24) { ++this->animCnt; }
	}
	else {
		//スイッチがOFFならアニメーションをMINUS方向に
		if (this->animCnt > 0) { --this->animCnt; }
	}

	Box2D src;
	int switchM[5] = { 0,1,2,3,4 };
	switch (this->ttype)
	{
	case TargetType::Heater:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 0, 256, 256);
		break;
	case TargetType::IceMachine:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 1, 256, 256);
		break;
	case TargetType::Fan:
		src = Box2D(switchM[this->animCnt / 5 % 5] * 256, 256 * 2, 256, 256);
		break;
	}

	src.OffsetSize();
	image.Draw(draw, src);

	//看板の設置
	{
		Box2D signD(this->position.x, this->position.y + 64.0f, 64.0f, 64.0f);
		signD.OffsetSize();
		Box2D signS(256*((int)this->ttype), 256 * 3, 256, 256);
		signS.OffsetSize();
		this->image.Draw(signD, signS);
	}

}
bool Switch::Finalize() {
	return image.Finalize();
}
void Switch::ChangeON_OFF() {
	//切り替え時サウンドを生成
	sound.play();
	for (auto target : targets_) {
		PostMsg(target);
	}
	this->isON_ = !this->isON_;
}
bool Switch::isON() {
	return this->isON_;
}

Switch::TargetType Switch::getTargetType() {
	return this->ttype;
}
bool Switch::PostMsg(std::shared_ptr<GameObject> target) {
	switch (ttype) {
	case TargetType::Fan:
		(std::static_pointer_cast<Fan>(target))->changeActive();
		break;
	case TargetType::Heater:
		(std::static_pointer_cast<Kanetuki>(target))->changeActive();
		break;
	case TargetType::IceMachine:
		(std::static_pointer_cast<Seihyouki>(target))->changeActive();
		break;
	default:
		return false;
	}
	return true;
}
Switch::SP Switch::Create(Vec2& pos, std::vector<std::shared_ptr<GameObject>> targets, TargetType ttype, bool flag) {
	Switch::SP to = Switch::SP(new Switch());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos, targets, ttype))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}





//bool Switch::Initialize(Vec2& pos)
//{
//	taskName = "Switch";
//	//タグ検索を検知可能にする
//	this->Init(taskName);			//TaskObject内の処理を行う
//									//当たり判定の実装
//	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
//	image.Create((std::string)"switch.png");
//	//サウンド生成
//	sound.create(soundname, false);
//	sound.volume(1.0f);
//	OGge->soundManager->SetSound(&sound);
//
//	cout << "通常スイッチ　初期化" << endl;
//	return true;
//}
//bool Switch::Initialize(Vec2& pos, Switch::SP target)
//{
//	taskName = "Switch";
//	if (target)
//	{
//		cout << "スイッチを検知" << endl;
//	}
//	else
//	{
//		cout << "スイッチ代入失敗" << endl;
//	}
//
//	//タグ検索を検知可能にする
//	this->Init(taskName);			//TaskObject内の処理を行う
//	//当たり判定の実装
//	CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
//	//ターゲットを代入する
//	SetTarget(target);
//	image.Create((std::string)"switch.png");
//	//サウンド生成
//	sound.create(soundname, false);
//	sound.volume(1.0f);
//	OGge->soundManager->SetSound(&sound);
//
//	cout << "ターゲットスイッチ　初期化" << endl;
//	return true;
//}
//void Switch::UpDate()
//{
//	//--------------------
//	//更新時に行う処理を記述
//	//--------------------
//	//このスイッチのフラグと対象に反転させる
//	if (targetswitch != nullptr)
//	{
//		this->TargetSwitchChenge();
//	}
//}
//void Switch::Render2D()
//{
//	//--------------------
//	//描画時に行う処理を記述
//	//--------------------
//	Box2D draw(position, Scale);
//	draw.OffsetSize();
//	Box2D src = this->Src;
//	src.OffsetSize();
//	if (this->GetisON())
//	{
//		int temp = src.x;
//		src.x = src.w;
//		src.w = temp;
//	}
//	image.Draw(draw, src);
//}
//
//bool Switch::Finalize()
//{
//	//-----------------------------------------
//	//このオブジェクトが消滅するときに行う処理を記述
//	//-----------------------------------------
//	
//	//次のタスクを作るかかつアプリケーションが終了予定かどうか
//	if (this->GetNextTask() && !OGge->GetDeleteEngine())
//	{
//		
//	}
//	return true;
//}
//bool Switch::GetisON()
//{
//	//切り替えフラグを返す
//	return is_on;
//}
//void Switch::ON_OFF()
//{
//	//切り替え時サウンドを生成
//	sound.play();
//	//trueとfalseの切り替えフラグを切り替える
//	is_on = !is_on;
//}
//void Switch::SetTarget(Switch::SP target)
//{
//	if (target != nullptr)
//	{
//		this->targetswitch = target;
//		this->is_on = !this->targetswitch->GetisON();
//	}
//}
//void Switch::TargetSwitchChenge()
//{
//	if (targetswitch != nullptr)
//	{
//		this->is_on = !this->targetswitch->GetisON();
//	}		
//}
//Switch::Switch()
//{
//	cout << "スイッチ　生成" << endl;
//	soundname = "switch.wav";
//}
//
//Switch::~Switch()
//{
//	this->Finalize();
//	cout << "スイッチ　解放" << endl;
//}
//Switch::SP Switch::Create(Vec2& pos,bool flag)
//{
//	Switch::SP to = Switch::SP(new Switch());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}
//Switch::SP Switch::Create(Vec2& pos, Switch::SP target,bool flag)
//{
//	Switch::SP to = Switch::SP(new Switch());
//	if (to)
//	{
//		to->me = to;
//		if (flag)
//		{
//			OGge->SetTaskObject(to);
//		}
//		if (!to->Initialize(pos, target))
//		{
//			to->Kill();
//		}
//		return to;
//	}
//	return nullptr;
//}