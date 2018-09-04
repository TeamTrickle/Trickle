#include "JecLogo.h"
#include "Task_Title.h"
#include "Load\LoadLogo.h"
LogoTask::LogoTask()
{
	this->logo = new Texture();
	logo->Create("JecLogo.png");
	this->logo_a = 0.f;
	this->back = Color(0, 0, 0, 0);
	this->mode = Mode::form1;
	__super::Init("LoadLogo");
}
LogoTask::~LogoTask()
{
	delete this->logo;
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{
		Title::Create();
		OG::BackColor(0.f, 0.f, 0.f, 0.f);
	}
}
void LogoTask::UpDate()
{
	OG::BackColor(this->back.alpha, this->back.alpha, this->back.alpha, this->back.alpha);
	switch (this->mode)
	{
		case Mode::form1:
			this->back.alpha += 0.03f;
			if (this->back.alpha > 1.0f)
			{
				this->mode = Mode::form2;
			}
			break;
		case Mode::form2:
			this->logo_a += 0.03f;
			if (this->logo_a > 2.f)
			{
				this->mode = Mode::form3;
			}
			break;
		case Mode::form3:
			this->logo_a -= 0.03f;
			if(this->logo_a <= 0.f)
			{
				this->mode = Mode::form4;
			}
			break;
		case Mode::form4:
			this->back.alpha -= 0.03f;
			if (this->back.alpha <= 0.f)
			{
				this->mode = Mode::end;
			}
			break;
		case Mode::end:
			auto load = Load::Create();
			if (load)
			{
				load->AddDeleteObjectName(this->GetTaskName());
				load->ALLTaskUpDateStop();
			}
			break;
	}
}
void LogoTask::Render2D()
{
	Box2D draw(OGge->camera->GetPos().x,
		(OGge->camera->GetSize().y + OGge->camera->GetPos().y) / 2.f - (OGge->camera->GetSize().x * 176.f / 1023.f / 2.f),
		OGge->camera->GetSize().x,
		OGge->camera->GetSize().x * 176.f / 1023.f);
	draw.OffsetSize();
	Box2D src(Vec2(0, 0), logo->GetTextureSize());
	src.OffsetSize();
	this->logo->Draw(draw, src, Color(1.f, 1.f, 1.f, this->logo_a));
}
LogoTask::SP LogoTask::Create()
{
	LogoTask::SP to = LogoTask::SP(new LogoTask());
	if (to)
	{
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}