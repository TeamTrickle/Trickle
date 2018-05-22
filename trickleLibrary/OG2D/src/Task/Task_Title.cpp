#include "Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\StageSelect.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Back\Back.h"
Title::Title()
{
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
	this->tex_a = 0.0f;
	this->cursor_a = 0.0f;
	this->cursorNum = 0;
}

Title::~Title()
{
	this->Finalize();
}

bool Title::Initialize()
{
	std::cout << "Title初期化" << std::endl;
	sound.create(std::string("playandhope.wav"), true);
	auto back = Back::Create((std::string)"outlook.png", 1920 * 2, 1080 * 2);

	this->Logo.CreateObject(Cube, Vec2(400,250), Vec2(640, 384), 0.0f);
	this->Logo.Radius = { 1.0f,0.5f };
	startPos = Vec2(720.f - 128.f,624.f + 30.f);
	pausePos = Vec2(720.f - 128.f,624.f + 129.f + 30.f);
	closePos = Vec2(720.f - 128.f,624.f + 258.f + 30.f);
	this->cursorPos[0] = { this->startPos.x - 30.f - 64.f,this->startPos.y };
	this->cursorPos[1] = { this->pausePos.x - 30.f - 64.f,this->pausePos.y };
	this->cursorPos[2] = { this->closePos.x - 30.f - 64.f,this->closePos.y };

	texCursor.Create((std::string)"gear.png");
	texStart.Create((std::string)"start.png");
	texClose.Create((std::string)"close.png");
	texPause.Create((std::string)"pause.png");
	this->texLogo.Create((std::string)"logo.png");

	//カメラ位置の移動
	OGge->camera->SetPos(Vec2(OGge->window->GetSize().x / 2, 0.f));
	//水読み込みと生成
	auto water = Water::Create(Vec2(500.f, 0.f));
	waterTex.Create((std::string)"waterTex.png");
	water->SetTexture(&this->waterTex);
	water->SetMaxSize(Vec2(128, 128));

	//マップ生成(地面用)
	auto map = Map::Create((std::string)"title.csv");
	
	this->nextTaskCheck = 0;
	__super::Init((std::string)"title");
	__super::SetDrawOrder(0.5f);

	//-----------------------
	//テスト
	//-----------------------
	this->testObj.CreateObject(Cube, Vec2(400.f, 0.f), Vec2(64, 64), 0.0f);
	this->cm.SetObject(&(*water));
	OGge->camera->SetSize(Vec2(960 / 2, 540 / 2));
	OGge->camera->SetPos(Vec2(500 - (480 / 2), 0));
	this->cm.SetSize(Box2D(Vec2(0, 0), OGge->window->GetSize() * 2));
	this->cm.SetRange(Box2D(100.f, 100.f, OGge->window->GetSize().x - 200.f, OGge->window->GetSize().y - 600.f));
	this->mode = Mode::from1;
	return true;
}

