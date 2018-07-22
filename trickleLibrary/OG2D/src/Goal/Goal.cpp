#include "Goal.h"
#include "Water\water.h"
#include "Player\Player.h"
#include "Map\Map.h"
#include "Task/Task_Game.h"

Goal::Goal(const Vec2& pos)
{
	this->CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	this->objectTag = "Goal";
	__super::Init(this->objectTag);
	__super::SetDrawOrder(0.8f);
	this->isClear = false;
	this->isCheck = false;
	this->cameraLock = true;
	this->animCnt = 0;
	this->image = nullptr;
	this->lightTex.Create((std::string)"goallight.png");      //光のエフェクト生成
	this->lightCreate = false;                                //光のエフェクトを生成するかどうか
	this->lightscale = Vec2(0.f, 0.f);
	this->color = Paint::PaintColor::Normal;
	this->termsColor = Paint::PaintColor::Normal;
	this->mode = Mode::Non;
	this->precmPos = nullptr;
	this->precmSize = nullptr;
	auto goals = OGge->GetTasks<Goal>("Goal");
	auto id = goals->begin();
	unsigned int count = 0;
	while (id != goals->end())
	{
		count++;
		id++;
	}
	this->ID = count;
	this->soundname = "flower.wav";         //サウンドのファイル名格納
	sound.create(soundname, false);
	this->testClear = false;
}

Goal::~Goal()
{
	this->image = nullptr;
	this->lightTex.Finalize();
	if (this->precmPos)
	{
		delete this->precmPos;
		this->precmPos = nullptr;
	}
	if (this->precmSize)
	{
		delete this->precmSize;
		this->precmSize = nullptr;
	}
}

void Goal::SetColor(const Paint::PaintColor & color)
{
	this->termsColor = color;
}

Paint::PaintColor Goal::GetColor() const
{
	return this->termsColor;
}

bool Goal::ColorCheck() const
{
	return this->termsColor == this->color ? true : false;
}

void Goal::UpDate()
{
	switch (this->mode)
	{
	case Mode::Non:
		if (this->WaterHit() || this->testClear)
		{
			//カメラ移動終了地点を設定
			this->cm_Pos.Set(OGge->camera->GetPos(), Vec2(this->position.x - (320.f / 2.f), this->position.y - (180.f / 2.f)), 5);
			this->cm_Size.Set(OGge->camera->GetSize(), /*this->Scale + */Vec2(320, 180), 5);
			//移動前のカメラの位置とサイズを保存しておく
			this->precmPos = new Vec2(OGge->camera->GetPos());
			this->precmSize = new Vec2(OGge->camera->GetSize());
			this->cameraLock = false;
			this->mode = Form1;
			auto player = OGge->GetTasks<Player>("Player");
			for (auto id = player->begin(); id != player->end(); ++id)
			{
				(*id)->SetInput(true);
			}
			OGge->SetPause(false);
		}
		break;
	case Mode::Form1:
		OGge->camera->SetPos(this->cm_Pos.Move());
		OGge->camera->SetSize(this->cm_Size.Move());
		if (!this->cm_Pos.isPlay() && !this->cm_Size.isPlay())
		{
			this->isCheck = true;
			//サウンドの再生
			sound.play();
			this->lightCreate = true;

			this->mode = Mode::Form2;
			if (this->isGoalCheck())
			{
				auto player = OGge->GetTasks<Player>("Player");
				for (auto id = player->begin(); id != player->end(); ++id)
				{
					(*id)->SetInputAuto(true);
				}
			}
		}
		break;
	case Mode::Form2:
		++this->animCnt;
		if (this->animCnt >= 99)
		{
			//元のカメラ位置に戻す
			//ここでプレイヤーの座標からカメラの位置を計算して求めてSetにいれれば問題解決できる気がする。
			this->cm_Pos.Set(OGge->camera->GetPos(), *this->precmPos, 6);
			this->cm_Size.Set(OGge->camera->GetSize(), *this->precmSize, 6);
			delete this->precmPos;
			delete this->precmSize;
			this->precmPos = nullptr;
			this->precmSize = nullptr;
			if (this->isGoalCheck())
			{
				auto player = OGge->GetTasks<Player>("Player");
				for (auto id = player->begin(); id != player->end(); ++id)
				{
					(*id)->SetState(Player::State::CLEAR);
				}
			}
			this->mode = Mode::Form3;
		}
		break;
	case Mode::Form3:
		OGge->camera->SetPos(this->cm_Pos.Move());
		OGge->camera->SetSize(this->cm_Size.Move());
		if (!this->cm_Pos.isPlay() && !this->cm_Size.isPlay())
		{
			this->cameraLock = true;

			auto game = OGge->GetTask<Game>("game");
			if (game != nullptr)
			{
				game->canvolControl = false;
			}

			auto player = OGge->GetTasks<Player>("Player");
			for (auto id = player->begin(); id != player->end(); ++id)
			{
				(*id)->SetInput(false);
			}
			this->mode = Mode::End;
		}
		break;
	case Mode::End:
		this->isClear = true;
		break;
	}

	if (lightCreate)
	{
		//縦移動完成版  使用していない
		/*if (lightscale.x < 1.0f)
		{
		this->lightscale.x += 0.05f;
		}
		if (lightscale.y < 1.0f)
		{
		this->lightscale.y += 0.05f;
		}*/
		//横移動版
		if (this->lightscale.x < 150)
		{
			this->lightscale.x += 5;
		}
	}
}

