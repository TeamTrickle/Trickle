#include "LoadLogo.h"

Load::Load()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(OGge->window->GetWindow());
	__super::Init((std::string)"load");
	__super::SetDrawOrder(1.1f);
	this->image.Create("LoadTest.png");
	this->tex.Create("EffectTest.png");
	this->param = std::make_shared<Param>();
	this->param->animCnt = 0;
	this->param->on = true;
	/*std::thread thread(Render, &this->tex, this->param);
	thread.detach();*/
}

Load::~Load()
{
	this->Delete();
	this->image.Finalize();
	this->tex.Finalize();
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

void Load::Render(Texture* tex,std::shared_ptr<Param>& param)
{
	Texture* image = tex;
	while (param->on && !glfwWindowShouldClose(OGge->window->GetWindow()))
	{
		glMatrixMode(GL_MODELVIEW);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(OGge->camera->GetPos().x, OGge->camera->GetSize().x, OGge->camera->GetSize().y, OGge->camera->GetPos().y, -1.0f, 1.0f);
		std::cout << param->animCnt << std::endl;
		param->animCnt++;
		if (param->animCnt >= 100)
		{
			param->animCnt = 0;
		}
	/*	Box2D d(OGge->camera->GetSize().x - 400, OGge->camera->GetSize().y - 300, 256.f, 256.f);
		d.OffsetSize();
		Box2D s((param->animCnt / 10) * 256, 270.f, 256.f, 270.f);
		s.OffsetSize();*/
		Box2D d(0, 0, 1920, 1080);
		d.OffsetSize();
		Box2D s(0.f, 0.f, image->GetTextureSize().x, image->GetTextureSize().y);
		image->Draw(d, s);
		glfwSwapBuffers(OGge->window->GetWindow());
		glfwPollEvents();
	}
}

void Load::Delete()
{
	this->param->on = false;
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