void Title::UpDate()
{
	//----------------
	//テスト
	//----------------
	if (OGge->in->key.on(In::A))
	{
		this->testObj.position.x -= 10.0f;
	}
	if (OGge->in->key.on(In::D))
	{
		this->testObj.position.x += 10.0f;
	}
	if (OGge->in->key.on(In::W))
	{
		this->testObj.position.y -= 10.0f;
	}
	if (OGge->in->key.on(In::S))
	{
		this->testObj.position.y += 10.0f;
	}
	if (OGge->in->key.on(In::Q))
	{
		OGge->camera->MoveSize(Vec2(-32, -18));
		OGge->camera->MovePos(Vec2(16.f, 9.f));
	}
	if (OGge->in->key.on(In::E))
	{
		OGge->camera->MoveSize(Vec2(32, 18));
		OGge->camera->MovePos(Vec2(-16.f, -9.f));
	}
	this->cm.move();
	switch (this->mode)
	{
	case from1:	//水出現から水消滅まで
	{
		//水情報取得
		auto water = OGge->GetTask<Water>("water");
		if (water)
		{
			if (this->Logo.hit(*water) && water->GetSituation() == Water::Situation::Normal)
			{
				//水を削除モードへ移行
				water->SetSituation(Water::Situation::Deleteform);
				this->cm.DeleteObject();
				//this->mode = from2;
			}
			if (water->GetSituation() == Water::Situation::CreaDelete)
			{
				this->mode = from2;
			}
		}
	}
		break;
	case from2:	//花咲き開始から終了まで
	{
		//テスト用10フレーム後移動
		if (this->timeCnt > 10)
		{
			this->mode = from3;
			//歯車を回す処理
			//カメラの移動値を登録
			this->cameraPos.Set(OGge->camera->GetPos(), Vec2(0, 200));
			this->cameraSize.Set(OGge->camera->GetSize(), Vec2(1440, 810));
		}
	}
		break;
	case from3:	//カメラサイズ移動開始から終了まで
	{
		//移動を行う
		OGge->camera->SetPos(this->cameraPos.Move());
		OGge->camera->SetSize(this->cameraSize.Move());
		//両方の移動が完了した場合
		if (!this->cameraPos.isPlay() && !this->cameraSize.isPlay())
		{
			//次へ
			this->mode = from4;
		}
	}
		break;
	case from4:	//文字出現
	{
		this->tex_a += 0.01f;
		if (this->tex_a >= 1.0f)
		{
			this->mode = from5;
			//auto Npc = Chara::Create((std::string)"player2.png", Vec2(1600, 300));
		}
	}
		break;
	case from5:	//矢印とプレイヤー出現
	{
		this->cursor_a += 0.01f;

		if (this->cursor_a >= 1.0f)
		{
			this->mode = from6;
		}
	}
		break;
	case from6:	//決定待ち状態
	{
		CursorMove();
		if (OGge->in->down(Input::in::B2))
		{
			this->mode = from7;
		}
	}
		break;
	case from7:	//ジャンプからselectまでの移動
	{
		this->mode = End;
	}
		break;
	case End:	//Selectの読み込みと自身の破棄
	{
		this->Kill();
	}
		break;
	default:
		break;
	}
	this->ModeCheck();
}

