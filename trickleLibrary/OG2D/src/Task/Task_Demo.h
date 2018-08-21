#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "OGSystem/OGsystem.h"
#include "OGSystem/Timer/glTimer.h"

/**
	@brief	ƒfƒ‚ƒvƒŒƒC‚ðÄ¶‚µ‚Ü‚·
	@date	2018-07-22
	@author	Heewon Kim (nabicore@icloud.com)
 */

class Demo : public TaskObject {

	void Fadeout();

public:
	explicit Demo() {}
	~Demo() { this->Finalize(); }

	bool Initialize(const std::string&);
	void UpDate() override;
	void Render2D() override;
	bool Finalize();

	typedef std::shared_ptr<Demo> SP;
	static SP Create(const std::string&, bool = true);

private:
	bool						deadFlag = false;
	cv::VideoCapture			cap;
	cv::Mat						frame;
	Box2D						draw;
	float						videoFPS;
	float						delay;
	float						startTime;
	Color						texColor;
	Texture						tex;
	Time						timer;
};