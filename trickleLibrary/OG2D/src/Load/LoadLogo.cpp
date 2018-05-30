#include "LoadLogo.h"

Load::Load()
{
	__super::Init((std::string)"load");
	__super::SetDrawOrder(1.1f);
	this->image.Create("LoadTest.png");
}

Load::~Load()
{
	this->image.Finalize();
}

void Load::UpDate()
{

}

void Load::Draw()
{
	this->draw = { OGge->camera->GetPos(),OGge->camera->GetSize() };
	this->draw.OffsetSize();
	this->src = { 0.f,0.f,this->image.GetTextureSize().x,this->image.GetTextureSize().y };
	this->src.OffsetSize();
	this->image.Draw(this->draw, this->src);
	glfwSwapBuffers(OGge->window->GetWindow());
}

void Load::Render2D()
{
	this->draw = { OGge->camera->GetPos(),OGge->camera->GetSize() };
	this->draw.OffsetSize();
	this->src = { 0.f,0.f,this->image.GetTextureSize().x,this->image.GetTextureSize().y };
	this->src.OffsetSize();
	this->image.Draw(this->draw, this->src);
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