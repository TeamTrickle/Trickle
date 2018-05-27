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
	__super::SetDrawOrder(1.0f);	//描画順を登録
	this->objectTag = this->taskName;	//タグを登録
	this->direction = Direction::LEFT;	//向きを設定
	this->AnimCnt = 0;					//アニメーションカウントを初期化
	this->isAuto = true;				//オート移動設定を初期化
	this->isCollision = true;			//当たり判定設定初期化
	this->MoveCnt = 0;					//移動カウント初期化
	this->Radius = Vec2(1.0f, 0.9f);	//当たり判定を制限
	this->isCollisionNow = -1;			//当たり判定カウントを初期化
	this->isAutoOff = false;			//オート移動チェックを初期化
	this->isAutoMode = false;			//オートモードを初期化
}
Chara::~Chara()
{
	//画像の解放
	this->Image.Finalize();
}
void Chara::UpDate()
{
	//std::cout << "pos_x:" << this->position.x << "pos_y:" << this->position.y << "move_x:" << this->move.x << "move_y:" << this->move.y << std::endl;
	//位置に応じて当たり判定の設定を変更する処理
	//仕様が変わったため不要となりました。
	/*if (this->isCollisionNow == 0)
	{
		if (this->position.y > 1200.f)
		{
			this->isCollisionNow++;
		}
	}*/
	//オート機能を切っていない状態でオート動作をするならば
	if (this->isAuto && !this->isAutoOff)
	{
		//キャラに登録されているオート移動を行う
		//ここで実際は外部ファイルより情報を得てオート操作をさせたい
		this->AutoMove();
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
	//アニメーション用
	int idle[10] = { 0,0,0,0,0,0,0,1,1,1 };

	if (this->AnimCnt < 30) {
		this->AnimCnt++;
	}
	if (this->AnimCnt >= 30) {
		this->AnimCnt = 0;
	}

	Box2D src(idle[this->AnimCnt / 3] * 550, 0, 550, 550);
	src.OffsetSize();
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
		int k = src.w;
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
				if (map->MapHitCheck(*this))
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

				if (map->MapHitCheck(*this))
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
		if (map->MapHitCheck(foot))
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
void Chara::AutoMove()
{
	//オートモードがtrueなら設定してある移動を行う
	if(this->isAutoMode)
	{
		this->move.x = this->easing_x.quad.InOut(this->easing_x.Time(15), this->startPos.x, this->EndPos.x, 15) - this->position.x;
		this->isAutoMode = this->easing_x.isplay();
		this->isAutoOff = !this->easing_x.isplay();
	}
	else
	{
		//そうでなければ元々用意されている移動を行う
		if (this->position.x > 1100 || this->position.x < 200)
		{
			if (this->direction == Direction::LEFT)
			{
				this->direction = Direction::RIGHT;
			}
			else
			{
				this->direction = Direction::LEFT;
			}
		}
		if (this->direction == Direction::LEFT)
		{
			this->move.x = -5.0f;
		}
		else
		{
			this->move.x = 5.0f;
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
void Chara::Set(const Vec2& start_, const Vec2& end_)
{
	//開始位置を登録
	this->startPos = start_;
	//終了位置を登録
	this->EndPos = end_;
	//終了位置からの移動値に上書き
	this->EndPos -= this->startPos;
	this->easing_x.ResetTime();
	this->SetAutoMode(true);
	this->SetAutoFlag(false);
}
bool Chara::isAutoPlay() const
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
