#include "SterEffect.h"

#include "GameProcessManagement\FlagUI.h"

bool SterEffect::Initialize(std::shared_ptr<GameObject> target)
{
	//タスク関連
	this->taskName = "SterEffect";
	this->Init(taskName);

	//基本の情報
	this->CreateObject(Cube, Vec2{}, Vec2(64, 64), 0.f);

	//アニメーションの動き
	this->animetion.StateChenge(State::Motion);

	//Easing関連
	this->ResetEasing(easingX);
	this->ResetEasing(easingY);
	if (target != nullptr)
	{
		this->target = target;
	}

	//Easing開始場所
	if ((std::static_pointer_cast<FlagUI>)(target)->GetFlag())
	{
		//画像関連
		image.Create((std::string)"Ster.png");
	}
	else
	{
		image.Create((std::string)"SterB.png");
	}

	std::cout << "スターエフェクト　初期化" << std::endl;
	return true;
}
bool SterEffect::Initialize(std::shared_ptr<GameObject> target , std::shared_ptr<SterEffect> effect)
{
	//タスク関連
	this->taskName = "SterEffect";
	this->Init(taskName);

	//基本の情報
	this->CreateObject(Cube, Vec2{}, Vec2(64, 64), 0.f);

	//アニメーションの動き
	this->animetion.StateChenge(State::Motion);

	//Easing関連
	this->ResetEasing(easingX);
	this->ResetEasing(easingY);
	if (target != nullptr)
	{
		this->target = target;
	}
	if (effect != nullptr)
	{
		this->effect = effect;
	}
	//Easing開始場所
	if ((std::static_pointer_cast<FlagUI>)(target)->GetFlag())
	{
		//画像関連
		image.Create((std::string)"Ster.png");
	}
	else
	{
		image.Create((std::string)"SterB.png");
	}

	std::cout << "スターエフェクト　初期化" << std::endl;
	return true;
}
void SterEffect::ResetEasing(Easing& easing)
{
	easing.Init();
	easing.ResetTime();
	this->isPlayed = false;
}
bool SterEffect::Finalize()
{
	image.Finalize();
	return true;
}
void SterEffect::UpDate()
{
	if (effect)
	{
		if (effect->EasingIsPlay())
		{
			Think();
			MotionActive();
		}
	}
	else
	{
		Think();
		MotionActive();
	}
}
void SterEffect::Render2D()
{
	if (effect)
	{
		if (effect->EasingIsPlay())
		{
			Box2D draw(this->position, this->Scale);
			draw.OffsetSize();
			Box2D src = this->Src;
			src.OffsetSize();
			image.Draw(draw, src);
		}
	}
	else
	{
		Box2D draw(this->position, this->Scale);
		draw.OffsetSize();
		Box2D src = this->Src;
		src.OffsetSize();
		image.Draw(draw, src);
	}
}
bool SterEffect::EasingIsPlay()
{
	return this->isPlayed ? true : false;
}
void SterEffect::Think()
{
	State nm = this->animetion.motion;
	switch (this->animetion.motion)
	{
	case State::NON:
		break;
	case State::Motion:
		if (this->isPlayed)
		{
			nm = NON;
		}
		break;
	default:
		break;
	}
	this->animetion.StateChenge(nm);
}
void SterEffect::MotionActive()
{
	switch (this->animetion.motion)
	{
	case State::NON:
		//エフェクト演出が終了したことを伝える
		(std::static_pointer_cast<FlagUI>(target))->SetEffectEnd();
		this->Kill();
		break;
	case State::Motion:
		this->MoveEasing();
		break;
	default:
		break;
	}
}
void SterEffect::MoveEasing()
{
	Vec2 camerasize = OGge->camera->GetSize();

	Vec2 flagui = (std::static_pointer_cast<FlagUI>(target))->GetPos();

	if (easingX.isplay() || easingY.isplay())
	{
		//右から左
		this->position.x = easingX.cubic.Out(10.5f, -camerasize.x + flagui.x, camerasize.x, easingX.Time(10.5f));
		//上から下
		this->position.y = easingY.cubic.Out(12, 230 + flagui.y, -230, easingY.Time(12));
	}
	else
	{
		this->isPlayed = true;
	}
}
void SterEffect::Animetion::StateChenge(SterEffect::State state)
{
	this->motion = state;
}
SterEffect::SterEffect()
{
	std::cout << "スターエフェクト　生成" << std::endl;
}
SterEffect::~SterEffect()
{
	std::cout << "スターエフェクト　解放" << std::endl;
}
SterEffect::SP SterEffect::Create(std::shared_ptr<GameObject> target ,bool flag)
{
	SterEffect::SP to = SterEffect::SP(new SterEffect());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(target))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}
SterEffect::SP SterEffect::Create(std::shared_ptr<GameObject> target,std::shared_ptr<SterEffect> effect , bool flag)
{
	SterEffect::SP to = SterEffect::SP(new SterEffect());
	if (to)
	{
		to->me = to;
		if (flag)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(target,effect))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}