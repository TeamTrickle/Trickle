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
	videoFPS = (int)cap.get(CV_CAP_PROP_FPS) * 0.5f;
	Vec2 winSize = OGge->window->GetSize();
	draw = Box2D(0, 0, (int)winSize.x, (int)winSize.y);
	return true;
}

void Demo::UpDate() {
	if (frameCnt >= videoFPS) {
		tex.Finalize();
		cv::Mat frame;
		cap >> frame;

		if (frame.empty()) {
			this->Kill();
		}

		frameCnt = 0;
		tex.Create(frame);
	}
	tex.Draw(draw, Box2D(0, 0, (int)tex.GetTextureSize().x, (int)tex.GetTextureSize().y));
	frameCnt += 1;
}

bool Demo::Finalize()
{
	cap.release();
	return true;
}
