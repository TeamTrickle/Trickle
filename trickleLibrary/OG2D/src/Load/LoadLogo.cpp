#include "LoadLogo.h"

Load::Load()
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(OGge->window->GetWindow());*/
	__super::Init((std::string)"load");
	__super::SetDrawOrder(1.1f);
	this->image.Create("LoadTest.png");
	this->tex.Create("EffectTest.png");
	this->color = new Color(1, 1, 1, 0);
}

Load::~Load()
{
	this->image.Finalize();
	this->tex.Finalize();
	delete this->color;
}

void Load::UpDate()
{
	if (this->color->alpha > 0)
	{
		this->color->alpha -= 0.05f;
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
	OGge->camera->CameraUpdate();
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
			
			this->color->alpha += 0.01f;
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

Load::SP Load::Create(bool flag)
{
	Load::SP to = Load::SP(new Load());
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