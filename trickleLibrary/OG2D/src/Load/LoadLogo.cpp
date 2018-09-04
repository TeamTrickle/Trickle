#include "LoadLogo.h"

Load::Load()
	:feadInTime(0.02f),feadOutTime(0.03f)
{
	__super::Init("load");
	__super::SetDrawOrder(1.1f);
	this->logoimage = rm->GetTextureData("LoadLogo");
	this->backimage = rm->GetTextureData("BrackBackGround");
	this->logocolor = new Color(1, 1, 1, 0);
	this->backcolor = new Color(1, 1, 1, 0);
	this->mode = Fead::BackIn;
	this->Stop(false);
}

Load::~Load()
{
	if (this->logocolor)
	{
		delete this->logocolor;
	}
	if (this->backcolor)
	{
		delete this->backcolor;
	}
}

void Load::UpDate()
{
	switch (this->mode)
	{
	case Fead::LogoIn:
		this->FeadLogoInUpDate();
		break;
	case Fead::LogoOut:
		this->FeadLogoOutUpDate();
		break;
	case Fead::BackIn:
		this->FeadBackInUpDate();
		break;
	case Fead::BackOut:
		this->FeadBackOutUpDate();
		break;
	default:
		break;
	}
}

void Load::FeadLogoInUpDate()
{
	if (this->logocolor->alpha < 1.f)
	{
		this->logocolor->alpha += this->feadInTime;
	}
	else
	{
		for (auto id = this->deleteObjectName.begin(); id != this->deleteObjectName.end(); ++id)
		{
			auto task = OGge->GetTasks<TaskObject>(*id);
			for (auto is = task->begin(); is != task->end(); ++is)
			{
				(*is)->Kill();
			}
		}
		this->deleteObjectName.clear();
		OGge->AllStop(false);
		this->mode = Fead::LogoOut;
	}
}

void Load::FeadLogoOutUpDate()
{
	if (this->logocolor->alpha > 0)
	{
		this->logocolor->alpha -= this->feadOutTime;
	}
	else
	{
		for (auto id = this->deleteObjectName.begin(); id != this->deleteObjectName.end(); ++id)
		{
			auto task = OGge->GetTasks<TaskObject>(*id);
			for (auto is = task->begin(); is != task->end(); ++is)
			{
				(*is)->Kill();
			}
		}
		this->deleteObjectName.clear();
		OGge->AllStop(false);
		this->mode = Fead::BackOut;
	}
}

void Load::FeadBackInUpDate()
{
	if (this->backcolor->alpha < 1.f)
	{
		this->backcolor->alpha += this->feadInTime;
	}
	else
	{
		this->mode = Fead::LogoIn;
	}
}

void Load::FeadBackOutUpDate()
{
	if (this->backcolor->alpha > 0)
	{
		this->backcolor->alpha -= this->feadOutTime;
	}
	else
	{
		this->Kill();
	}
}

void Load::PauseUpDate()
{
	if (this->logocolor->alpha > 0)
	{
		this->logocolor->alpha -= 0.005f;
	}
	else
	{
		this->Kill();
	}
}

void Load::Draw()
{
	OGge->camera->SetSize(Vec2(1920, 1080));
	OGge->camera->SetPos(Vec2(0, 0));
	OGge->camera->UpDate();
	unsigned int time = 0;
	while (this->logocolor->alpha <= 1.0)
	{
		if (time >= 60)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->draw = { 0,0,1920,1080 };
			this->draw.OffsetSize();
			this->src = { 0.f,0.f,this->logoimage->GetTextureSize().x,this->logoimage->GetTextureSize().y };
			this->src.OffsetSize();
			this->logoimage->Draw(this->draw, this->src, *this->logocolor);
		
			glfwSwapBuffers(OGge->window->GetWindow());
			
			this->logocolor->alpha += 0.005f;
			time = 0;
		}
		else
		{
			time++;
		}
	}
}

void Load::Render2D()
{
	this->draw = { OGge->camera->GetPos(),OGge->camera->GetSize() };
	this->draw.OffsetSize();
	this->src = { 0.f,0.f,this->backimage->GetTextureSize().x,this->backimage->GetTextureSize().y };
	this->src.OffsetSize();
	this->backimage->Draw(this->draw, this->src, *this->backcolor);

	this->draw = { OGge->camera->GetPos(),OGge->camera->GetSize() };
	this->draw.OffsetSize();
	this->src = { 0.f,0.f,this->logoimage->GetTextureSize().x,this->logoimage->GetTextureSize().y };
	this->src.OffsetSize();
	this->logoimage->Draw(this->draw, this->src, *this->logocolor);
}

void Load::SetFead(const Fead& fead)
{
	this->mode = fead;
	/*if (this->mode == Fead::LogoOut)
	{

	}
	else
	{
		OGge->AllStop(true);
	}*/
	this->Stop(false);
}

Load::Fead Load::Get() const
{
	return this->mode;
}

void Load::AddDeleteObjectName(const std::string& d)
{
	this->deleteObjectName.push_back(d);
}

void Load::ALLTaskUpDateStop(const bool flag)
{
	OGge->AllStop(flag);
	this->Stop(false);
}

Load::SP Load::Create()
{
	if (OGge->GetTask<Load>("load"))
	{
		return nullptr;
	}
	Load::SP to = Load::SP(new Load());
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		return to;
	}
	return nullptr;
}