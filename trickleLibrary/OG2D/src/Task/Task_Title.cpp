#include "Task_Title.h"
#include "Task\Task_Option.h"
#include "Task\StageSelect.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Back\Back.h"
#include "Chara\Chara.h"
#include "Load\LoadLogo.h"
#include "Effect\Effect.h"
Title::Title()
{
	this->mode = Non;
	this->preMode = Non;
	this->timeCnt = 0;
	this->tex_a = 0.0f;
	this->cursor_a = 0.0f;
	this->cursorNum = 0;
	this->isGierAng = false;
	this->flowerVolume = 0.f;
	this->isSkip = false;
	this->soundname = "title.wav";     //サウンドのファイル名	
	this->sound = nullptr;
	//タグ設定
	__super::Init((std::string)"title");
}

Title::~Title()
{
	//ロードの生成を行い強制描画を行う
	if (!OGge->GetDeleteEngine())
	{
		auto load = Load::Create();
		load->Draw();
	}
	this->Finalize();
}

bool Title::Initialize()
{
	std::cout << "Title初期化" << std::endl;
	//背景読み込み
	auto back = Back::Create((std::string)"back.png", 1440, 810);
	//ロゴオブジェクト生成
	this->Logo.CreateObject(Cube, Vec2(400, 250), Vec2(640, 384), 0.0f);
	this->Logo.Radius = { 1.0f,0.5f };
	//文字位置設定
	startPos = Vec2(720.f - 155.f/*128.f*/, 624.f + 129.f + 30.f);
	closePos = Vec2(720.f - 128.f, 624.f + 258.f + 30.f);
	this->textPos[0] = { this->startPos,Vec2(256,64) };
	this->textPos[1] = { this->closePos,Vec2(256,64) };
	//配列管理を行う
	this->cursorPos[0] = { this->startPos.x - 30.f - 64.f,this->startPos.y };
	this->cursorPos[1] = { this->closePos.x - 30.f - 64.f,this->closePos.y };
	//画像読み込み
	texCursor.Create("gear3.png");
	this->texLogo.Create("logo.png");
	this->GierLogo.Create("gearofi.png");
	this->flowerLogo.Create("flower.png");
	this->texEffect.Create("Effect02.png");
	
	
	this->effect03.Create("starteffect.png");
	
	//サウンドの生成
	sound = new Sound();
	sound->create(soundname, true);
	rm->SetSoundData((std::string)"titleBGM", sound);
	//カメラ位置の移動
	OGge->camera->SetPos(Vec2(OGge->window->GetSize().x / 2, 0.f));
	//水読み込みと生成
	auto water = Water::Create(Vec2(500.f, 0.f));
	waterTex.Create((std::string)"waterTex.png");
	water->SetTexture(&this->waterTex);
	water->SetMaxSize(Vec2(128, 128));

	//マップ生成(地面用)
	auto map = Map::Create((std::string)"title.csv");
	//矢印の位置で使用する
	this->nextTaskCheck = 0;
	auto chara = Chara::Create((std::string)"player.png", Vec2(1600, 628));
	chara->SetPause(true);

	//描画順の決定
	__super::SetDrawOrder(0.5f);
	//カメラの中心のターゲットを登録
	this->cm.SetObject(&(*water));
	//カメラのサイズと位置を調整
	OGge->camera->SetSize(Vec2(960 / 2, 540 / 2));
	OGge->camera->SetPos(Vec2(500 - (480 / 2), 0));
	//カメラの画面外設定
	this->cm.SetSize(Box2D(Vec2(0, 0), OGge->window->GetSize() * 2));
	//開始時のモード設定
	this->mode = Mode::from1;
	return true;
}