void Title::Render2D()
{
	//背景表示
	{
		Box2D draw(Vec2(0, 0), Vec2(1920 * 2, 1080 * 2));
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 720);
		src.OffsetSize();
		this->texLogo.Draw(draw, src, Color(0, 0, 0, 0));
	}
	//ロゴ表示
	{
		Box2D draw(this->Logo.position, this->Logo.Scale);
		draw.OffsetSize();
		Box2D src(0, 0, 1280, 768);
		this->texLogo.Draw(draw, src);
	}
	//カーソルの表示
	{
		//表示位置、大きさは仮ゲームスタート
		Box2D draw(cursorPos[this->cursorNum].x, cursorPos[this->cursorNum].y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 195, 195);
		src.OffsetSize();
		texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
		Box2D draw2(cursorPos[this->cursorNum].x + 64.0f + (30.f * 2.f) + 256.f, cursorPos[this->cursorNum].y, 64.f, 64.f);
		draw2.OffsetSize();
		texCursor.Draw(draw2, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
	}
	//ゲームスタート
	{
		Box2D draw(this->startPos.x, this->startPos.y, 256.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texStart.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//終了
	{
		Box2D draw(closePos.x, closePos.y, 256.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texClose.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//設定
	{
		Box2D draw(pausePos.x, pausePos.y, 256.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 64);
		src.OffsetSize();
		texPause.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//テスト
	{
		Box2D draw(this->testObj.position, this->testObj.Scale);
		draw.OffsetSize();
		Box2D src(0, 0, 256, 256);
		this->waterTex.Draw(draw, src);
	}
}

bool Title::Finalize()
{
	std::cout << "Title解放" << std::endl;

	//使用画像の解放
	texCursor.Finalize();
	texStart.Finalize();
	texClose.Finalize();
	texPause.Finalize();
	this->texLogo.Finalize();

	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->Kill();
	}
	this->waterTex.Finalize();

	auto water = OGge->GetTasks<Water>("water");
	for (auto id = (*water).begin(); id != (*water).end(); ++id)
	{
		(*id)->Kill();
	}
	auto map = OGge->GetTask<Map>("map");
	if(map)
	{
		(*map).Kill();
	}

	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		switch (this->cursorNum)
		{
		case 0:
		{
			/*auto stage = */StageSelect::Create();
		}
		break;
		case 1:
		
			{
				/*auto option = */Option::Create();
			}
			break;
		case 2:
		
			OGge->GameEnd();
			break;
		default:
			break;
		}
	}
	
	return true;
}

void Title::CursorMove()
{
	if (OGge->in->down(In::CU))
	{
		this->cursorNum--;
	}
	if (OGge->in->down(In::CD))
	{
		this->cursorNum++;
	}
	if (this->cursorNum > 2)
	{
		this->cursorNum = 0;
	}
	if (this->cursorNum < 0)
	{
		this->cursorNum = 2;
	}
}

void Title::ModeCheck()
{
	if (this->preMode != this->mode)
	{
		this->timeCnt = 0;
		this->preMode = this->mode;
	}
	else
	{
		this->timeCnt++;
	}
}

Title::Animation::Animation()
{

}

void Title::Animation::Set(Vec2& start_, Vec2& end_)
{
	this->StartPos = start_;
	this->EndPos = end_ - start_;
}

Vec2 Title::Animation::Move()
{
	//OGge->camera->SetPos(Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10)));
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

bool Title::Animation::isPlay() const
{
	if (this->easing_x.isplay() || this->easing_y.isplay())
	{
		return true;
	}
	return false;
}

Title::SP Title::Create(bool flag_)
{
	auto to = Title::SP(new Title());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize())
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Chara::Chara(std::string& path, Vec2& pos)
{
	this->position = pos;
	this->Image.Create(path);
	this->CreateObject(Cube, pos, Vec2(64, 64), 0.0f);
	this->taskName = "Chara";
	__super::Init(this->taskName);
	__super::SetDrawOrder(1.0f);
	this->objectTag = this->taskName;
	this->direction = Direction::LEFT;
	this->AnimCnt = 0;
	this->isAuto = true;
	this->isCollision = true;
	this->MoveCnt = 0;
}
Chara::~Chara()
{
	this->Image.Finalize();
}
void Chara::UpDate()
{
	if (this->isAuto)
	{
		this->AutoMove();
	}
	else
	{
		this->MoveCnt++;
	}
	if (this->MoveCnt > 10)
	{
		this->isAuto = true;
	}
	this->Friction();
	this->MoveCheck(this->move);
}
void Chara::Render2D()
{
	Box2D draw(this->position.x, this->position.y, this->Scale.x, this->Scale.y);
	draw.OffsetSize();

	int idle[10] = { 0,0,0,0,0,0,0,1,1,1 };

	if (this->AnimCnt < 30) {
		this->AnimCnt++;
	}
	if (this->AnimCnt >= 30) {
		this->AnimCnt = 0;
	}

	Box2D src(idle[this->AnimCnt / 3] * 550, 0, 550, 550);
	src.OffsetSize();
	//左向きなら画像を逆にする
	if (direction == Direction::RIGHT) {
		int k = src.w;
		src.w = src.x;
		src.x = k;
	}
	this->Image.Draw(draw, src);
}
void Chara::Friction()
{
	if (this->move.x > 0)
	{
		this->move.x = std::min(this->move.x + this->FIN_SPEED, 0.f);
	}
	else
	{
		this->move.x = std::max(this->move.x - this->FIN_SPEED, 0.f);
	}
	if (!this->FootCheck() || this->move.y < 0)
	{
		this->move.y = std::min(this->move.y + this->GRAVITY, this->MAX_FALL);
	}
	else
	{
		this->move.y = 0.0f;
	}
}
void Chara::MoveCheck(Vec2& est)
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
		if (map && this->isCollision)
		{
			if (map->MapHitCheck(*this))
			{
				this->position.x = preX;
				break;
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
bool Chara::FootCheck()
{
	GameObject foot;
	foot.CreateObject(Objform::Cube, Vec2(this->position.x, this->position.y + this->Scale.y), Vec2(this->Scale.x, 1.0f), 0.0f);
	auto map = OGge->GetTask<Map>("map");
	if (map && this->isCollision)
	{
		if (map->MapHitCheck(*this))
		{
			return true;
		}
	}
	return false;
}
bool Chara::Jump()
{
	return false;
}
void Chara::AutoMove()
{

}
void Chara::ManualMove(Vec2& est)
{
	this->isAuto = false;
	this->MoveCnt = 0;
	this->move += est;
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
