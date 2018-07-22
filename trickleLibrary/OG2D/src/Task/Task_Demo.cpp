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
	return true;
}

void Demo::UpDate() {
	cv::Mat frame;
	cap >> frame;

	if (frame.empty()) {
		return;
	}

	cv::imshow("Frame", frame);
	char c = (char)cv::waitKey(25);
	if (c == 27) {
		return;
	}
}

bool Demo::Finalize()
{
	cap.release();
	cv::destroyAllWindows();
	return true;
}
