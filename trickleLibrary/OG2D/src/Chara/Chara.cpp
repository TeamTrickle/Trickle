#include "Chara.h"
#include "Map\Map.h"

Chara::Chara(std::string& path, Vec2& pos)
	:MOVE_SPEED(5.f), JUMP_POWER(-5.0f), MAX_FALL(30.f), GRAVITY((9.8f / 60.f / 60.f * 32) * 5), FIN_SPEED(0.5f)
{							   
	this->position = pos;	//位置設定
	this->Image.Create(path);	//画像設定
	this->CreateObject(Cube, pos, Vec2(128, 128), 0.0f);	//オブジェクト生成
	this->taskName = "Chara";	//タスク名決定
	__super::Init(this->taskName);	//タスク名をオブジェクトにも反映
	__super::SetDrawOrder(0.99f);	//描画順を登録
	this->objectTag = this->taskName;	//タグを登録
	this->direction = Direction::LEFT;	//向きを設定
	this->AnimCnt = 0;					//アニメーションカウントを初期化
	this->happyCnt = 0;					//クリア状態のカウント
	this->motion = Motion::Normal;		//motion初期化
	this->isAuto = true;				//オート移動設定を初期化
	this->isCollision = true;			//当たり判定設定初期化
	this->MoveCnt = 0;					//移動カウント初期化
	this->Radius = Vec2(1.0f, 0.9f);	//当たり判定を制限
	this->isCollisionNow = -1;			//当たり判定カウントを初期化
	this->isAutoOff = false;			//オート移動チェックを初期化
	this->isAutoMode = false;			//オートモードを初期化
	this->Restriction_x = nullptr;
	this->creditFlag = false;
	__super::SetDrawOrder(0.97f);
}
Chara::~Chara()
{
	//画像の解放
	this->Image.Finalize();
	if (player) {
		this->player->Destroy();
	}
	if (recorder) {
		this->recorder->Destroy();
	}
	if (this->Restriction_x)
	{
		delete this->Restriction_x;
	}
}
void Chara::UpDate()
{
	++AnimCnt;				//アニメーションカウントを増やす
	//オート機能を切っていない状態でオート動作をするならば
	if (this->isAuto && !this->isAutoOff && !this->creditFlag)
	{
		//キャラに登録されているオート移動を行う
		//ここで実際は外部ファイルより情報を得てオート操作をさせたい
		this->AutoMove();
	}
	else if (recorder) {
		if (OGge->in->on(Input::in::CL)) {
			this->move.x = -5.0f;
			this->direction = Direction::LEFT;
		}
		if (OGge->in->on(Input::in::CR)) {
			this->move.x = 5.0f;
			this->direction = Direction::RIGHT;
		}
		if (OGge->in->on(Input::in::B1)) {
			this->AutoJump();
		}
	}
	else
	{
		//そうでない時
		//移動値がないならカウントを増やす
		if (this->move.x == 0 && this->move.y == 0)
		{	
			//10は超えないように制限しておく
			if (this->MoveCnt <= 10)
			{
				this->MoveCnt++;
			}
		}
		else
		{
			//移動している間はカウントを0にしておく
			this->MoveCnt = 0;
		}
		
	}

	std::cout << move.y << std::endl;
	if (player) {
		float tilt = player->GetCurrentStickTilt(In::AXIS_LEFT_X);
		if (tilt < 0.f) {
			this->move.x = tilt * 5.f;
			this->direction = Direction::LEFT;
		}
		if (tilt > 0.f) {
			this->move.x = tilt * 5.f;
			this->direction = Direction::RIGHT;
		}
	}

	if (this->motion != Happy_N && this->motion != Happy_J && this->motion != Happy_F) {
		if (this->move.x == 0) { this->motion = Normal; }
		else { this->motion = Walk; }
		if (this->move.y > 0) { this->motion = Motion::Fall; }
		if (this->move.y < 0) { this->motion = Motion::Jump_M; }
		if (this->EndPos.y != 0) { this->motion = Motion::Ladder; }
	}
	//カウントが10を超えているならばオート移動へ移行する
	if (this->MoveCnt > 10)
	{
		this->isAuto = true;
	}
	//左右移動の減算処理と重力計算
	this->Friction(this->move);
	//移動値から実際の移動を行う
	this->MoveCheck(this->move);
}
void Chara::Render2D()
{
	//描画位置とサイズを指定
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();
	Box2D src = this->returnSrc(this->motion);
	src.OffsetSize();
	if (this->Restriction_x)
	{
		if (this->direction == Direction::LEFT)
		{
			if (draw.x < *this->Restriction_x)
			{
				draw.x = *this->Restriction_x;
				src.x += this->srcX - (this->srcX * ((draw.w - draw.x) / this->Scale.x));
			}
		}
		else
		{
			if (draw.w > *this->Restriction_x)
			{
				draw.w = *this->Restriction_x;
				src.x += this->srcX - (this->srcX * ((draw.w - draw.x) / this->Scale.x));
			}
		}
	}
	//移動値に合わせて向きを合わせる
	//おそらくここでやるべきではないので後日修正します
	if (this->move.x > 0)
	{
		this->direction = Direction::RIGHT;
	}
	if (this->move.x < 0)
	{
		this->direction = Direction::LEFT;
	}
	//左向きなら画像を逆にする
	if (direction == Direction::RIGHT) {
		float k = src.w;
		src.w = src.x;
		src.x = k;
	}
	//描画
	this->Image.Draw(draw, src);
}
void Chara::Friction(Vec2& est)
{
	//横移動の減算処理
	if (est.x > 0)
	{
		est.x = std::max(est.x - this->FIN_SPEED, 0.f);
	}
	else
	{
		est.x = std::min(est.x + this->FIN_SPEED, 0.f);
	}
	//足元に地面がない時、または移動値がマイナスの時
	if (!this->FootCheck() || est.y < 0)
	{
		//重力計算
		est.y = std::min(est.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		//移動値を0にする
		est.y = 0.0f;
	}
}
void Chara::MoveCheck(Vec2 est)
{
	auto map = OGge->GetTask<Map>("map");
	while (est.x != 0.f)
	{
		float preX = this->position.x;
		if (est.x >= 1.f)
		{
			this->position.x += 1.f;
			est.x -= 1.f;
		}
		else if (est.x <= -1.f)
		{
			this->position.x -= 1.f;
			est.x += 1.f;
		}
		else
		{
			this->position.x += est.x;
			est.x = 0.f;
		}
		//当たり判定を行うカウントでありマップが存在しており当たり判定を行う設定の場合
		if (this->isCollisionNow != 0)
		{
			if (map && this->isCollision)
			{
				if (map->HitCheck(*this, 1))
				{
					this->position.x = preX;
					break;
				}
			}
		}
	}
	while (est.y != 0.f)
	{
		float preY = this->position.y;
		if (est.y >= 1.f)
		{
			this->position.y += 1.f;
			est.y -= 1.f;
		}
		else if (est.y <= -1.f)
		{
			this->position.y -= 1.f;
			est.y += 1.f;
		}
		else
		{
			this->position.y += est.y;
			est.y = 0.f;
		}
		//当たり判定を行うカウントでありマップが存在しており当たり判定を行う設定の場合
		if (this->isCollisionNow != 0)
		{
			if (map && this->isCollision)
			{

				if (map->HitCheck(*this, 1))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}
bool Chara::FootCheck()
{
	//当たり判定を行うカウントでないならfalseを返す
	if (this->isCollisionNow == 0)
	{
		return false;
	}
	//足元判定を生成
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && this->isCollision)
	{
		if (map->HitCheck(foot, 1))
		{
			return true;
		}
	}
	return false;
}
bool Chara::Jump()
{
	//ジャンプ値を移動値にいれる
	this->move.y = this->JUMP_POWER;
	//カウントを増やす(当たり判定を消すもしくは復活させる)
	this->IsCollisionCheck();
	return true;
}
void Chara::Happy(int count)
{
	//ジャンプする
	if (this->happyCnt < count-1) {
		//モーションを変える
		if (this->move.y > 0) {
			this->motion = Motion::Happy_J;
		}
		else {
			this->motion = Motion::Happy_F;
		}
		//向きを変える
		if (this->happyCnt % 2 == 0) {
			this->direction = Direction::LEFT;
			this->move.x = -2;
		}
		else {
			this->direction = Direction::RIGHT;
			this->move.x = 2;
		}
		//ジャンプする
		if (this->FootCheck() && this->move.y == 0) {
			this->motion = Motion::Happy_N;
			if (this->happyCnt < count - 2) {
				this->move.y = this->JUMP_POWER - 5.f;
			}
			++this->happyCnt;
		}
	}
	//終わったらモーション調整
	else {
		this->motion = Motion::Normal;
		++this->happyCnt;
	}
}
void Chara::AutoMove()
{
	//オートモードがtrueなら設定してある移動を行う
	if(this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(this->time), this->startPos.x, this->EndPos.x, this->time) - this->position.x;
		this->move.y = this->easing_y.quad.InOut(this->easing_y.Time(this->time), this->startPos.y, this->EndPos.y, this->time) - this->position.y;
		this->isAutoMode = this->easing_x.isplay() || this->easing_y.isplay();
		this->isAutoOff = !this->easing_x.isplay() || !this->easing_y.isplay();
			
	}
	else
	{
		//そうでなければ元々用意されている移動を行う
		if (player) {
			player->SetPlay();
			player->Play();
		}
	}
}
void Chara::AutoMoveX()
{
	//オートモードがtrueなら設定してある移動を行う
	if (this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(this->time), this->startPos.x, this->EndPos.x, this->time) - this->position.x;
		this->isAutoMode = this->easing_x.isplay();
		this->isAutoOff = !this->easing_x.isplay();
	}
	else
	{
		//そうでなければ元々用意されている移動を行う
		if (player) {
			player->SetPlay();
			player->Play();
		}
	}
}
void Chara::ManualMove(Vec2& est)
{
	//手動移動値をそのまま入れる
	this->isAuto = false;
	this->MoveCnt = 0;
	this->move = est;
}
void Chara::IsCollisionCheck()
{
	//カウントを増やす
	this->isCollisionNow++;
}
bool Chara::CollisionNumCheck(__int8 num)
{
	//同じかを比べてその結果を返す
	return this->isCollisionNow == num ? true : false;
}
void Chara::MoveReset()
{
	//0,0に初期化
	this->move = { 0,0 };
}
void Chara::SetDirection(const Direction& set)
{
	//向きを上書き
	this->direction = set;
}
void Chara::SetAutoFlag(const bool flag)
{
	//オートモードの設定を上書き
	this->isAutoOff = flag;
}
Vec2 Chara::GetMove() const
{
	//移動値を返す
	return this->move;
}
void Chara::SetAutoMode(const bool flag)
{
	//オートモード設定を上書き
	this->isAutoMode = flag;
}
void Chara::Set(const Vec2& start_, const Vec2& end_,const float time_)
{
	//開始位置を登録
	this->startPos = start_;
	//終了位置を登録
	this->EndPos = end_;
	//移動時間を登録
	this->time = time_;
	//終了位置からの移動値に上書き
	this->EndPos -= this->startPos;
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
void Chara::SetX(const float start_, const float end_, const float time_)
{
	//開始位置を登録
	this->startPos.x = start_;
	//終了位置を登録
	this->EndPos.x = end_;
	//移動時間を登録
	this->time = time_;
	//終了位置からの移動値に上書き
	this->EndPos.x -= this->startPos.x;
	this->easing_x.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
bool Chara::isAutoPlay() const
{
	//イージングの移動を行っているかを返す
	return this->easing_x.isplay() || this->easing_y.isplay();
}
bool Chara::isAutoPlayX() const
{
	//イージングの移動を行っているかを返す
	return this->easing_x.isplay();
}
Chara::Direction Chara::nowDirection() const
{
	//向きを返す
	return this->direction;
}
Chara::SP Chara::Create(std::string& path, Vec2& pos, bool flag)
{
	Chara::SP to = Chara::SP(new Chara(path, pos));
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}
void Chara::SetReplayEnable()
{
	this->player = RecPlayer::Create("./data/TitleMovement.txt", true);
	this->player->SetPause();
	this->player->SetRepeat(true);
	this->player->AddKeyEvent(Input::in::CL, RecDef::KeyState::PRESS, [&]() {
		this->move.x = -5.0f;
		this->direction = Direction::LEFT;
	});
	this->player->AddKeyEvent(Input::in::CR, RecDef::KeyState::PRESS, [&]() {
		this->move.x = 5.0f;
		this->direction = Direction::RIGHT;
	});
	this->player->AddKeyEvent(Input::in::B1, RecDef::KeyState::PRESS, [&]() {
		this->AutoJump();
	});
	this->player->SetEndCallback([&]() -> bool {
		float judgeDirection = 790.f - this->position.x;
		if (abs(judgeDirection) > 5.f) {
			if (judgeDirection > 0) {
				this->move.x = 5.f;
				this->direction = Direction::RIGHT;
				return false;
			}
			if (judgeDirection < 0) {
				this->move.x = -5.f;
				this->direction = Direction::LEFT;
				return false;
			}
		}
		this->move.x = judgeDirection;
		this->direction = (judgeDirection < 0) ? Direction::LEFT : Direction::RIGHT;
		return true;
	});
}
void Chara::SetRecordEnable()
{
	this->isAuto = false;
	this->isAutoOff = true;
	recorder = Recorder::Create("./data/TitleMovement.txt", true);
	recorder->ActivateKeyRecord(OGge->in);
	recorder->RecordJoysticks();
	(*recorder) >> Input::in::CL;
	(*recorder) >> Input::in::CR;
	(*recorder) >> Input::in::B1;
	recorder->RecordStart();
}
bool Chara::AutoJump()
{
	//ジャンプ値を移動値にいれる
	this->move.y = this->JUMP_POWER;
	this->EndPos.y = 0;
	return true;
}
void Chara::SetRestriction(const float x_)
{
	if (this->Restriction_x)
	{
		delete this->Restriction_x;
	}
	this->Restriction_x = new float(x_);
}
Box2D Chara::returnSrc(Motion motion)
{
	Box2D src(0, 0, this->srcX, this->srcY);	//仮のsrc（後で消すかも）
	switch (motion)
	{
	case Motion::Normal:
		src = Box2D(this->idle[this->AnimCnt / 3 % 10] * this->srcX, 0, this->srcX, this->srcY);
		break;

	case Motion::Walk:
		src = Box2D(this->walk[this->AnimCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Jump_M:
		src = Box2D(0 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Fall:
		src = Box2D(1 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Ladder:
		src = Box2D(this->ladder[this->AnimCnt / 15 % 2] * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
		break;

	case Motion::Happy_N:
		src = Box2D(2* 641, 10 * this->srcY, 641, this->srcY);
		break;
	case Motion::Happy_J:
		src = Box2D(0 * 641, 10 * this->srcY, 641, this->srcY);
		break;
	case Motion::Happy_F:
		src = Box2D(1 * 641, 10 * this->srcY, 641, this->srcY);
		break;
	}
	return src;
}

void Chara::SetCollisionNow(__int8 now)
{
	isCollisionNow = now;
}