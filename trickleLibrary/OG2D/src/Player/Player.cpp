#include "Player.h"
#include "Bucket\bucket.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Block\block.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Gimmick\NO_MOVE\Door.h"
#include "Gimmick/NO_MOVE/WeightSwitch.h"

Player::Player()
	:MOVE_SPEED(5.0f),
	JUMP_POWER(-13.0f),
	MAX_FALL(15.0f),
	GRAVITY((9.8f/60.0f/60.0f*32.0f)*10.0f),
	FIN_SPEED(0.5f)
{
	this->hold = false;
	this->isInputAuto = false;
	this->isInput = false;
	this->haveAddPos = { 0,0 };
	this->mass = 1.0f;      //仮
}
Player::~Player()
{
}
bool Player::Initialize(Vec2& pos)
{
	this->taskName = "Player";
	__super::Init(this->taskName);
	__super::SetDrawOrder(0.45f);
	//オブジェクトの初期化
	this->CreateObject(Cube, pos, Vec2(64.0f, 80.f), 0.0f);
	this->objectTag = "Player";
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
	if (this->animation.timeCnt >= 300000)
	{
		this->animation.timeCnt = 0;
	}
	//アニメーションカウントを増やす
	this->StateUpDate();
	//各状態での処理と別状態への移行
	if (this->state != State::ANIMATION)
	{
		if (!this->MotionUpDate())
		{
			//終了を指示された結果ならreturnで後の処理を行わない
			return;
		}
		//重力と摩擦の計算
		this->Friction();

		//スイッチはすぐモーションが変わらないのでanimation中の状態を持ってくる
		if (this->motion != Motion::Ladder && animation.animMo != Motion::Switch_M && this->animation.animMo != Motion::Ladder &&
			this->motion != Motion::Lift && this->motion != Lower && this->motion != Spill && this->motion != Motion::NoLower) {
			if (this->InputLeft())
			{
				this->est.x = -this->MOVE_SPEED;
				this->direction = Direction::LEFT;
			}
			else if (this->InputRight())
			{
				this->est.x = +this->MOVE_SPEED;
				this->direction = Direction::RIGHT;
			}
			else
			{
				this->est.x = this->AxisLX() * this->MOVE_SPEED;
				if (this->AxisLX() > 0)
				{
					this->direction = Direction::RIGHT;
				}
				if (this->AxisLX() < 0)
				{
					this->direction = Direction::LEFT;
				}
			}
			
		}
	}
	//最終的な移動値を反映させる
	Vec2 move = this->est;
	this->MoveCheck(move);
	if (this->TohaveObjectHit() && this->state == State::NORMAL) {
		//ブロックを押す
		this->motion = Motion::Block_M;
	}
	if (this->state == State::BUCKET)
	{
		this->HaveObjectPosMove();
	}
}
void Player::Render2D()
{
	Box2D draw;
	if (this->hold)
	{
		draw = { this->position.x - 8.f,this->position.y + this->haveAddPos.y,this->Scale.x + 8.f, this->Scale.y - this->haveAddPos.y };
		draw.OffsetSize();
	}
	else
	{
		draw = { this->position.x - 8.f, this->position.y, this->Scale.x + 8.f, this->Scale.y };
		draw.OffsetSize();
	}
	{
		draw.y += 2.f;
		draw.h += 2.f;
	}
	Box2D src = this->animation.returnSrc(this->motion, this->state, this->direction);
	//モ-ションを受けsrcをreturnする
	src.OffsetSize();

	//左向きなら画像を逆にする
	if (direction == Direction::RIGHT) {
		float k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->playerimg->Rotate(0);
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
	if (this->state == State::CLEAR)
	{
		return false;
	}
	this->head.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && map->HitCheck(head, 1))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (this->head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->head.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	auto door = OGge->GetTasks<Door>("Door");
	for (auto id = door->begin(); id != door->end(); ++id)
	{
		if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (head.hit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}
bool Player::HeadMapCheck(const std::string& objname_, bool flag)
{
	this->head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (head.IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (head.CubeHit(map->hitBase[y][x]))
				{
					if (flag)
					{
						if (map->hitBase[y][x].objectTag == objname_)
						{
							//this->animation.SetAnimaVec(this->position, map->hitBase[y][x].position);
							this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y - (this->Scale.y - 64.f)));
							return true;
						}
					}
					else
					{
						if (map->hitBase[y][x].objectTag != objname_)
						{
							this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y - (this->Scale.y - 64.f)));
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
bool Player::HeadSolidCheck()
{
	if (this->hold)
	{
		return false;
	}
	//頭の当たり判定
	head.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y - 1.0f), Vec2(this->Scale.x - 1.f, this->Scale.y), 0.0f);
	//水情報
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//相手が氷であり
		if ((*id)->GetState() == Water::State::SOLID)
		{
			//自分の近辺に存在しており
			if (head.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				//相手が持っている氷じゃなくて
				if (!(*id)->GetHold())
				{
					//当たっているならば
					if (head.CubeHit(*(*id)))
					{
						(*id)->HoldCheck(true);
						this->hold = true;
						this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) + 30.f };
						this->position.y -= this->haveAddPos.y;
						this->Scale.y += this->haveAddPos.y;
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Player::SolidHitCheck()
{
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->objectTag == "SOLID" && !(*id)->GetHold())
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool Player::FootCheck()
{
	this->foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && map->HitCheck(foot, 1))
	{
		return true;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				if ((*id)->objectTag == "SOLID")
				{
					return true;
				}
			}
		}
	}

	//テスト追加
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");
	for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
	{
		if (foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}

	return false;
}
bool Player::FootMapCheck(const std::string& objname_, bool flag)
{
	this->foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y + 1.5f), Vec2(this->Scale.x - 1.f, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (foot.IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (foot.CubeHit(map->hitBase[y][x]))
				{
					if (flag)
					{
						if (map->hitBase[y][x].objectTag == objname_)
						{
							this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, map->hitBase[y][x].position.y + 10.f));
							return true;
						}
					}
					else
					{
						if (map->hitBase[y][x].objectTag != objname_)
						{
							//this->animation.SetAnimaVec(this->position, Vec2(map->hitBase_[y][x].position.x, map->hitBase_[y][x].position.y + 10.f));
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
bool Player::SolidFootCheck()
{
	foot.CreateObject(Objform::Cube, Vec2(this->position.x + 1.f, this->position.y + this->Scale.y), Vec2(this->Scale.x - 1.f, 64.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		//氷であり自分の近辺であり
		if ((*id)->GetState() == Water::State::SOLID && foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			//当たっているならば
			if (foot.CubeHit(*(*id)))
			{
				return true;
			}
		}
	}
	return false;
}
void Player::MoveCheck(Vec2& est)
{
	auto map = OGge->GetTask<Map>("map");
	if (!map)
	{
		return;
	}
	auto blocks = OGge->GetTasks<Block>("block");
	auto waters = OGge->GetTasks<Water>("water");
	auto block = OGge->GetTask<Block>("block");
	auto door = OGge->GetTasks<Door>("Door");
	//テスト追加
	auto Wswitch = OGge->GetTasks<WeightSwitch>("WeightSwitch");

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
		if (map->HitCheck(*this, 1))
		{
			this->position.x = preX;
			break;
		}
		for (auto id = door->begin(); id != door->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}
		//テスト追加
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.x = preX;
					break;
				}
			}
		}

		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					block->plhit = true;

					this->position.x = preX;
					break;
				}
				else
				{
					block->plhit = false;
				}
			}
		}
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//氷であり
			if ((*id)->objectTag == "SOLID")
			{
				//所持状態でないときのみ
				if (!(*id)->GetHold())
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						//当たり判定を行う
						if (this->CubeHit(*(*id)))
						{
							this->position.x = preX;
							break;
						}
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
		if (map->HitCheck(*this, 1))
		{
			this->position.y = preY;
			break;
		}
		for (auto id = door->begin(); id != door->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->hit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
		//テスト追加
		for (auto id = Wswitch->begin(); id != Wswitch->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					this->position.y += (*id)->SetSwitchUpPos();
					break;
				}
			}
		}

		for (auto id = blocks->begin(); id != blocks->end(); ++id)
		{
			if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
		for (auto id = (*waters).begin(); id != (*waters).end(); ++id)
		{
			//氷であり
			if ((*id)->objectTag == "SOLID")
			{
				//所持状態でないときのみ
				if (!(*id)->GetHold())
				{
					if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
					{
						//当たり判定を行う
						if (this->CubeHit(*(*id)))
						{
							this->position.y = preY;
							break;
						}
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
bool Player::HaveObjectHit()
{
	if (this->inv > 0)
	{
		return false;
	}
	//すでに持っているならば動かない
	if (this->hold || this->motion == Motion::Switch_M)
	{
		return false;
	}
	auto bucket = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*bucket).begin(); id != (*bucket).end(); ++id)
	{
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (this->CubeHit(*(*id)))
			{
				(*id)->HoldCheck(true);
				this->hold = true;
				this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) };
				this->position.y -= this->haveAddPos.y;
				this->Scale.y += this->haveAddPos.y;
				return true;
			}
		}
	}
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 16.0f, this->position.y), Vec2(16.0f + this->Scale.x, this->Scale.y), 0.0f);
	right.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y), Vec2(16.0f + this->Scale.x, this->Scale.y), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if (!(*id)->GetHold())
		{
			if ((*id)->GetState() == Water::State::SOLID)
			{
				if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale) || right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (left.CubeHit(*(*id)) || right.CubeHit(*(*id)))
					{
						(*id)->HoldCheck(true);
						this->hold = true;
						this->haveAddPos = { ((*id)->Scale.x * (*id)->Radius.x) - (this->Scale.x - ((*id)->Scale.x * (*id)->Radius.x)),((*id)->Scale.y * (*id)->Radius.y) - (this->Scale.y - ((*id)->Scale.y * (*id)->Radius.y)) + 30.f };
						this->position.y -= this->haveAddPos.y;
						this->Scale.y += this->haveAddPos.y;
						return true;
					}
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
		if (this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if ((*id)->CubeHit(*this))
			{
				//移動する位置を返す
				this->animation.SetAnimaVec(this->position, Vec2((*id)->position));
				//移動した後にスイッチのアニメーションをするように
				this->animation.animMo = Motion::Switch_M;
				//移動するアニメーションに変える
				this->state = State::ANIMATION;
				this->est = { 0.f,0.f };
				return;
			}
		}
	}
}
void Player::HaveObjectPosMove()
{
	auto buckets = OGge->GetTasks<Bucket>("bucket");
	for (auto id = (*buckets).begin(); id != (*buckets).end(); ++id)
	{
		if ((*id)->GetHold())
		{
			if (this->motion == Motion::Spill) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 3) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y + 30 };
						(*id)->angle = 315;
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y + 60 };
						(*id)->angle = 270;
						break;
					case 2:
						(*id)->position = { this->position.x - 40,this->position.y + 30 };
						(*id)->angle = 315;
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 3) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y + 30 };
						(*id)->angle = 45;
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y + 60 };
						(*id)->angle = 90;
						break;
					case 2:
						(*id)->position = { this->position.x + 40,this->position.y + 30 };
						(*id)->angle = 45;
						break;
					}
				}
			}
			else if (this->motion == Motion::Lift) {
				if (this->animation.animCnt == 0)
				{
					this->animation.animCnt = 5;
				}
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y + 60 };
						break;
					case 1:
						(*id)->position = { this->position.x - 20,this->position.y + 30 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y + 60 };
						break;
					case 1:
						(*id)->position = { this->position.x + 20,this->position.y + 30 };
						break;
					}
				}
			}
			else if (this->motion == Motion::Lower) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 20,this->position.y + 30 };
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y + 50 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 20,this->position.y + 30 };
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y + 50 };
						break;
					}
				}
			}
			else {
				if (this->direction == Direction::RIGHT)
				{
					(*id)->position = { this->position.x,this->position.y - (*id)->Scale.y + 60.f };
				}
				else
				{
					(*id)->position = { this->position.x - 8.f,this->position.y - (*id)->Scale.y + 60.f };
				}
				(*id)->angle = 0;
			}
		}
	}
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetHold())
		{
			if (this->motion == Motion::Lift) {
				if (this->animation.animCnt == 0)
				{
					this->animation.animCnt = 5;
				}
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					case 1:
						(*id)->position = { this->position.x - 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					case 1:
						(*id)->position = { this->position.x + 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					}
				}
			}
			else if (this->motion == Motion::Lower) {
				if (this->direction == Direction::LEFT)
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x - 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					case 1:
						(*id)->position = { this->position.x - 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					}
				}
				else
				{
					switch (animation.animCnt / 8 % 2) {
					case 0:
						(*id)->position = { this->position.x + 20,this->position.y - this->haveAddPos.y + 50 };
						break;
					case 1:
						(*id)->position = { this->position.x + 40,this->position.y - this->haveAddPos.y + 70 };
						break;
					}
				}
			}
			else {
				if (this->direction == Direction::RIGHT)
				{
					(*id)->position = { this->position.x,this->position.y - this->haveAddPos.y + 35.f };
				}
				else
				{
					(*id)->position = { this->position.x - 8.f,this->position.y - this->haveAddPos.y + 35.f };
				}
			}
		}
	}
}
void Player::Animation::SetAnimaVec(Vec2& start_, Vec2& end_)
{
	this->startVec = start_;
	this->endVec = end_;
	if (this->startVec == this->endVec) {
		this->same_flag = true;
	}
	this->animationVec = { this->endVec.x - this->startVec.x ,this->endVec.y - this->startVec.y };
}
bool Player::Animation::Initialize()
{
	this->animationVec = { 0.f,0.f };
	this->startVec = { 0.f,0.f };
	this->endVec = { 0.f,0.f };
	this->timeCnt = 0;
	this->animCnt = 0;
	this->animMo = Normal;
	return true;
}
Vec2 Player::Animation::Move(Motion motion_)
{
	auto player = OGge->GetTask<Player>("Player");
	Vec2 move = { 0.f,0.f };
	//X軸だけ移動(目的地まで歩いて行く)
	if (this->animationVec.x != 0.f)
	{
		if (this->animationVec.x > 0.f)
		{
			player->direction = Player::Direction::RIGHT;
		}
		else if (this->animationVec.x < 0.f)
		{
			player->direction = Player::Direction::LEFT;
		}
		player->motion = Motion::Walk;
		if (this->animationVec.x >= 5.0f)
		{
			move.x += 5.0f;
			this->animationVec.x -= 5.0f;
		}
		else if (this->animationVec.x <= -5.0f)
		{
			move.x -= 5.0f;
			this->animationVec.x += 5.0f;
		}
		else
		{
			move.x += this->animationVec.x;
			this->animationVec.x = 0.f;
		}
	}
	//Ｙ軸だけ移動
	if (this->animationVec.x == 0.f)
	{
		//梯子に乗る
		if (this->animationVec.y >= 0.f && motion_ == Motion::Ladder)
		{
			move.y += this->animationVec.y;
			player->motion = motion_;
			this->animationVec.y = 0.f;
			this->animMo = Motion::Normal;
		}
		//スイッチを押す
		else if (this->animationVec.y >= 0.f && motion_ == Motion::Switch_M)
		{
			//スイッチのアニメーションを実行する
			player->direction = Direction::RIGHT;
			auto switchs = OGge->GetTasks<Switch>("Switch");
			for (auto id = switchs->begin(); id != switchs->end(); ++id)
			{
				if ((*id)->hit(*player))
				{
					(*id)->ChangeON_OFF();
				}
			}
			//yに移動させないようにする
			this->animationVec.y = 0.f;
			//プレイヤがスイッチを押すアニメーション
			player->motion = motion_;
		}
		//梯子から土に行く（Normal状態）
		else
		{
			move.y += this->animationVec.y;
			this->animCnt = 0;
			player->motion = Motion::Normal;
			this->animationVec.y = 0.f;
			this->animMo = Motion::Normal;
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
Box2D Player::Animation::returnSrc(Motion motion, State state, Direction dir)
{
	auto player = OGge->GetTask<Player>("Player");
	Box2D src(0, 0, this->srcX, this->srcY);
	//src = Box2D(this->指定したアニメーションの順番の配列[this->timeCnt / ディレイ　% コマ数] * this->srcX, 
	//		読み込む画像の行数 * this->srcY, 
	//		this->srcX, this->Y);
	if (state == Normal) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * this->srcX, 0, this->srcX, this->srcY);
			break;
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * this->srcX, 2 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Ladder:
			src = Box2D(this->ladder[this->animCnt / 8 % 2] * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Block_M:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 9 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Switch_M:
		{
			auto switchs = OGge->GetTasks<Switch>("Switch");
			for (auto id = switchs->begin(); id != switchs->end(); ++id) {
				if ((*id)->hit(*player)) {
					if ((*id)->isON()) {
						if (dir == Direction::LEFT)
						{
							src = Box2D(this->switch_1[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
						else
						{
							src = Box2D(this->switch_2[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
					}
					else {
						if (dir == Direction::LEFT)
						{
							src = Box2D(this->switch_2[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
						else
						{
							src = Box2D(this->switch_1[this->animCnt / 5 % 5] * this->srcX, 8 * this->srcY, this->srcX, this->srcY);
						}
					}
				}
			}
		}
		break;
		}
	}
	if (state == ANIMATION)
	{
		switch (motion) {
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Ladder:
			src = Box2D(0 * this->srcX, 3 * this->srcY, this->srcX, this->srcY);
			break;
		}
	}
	if (state == BUCKET) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(this->idle[this->timeCnt / 3 % 10] * this->srcX, 4 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Walk:
			src = Box2D(this->walk[this->timeCnt / 3 % 9] * this->srcX, 5 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * this->srcX, 7 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * this->srcX, 7 * this->srcY, this->srcX, this->srcY);
			break;

		case Motion::Lift:
			src = Box2D(this->lift[this->animCnt / 8 % 2] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Lower:
			src = Box2D(this->lower[this->animCnt / 8 % 2] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::Spill:
			src = Box2D(this->spill[this->animCnt / 8 % 3] * this->srcX, 6 * this->srcY, this->srcX, this->srcY);
			break;
		case Motion::NoLower:
			src = Box2D(2 * this->srcX, 4 * this->srcY, this->srcX, this->srcY);
			break;
		}
	}
	if (state == CLEAR) {
		switch (motion) {
		case Motion::Normal:
			src = Box2D(2 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		case Motion::Jump:
			src = Box2D(0 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		case Motion::Fall:
			src = Box2D(1 * 641, 10 * this->srcY, 641, this->srcY);
			break;
		}
	}
	return src;

}
void Player::LadderMoveCheck(Vec2& est)
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
		if (map && (map->HitCheck(*this, "Floor") || map->HitCheck(*this, "LadderTop")))
		{
			this->position.y = preY;
			break;
		}
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if ((*id)->GetState() == Water::State::SOLID && this->IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->CubeHit(*(*id)))
				{
					this->position.y = preY;
					break;
				}
			}
		}
	}
}
bool Player::MapHitCheck(const std::string& objname_)
{
	auto map = OGge->GetTask<Map>("map");
	for (int y = 0; y < map->mapSize.y; ++y)
	{
		for (int x = 0; x < map->mapSize.x; ++x)
		{
			if (this->IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
			{
				if (this->CubeHit(map->hitBase[y][x]))
				{
					if (map->hitBase[y][x].objectTag == objname_)
					{
						this->animation.SetAnimaVec(this->position, Vec2(map->hitBase[y][x].position.x, this->position.y));
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Player::TohaveObjectHit()
{
	left.CreateObject(Objform::Cube, Vec2(this->position.x - 1.0f, this->position.y), Vec2(1.0f, this->Scale.y - 1.0f), 0.0f);
	right.CreateObject(Objform::Cube, Vec2(this->position.x + this->Scale.x, this->position.y), Vec2(1.0f, this->Scale.y - 1.0f), 0.0f);
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = (*blocks).begin(); id != (*blocks).end(); ++id)
	{
		if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (left.CubeHit(*(*id)))
			{
				(*id)->PlCheckHit(left);
				if (this->est.x < 0)
				{
					(*id)->GetMove(this->est * 0.5f);
					return true;
				}
			}
		}
		if (right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
		{
			if (right.CubeHit(*(*id)))
			{
				(*id)->PlCheckHit(right);
				if (this->est.x > 0)
				{
					(*id)->GetMove(this->est * 0.5f);
					return true;
				}
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
				if (left.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (left.CubeHit(*(*id)))
					{
						if (!((*id)->MoveSolid(this->est) == Vec2(0, 0)))
						{
							return true;
						}
					}
				}
			}
			if (this->est.x > 0)
			{
				if (right.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
				{
					if (right.CubeHit(*(*id)))
					{
						if (!((*id)->MoveSolid(this->est) == Vec2(0, 0)))
						{
							return true;
						}
					}
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
	if (this->hold)
	{
		return Vec2(this->position.x, this->position.y + this->haveAddPos.y);
	}
	return this->position;
}
bool Player::ReleaseHold()
{
	if (this->hold)
	{
		if (this->PutCheck(this->Scale.x))
		{
			//持っている判定を元に戻す
			auto bucket = OGge->GetTasks<Bucket>("bucket");
			for (auto id = bucket->begin(); id != bucket->end(); ++id)
			{
				if ((*id)->GetHold())
				{
					(*id)->HoldCheck(false);
					this->hold = false;
					if (this->direction == Direction::LEFT)
					{
						(*id)->position.x = this->position.x - 50;
					}
					else
					{
						(*id)->position.x = this->position.x + 50;
					}
				}
			}
			auto waters = OGge->GetTasks<Water>("water");
			for (auto id = waters->begin(); id != waters->end(); ++id)
			{
				if ((*id)->GetHold())
				{
					if (this->direction == Direction::LEFT)
					{
						(*id)->position.x = this->position.x - 60;
					}
					else
					{
						(*id)->position.x = this->position.x + 60;
					}
					(*id)->HoldCheck(false);
					(*id)->ResetMove();
					this->hold = false;
				}
			}
			this->inv = 10;
			this->position.y += this->haveAddPos.y;
			this->Scale.y -= this->haveAddPos.y;
			this->haveAddPos = { 0,0 };
			return true;
		}
		else
		{
			this->animation.animCnt = 0;
			this->motion = Motion::NoLower;
		}
	}
	return false;
}
bool Player::ResetHold()
{

	if (this->hold)
	{
		if (this->PutCheck(this->Scale.x))
		{
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
					(*id)->HoldCheck(false);
					(*id)->ResetMove();
					this->hold = false;
				}
			}
			this->inv = 10;
			this->position.y += this->haveAddPos.y;
			this->Scale.y -= this->haveAddPos.y;
			this->haveAddPos = { 0,0 };
			return true;
		}
		else
		{
			this->animation.animCnt = 0;
			this->motion = Motion::NoLower;
		}
	}
	return false;
}
bool Player::ReleaseSolid()
{
	if (this->hold)
	{
		auto waters = OGge->GetTasks<Water>("water");
		for (auto id = waters->begin(); id != waters->end(); ++id)
		{
			if ((*id)->GetHold())
			{
				(*id)->position.x = this->position.x;
				(*id)->HoldCheck(false);
				(*id)->ResetMove();
				this->hold = false;
			}
		}
		this->inv = 0;
		this->position.y += this->haveAddPos.y;
		this->Scale.y -= this->haveAddPos.y;
		this->haveAddPos = { 0,0 };
		return true;
	}
	return false;
}
bool Player::LadderJumpCheck()
{
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		for (int y = 0; y < map->mapSize.y; ++y)
		{
			for (int x = 0; x < map->mapSize.x; ++x)
			{
				if (map->hitBase[y][x].Getarr() == 24)
				{
					if (this->IsObjectDistanceCheck(map->hitBase[y][x].position, map->hitBase[y][x].Scale))
					{
						if (this->CubeHit(map->hitBase[y][x]))
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
bool Player::PutCheck(const float scale_x)
{
	left.CreateObject(
		Cube,
		Vec2(this->position.x - scale_x, this->position.y),
		Vec2(scale_x, this->Scale.y),
		0.0f);
	right.CreateObject(Cube,
		Vec2(this->position.x + this->Scale.x, this->position.y),
		Vec2(scale_x, this->Scale.y),
		0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		if (this->direction == Direction::LEFT)
		{	
			if (map->HitCheck(left,1))
			{
				return false;
			}
		}
		else
		{
			if (map->HitCheck(right,1))
			{
				return false;
			}
		}
	}
	auto blocks = OGge->GetTasks<Block>("block");
	for (auto id = blocks->begin(); id != blocks->end(); ++id)
	{
		if (this->direction == Direction::LEFT)
		{
			if ((*id)->IsObjectDistanceCheck(left.position, left.Scale))
			{
				if ((*id)->CubeHit(left))
				{
					return false;
				}
			}
		}
		else
		{
			if ((*id)->IsObjectDistanceCheck(right.position, right.Scale))
			{
				if ((*id)->CubeHit(right))
				{
					return false;
				}
			}
		}
	}
	auto doors = OGge->GetTasks<Door>("Door");
	for (auto id = doors->begin(); id != doors->end(); ++id)
	{
		if (this->direction == Direction::LEFT)
		{
			if ((*id)->IsObjectDistanceCheck(left.position, left.Scale))
			{
				if ((*id)->hit(left))
				{
					return false;
				}
			}
		}
		else
		{
			if ((*id)->IsObjectDistanceCheck(right.position, right.Scale))
			{
				if ((*id)->hit(right))
				{
					return false;
				}
			}
		}
	}
	return true;
}
void Player::SetMotion(const Motion& motion_)
{
	this->motion = motion_;
}
void Player::SetState(const State& state_)
{
	this->state = state_;
}
void Player::SetInputAuto(bool flag)
{
	this->isInputAuto = flag;
	if (this->isInputAuto)
	{
		if (this->state == State::BUCKET)
		{
			this->motion = Motion::Lower;
			this->ResetHold();
		}
	}
}
bool Player::GetInputAuto() const
{
	return this->isInputAuto;
}
void Player::StateUpDate()
{
	switch (this->state)
	{
	case State::ANIMATION:
		//プレイヤが移動する距離が残っているとき||元々移動する距離がないとき
		if (this->animation.isMove() || animation.same_flag)
		{
			//移動処理
			this->position += this->animation.Move(this->animation.animMo);
			if (this->direction == Direction::LEFT)
			{
				this->est.x -= 5.0f;
			}
			else
			{
				this->est.x += 5.0f;
			}
			if (this->TohaveObjectHit())
			{
				this->state = State::NORMAL;
				this->motion = Motion::Normal;
			}
			this->est = { 0,0 };
			animation.same_flag = false;
		}
		else
		{
			//通常に戻す
			this->state = State::NORMAL;
		}
		break;
	case State::BUCKET:
		//バケツの値を自分に合わせる
		//this->HaveObjectPosMove();
		//バケツを置く動作
		if (this->InputB2down() && this->FootCheck() && this->motion != Motion::NoLower)
		{
			if (this->PutCheck(this->Scale.x) && this->motion != Motion::Spill)
			{
				this->motion = Motion::Lower;
			}
			else
			{
				this->animation.animCnt = 0;
				this->motion = Motion::NoLower;
			}
		}
		break;
	case State::NORMAL:
		break;
	case State::CLEAR:
		StateClearUpdate();
		break;
	}
	//無敵時間減少
	if (this->inv > 0)
	{
		this->inv--;
	}
}
bool Player::MotionUpDate()
{
	switch (this->motion)
	{
	case Motion::Normal:
		if (!this->MotionNormalUpDate())
		{
			return false;
		}
		break;
	case Motion::Jump:
		if (!this->MotionJumpUpDate())
		{
			return false;
		}
		break;
	case Motion::Fall:
		//地面についたら通常に戻る
		if (this->FootCheck())
		{
			this->motion = Motion::Normal;
		}
		break;
	case Motion::Ladder:
		//梯子処理
		//アニメーション中以外
		if (this->state != State::ANIMATION)
		{
			if (!this->MotionLadderUpDate())
			{
				return false;
			}
		}
		break;
	case Walk:
		if (!this->MotionWalkUpDate())
		{
			return false;
		}
		break;
	case Switch_M:
		++this->animation.animCnt;
		//スイッチのアニメーションが終わった時(フレイム5＊コマ数5) - 1
		if (this->animation.animCnt > 24) {
			//スイッチのモーションが終わると動けるようにする
			animation.animMo = Motion::Normal;
			this->motion = Motion::Normal;
			this->state = State::NORMAL;
			this->animation.animCnt = 0;
		}
		break;
	case Block_M:
		if (this->InputB1down())
		{
			if (this->FootCheck())
			{
				//落下していない時のみジャンプが有効
				this->motion = Motion::Jump;
				this->moveCnt = 0;
			}
		}
		if (!this->TohaveObjectHit()) {
			this->motion = Motion::Normal;
		}
		break;
	case Lift:
		++this->animation.animCnt;
		//8フレーム＊２コマ-１
		if (this->animation.animCnt > 15) {
			this->motion = Motion::Normal;
			this->animation.animCnt = 0;
		}
		break;
	case Lower:
		++this->animation.animCnt;
		//8フレーム＊２コマ-１
		if (this->animation.animCnt > 15) {
			this->ReleaseHold();
			this->motion = Motion::Normal;
			this->state = State::NORMAL;
			this->animation.animCnt = 0;
		}
		break;
	case Spill:
		++this->animation.animCnt;
		//8フレーム＊３コマ-１
		if (this->animation.animCnt > 23) {
			this->motion = Motion::Normal;
			this->animation.animCnt = 0;
		}
		break;
	case NoLower:
		if (!this->MotionNoLowerUpDate())
		{
			return false;
		}
		break;
	}
	return true;
}
bool Player::MotionNormalUpDate()
{
	if (this->InputB1down())
	{
		if (this->FootCheck())
		{
			//落下していない時のみジャンプが有効
			this->motion = Motion::Jump;
			this->moveCnt = 0;
		}
	}
	if (this->InputB2down())
	{
		//バケツを持つ
		if (this->HaveObjectHit())
		{
			this->state = State::BUCKET;
			this->motion = Motion::Lift;
		}
		else
		{
			if (this->state == State::NORMAL) {
				//スイッチを操作する
				this->SwitchCheck();
			}
		}
	}
	if (this->InputLeft() || this->InputRight() || this->AxisLX() != 0)
	{
		//NORMALの時、左右ボタンを押すとWALKに変わる
		this->motion = Motion::Walk;
	}
	this->LadderCheck();
	if (!this->FootCheck())
	{
		//地面がない場合に落下処理に移行
		this->motion = Motion::Fall;
	}
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionJumpUpDate()
{
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
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionLadderUpDate()
{
	if (this->InputDown() || this->isInputAuto)
	{
		++this->animation.animCnt;
		Vec2 e = { 0.f,5.0f };
		if (this->isInputAuto)
		{
			e.y += 10.f;
		}
		this->LadderMoveCheck(e);
		if (this->FootMapCheck("Ladder", false) || this->SolidFootCheck())
		{
			this->animation.animCnt = 0;
			this->motion = Motion::Normal;
		}
		else
		{
			//重力処理を行わないのでここで終了
			return false;
		}
	}
	else if (this->InputUp())
	{
		++this->animation.animCnt;
		Vec2 e = { 0.f,-5.0f };
		this->LadderMoveCheck(e);
		if (this->HeadMapCheck("LadderTop", true))
		{
			//移動が終わったら梯子モーションをするように設定
			this->animation.animMo = Motion::Normal;
			//アニメーション状態に移行
			this->state = State::ANIMATION;
			//カウントリセット
			this->moveCnt = 0;
			//移動値をすべてリセット
			this->est = { 0.f,0.f };
		}
	}
	else if (this->InputLeft() || this->InputRight() || this->AxisLX() > 0.8f || this->AxisLX() < -0.8f)
	{
		if (this->LadderJumpCheck())
		{
			this->motion = Normal;
			this->animation.animCnt = 0;
			this->moveCnt = 0;
			this->est = { 0,0 };
			return true;
		}
	}
	return true;
}
bool Player::MotionWalkUpDate()
{
	if (!this->FootCheck())
	{
		this->motion = Motion::Fall;
		return true;
	}
	if (!this->InputRight() && !this->InputLeft() && this->AxisLX() == 0)
	{
		//左右ボタンを押さないとnormalに戻る
		this->motion = Motion::Normal;
	}
	if (this->InputB1down())
	{
		//歩いてるときのジャンプ
		this->motion = Motion::Jump;
		this->moveCnt = 0;
	}
	if (this->InputB2down())
	{
		//バケツを持つ
		if (this->HaveObjectHit())
		{
			this->state = State::BUCKET;
			this->motion = Motion::Lift;
		}
		else
		{
			//スイッチを押す
			if (this->state == State::NORMAL) {
				this->SwitchCheck();
			}
		}
	}
	//if (this->TohaveObjectHit() && this->state == State::NORMAL) {
	//	//ブロックを押す
	//	this->motion = Motion::Block_M;
	//}
	if (this->HeadSolidCheck())
	{
		this->state = State::BUCKET;
	}
	return true;
}
bool Player::MotionNoLowerUpDate()
{
	this->animation.animCnt++;
	if (this->animation.animCnt >= 20)
	{
		this->motion = Motion::Normal;
		this->animation.animCnt = 0;
	}
	return true;
}
void Player::StateClearUpdate()
{
	if (this->motion == Motion::Normal) {
		this->moveCnt = 0;
		this->motion = Motion::Jump;
	}
}
bool Player::InputLeft() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CL);
}
bool Player::InputRight() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CR);
}
bool Player::InputDown() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(Input::CD) || OGge->in->on(In::LD);
}
bool Player::InputUp() {
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(In::CU) || OGge->in->on(In::LU);
}
float Player::AxisLX()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	if (OGge->in->axis(In::AXIS_LEFT_X) > 0.3f || OGge->in->axis(In::AXIS_LEFT_X) < -0.3f)
	{
		return OGge->in->axis(In::AXIS_LEFT_X);
	}
	return 0.0f;
}
float Player::AxisLY()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_LEFT_Y);
}
float Player::AxisRX()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_RIGHT_X);
}
float Player::AxisRY()
{
	if (this->isInputAuto || this->isInput)
	{
		return 0.0f;
	}
	return OGge->in->axis(In::AXIS_RIGHT_Y);
}
bool Player::InputB1down()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->down(In::B1);
}
bool Player::InputB2down()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->down(In::B2);
}
bool Player::InputB1on()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(In::B1);
}
bool Player::InputB2on()
{
	if (this->isInputAuto || this->isInput)
	{
		return false;
	}
	return OGge->in->on(In::B2);
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
void Player::SetInput(bool b)
{
	this->isInput = b;
}
bool Player::GetInput() const
{
	return this->isInput;
}
bool Player::LadderCheck()
{
	if (this->FootCheck())
	{
		if (this->InputDown())
		{
			if (this->FootMapCheck("Ladder", true) && !this->SolidFootCheck())
			{
				//バケツをおろす
				if (this->hold)
				{
					if (!this->ReleaseHold())
					{
						return false;
					}

				}
				//移動が終わったら梯子モーションをするように設定
				this->animation.animMo = Motion::Ladder;
				//アニメーション状態に移行
				this->state = State::ANIMATION;
				//カウントリセット
				this->moveCnt = 0;
				//移動値をすべてリセット
				this->est = { 0.f,0.f };
				return true;
			}
		}
		if (this->InputUp())
		{
			if (this->MapHitCheck("Ladder") && !this->SolidHitCheck())
			{
				if (this->hold)
				{
					if (!this->ReleaseHold())
					{
						return false;
					}
				}
				this->animation.animMo = Motion::Ladder;
				this->state = State::ANIMATION;
				this->moveCnt = 0;
				this->est = { 0.f,0.f };
				return true;
			}
		}
	}
	return false;
}