void Title::UpDate()
{
	if (OGge->in->key.down(In::SPACE))
	{
		this->Kill();
	}
	if (OGge->in->key.down(In::ENTER) || OGge->in->down(In::B2))
	{
		this->Skip();
	}
	//カメラの自動移動
	this->cm.move();
	//ギアを回す場合
	if (this->isGierAng)
	{
		//値を増やす
		this->gierCnt++;
		//360度を超えたら0度に戻す
		if (this->gierCnt > 360)
		{
			this->gierCnt = 0;
		}
	}
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
				this->timeCnt = 0;
			}
		}
		else
		{
			if (this->timeCnt < 81)
			{
				OGge->camera->MovePos(Vec2(0, 10));
			}
			else
			{
				this->isGierAng = true;
				this->mode = from2;
				auto effect = Effect::Create(Vec2(this->Logo.position.x, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)) - 96.f), Vec2(128, 128), Vec2(64, 64), 1, 100, 100, "titleEffect");
				effect->SetTexture(&this->texEffect);
				effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 500), 15);
				effect->SetMode(Effect::Mode::Flash);
				for (int i = 0; i < 10; ++i)
				{
					float rand = random::GetRand(this->Logo.position.x, this->Logo.position.x + 182.f);
					auto effect_r = Effect::Create(Vec2(rand, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)) - 96.f), Vec2(128, 128), Vec2(64, 64), 1, 100, 100, "titleEffect");
					effect_r->SetTexture(&this->texEffect);
					effect_r->Set(effect_r->position, Vec2(effect_r->position.x, effect_r->position.y - 500), 15);
					effect_r->SetMode(Effect::Mode::Flash);
					float rand_a = random::GetRand(0.0f, 1.0f);
					effect_r->Color_a(rand_a);
				}
			}
		}
	}
	break;
	case from2:	//花咲き開始から終了まで
	{
		//テスト用10フレーム後移動
		if (this->flowerVolume >= 1.0f)
		{
			//花が咲いた時点でサウンドの再生を始める
			sound->play();
			this->mode = from3;
			//歯車を回す処理

			//カメラの移動値を登録
			this->cameraPos.Set(OGge->camera->GetPos(), Vec2(0, 200));
			this->cameraSize.Set(OGge->camera->GetSize(), Vec2(1440, 810));
		}
		else
		{
			if (this->flowerVolume < 1.f)
			{
				this->flowerVolume += 0.01f;
			}
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
			auto Npc = OGge->GetTask<Chara>("Chara");
			Npc->SetReplayEnable();
			Npc->SetPause(false);
		}
	}
	break;
	case from5:	//矢印とプレイヤー出現
	{
		auto Npc = OGge->GetTask<Chara>("Chara");
		if (Npc)
		{
			Npc->ManualMove(Vec2(-8.f, 0.0f));
		}
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
			switch (this->cursorNum)
			{
			case 0:
			{
				auto chara = OGge->GetTask<Chara>("Chara");
				if (chara->position.x > 740)
				{
					chara->ManualMove(Vec2(-10.f, 0.0f));
				}
				else
				{
					chara->ManualMove(Vec2(10.f, 0.0f));
				}
				chara->Jump();
				//this->cm.SetObject(&(*chara));
				this->mode = from7;
			}
			break;
			case 1:
				OGge->GameEnd();
				break;
			case 2:
				break;
			}
			auto effect03 = Effect::Create(
				Vec2(this->textPos[this->cursorNum].x + (this->textPos[this->cursorNum].w / 2), this->textPos[this->cursorNum].y + (this->textPos[this->cursorNum].h / 2)),
				Vec2(0, 0),
				Vec2(320, 64),
				1,
				100);
			effect03->SetMode(Effect::Mode::Expansion);
			effect03->SetTexture(&this->effect03);
			effect03->SetMaxSize(Vec2(640, 128));
		}
	}
	break;
	case from7:	//ジャンプからselectまでの移動
	{
		//降りたらロードを挟みセレクトへ移行する行動
		auto chara = OGge->GetTask<Chara>("Chara");
		if (chara->position.y > OGge->camera->GetPos().x + OGge->camera->GetSize().x)
		{
			this->mode = Mode::End;
		}
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
	{
		Box2D draw(634, 380, 52, 52);
		draw.OffsetSize();
		Box2D src(0, 0, 128, 128);
		this->GierLogo.Rotate((float)this->gierCnt);
		this->GierLogo.Draw(draw, src);
	}
	{
		Box2D draw(this->Logo.position.x, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)), this->Logo.Scale.x, (this->Logo.Scale.y * (this->flowerVolume / 1.f)));
		draw.OffsetSize();
		Box2D src(0.f, 768 - (768 * (this->flowerVolume / 1.f)), 1280.f, 768.f);
		this->flowerLogo.Draw(draw, src);
	}
	//カーソルの表示
	{
		//表示位置、大きさは仮ゲームスタート
		Box2D draw(cursorPos[this->cursorNum].x, cursorPos[this->cursorNum].y, 64.0f, 64.0f);
		draw.OffsetSize();
		Box2D src(0, 0, 195, 195);
		src.OffsetSize();
		this->texCursor.Rotate((float)this->gierCnt);
		texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
		Box2D draw2(cursorPos[this->cursorNum].x + 64.0f + (30.f * 2.f) + 320.f/*256.f*/, cursorPos[this->cursorNum].y, 64.f, 64.f);
		draw2.OffsetSize();
		texCursor.Draw(draw2, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
	}
	//終了
	{
		Box2D draw(closePos.x, closePos.y, 64.f*4, 64.f/* 256.f, 64.f*/);
		draw.OffsetSize();
		Box2D src(0, 64, 64*4, 64);
		src.OffsetSize();
		rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
	//スタート
	{
		//Box2D draw(startPos.x, startPos.y, 256.f, 128.f);
		Box2D draw(startPos.x, startPos.y, 320.f, 64.f);
		draw.OffsetSize();
		Box2D src(0, 0, 64*5, 64);
		src.OffsetSize();
		//texStart.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
		rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	}
}

bool Title::Finalize()
{
	std::cout << "Title解放" << std::endl;

	//使用画像の解放
	texCursor.Finalize();
	//texStart.Finalize();
	//texClose.Finalize();
	//texPause.Finalize();
	this->texLogo.Finalize();
	this->GierLogo.Finalize();
	this->flowerLogo.Finalize();
	this->texEffect.Finalize();
	this->effect03.Finalize();

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
	if (map)
	{
		(*map).Kill();
	}
	auto Npc = OGge->GetTask<Chara>("Chara");
	if (Npc)
	{
		Npc->Kill();
	}
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}

	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		switch (this->cursorNum)
		{
		case 0:
		{
			auto stage = StageSelect::Create();
		}
		break;
		case 1:
			OGge->GameEnd();
			break;
		default:
			break;
		}
	}
	else
	{
		//次を生成しない場合Soundデータを解放する
		if (this->sound)
		{
			delete this->sound;
			this->sound = nullptr;
		}
	}

	return true;
}

