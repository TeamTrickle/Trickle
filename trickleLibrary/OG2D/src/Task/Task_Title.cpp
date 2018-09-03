#include "Task_Title.h"
#include "Task\Task_Demo.h"
#include "Task\Task_Option.h"
#include "Task\StageSelect.h"
#include "Water\water.h"
#include "Map\Map.h"
#include "Back\Back.h"
#include "Chara\Chara.h"
#include "Load\LoadLogo.h"
#include "Effect\Effect.h"
#include "GameProcessManagement\GameProcessManagement.h"



const std::string Title::DEMO_VIDEOS[]{
	"./data/test.mp4",
	"./data/test1.mp4"
};



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
	this->soundcursorname = "cursormove.wav";
	this->sounddecisionname = "decision.wav";
	this->soundflowername = "flower.wav";
	this->soundstart = true;
	this->sound = nullptr;
	this->skipInoutFlag = false;
	
	this->pressB = false;           //Bキーを押したかどうかの判断
	this->nowmoveL = false;
	this->nowmoveR = false;
	//タグ設定
	__super::Init((std::string)"title");
	__super::SetDrawOrder(0.98f);
}

Title::~Title()
{
	//ロードの生成を行い強制描画を行う
	if (!OGge->GetDeleteEngine())
	{
	}
	this->Finalize();
}

bool Title::Initialize()
{
	//背景読み込み
	auto back = Back::Create((std::string)"back.png", 1440, 810);
	//ロゴオブジェクト生成
	this->Logo.CreateObject(Cube, Vec2(400, 250), Vec2(640, 384), 0.0f);
	this->Logo.Radius = { 1.0f,0.5f };
	//文字位置設定
	startPos = Vec2(720.f - 155.f, 624.f + 129.f + 30.f);
	//closePos = Vec2(720.f - 128.f, 624.f + 129.f + 30.f);
	closePos=Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);

	start = non;          //startの文字の現在の状態
	del = no;             //データを消すかどうかの選択(最初はno)

	//現在の使用する文字のサイズ格納
	this->startsize = Vec2(320.f, 64.f);
	this->closesize = Vec2(0.f, 64.f);
	this->creditsize = Vec2(0.f, 64.f);
	this->dataDeletesize = Vec2(0.f, 64.f);
	//文字の最大横サイズを格納
	this->startmax = 64.f * 5;
	this->closemax = 64.f * 4;
	this->creditmax = 64.f * 6;
	this->datadeletemax = 64.f * 11;
	//文字の初期位置指定
	this->dataDeletepos = Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);
	this->creditpos = Vec2(1345.f-135.f, 624.f + 129.f + 30.f);
	this->monitorSpos = 165.f;
	this->monitorEpos = 1345.f;
	//文字α値
	this->press_a = 0;
	this->press_delta_a = 0.01f;

	//使わなくなってる
	//this->textPos[0] = { this->startPos,Vec2(256,64) };
	//this->textPos[1] = { this->closePos,Vec2(256,64) };
	////配列管理を行う
	//this->cursorPos[0] = { this->startPos.x - 30.f - 64.f,this->startPos.y ,320.f,64.f };
	//this->cursorPos[1] = { this->closePos.x - 30.f - 64.f,this->closePos.y ,64.f*4.f,64.f };

	//画像読み込み
	texCursor.Create("gear3.png");
	this->texLogo.Create("logo.png");
	this->GierLogo.Create("gearofi.png");
	this->flowerLogo.Create("flower.png");
	this->texEffect.Create("Effect01.png");
	this->monitorTex.Create("selectframe.png");     //モニターの画像追加
	this->fontTex.Create("Font_new.png");           //文字フォントの画像追加

	this->forTransform.Create("TransparentBackTitle.png");
	this->canVolControl = false;     //BGMのフェードインに使用
	
	this->effect03.Create("starteffect.png");
	
	//サウンドの生成
	//BGM
	sound = new Sound();
	sound->create(soundname, true);
	rm->SetSoundData((std::string)"titleBGM", sound);
	//カーソルの移動音
	cursorsound.create(soundcursorname,false);
	cursorsound.volume(1.0f);
	//決定音
	decisionsound.create(sounddecisionname, false);
	decisionsound.volume(1.0f);
	//花が咲く効果音
	flowersound.create(soundflowername, false);
	flowersound.volume(0.1f);

	
	//カメラ位置の移動
	OGge->camera->SetPos(Vec2(OGge->window->GetSize().x / 2, 0.f));
	//水読み込みと生成
	auto water = Water::Create(Vec2(500.f, -64.f));
	waterTex.Create((std::string)"waterTex.png");
	water->SetTexture(&this->waterTex);
	water->SetMaxSize(Vec2(128, 128));

	//マップ生成(地面用)
	auto map = Map::Create((std::string)"title.csv");
	//矢印の位置で使用する
	this->nextTaskCheck = 0;
	auto chara = Chara::Create((std::string)"player.png", Vec2(1600, 628));
	chara->SetPause(true);
	//ロゴの歯車回転
	this->gierCnt = 0;

	//描画順の決定
	//__super::SetDrawOrder(1.f);
	__super::SetDrawOrder(0.98f);
	//カメラの中心のターゲットを登録
	this->cm.SetObject(&(*water));
	//カメラのサイズと位置を調整
	OGge->camera->SetSize(Vec2(960 / 2, 540 / 2));
	OGge->camera->SetPos(Vec2(500 - (480 / 2), 0));
	//カメラの画面外設定
	this->cm.SetSize(Box2D(Vec2(0, 0), OGge->window->GetSize() * 2));
	//開始時のモード設定
	this->mode = Mode::from1;
	auto load = OGge->GetTask<Load>("load");
	if (load)
	{
		load->ALLTaskUpDateStop();
	}
	return true;
}

