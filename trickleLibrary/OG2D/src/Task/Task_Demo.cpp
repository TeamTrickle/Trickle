#include "Task_Demo.h"
#include "Task_Title.h"
#include "Chara\Chara.h"

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
	av_register_all();
	format_context = nullptr;
	if (avformat_open_input(&format_context, demoVideoPath.c_str(), nullptr, nullptr)) {
		std::cout << "Demo: Failed to read video file!" << std::endl;
		return false;
	}

	if (avformat_find_stream_info(format_context, nullptr)) {
		std::cout << "Demo: Failed to find context!" << std::endl;
		return false;
	}

	for (int i = 0; i < (int)format_context->nb_streams; ++i) {
		if (format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = format_context->streams[i];
			break;
		}
	}

	if (!videoStream) {
		std::cout << "Demo: Failed to find stream!" << std::endl;
		return false;
	}

	AVCodec* codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
	if (!codec) {
		std::cout << "Demo: Failed to find codec!" << std::endl;
		return false;
	}

	codec_context = avcodec_alloc_context3(codec);
	if (!codec_context) {
		std::cout << "Demo: Failed to find codec context! " << std::endl;
		return false;
	}

	avcodec_parameters_to_context(codec_context, videoStream->codecpar);
	avcodec_open2(codec_context, codec, nullptr);
	frame = av_frame_alloc();
	packet = AVPacket();

	Vec2 winSize = OGge->window->GetSize();
	draw = Box2D(OGge->camera->GetPos(), OGge->camera->GetSize());
	draw.OffsetSize();
	texColor = Color(1.f, 1.f, 1.f, 1.f);
	timer.Start();

	__super::Init((std::string)"demo");
	__super::SetDrawOrder(1.1f);
	return true;
}

void Demo::UpDate() {
	if (av_read_frame(format_context, &packet) != 0) {
		
	}
}

void Demo::Render2D()
{
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
	avcodec_free_context(&codec_context);
	avformat_close_input(&format_context);
	auto title = OGge->GetTask<Title>((std::string)"title");
	if (title) title->SetPauseEveryChild(false);
	return true;
}
