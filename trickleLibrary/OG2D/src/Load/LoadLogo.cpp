#include "LoadLogo.h"

Load::Load()
{
	__super::Init((std::string)"load");
	__super::SetDrawOrder(1.1f);
	this->image.Create("LoadTest.png");
	this->color = new Color(1, 1, 1, 0);
	this->mode = Fead::In;
	this->Stop(false);
}

Load::~Load()
{
	this->image.Finalize();
	delete this->color;
}

void Load::UpDate()
{
	if (this->mode == Fead::Out)
	{
		this->FeadOutUpDate();
	}
	else
	{
		this->FeadInUpDate();
	}
}

void Load::FeadInUpDate()
{
	if (this->color->alpha < 1.f)
	{
		this->color->alpha += 0.005f;
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
	}
}

void Load::FeadOutUpDate()
{
	if (this->color->alpha > 0)
	{
		this->color->alpha -= 0.01f;
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
		this->Kill();
		OGge->AllStop(false);
	}
}

void Load::PauseUpDate()
{
	if (this->color->alpha > 0)
	{
		this->color->alpha -= 0.005f;
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
	while (this->color->alpha <= 1.0)
	{
		if (time >= 60)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->draw = { 0,0,1920,1080 };
			this->draw.OffsetSize();
			this->src = { 0.f,0.f,this->image.GetTextureSize().x,this->image.GetTextureSize().y };
			this->src.OffsetSize();
			this->image.Draw(this->draw, this->src, *this->color);
		
			glfwSwapBuffers(OGge->window->GetWindow());
			
			this->color->alpha += 0.005f;
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
	this->src = { 0.f,0.f,this->image.GetTextureSize().x,this->image.GetTextureSize().y };
	this->src.OffsetSize();
	this->image.Draw(this->draw, this->src, *this->color);
}

void Load::SetFead(const Fead& fead)
{
	this->mode = fead;
	if (this->mode == Fead::Out)
	{

	}
	else
	{
		OGge->AllStop(true);
	}
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