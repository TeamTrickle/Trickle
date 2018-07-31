#pragma once
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
extern "C" {
#include <ffmpeg/libavutil/imgutils.h>
#include <ffmpeg/libavutil/frame.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavformat/avformat.h>
}
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
	AVFormatContext*			format_context = nullptr;
	AVCodecContext*				codec_context = nullptr;
	AVStream*					videoStream = nullptr;
	AVFrame*					frame = nullptr;
	AVPacket					packet;
	bool						deadFlag = false;
	Box2D						draw;
	float						videoFPS;
	float						delay;
	float						startTime;
	Color						texColor;
	Texture						tex;
	Time						timer;
};