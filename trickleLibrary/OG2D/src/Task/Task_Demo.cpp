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
	Vec2 winSize = OGge->window->GetSize();
	draw = Box2D(0, 0, (int)winSize.x, (int)winSize.y);
	return true;
}

void Demo::UpDate() {
	cv::Mat frame;
	cap >> frame;

	if (frame.empty()) {
		this->Kill();
	}

	Texture tmpTex;
	tmpTex.Create(frame);
	tmpTex.Draw(draw, Box2D(0, 0, frame.cols, frame.rows));
	tmpTex.Finalize();
}

bool Demo::Finalize()
{
	cap.release();
	return true;
}
