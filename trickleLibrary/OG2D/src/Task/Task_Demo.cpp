#include "Task_Demo.h"

Demo::SP Demo::Create(const std::string& fp_, bool flag_) {
	auto to = Demo::SP(new Demo());
	if (to)
	{
		to->me = to;
		if (flag_)
		{
			OGge->SetTaskObject(to);
		}
		if (!to->Initialize(fp_))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

bool Demo::Initialize(const std::string& demoVideoPath) {
	cap.open(demoVideoPath);
	if (!cap.isOpened()) {
		std::cout << "デモプレイファイルオープンエラー!" << std::endl;
		return false;
	}
	videoFPS = (float)cap.get(CV_CAP_PROP_FPS);
	delay = 0.3f / videoFPS;
	Vec2 winSize = OGge->window->GetSize();
	draw = Box2D(0, 0, (int)winSize.x, (int)winSize.y);
	texColor = Color(1.f, 1.f, 1.f, 1.f);
	timer.Start();
	return true;
}

void Demo::UpDate() {
	if (deadFlag) {
		Fadeout();
	}
	else if (timer.GetTime() - startTime >= delay) {
		cv::Mat frame;
		cap >> frame;
		if (frame.empty()) {
			deadFlag = true;
			return;
		}
		tex.Finalize();
		tex.Create(frame);
		startTime = timer.GetTime();
	}
	if (OGge->in->down(In::B1)) {
		deadFlag = true;
	}
	tex.Draw(draw, Box2D(0, 0, (int)tex.GetTextureSize().x, (int)tex.GetTextureSize().y), texColor);
}

void Demo::Fadeout() {
	texColor.alpha -= 0.01f;
	if (texColor.alpha <= 0.f) {
		this->Kill();
	}
}

bool Demo::Finalize()
{
	tex.Finalize();
	cap.release();
	return true;
}
