#include "Switch.h"
using namespace std;

Switch::Switch()
{
	cout << "スイッチ　生成" << endl;
	soundname = "switch.wav";
	this->taskName = "Switch";
	//タグ検索を検知可能にする
	this->Init(taskName);
}

Switch::~Switch()
{
	this->Finalize();
	cout << "スイッチ　解放" << endl;
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
	srcbase = Box2D(0, 0, 256, 256);
	//ターゲット関連
	this->ttype = ttype;
	this->targets_ = targets;

	cout << "通常スイッチ　初期化" << endl;
	return true;

}
void Switch::Update() {

}
void Switch::Render2D() {
	//現在は画像反転で対応、あとでアニメーションつける
	//TargetType(ttype)によって使用する画像の色を分けること
	Box2D src = this->srcbase;
	if (this->isON_)
	{
		int temp = src.x;
		src.x = src.w;
		src.w = temp;
	}
	image.Draw(draw, src);
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