void Title::UpDate()
{
	if (OGge->in->down(In::B2) && !this->skipInoutFlag)
	{
		this->Skip();
	}

	//BGMのフェードイン
	if (canVolControl)
	{
		sound->volume(volControl.FadeIn(canVolControl));
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
	if (OGge->in->on(In::D1) && OGge->in->on(In::D2) && OGge->in->on(In::L1) && OGge->in->on(In::R1))
	{
		GameManager::ResetData();
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
				auto effect = Effect::Create(Vec2(this->Logo.position.x, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)) - 96.f), Vec2(128, 128), Vec2(64, 64), 1, 5, 100, "titleEffect");
				effect->SetTexture(&this->texEffect);
				effect->Set(effect->position, Vec2(effect->position.x, effect->position.y - 500), 15);
				effect->SetMode(Effect::Mode::Flash);
			}
		}
	}
	break;
	case from2:	//花咲き開始から終了まで
	{
		//10フレーム後移動
		if (this->flowerVolume >= 1.0f)
		{
			//花が咲いた時点でサウンドの再生を始める
			this->canVolControl = true;
			sound->play();
			soundstart = true;      //花の咲く効果音で使用

			this->mode = from3;
			//歯車を回す処理

			//カメラの移動値を登録
			this->cameraPos.Set(OGge->camera->GetPos(), Vec2(0, 200));
			this->cameraSize.Set(OGge->camera->GetSize(), Vec2(1440, 810));
		}
		else
		{
			for (int i = 0; i < 7; ++i)
			{
				float rand = random::GetRand(this->Logo.position.x, this->Logo.position.x + 182.f);
				auto effect_r = Effect::Create(Vec2(rand, (this->Logo.position.y + this->Logo.Scale.y) - (this->Logo.Scale.y * (this->flowerVolume / 1.f)) - 32.f), Vec2(32,32), Vec2(64, 64), 1, 15, 100, "titleEffect");
				effect_r->SetTexture(&this->texEffect);
				//effect_r->Set(effect_r->position, Vec2(effect_r->position.x, effect_r->position.y - 500), 15);
				effect_r->SetMode(Effect::Mode::Down);
				rand = random::GetRand(-10.f, 10.f);
				effect_r->SetMove(Vec2(rand, 0.f));
				effect_r->Color_a(0.6f);
			}
			if (this->flowerVolume < 1.f)
			{
				//花が咲く効果音の再生------------------------
				if (soundstart)
				{
					flowersound.play();
					soundstart = false;
				}
				//--------------------------------------------
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
	case from6:	//Bキー入力待ち状態
	{
		demoTimer.Start();
		if (PressB() == false)
		{
			this->press_a += this->press_delta_a;
			if (this->press_a < 0 || this->press_a >= 1.0f) {
				this->press_delta_a *= -1;
			}
			if (demoTimer.GetTime() >= DEMO_LIMIT) {
				this->mode = Mode::from10;
				break;
			}
			break;
		}
		else
		{
			this->mode = Mode::from7;
		}
	}
	break;

	case from7:	//決定待ち状態
	{
		if (!demoTimer.isplay()) {
			demoTimer.Start();
		}
		//左へ
		if (nowmoveR == false)
		{
			if (OGge->in->down(In::CL) || OGge->in->down(In::LL))
			{
				this->nowmoveL = true;
				//カーソルの移動音再生
				cursorsound.play();

				//文字を待機位置に移動させる処理(モニター右端へ)
				if (startsize.x <= 0.0f)
				{
					startPos = Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);
				}
				if (closesize.x <= 0.0f)
				{
					closePos = Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);
				}
				if (dataDeletesize.x <= 0.0f)
				{
					dataDeletepos = Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);
				}
				if (creditsize.x <= 0.0f)
				{
					creditpos = Vec2(1345.f - 135.f, 624.f + 129.f + 30.f);
				}
			}
		}
		//右へ
		if (nowmoveL == false)
		{
			if (OGge->in->down(In::CR) || OGge->in->down(In::LR))
			{
				this->nowmoveR = true;
				//カーソルの移動音再生
				cursorsound.play();

				//文字を待機位置に移動させる処理(モニター左端へ)
				if (startsize.x <= 0.0f)
				{
					startPos = Vec2(monitorSpos + 120, 624.f + 129.f + 30.f);
				}
				if (closesize.x <= 0.0f)
				{
					closePos = Vec2(monitorSpos + 120, 624.f + 129.f + 30.f);
				}
				if (dataDeletesize.x <= 0.0f)
				{
					dataDeletepos = Vec2(monitorSpos + 120, 624.f + 129.f + 30.f);
				}
				if (creditsize.x <= 0.0f)
				{
					creditpos = Vec2(monitorSpos + 120, 624.f + 129.f + 30.f);
				}
			}
		}

		//文字の移動処理--------------------------------------------------------------
		switch (cursorNum)
		{
		case 0:          //選択肢がstart
		{
			startPos = TextMoveout(startPos);
			startsize = TextSizeout(startPos, startsize,startmax);
			if (nowmoveL)
			{
				start = out;

				credit = in;
				creditpos = TextMovein(creditpos,creditsize,startsize,creditmax);
				creditsize = TextSizein(creditpos, creditsize,creditmax);
			}
			if (nowmoveR)
			{
				start = out;

				close = in;
				closePos = TextMovein(closePos,closesize,startsize,closemax);
				closesize = TextSizein(closePos, closesize,closemax);
			}
		}
			break;
		case 1:           //選択肢がcredit
		{
			creditpos = TextMoveout(creditpos);
			creditsize = TextSizeout(creditpos, creditsize,creditmax);
			if (nowmoveL)
			{
				credit = out;

				dataDelete = in;
				dataDeletepos = TextMovein(dataDeletepos,dataDeletesize,creditsize,datadeletemax);
				dataDeletesize = TextSizein(dataDeletepos, dataDeletesize,datadeletemax);
			}
			if (nowmoveR)
			{
				credit = out;

				start = in;
				startPos = TextMovein(startPos,startsize,creditsize,startmax);
				startsize = TextSizein(startPos, startsize,startmax);
			}
		}
			break;
		case 2:            //選択肢がdelete
		{
			dataDeletepos = TextMoveout(dataDeletepos);
			dataDeletesize = TextSizeout(dataDeletepos, dataDeletesize,datadeletemax);
			if (nowmoveL)
			{
				dataDelete = out;

				close = in;
				closePos = TextMovein(closePos,closesize,dataDeletesize,closemax);
				closesize = TextSizein(closePos, closesize,closemax);
			}
			if (nowmoveR)
			{
				dataDelete = out;

				credit = in;
				creditpos = TextMovein(creditpos,creditsize,dataDeletesize,creditmax);
				creditsize = TextSizein(creditpos, creditsize,creditmax);
			}
		}
			break;
		case 3:            //選択肢がexit
		{
			closePos = TextMoveout(closePos);
			closesize = TextSizeout(closePos, closesize,closemax);
			if (nowmoveL)
			{
				close = out;

				start = in;
				startPos = TextMovein(startPos,startsize,closesize,startmax);
				startsize = TextSizein(startPos, startsize,startmax);
			}
			if (nowmoveR)
			{
				close = out;

				dataDelete = in;
				dataDeletepos = TextMovein(dataDeletepos,dataDeletesize,closesize,datadeletemax);
				dataDeletesize = TextSizein(dataDeletepos, dataDeletesize,datadeletemax);
			}
		}
			break;
			//------------------------------------------------------------------------------------
		}
		if (demoTimer.GetTime() >= DEMO_LIMIT) {
			this->mode = Mode::from10;
			break;
		}

		//決定して次へ
		if (OGge->in->down(Input::in::B2))
		{
			//決定音の再生
			decisionsound.play();
			switch (this->cursorNum)
			{
			//ステージセレクトに進む
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
				this->mode = from8;
			}
			break;
			//クレジットに進む
			case 1:
			{
				//未実装のため、ゲームを閉じる
				OGge->GameEnd();
			}
				break;
			//データ消去
			case 2:
			{
				//yes,noを選択するモードに切り替える
				this->mode = from9;
			}
				break;
			//終了
			case 3:
				OGge->GameEnd();
				break;
			}

			auto effect03 = Effect::Create(
				Vec2(this->textPos[this->cursorNum].x + (this->textPos[this->cursorNum].w / 2 + 50), this->textPos[this->cursorNum].y + (this->textPos[this->cursorNum].h / 2)),
				Vec2(0, 0),
				Vec2(320, 64),
				1,
				30);
			effect03->SetMode(Effect::Mode::Expansion);
			effect03->SetAlphaMode(Effect::ModeAlpha::DOWN);
			effect03->SetTexture(&this->effect03);
			effect03->SetMaxSize(Vec2(640, 128));
		}
	}
	break;

	case from8:  //ジャンプからselectまでの移動
	{
		//降りたらロードを挟みセレクトへ移行する行動
		auto chara = OGge->GetTask<Chara>("Chara");
		if (chara->position.y > OGge->camera->GetPos().x + OGge->camera->GetSize().x)
		{
			this->mode = Mode::End;
		}
	}
	break;

	case from9:            //datadeleteのyesかnoかを選択する
		if (OGge->in->down(In::CL) || OGge->in->down(In::LL) || OGge->in->down(In::CR) || OGge->in->down(In::LR))
		{
			//カーソルの移動音再生
			cursorsound.play();

			if (del == no)
			{
				del = yes;
				break;
			}
			if (del == yes)
			{
				del = no;
				break;
			}
		}
		if (OGge->in->down(Input::in::B2))
		{
			//決定音の再生
			decisionsound.play();

			if (del == no)
			{
				this->mode = from7;
			}
			if (del == yes)
			{
				//データ削除の処理
				GameManager::ResetData();
				this->mode = from7;
			}
		}
		break;

	case from10: // Demo画面に移動するとき
	{
		trans_a += 0.01f;
		if (trans_a > 1.f) {
			trans_a = 1.f;
			if (curPlayVideo >= _countof(DEMO_VIDEOS)) {
				curPlayVideo = 0;
			}
			auto demo = Demo::Create(DEMO_VIDEOS[curPlayVideo]);
			this->curPlayVideo += 1;
			this->mode = Mode::from11;
			this->demoTimer.Stop();
			this->SetPauseEveryChild(true);
		}
	}
	break;
	case from11: // Demo画面から戻ってきたとき
	{
		auto Npc = OGge->GetTasks<Chara>("Chara");
		for (auto id = Npc->begin(); id != Npc->end(); ++id)
		{
			(*id)->MoveReset();
		}
		trans_a -= 0.01f;
		if (trans_a <= 0.0f) {
			trans_a = 0.f;
			
			this->demoTimer.Start();
			this->mode = Mode::from7;
		}
	}
	break;
	case End:	//Selectの読み込みと自身の破棄
	{
		//this->Kill();
		auto load = Load::Create();
		if (load)
		{
			load->AddDeleteObjectName(this->GetTaskName());
		}
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

	//モニターの表示
	{
		Box2D draw(Vec2(165.f, 783.f), Vec2(1180.f, 256.f));
		draw.OffsetSize();
		Box2D src(0.0f, 0.0f, 1000.0f, 500.0f);

		this->monitorTex.Draw(draw, src);
	}
	//PressAnyButton
	{
		if (this->mode == from6) {
			Box2D draw(this->startPos.x - 275, this->startPos.y + 60, 64.f * 15, 64.f);
			draw.OffsetSize();
			Box2D src(0.f, 64.f * 16, 64.f * 15, 64.f);
			src.OffsetSize();
			rm->GetTextureData(std::string("fontui"))->Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->press_a));
		}
	}

	//文字表示
	if (pressB)
	{
		//start
		{
			Box2D draw(startPos.x, startPos.y + 80.f, startsize.x, startsize.y);
			draw.OffsetSize();
			if (start == non)
			{
				Box2D src((64.f*5.f - startsize.x), 0.f, startsize.x, 64.f);
				src.OffsetSize();
				
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
			//一番初めは真ん中にstartを表示
			if (start == in)
			{
				Box2D src = intextsrc;
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
			if(start == out)
			{
				Box2D src = outtextsrc;
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
		}
		//credit
		{
			Box2D draw(creditpos.x, creditpos.y + 80.f, creditsize.x, creditsize.y);
			draw.OffsetSize();
			if (credit == in)
			{
				Box2D src = intextsrc;
				src.y = 64.f * 12;
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
			else
			{
				Box2D src = outtextsrc;
				src.y = 64.f * 12;
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
		}
		//delete
		{
			if (mode != from9)
			{
				Box2D draw(dataDeletepos.x, dataDeletepos.y + 80.f, dataDeletesize.x, dataDeletesize.y);
				draw.OffsetSize();
				//Box2D src((64.f*5.f - dataDeletesize.x), 0.f, dataDeletesize.x, 64.f);
				if (dataDelete == in)
				{
					Box2D src = intextsrc;
					src.y = 64.f * 13;
					src.OffsetSize();
					this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
				}
				else
				{
					Box2D src = outtextsrc;
					src.y = 64.f * 13;
					src.OffsetSize();
					this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
				}
			}
		}
		//exit
		{
			//仮処理
			Box2D draw(closePos.x, closePos.y + 80.f, closesize.x, closesize.y);
			draw.OffsetSize();
			if (close == in)
			{
				Box2D src = intextsrc;
				src.y = 64.f;                  //読み込む画像を変える
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
			else
			{
				Box2D src = outtextsrc;
				src.y = 64.f;                  //読み込む画像を変える
				src.OffsetSize();
				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
		}
		if (mode == from9)                      //yes,noの表示
		{
			if (del == yes || del == no)
			{
				Box2D draw = Box2D(monitorSpos + 390, 850.f, 64.f * 6, 64.f);
				draw.OffsetSize();
				Box2D src = Box2D(0, 64 * 14, 64 * 6, 64);
				src.OffsetSize();

				this->fontTex.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
			}
			//カーソルの表示
			Box2D src(0, 0, 195, 195);
			src.OffsetSize();
			this->texCursor.Rotate((float)this->gierCnt);
			if (del == yes)
			{
				Box2D draw(monitorSpos + 390 - 64.f, 850.f, 64.0f, 64.0f);
				draw.OffsetSize();
				texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
			}
			if (del == no)
			{
				Box2D draw(monitorSpos + 390 + 64.f*3, 850.f, 64.0f, 64.0f);
				draw.OffsetSize();
				texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
			}
		}
	}

	////カーソルの表示
	//{
	//	//表示位置、大きさは仮ゲームスタート
	//	Box2D draw(cursorPos[this->cursorNum].x, cursorPos[this->cursorNum].y, 64.0f, 64.0f);
	//	draw.OffsetSize();
	//	Box2D src(0, 0, 195, 195);
	//	src.OffsetSize();
	//	this->texCursor.Rotate((float)this->gierCnt);
	//	texCursor.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
	//	Box2D draw2(cursorPos[this->cursorNum].x + 64.0f + (30.f * 2.f) + cursorPos[this->cursorNum].w, cursorPos[this->cursorNum].y, 64.f, 64.f);
	//	draw2.OffsetSize();
	//	texCursor.Draw(draw2, src, Color(1.0f, 1.0f, 1.0f, this->cursor_a));
	//}
	////終了
	//{
	//	Box2D draw(closePos.x, closePos.y, 64.f*4, 64.f/* 256.f, 64.f*/);
	//	draw.OffsetSize();
	//	Box2D src(0, 64, 64*4, 64);
	//	src.OffsetSize();
	//	rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	//}
	////スタート
	//{
	//	//Box2D draw(startPos.x, startPos.y, 256.f, 128.f);
	//	Box2D draw(startPos.x, startPos.y, 320.f, 64.f);
	//	draw.OffsetSize();
	//	Box2D src(0, 0, 64*5, 64);
	//	src.OffsetSize();
	//	//texStart.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	//	rm->GetTextureData((std::string)"fontui")->Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->tex_a));
	//}

	//画面転換用黒いやつ
	if (this->trans_a > 0.f) {
		Box2D draw(Vec2(0, 0), Vec2(1920 * 2, 1080 * 2));
		Box2D src(0, 0, 1, 1);
		forTransform.Draw(draw, src, Color(1.0f, 1.0f, 1.0f, this->trans_a));
	}
}

bool Title::Finalize()
{
	//使用画像の解放
	texCursor.Finalize();
	this->texLogo.Finalize();
	this->GierLogo.Finalize();
	this->flowerLogo.Finalize();
	this->texEffect.Finalize();
	this->effect03.Finalize();
	this->forTransform.Finalize();
	this->canVolControl = false;
	this->monitorTex.Finalize();
	this->fontTex.Finalize();

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
	auto Npc = OGge->GetTasks<Chara>("Chara");
	for(auto id = Npc->begin(); id != Npc->end();++id)
	{
		(*id)->Kill();
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

//Bキーが押されたかの判定に使用
bool Title::PressB()
{
	if (OGge->in->down(Input::in::B2))
	{
		//決定音の再生
		decisionsound.play();

		this->pressB = true;
		return true;
	}
	return false;
}


//文字の移動について---------------------------------------------------------------------------
//textがモニターの外に出ていく動き
Vec2 Title::TextMoveout(Vec2 pos)
{
	if (this->nowmoveL)
	{
		if (pos.x >= this->monitorSpos + 120.f)
		{
			pos.x -= 16.f;
		}
	}
	if (this->nowmoveR)
	{
		if (pos.x < monitorEpos-120.f)
		{
			pos.x += 15.f;
		}
	}
	return pos;
}

//textがモニターの内側に入ってくる動き
Vec2 Title::TextMovein(Vec2 pos,Vec2 size,Vec2 outsize,float maxsize)      //必要止める場所指定用
{
	if (this->nowmoveL)
	{
		if (pos.x >= ((monitorEpos - monitorSpos)- (maxsize/2.f)) / 2.f + 40.f)
		{
			pos.x -=15;
		}
		if (pos.x < ((monitorEpos - monitorSpos) - (maxsize)/2.f) / 2.f + 40.f && outsize.x<=0.0f)
		{
			if (cursorNum < 3)
			{
				cursorNum++;
			}
			else
			{
				cursorNum = 0;
			}
			nowmoveL = false;
		}
	}

	if (this->nowmoveR)
	{
		if (pos.x <= ((monitorEpos - monitorSpos) - (maxsize/2.f)) / 2.f )
		{
			if (size.x >= maxsize)
			{
				pos.x += 15.f;
			}
		}
		if (pos.x >= ((monitorEpos - monitorSpos)- (maxsize/2.f)) / 2.f && outsize.x <= 0.0f )
		{
			if (cursorNum > 0)
			{
				cursorNum--;
			}
			else
			{
				cursorNum = 3;
			}
			nowmoveR = false;
		}
	}
	return pos;
}

//textの出ていくときの横サイズ変更処理
Vec2 Title::TextSizeout(Vec2 pos,Vec2 size ,float maxsize)
{
	if (this->nowmoveL)
	{
		if(pos.x<this->monitorSpos+120.f)
		{
			if (size.x >= 0.0f)
			{
				size.x -= 16;
			}
		}

		if (size.x == 0.0f)
		{
			pos.x = (monitorSpos - size.x);
		}
		this->outtextsrc = Box2D((maxsize - size.x), 0.f, size.x, 64.f);
	}
	if (this->nowmoveR)
	{
		//この位置より右側に入ってもsizeが0になっていない
		if (pos.x+size.x > this->monitorEpos-115.f)       //ここでひっかかってる
		{
			if (size.x >= 0.0f)
			{
				size.x -= 15; 
			}
			if (size.x < 15)
			{
				size.x = 0;
			}
		}
		if (size.x == 0.0f)
		{
			pos.x = (monitorEpos + size.x);
		}
		this->outtextsrc = Box2D(0.f, 0.f, size.x, 64.f);
	}
	return size;
}

//textの横サイズ
Vec2 Title::TextSizein(Vec2 pos, Vec2 size, float maxsize)        //必要最大サイズ指定用
{
	if (this->nowmoveL)
	{
		if (size.x <= maxsize)
		{
			size.x +=15.f;
		}
		intextsrc = Box2D(0.f, 0.f, size.x, 64.f);
	}
	if (this->nowmoveR)
	{
		if (size.x <= maxsize)
		{
			size.x += 15.f;
		}
		intextsrc = Box2D((maxsize - size.x), 0.f, size.x, 64.f);
	}
	return size;
}

//-----------------------------------------------------------------------------------------

void Title::CursorMove()
{
	//左へ
	if (OGge->in->down(In::CL) || OGge->in->down(In::LL))
	{
		//カーソルの移動音再生
		cursorsound.play();
		this->cursorNum--;
	}
	//右へ
	if (OGge->in->down(In::CR) || OGge->in->down(In::LR))
	{
		//カーソルの移動音再生
		cursorsound.play();
		this->cursorNum++;
	}
	if (this->cursorNum > 3)
	{
		this->cursorNum = 0;
	}
	if (this->cursorNum < 0)
	{
		this->cursorNum = 3;
	}
}

void Title::SetPauseEveryChild(const bool& p)
{
	auto back = OGge->GetTask<Back>("back");
	if (back)
	{
		back->SetPause(p);
	}
	auto water = OGge->GetTasks<Water>("water");
	for (auto id = (*water).begin(); id != (*water).end(); ++id)
	{
		(*id)->SetPause(p);
	}
	auto map = OGge->GetTask<Map>("map");
	if (map)
	{
		(*map).SetPause(p);
	}
	auto Npc = OGge->GetTasks<Chara>("Chara");
	for (auto id = Npc->begin(); id != Npc->end(); ++id)
	{
		(*id)->SetPause(p);
	}
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->SetPause(p);
	}
	this->SetPause(p);
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
	this->mode = Mode::from4;
	auto waters = OGge->GetTasks<Water>("water");
	for (auto id = waters->begin(); id != waters->end(); ++id)
	{
		(*id)->Kill();
	}
	auto npc = OGge->GetTask<Chara>("Chara");
	if (npc)
	{
		npc->Kill();
	}
	this->cm.DeleteObject();
	OGge->camera->SetPos(Vec2(0, 200));
	OGge->camera->SetSize(Vec2(1440, 810));
	this->flowerVolume = 1.0f;
	this->tex_a = 1.0f;
	this->isGierAng = true;
	auto npc2 = Chara::Create((std::string)"player.png", Vec2(1600, 628));
	npc2->SetPause(true);
	this->sound->play();
	this->skipInoutFlag = true;
}

void Title::SkipMove()
{
	demoTimer.Start();
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
