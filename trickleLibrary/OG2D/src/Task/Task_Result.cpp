#include "Task_Result.h"
#include "Chara\Chara.h"
#include "Back\Back.h"
#include "Map\Map.h"
#include "Effect/Effect.h"
#include "StageSelect.h"
#include "Load\LoadLogo.h"

Result::Result() {
	this->taskName = "Result";
	__super::Init(taskName);
	starsoundname = "kira2.wav";
	drumsoundname = "drum.wav";
}
Result::~Result() {
	this->Finalize();
}

bool Result::Initialize() {
	fontui.Create((std::string)"fontui.png");
	numberui.Create((std::string)"number.png");

	backTex.Create((std::string)"back.png");
	this->starTex.Create((std::string)"resultstar.png");
	this->frameTex.Create((std::string)"resultframe.png");
	this->stareffectTex.Create((std::string)"stareffect.png");
	this->petalTex1.Create((std::string)"resultFlower1.PNG");
	this->petalTex2.Create((std::string)"resultFlower2.PNG");
	this->petalTex3.Create((std::string)"resultFlower3.PNG");
	this->petalTex4.Create((std::string)"resultFlower4.PNG");
	this->petalTex5.Create((std::string)"resultFlower5.PNG");

	//this->clearTex

	//サウンドの生成
	soundstar.create(starsoundname, false);    //星のはまる音声
	soundstar.volume(1.0f);

	sounddrum.create(drumsoundname, false);     //ドラムロール
	sounddrum.volume(1.0f);

	//sound.create(soundname, true);           //BGM未実装
	//sound.volume(1.0f);
	//sound.play();

	this->effCounter = 0;

	this->nowMode = Mode1;
	auto npc = Chara::Create((std::string)"player.png", Vec2(-120, 64 * 8));
	npc->SetDirection(Chara::Direction::RIGHT);
	npc->Set(Vec2(-120, 64 * 8), Vec2(64 * 2, 64 * 8), 15.f);
	Map::Create((std::string)"result.csv");
	//TIME
	time.nowWH = Vec2(0, 0);
	time.pos = Vec2(150 + 64 * 2, 280 + 32);
	for (int i = 0; i < 3; ++i) {
		//星の枠
		starFrame[i].nowWH = Vec2(0, 0);
		starFrame[i].pos = Vec2(300 + 64 + i * 200, 370 + 64 - 8 * i);
		//星
		star[i].nowWH = Vec2(512, 512);
		star[i].pos = Vec2(1280, 300);
		star[i].bezcnt = 0.0f;
		star[i].angle = -5;
		//星出すフラグ
		starFlag[i] = false;
		starturn[i] = false;
		this->effectStarFlag[i] = false;
		num[i] = 0;
	}
	num[3] = 0;
	cnt = 0;
	this->maxTrueNumber = -1;
	this->RoadData();
	OGge->camera->SetSize(Vec2(1280, 720));
	return true;
}
void Result::UpDate() {
	auto npc = OGge->GetTask<Chara>("Chara");
	float pretimew = 0, pretimeh = 0;
	float prestarw[3] = {}, prestarh[3] = {};
	float starytmp[3] = {};
	float presfw = 0, presfh = 0;
	switch (nowMode) {
	case Mode1:
		npc->AutoMove();
		if (!npc->isAutoPlay()) {
			this->nowMode = Mode2;
		}
		break;
	case Mode2:
		++cnt;
		//TIME
		if (time.nowWH.x < 64 * 4) {
			pretimew = time.nowWH.x;
			time.nowWH.x = time.easeX.expo.In(time.easeX.Time(3), 0.0f, 64 * 4, 3);
			time.pos.x -= (time.nowWH.x - pretimew) / 2.0f;
			if (time.nowWH.x >= 64 * 4) {
				time.nowWH.x = 64 * 4;
				time.pos.x = 150;
			}
		}
		if (time.nowWH.y < 64) {
			pretimeh = time.nowWH.y;
			time.nowWH.y = time.easeY.bounce.In(time.easeY.Time(3), 0.0f, 64, 3);
			time.pos.y -= (time.nowWH.y - pretimeh) / 2.0f;
			if (time.nowWH.y >= 64) {
				time.nowWH.y = 64;
				time.pos.y = 280;
			}
		}
		//星の枠
		for (int i = 0; i < 3; ++i) {
			if (starFrame[i].nowWH.x < 64 * 2) {
				presfw = starFrame[i].nowWH.x;
				starFrame[i].nowWH.x = starFrame[i].easeX.expo.In(starFrame[i].easeX.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.x -= (starFrame[i].nowWH.x - presfw) / 2.0f;
				if (starFrame[i].nowWH.x >= 64.f * 2.f) {
					starFrame[i].nowWH.x = 64.f * 2.f;
					starFrame[i].pos.x = 300.f + i * 200.f;
				}
			}
			if (starFrame[i].nowWH.y < 64 * 2) {
				presfh = starFrame[i].nowWH.y;
				starFrame[i].nowWH.y = starFrame[i].easeY.bounce.In(starFrame[i].easeY.Time(3), 0.0f, 64 * 2, 3);
				starFrame[i].pos.y -= (starFrame[i].nowWH.y - presfh) / 2.0f;
				if (starFrame[i].nowWH.y >= 64.f * 2.f) {
					starFrame[i].nowWH.y = 64.f * 2.f;
					starFrame[i].pos.y = 370.f - i * 8.f;
				}
			}
		}
		if (cnt >= 100) {
			this->nowMode = Mode3;
			cnt = 0;
		}
		break;
	case Mode3:
		++cnt;
		if (cnt < 120) {
			//サウンドの再生
			if (cnt == 1)        //0だと入らないので1の時にプレイを開始、二秒後に停止
			{
				sounddrum.play();
			}

			for (int i = 0; i < 4; ++i) {
				num[i] = random::GetRand(0, 9);
			}
		}
		else {
			for (int i = 0; i < 4; ++i) {
				num[i] = this->timer[i];
			}
		}
		if (cnt >= 150) {
			this->nowMode = Mode4;
			cnt = 0;
		}
		break;
	case Mode4:
		if (this->maxTrueNumber == -1)
		{
			this->nowMode = Mode5;
			break;
		}
		++cnt;
		//星出現
		for (int i = 0; i < 3; ++i) {
			if (starFlag[i] && cnt >= 20 * i) {
				star[i].bezcnt += 0.03f;
				star[i].angle += 15;
				//X
				star[i].pos.x = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 1280 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 1000 + star[i].bezcnt * star[i].bezcnt * (300 + i * 200);
				if (star[i].pos.x <= 300.f + i * 200.f) {
					star[i].pos.x = 300.f + i * 200.f;
				}
				//Y
				star[i].pos.y = (1 - star[i].bezcnt)*(1 - star[i].bezcnt) * 300 + 2 * (1 - star[i].bezcnt)*star[i].bezcnt * 0 + star[i].bezcnt * star[i].bezcnt * (370 - i * 8);
				if (star[i].pos.y >= 370.f - i * 8.f) {
					star[i].pos.y = 370.f - i * 8.f;
				}
				//W,H縮小
				star[i].nowWH.x = star[i].nowWH.y = star[i].easeX.cubic.Out(star[i].easeX.Time(5), 512, 128 - 512, 5);
				if (star[i].nowWH.x <= 128) {
					star[i].nowWH.x = star[i].nowWH.y = 128;
				}
				//停止地点に到着
				if (star[i].pos == Vec2(300 + i * 200, 370 - i * 8) && star[i].nowWH == Vec2(128, 128)) {
					star[i].angle = -5;
					//サウンドの再生
					soundstar.play();

					//星のエフェクト
					if (!this->effectStarFlag[i])
					{
						for (int j = 0; j < 4; ++j)
						{
							auto effect = Effect::Create(Vec2(310 + i * 200, 370), Vec2(64, 64), Vec2(256, 256), 1, 15);
							effect->SetMode(Effect::Mode::Down);
							effect->SetTexture(&stareffectTex);
							if (j / 2 == 0)
							{
								//移動値を登録
								effect->SetMove(Vec2(-10, ((j % 2) - 1) * 8));
								//内部で行われる重力、摩擦の時の値をいじる
								//最大落下速度15.f,1fごとに下に落ちていく重力値,横移動の摩擦値
								effect->SetSpeed(15.f, (9.8f / 60.f / 60.f * 32) * 10, 0.1f);
								effect->SetAngle(15.f, -1);
							}
							else
							{
								effect->SetMove(Vec2(10, ((j % 2) - 1) * 8));
								effect->SetSpeed(15.f, (9.8f / 60.f / 60.f * 32) * 10, 0.1f);
								effect->SetAngle(15.f, 1);
							}

							//effect->Set(Vec2((effect->position.x+64.0f)+random::GetRand(-30,30),effect->position.y), Vec2(effect->position.x + random::GetRand(-100, 100), effect->position.y + random::GetRand(-100, 100)));
							//effect->Set(effect->position, Vec2(effect->position.x-30, effect->position.y + 100));
							effect->SetDrawOrder(1.0f);
						}
					}
					this->effectStarFlag[i] = true;
					//auto eff = Effect::Create(Vec2(300 + i * 200, 370 - i * 8), Vec2(32, 32), Vec2(256, 256), 5, 5);
					//eff->SetMode(Effect::Mode::Decrease);
					//eff->SetTexture(&this->stareffectTex);
					//eff->Set(eff->position, Vec2(eff->position.x + random::GetRand(-30, 30), eff->position.y + random::GetRand(-30, 30)));
				}
			}
		}
		if (star[this->maxTrueNumber].pos == Vec2(300 + this->maxTrueNumber * 200, 370 - this->maxTrueNumber * 8) && star[this->maxTrueNumber].nowWH == Vec2(128, 128)) {
			cnt = 0;
			this->nowMode = Mode5;
		}
		break;
	case Mode5:
		//アニメーションが終わるまで(５回ジャンプ＋位置調整)は入力できない
		if (npc->happyCnt < 7) {

			//花を降らせるエフェクト-----------------------------------------------------
			if (effCounter < 300)
			{
				effCounter++;
			}
			else
			{
				effCounter = 0;
			}
			//一定時間ごとに花びらが出現
			if (effCounter % 3 == 0)
			{
				int x = random::GetRand(-768, 1800);

				auto effect = Effect::Create(Vec2(x, -700), Vec2(256, 256), Vec2(256, 256), 1, 400);
				effect->SetMode(Effect::Mode::Down);

				//画像の種類にランダムをかける
				int anim = rand() % 5 + 1;
				switch (anim)
				{
				case 1:
					effect->SetTexture(&petalTex1);
					break;
				case 2:
					effect->SetTexture(&petalTex2);
					break;
				case 3:
					effect->SetTexture(&petalTex3);
					break;
				case 4:
					effect->SetTexture(&petalTex4);
					break;
				case 5:
					effect->SetTexture(&petalTex5);
					break;
				}
				//出現した花びらの動きについて
				if (npc->happyCnt % 3 == 0)
				{
					effect->SetMove(Vec2(-15, 5));
					effect->SetSpeed(10.f, (9.8f / 60.f / 60.f * 32) * 5, 0.1f);
					effect->SetAngle(3.f, -1);
				}
				else if (npc->happyCnt % 3 == 1)
				{
					effect->SetMove(Vec2(-15, 5));
					effect->SetSpeed(10.f, (9.8f / 60.f / 60.f * 32) * 5, 0.1f);
					effect->SetAngle(2.f, 1);
				}
				else
				{
					effect->SetMove(Vec2(15, 15));
					effect->SetSpeed(10.f, (9.8f / 60.f / 60.f * 32) * 15, 0.1f);
					effect->SetAngle(2.f, 1);
				}
			}
			//--------------------------------------------------------------------------------
			npc->Happy(7);
			//クリアUI出現(未実装)
		}
		else {
			++cnt;
			if (OGge->in->down(Input::in::B2) || cnt > 1800)
			{
				npc->MoveReset();
				npc->Set(npc->position, Vec2(1500.f, npc->position.y), 30.f);
				this->nowMode = Mode6;
			}
		}

		break;
	case Mode6:
		//プレイヤ退場
		npc->AutoMove();
		if (npc->position.x >= 1450) {
			this->nowMode = Mode::Mode7;
			auto load = Load::Create();
			if (load)
			{
				load->AddDeleteObjectName(this->GetTaskName());
			}
		}
		break;
	case Mode7:
		break;
	case Non:
	default:
		break;
	}
}
void Result::Render2D() {
	//背景
	{
		backTex.Draw(Box2D(0, 0, 1280, 720), Box2D(0, 0, 1280, 720));
	}
	//モニター枠
	{
		Box2D draw((1280 - 1400) / 2, 720 - 700 - 32, 1400, 700);
		draw.OffsetSize();
		Box2D src(0, 0, 1000, 500);
		frameTex.Draw(draw, src);
	}
	//Result
	{
		Box2D draw(470, 110, 64 * 6, 64);
		draw.OffsetSize();
		Box2D src = Box2D(0, 64 * 2, 64 * 6, 64);
		src.OffsetSize();
		fontui.Rotate(-5);
		fontui.Draw(draw, src);
	}
	//rm->GetTextureData((std::string)"fontui")->Draw(draw, src);
	//TIME
	{
		Box2D draw(time.pos.x, time.pos.y, time.nowWH.x, time.nowWH.y);
		draw.OffsetSize();
		Box2D src(0, 64 * 3, 64 * 4, 64);
		src.OffsetSize();
		fontui.Draw(draw, src);
	}
	//星の枠
	{
		for (int i = 0; i < 3; ++i) {
			Box2D draw(starFrame[i].pos.x, starFrame[i].pos.y, starFrame[i].nowWH.x, starFrame[i].nowWH.y);
			draw.OffsetSize();
			Box2D src(0, 0, 256, 256);
			starTex.Rotate(-5);
			starTex.Draw(draw, src);
		}
	}
	//タイム
	{
		if (nowMode >= Mode3) {
			//数字
			for (int i = 0; i < 4; ++i) {
				Box2D draw(150 + 64 * 4 + 100 + 96 * i, 250 - 7 * i, 96, 96);
				draw.OffsetSize();
				Box2D src(64 * num[i], 0, 64, 64);
				src.OffsetSize();
				numberui.Rotate(-5);
				numberui.Draw(draw, src);
			}
			//：
			Box2D draw(150 + 96 * 4 + 100 + 40, 260 - 17, 64, 64);
			draw.OffsetSize();
			Box2D src(64 * 10, 0, 40, 64);
			src.OffsetSize();
			numberui.Draw(draw, src);
		}
	}
	//星
	{
		if (nowMode >= Mode4) {
			for (int i = 0; i < 3; ++i) {
				Box2D draw(star[i].pos, star[i].nowWH);
				draw.OffsetSize();
				Box2D src(256, 0, 256, 256);
				src.OffsetSize();
				starTex.Rotate((float)star[i].angle);
				starTex.Draw(draw, src);
			}
		}
	}
}
bool Result::Finalize() {
	//解放処理
	this->backTex.Finalize();
	//this->clearTex.Finalize();
	this->frameTex.Finalize();
	this->fontui.Finalize();
	this->numberui.Finalize();
	this->starTex.Finalize();
	auto effects = OGge->GetTasks<Effect>("effect");
	for (auto id = effects->begin(); id != effects->end(); ++id)
	{
		(*id)->Kill();
	}
	auto npc = OGge->GetTask<Chara>("Chara");
	if (npc) { npc->Kill(); }
	auto map = OGge->GetTask<Map>("map");
	if (map) { map->Kill(); }
	//ステージセレクトに戻る
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		OGge->ChengeTask();
		StageSelect::Create();
	}

	return true;
}
void Result::RoadData()
{
	std::ifstream ifs("./data/Result/save" + std::to_string(*MapNum) + ".bin", std::ios::in | std::ios::binary);
	if (!ifs)
	{
		this->Kill();
	}
	std::string line;
	std::getline(ifs, line);
	std::istringstream* is = new std::istringstream(line);
	std::string text;
	for (int i = 0; i < 2; ++i)
	{
		int t_time;
		std::getline(*is, text, ',');
		(std::stringstream)text >> t_time;
		this->timer[i * 2] = t_time / 10;
		this->timer[i * 2 + 1] = t_time % 10;
	}
	std::getline(ifs, line);
	delete is;
	is = new std::istringstream(line);
	for (int i = 0; i < 3; ++i)
	{
		std::getline(*is, text, ',');
		if (text == "t")
		{
			this->starFlag[i] = true;
			this->maxTrueNumber = (__int8)i;
		}
	}
	delete is;
}

Result::SP Result::Create(bool flag) {
	Result::SP to = Result::SP(new Result());
	if (to)
	{
		to->me = to;
		if (flag)
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