void Title::CursorMove()
{
	if (OGge->in->down(In::CU) || OGge->in->down(In::LU))
	{
		this->cursorNum--;
	}
	if (OGge->in->down(In::CD) || OGge->in->down(In::LD))
	{
		this->cursorNum++;
	}
	if (this->cursorNum > 1)
	{
		this->cursorNum = 0;
	}
	if (this->cursorNum < 0)
	{
		this->cursorNum = 1;
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
	return Vec2(this->easing_x.sine.In(this->easing_x.Time(10), this->StartPos.x, this->EndPos.x, 10), this->easing_y.sine.In(this->easing_y.Time(10), this->StartPos.y, this->EndPos.y, 10));
}

bool Title::Animation::isPlay() const
{
	return this->easing_x.isplay() || this->easing_y.isplay();
}

void Title::Skip()
{
	if (this->mode < Mode::from6)
	{
		this->SkipMove();
	}
}

void Title::BackTitleSkip()
{
	this->mode = Mode::from5;
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		(*id)->Kill();
	}
	this->cm.DeleteObject();
	OGge->camera->SetPos(Vec2(0, 200));
	OGge->camera->SetSize(Vec2(1440, 810));
	this->flowerVolume = 1.0f;
	this->tex_a = 1.0f;
	auto npc2 = Chara::Create((std::string)"player.png", Vec2(1600, 628));
	npc2->SetReplayEnable();
	this->sound->play();
}

void Title::SkipMove()
{
	this->mode = Mode::from6;
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		(*id)->Kill();
	}
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	this->cm.DeleteObject();
	OGge->camera->SetPos(Vec2(0, 200));
	OGge->camera->SetSize(Vec2(1440, 810));
	this->flowerVolume = 1.0f;
	this->tex_a = 1.0f;
	this->cursor_a = 1.0f;
	auto npc = OGge->GetTask<Chara>("Chara");
	if (npc)
	{
		npc->Kill();
	}
	auto npc2 = Chara::Create((std::string)"player.png", Vec2(790, 639));
	npc2->SetReplayEnable();
	this->sound->play();
	this->isSkip = false;
	OGge->in->ResetInputData();
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