void Goal::Render2D()
{
	if (this->image)
	{
		this->draw = { this->position, this->Scale };
		if (this->isCheck)
		{
			this->draw += Box2D(-32, -60, 64, 64);
		}
		this->draw.OffsetSize();
		if (this->isCheck)
		{
			this->src = { 256 * (int)(animCnt / 10), 256, 256, 284 };
			switch (this->color)
			{
			case Paint::PaintColor::Red:
				this->src.y += 540;
				break;
			case Paint::PaintColor::Blue:
				this->src.y += 1080;
				break;
			case Paint::PaintColor::Purple:
				this->src.y += 1620;
				break;
			default:
				break;
			}
		}
		else
		{
			this->src = { 0,0,256,256 };
			switch (this->termsColor)
			{
			case Paint::PaintColor::Red:
				this->src.y += 540;
				break;
			case Paint::PaintColor::Blue:
				this->src.y += 1080;
				break;
			case Paint::PaintColor::Purple:
				this->src.y += 1620;
				break;
			default:
				break;
			}
		}

		this->src.OffsetSize();
		this->image->Draw(this->draw, this->src);

		//光の描画
		if (this->lightCreate)
		{
			//縦移動完成版 使用していない
			//Box2D draw(Vec2(this->position.x - (this->Scale.x - 30.0f), this->position.y - (this->Scale.y + 245.0f)), Vec2(100.0f, this->lightscale.y * 400));         //srcを拡大させて出現
			//横移動版
			Box2D draw(Vec2((this->position.x + 15) - (this->lightscale.x / 2.0f), this->position.y - (this->Scale.y + 245.0f)), Vec2(10.0f + this->lightscale.x, 400.0f));
			draw.OffsetSize();
			//縦移動完成版 使用していない
			//Box2D src(0.0f, 0.0f, 512.0f, 1024 * this->lightscale.x);
			//横移動版
			Box2D src(0.0f, 0.0f, 512.0f, 1024.0f);
			src.OffsetSize();
			lightTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, 0.6f));
		}
	}
}

bool Goal::GetClear() const
{
	return this->isClear;
}

void Goal::SetTexture(Texture* tex)
{
	this->image = tex;
}

bool Goal::WaterHit()
{
	this->foot.CreateObject(Cube, Vec2(this->position.x, this->position.y + this->Scale.y - 1.0f), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		if ((*id)->GetState() == Water::State::LIQUID)
		{
			if (this->foot.IsObjectDistanceCheck((*id)->position, (*id)->Scale))
			{
				if (this->foot.CubeHit(*(*id)))
				{
					this->color = (*id)->GetColor();
					(*id)->Kill();
					return true;
				}
			}
		}
	}
	return false;
}
bool Goal::GetLock() const
{
	return this->cameraLock;
}

void Goal::CameraAnim::Set(const Vec2& start, const Vec2& end, const unsigned int time)
{
	this->startPos = start;
	this->endPos = end;
	this->endPos = this->endPos - this->startPos;
	this->time = time;
	this->easing_x.ResetTime();
	this->easing_y.ResetTime();
}
Vec2 Goal::CameraAnim::Move()
{
	return Vec2(
		this->easing_x.sine.InOut(this->easing_x.Time((float)this->time), this->startPos.x, this->endPos.x, (float)this->time),
		this->easing_y.sine.InOut(this->easing_y.Time((float)this->time), this->startPos.y, this->endPos.y, (float)this->time));
}
bool Goal::CameraAnim::isPlay()
{
	return this->easing_x.isplay() || this->easing_y.isplay();
}

unsigned int Goal::GetID() const
{
	return this->ID;
}

bool Goal::isGoalCheck()
{
	auto goals = OGge->GetTasks<Goal>("Goal");
	for (auto id = goals->begin(); id != goals->end(); ++id)
	{
		if ((*id)->ID != this->ID)
		{
			if (!(*id)->GetClear())
			{
				return false;
			}
		}
	}
	return true;
}

void Goal::TestGoal()
{
	this->testClear = true;
}

Goal::SP Goal::Create(const Vec2& pos, bool flag)
{
	Goal::SP to = Goal::SP(new Goal(pos));
	if (to)
	{
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		return to;
	}
	return nullptr;
}