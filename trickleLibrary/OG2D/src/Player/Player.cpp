#include "Player.h"
#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Switch.h"

Player::Player()
{
	this->hold = false;
}
Player::~Player()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}
bool Player::Initialize()
{
	//オブジェクトの初期化
	this->CreateObject(Cube, Vec2(200.f, 200.0f), Vec2(64.0f, 64.f), 0.0f);
	this->objectTag = "Player";
	//デバッグ用位置調整
	//this->position = { 841,700 };
	//テクスチャの読み込み
	//各変数の初期化
	this->CheckJump = true;
	this->CheckGravity = true;
	this->est = { 0.f,0.f };
	this->moveCnt = 0;
	this->inv = 0;
	//状態の初期化
	this->direction = Direction::RIGHT;
	this->motion = Motion::Normal;
	this->state = State::NORMAL;
	//自動移動用値の初期化
	this->animation.Initialize();
	__super::Init((std::string)"Player");
	return true;
}
bool Player::Initialize(Vec2& pos)
{
	this->taskName = "Player";
	__super::Init(this->taskName);
	//オブジェクトの初期化
	this->CreateObject(Cube, pos, Vec2(64.0f, 64.f), 0.0f);
	this->objectTag = "Player";
	//デバッグ用位置調整
	//this->position = { 841,700 };
	//this->position = { 19 * 64 + 32,13 * 64 };
	//テクスチャの読み込み
	//各変数の初期化
	this->CheckJump = true;
	this->CheckGravity = true;
	this->est = { 0.f,0.f };
	this->moveCnt = 0;
	this->inv = 0;
	//状態の初期化
	this->direction = Direction::RIGHT;
	this->motion = Motion::Normal;
	this->state = State::NORMAL;
	//自動移動用値の初期化
	this->animation.Initialize();
	return true;
}
void Player::UpDate()
{
	++animation.timeCnt;
	//アニメーションカウントを増やす

	switch (this->state)
	{
	case State::ANIMATION:
		if (this->animation.isMove())
		{
			//this->motion = Motion::Walk;
			//移動処理
			this->position += this->animation.Move();
		}
		else
		{
			//通常に戻す
			this->state = State::NORMAL;
		}
		break;
	case State::BUCKET:
		//バケツの値を自分に合わせる
		this->BucketMove();
		if (OGge->in->down(In::B2))
		{
			if (this->hold)
			{
				//元に戻す
				this->state = State::NORMAL;
				//持っている判定を元に戻す
				auto bucket = OGge->GetTasks<Bucket>("bucket");
				for (auto id = bucket->begin(); id != bucket->end(); ++id)
				{
					if ((*id)->GetHold())
					{
						(*id)->HoldCheck(false);
						this->hold = false;
					}
				}
				auto waters = OGge->GetTasks<Water>("water");
				for (auto id = waters->begin(); id != waters->end(); ++id)
				{
					if ((*id)->GetHold())
					{
						if (this->direction == Direction::LEFT)
						{
							(*id)->position.x -= this->Scale.x;
						}
						else
						{
							(*id)->position.x += this->Scale.x;
						}
						(*id)->HoldCheck(false);
						(*id)->ResetMove();
						this->hold = false;
					}
				}
				this->inv = 10;
			}
		}
		break;
	case State::NORMAL:
		break;
	}
	if (this->inv > 0)
	{
		this->inv--;
	}
	//各状態での処理と別状態への移行
	switch (this->motion)
	{
	case Motion::Normal:
		if (!this->FootCheck())
		{
			//地面がない場合に落下処理に移行
			this->motion = Motion::Fall;
			break;
		}
		if (OGge->in->on(In::B1))
		{
			if (this->FootCheck())
			{
				//落下していない時のみジャンプが有効
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
		}
		if (OGge->in->down(In::B2))
		{
			//バケツを持つ
			if (this->BucketHit()) 
			{
				this->state = State::BUCKET;
			}
		}
		if (this->state != State::BUCKET) {
			if (this->InputDown())
			{
				if (this->FootCheck((std::string)"Ladder"))
				{
					//梯子状態に移行
					this->motion = Motion::Ladder;
					//アニメーション状態に移行
					this->state = State::ANIMATION;
					//カウントリセット
					this->moveCnt = 0;
					//移動値をすべてリセット
					this->est = { 0.f,0.f };
				}
			}
			if (this->InputUp())
			{
				if (this->ObjectHit((std::string)"Ladder"))
				{
					this->motion = Motion::Ladder;
					this->state = State::ANIMATION;
					this->moveCnt = 0;
					this->est = { 0.f,0.f };
				}
			}
		}
		if (this->InputLeft() || this->InputRight())
		{
			//NORMALの時、左右ボタンを押すとWALKに変わる
			this->motion = Motion::Walk;
		}
		this->BlockHit();
		if (OGge->in->down(In::B2))
		{
			animation.timeCnt = 0;
			this->motion = Motion::Switch_M;
			this->SwitchCheck();
		}
		break;
	case Motion::Jump:
		//飛び出したときに初期値を入れる
		if (this->moveCnt == 0)
		{
			this->est.y = Player::JUMP_POWER;
			this->moveCnt++;
		}
		//落下し始めたらFallに移動
		if (this->est.y >= 0.f)
		{
			this->motion = Fall;
		}
		//頭が当たったら上昇をやめて落下に移動
		if (this->HeadCheck())
		{
			this->est.y = 0.f;
			this->motion = Fall;
		}
		break;
	case Motion::Fall:
		//地面についたら通常に戻る
		if (this->FootCheck()) 
		{
			this->motion = Motion::Normal;
		}
		break;
	case Motion::Ladder:	//梯子処理
		//アニメーション中以外
		if (this->state != State::ANIMATION) 
		{
			if (OGge->in->on(In::B1))
			{
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
			if (this->InputUp())
			{	
				++this->animation.ladderCnt;
				Vec2 e = { 0.f,-5.0f };
				this->MoveCheck(e, (std::string)"Floor");
				if (this->HeadCheck((std::string)"Ladder", 1))
				{
					this->motion = Motion::Normal;
					//アニメーション状態に移行
					this->state = State::ANIMATION;
					//カウントリセット
					this->moveCnt = 0;
					//移動値をすべてリセット
					this->est = { 0.f,0.f };
				}
			}
			if (this->InputDown())
			{
				++this->animation.ladderCnt;
				Vec2 e = { 0.f,5.0f };
				this->MoveCheck(e, (std::string)"Floor");
				if (this->FootCheck((std::string)"Ladder", 1))
				{
					this->motion = Motion::Normal;
				}
				else
				{
					//重力処理を行わないのでここで終了
					return;
				}
				
			}
		}
		break; 
	case Walk:
		if (!this->InputRight() && !this->InputLeft())
		{
			this->motion = Motion::Normal;
		}
		if (OGge->in->on(In::B1))
		{
			//歩いてるときのジャンプ
			this->motion = Motion::Jump;
			this->moveCnt = 0;
		}
		if (OGge->in->down(In::B2))
		{
			//バケツを持つ
			if (this->BucketHit())
			{
				this->state = State::BUCKET;
			}
			else
			{
				//もしバケツをとれないならばスイッチの判定を行う
				this->SwitchCheck();
			}
		}
		this->BlockHit();
		break;
	case Switch_M:
		if (animation.timeCnt > 29) {
			this->motion = Motion::Normal;
		}
	}
	//重力とかとかの移動処理の計算
	if (this->state != State::ANIMATION)
	{
		this->Friction();
	}
	//はしご中以外は左右移動ができる
	if (this->motion != Motion::Ladder)
	{
		if (this->InputLeft())
		{
			this->est.x = -this->MOVE_SPEED;
			this->direction = Direction::LEFT;
		}
		if (this->InputRight())
		{
			this->est.x = +this->MOVE_SPEED;
			this->direction = Direction::RIGHT;
		}
	}
	//最終的な移動値を反映させる
	this->MoveCheck(this->est);
}
void Player::Render2D()
{

	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();

	Box2D src = this->animation.returnSrc(this->motion, this->state);
	//モションを受けsrcをreturnする
	src.OffsetSize();

	//左向きなら画像を逆にする
	if (direction == Direction::RIGHT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg->Draw(draw, src);
}
bool Player::Finalize()
{
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		
	}
	return true;
}
Vec2 Player::GetEst() const {
	return est;
}
bool Player::HeadCheck()
{
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x,this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->hitBase[y][x].objectTag == "Floor" ||
				map->hitBase[y][x].objectTag == "Net" ||
				map->hitBase[y][x].objectTag == "Soil")
			{
				if (head.hit(map->hitBase[y][x]))
				{
					return true;
				}
			}
		}
	}
	auto block = OGge->GetTask<Block>("block");
	if (block)
	{
		if (head.hit(*block))
		{
			return true;
		}
	}
	return false;
}
bool Player::HeadCheck(std::string& objname_, int n)
{
	GameObject head;
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (n == 0) {
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					if (head.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, map->hitBase[y][x].position);
						return true;
					}
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag != objname_)
				{
					if (head.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y - 1.0f));
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Player::FootCheck()
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (map->hitBase[y][x].objectTag == "Floor" ||
				map->hitBase[y][x].objectTag == "Net" ||
				map->hitBase[y][x].objectTag == "Soil" || 
				map->_arr[y][x] == 24)
			{
				if (foot.hit(map->hitBase[y][x]))
				{
					return true;
				}
			}
		}
	}
	auto block = OGge->GetTask<Block>("block");
	if (block) 
	{
		if (foot.hit(*block))
		{
			return true;
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if (foot.hit(*(*id)))
		{
			if ((*id)->objectTag == "SOLID")
			{
				return true;
			}
		}
	}
	return false;
}
bool Player::FootCheck(std::string& objname_,int n)
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y + 1.1f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (n == 0) {
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					if (foot.hit(map->hitBase[y][x]))
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y + 10.f));
						return true;
					}
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].objectTag != objname_)
				{
					if (foot.hit(map->hitBase[y][x]))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Player::MoveCheck(Vec2 est)
{
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
		auto map = OGge->GetTask<Map>("map");
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "Net" || 
						map->_arr[y][x] == 24)
					{
						this->position.x = preX;
						break;
					}
				}
			}
		}
		auto block = OGge->GetTask<Block>("block");
		if (block)
		{
			if (this->hit(*block))
			{
				this->position.x = preX;
				break;
			}
		}
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//氷であり
			if ((*id)->objectTag == "SOLID")
			{
				//所持状態でないときのみ
				if (!(*id)->GetHold())
				{
					//当たり判定を行う
					if (this->hit(*(*id)))
					{
						this->position.x = preX;
						break;
					}
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
		auto map = OGge->GetTask<Map>("map");
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "Net" ||
						map->_arr[y][x] == 24)
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
		auto block = OGge->GetTask<Block>("block");
		if (block)
		{
			if (this->hit(*block))
			{
				this->position.y = preY;
				break;
			}
		}
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//氷であり
			if ((*id)->objectTag == "SOLID")
			{
				//所持状態でないときのみ
				if (!(*id)->GetHold())
				{
					//当たり判定を行う
					if (this->hit(*(*id)))
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}
void Player::Friction()
{
	if (this->motion == Motion::Ladder)
	{
		return;
	}
	if (this->est.x > 0)
	{
		this->est.x = std::min(this->est.x + this->FIN_SPEED, 0.f);
	}
	else
	{
		this->est.x = std::max(this->est.x - this->FIN_SPEED, 0.f);
	}
	if (!this->FootCheck() || this->est.y < 0)
	{
		this->est.y = std::min(this->est.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		this->est.y = 0.0f;
	}
}
bool Player::BucketHit()
{
	if (this->inv != 0)
	{
		return false;
	}
	//すでに持っているならば動かない
	if (this->hold)
	{
		return false;
	}
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*bucket).begin(); id != (*bucket).end(); ++id)
	{
		if (this->hit(*(*id)))
		{
			(*id)->HoldCheck(true);
			this->hold = true;
			return true;
		}
	}
	GameObject left;
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 3.0f, this->position.y), Vec2(3.0f, this->Scale.y), 0.0f);
	GameObject right;
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(3.0f, this->Scale.y), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (!(*id)->GetHold())
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				if (left.hit(*(*id)) || right.hit(*(*id)))
				{
					(*id)->HoldCheck(true);
					this->hold = true;
					return true;
				}
			}
		}
	}
	return false;
}
void Player::SwitchCheck()
{
	auto switchs = OGge->GetTasks<Switch>("Switch");
	for (auto id = switchs->begin(); id != switchs->end(); ++id)
	{
		if ((*id)->hit(*this))
		{
			(*id)->ON_OFF(); 
			(*id)->GetisON();
		}
	}
}
void Player::BucketMove()
{
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		if ((*id)->GetHold())
		{
			(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y };
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetHold())
		{
			(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y };
		}
	}
}
void Player::Animation::SetAnimaVec(Vec2& start_, Vec2& end_)
{
	this->startVec = start_;
	this->endVec = end_;
	this->animationVec = { this->endVec.x - this->startVec.x ,this->endVec.y - this->startVec.y };
}
bool Player::Animation::Initialize()
{
	this->animationVec = { 0.f,0.f };
	this->startVec = { 0.f,0.f };
	this->endVec = { 0.f,0.f };
	this->timeCnt = 0;
	this->ladderCnt = 0;
	return true;
}
Vec2 Player::Animation::Move()
{
	Vec2 move = { 0.f,0.f };
	if (this->animationVec.x != 0.f)
	{
		if (this->animationVec.x >= 1.0f)
		{
			move.x += 1.0f;
			this->animationVec.x -= 1.0f;
		}
		else if (this->animationVec.x <= -1.0f)
		{
			move.x -= 1.0f;
			this->animationVec.x += 1.0f;
		}
		else
		{
			move.x += this->animationVec.x;
			this->animationVec.x = 0.f;
		}
	}
	if (this->animationVec.y != 0.f)
	{
		if (this->animationVec.y >= 1.0f)
		{
			move.y += 1.0f;
			this->animationVec.y -= 1.0f;
		}
		else if (this->animationVec.y <= -1.0f)
		{
			move.y -= 1.0f;
			this->animationVec.y += 1.0f;
		}
		else
		{
			move.y += this->animationVec.y;
			this->animationVec.y = 0.f;
		}
	}
	return move;
}
bool Player::Animation::isMove()
{
	if (this->animationVec.x != 0.f || this->animationVec.y != 0.f)
	{
		return true;
	}
	return false;
}
Box2D Player::Animation::returnSrc(Motion motion, State state) 
{
	Box2D src(0,0,550,550);	//基本のsrc（後で消すかも）
//	if (state == Normal) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * 550, 0, 550, 550);
			return src;
			break;

		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * 550, 550, 550, 550);
			return src;
			break;

		case Motion::Jump:
			src = Box2D(0 * 550, 2 * 550, 550, 550);
			return src;
			break;

		case Motion::Fall:
			src = Box2D(1 * 550, 2 * 550, 550, 550);
			return src;
			break;
		//
		//case Motion::Ladder:
		//	src = Box2D(this->ladder[this->ladderCnt / 8 % 2] * 550, 3 * 550, 550, 550);
		//	break;

		//case Motion::Switch_M:
		//	auto switchs = OGge->GetTasks<Switch>("Switch");
		//	bool tempS;
		//	for (auto id = switchs->begin(); id != switchs->end(); ++id)
		//	{
		//		tempS = (*id)->GetisON();
		//	}
		//	if (tempS) {
		//		src = Box2D(this->switch_a[this->timeCnt / 5 % 6] * 550, 8 * 550, 550, 550);	
		//	}
		//	else {
		//		src = Box2D(this->switch_a[this->timeCnt / 5 % 6] * 550, 8 * 550, 550, 550);	//後で修正
		//	}
		//	break;
		//}
	}/*
	if (state == BUCKET) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * 550, 4*550, 550, 550);
			return src;
			break;

		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * 550, 5 * 550, 550, 550);
			return src;
			break;

		case Motion::Jump:
			src = Box2D(0 * 550, 7 * 550, 550, 550);
			return src;
			break;

		case Motion::Fall:
			src = Box2D(1 * 550, 7 * 550, 550, 550);
			return src;
			break;
		}
	}*/
	return src;

}
void Player::MoveCheck(Vec2& est, std::string& objname_)
{
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
		auto map = OGge->GetTask<Map>("map");
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (this->hit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == "Floor" ||
						map->hitBase[y][x].objectTag == "LadderTop")
					{
						this->position.y = preY;
						break;
					}
				}
			}
		}
	}
}
bool Player::ObjectHit(std::string& objname_)
{
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (this->hit(map->hitBase[y][x]))
			{
				if (map->hitBase[y][x].objectTag == objname_)
				{
					this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, this->position.y));
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::BlockHit()
{
	GameObject left;
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.0f,this->Scale.y), 0.0f);
	GameObject right;
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(1.0f, this->Scale.y), 0.0f);
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		if (left.hit(*(*id)))
		{
			(*id)->PlCheckHit(left);
			if (this->est.x < 0)
			{
				(*id)->GetMove(this->est);
			}
		}
		if (right.hit(*(*id)))
		{
			(*id)->PlCheckHit(right);
			if (this->est.x > 0)
			{
				(*id)->GetMove(this->est);
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if ((*id)->GetState() == Water::State::SOLID)
		{
			if (this->est.x < 0)
			{
				if (left.hit(*(*id)))
				{
					(*id)->MoveSolid(this->est);
				}
			}
			if (this->est.x > 0)
			{
				if (right.hit(*(*id)))
				{
					(*id)->MoveSolid(this->est);
				}
			}
		}
	}
	return false;
}
void Player::SetTexture(Texture* texture)
{
	this->playerimg = texture;
}
Player::State Player::NowState() const
{
	return this->state;
}
void Player::SetPos(Vec2& pos)
{
	this->position = pos;
}
Vec2 Player::GetPos() const
{
	return this->position;
}
Player::SP Player::Create(Vec2& pos, bool flag)
{
	auto to = Player::SP(new Player());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(pos))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}