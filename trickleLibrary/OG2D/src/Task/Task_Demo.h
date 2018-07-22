#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "OGSystem/OGsystem.h"

/**
	@brief	ƒfƒ‚ƒvƒŒƒC‚ğÄ¶‚µ‚Ü‚·
	@date	2018-07-22
	@author	Heewon Kim (nabicore@icloud.com)
 */

class Demo : public TaskObject {

public:
	explicit Demo() {}
	virtual ~Demo() {}

	bool Initialize(const std::string&);
	void UpDate() override;
	bool Finalize();

	typedef std::shared_ptr<Demo> SP;
	static SP Create(const std::string&, bool = true);

private:
	cv::VideoCapture			cap;
	Box2D						draw;
};