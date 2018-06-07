#pragma once
#include "OGSystem\_OGsystem.h"

class Audio
{
public:
	Audio();
	~Audio();
	typedef std::shared_ptr<Audio> SP;
	static SP Create();
private:
	ALCdevice* device;
	ALCcontext*context;
public:
};
class Buffer
{
public:
	Buffer();
	explicit Buffer(const std::string& path_);
	~Buffer();
	ALuint id_;
	float nowTime;
	float GetTime() const;
	ALuint GetID() const;
	void Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const;
};
class Source
{
public:
	Source();
	~Source();
	ALuint id_;
	void BindBuffer(const Buffer& buffer_);
	void UnBindBuffer() const;
	ALuint GetID() const;
	void Play() const;
	void Stop() const;
	void Pause() const;
	void Volume(const float volume_) const;
	void Pitch(const float value_) const;
	void Looping(const bool loop_) const;
	bool isPlay() const;
	float currenttime() const;
	void queueBuffer(const Buffer& buffer_) const;
	ALuint UnqueueBuffer() const;
	int processed() const;
};
class Wav
{
public:
	struct Info {
		u_int id;
		u_int ch;
		u_int sample_rate;
		u_int bit;
		u_int size;
	};
	explicit Wav(const std::string& file);
	//チャンネル数を返す
	u_int channel() const;
	//データがステレオならtrueを返す
	bool isStereo() const;
	//サンプリングレートを返す
	u_int sampleRate() const;
	//データサイズを返す
	u_int size() const;
	//再生時間を返す
	float time() const;
	//波形データを返す
	const char* data() const;
	//wavの情報を取得
	static bool analyzeWavFile(Info& info, std::ifstream& fstr);
private:
	Info info;
	float time_;
	std::vector<char> data_;
	//指定バイト数のメモリの内容をint値にする
	static u_int getValue(const char* ptr, const u_int num);
	//wavの指定チャンクを探す
	static bool searchChunk(std::ifstream& fstr, const char* chunk);
	//チャンクのサイズを取得
	static u_int getChunkSize(std::ifstream& fstr);
};
class StreamWav {
public:
	explicit StreamWav(const std::string& file);
	bool isStereo() const;
	u_int sampleRate() const;
	void loop(const bool loop);
	//再生位置を先頭に戻す
	void toTop();
	bool isEnd() const;
	size_t GetlastSize() const;
	//再生バッファにデータを読み込む
	size_t read(std::vector<char>& buffer);
private:
	std::ifstream fstr_;
	Wav::Info info;
	size_t top_pos_;
	bool loop_;
	size_t last_size_;
	//ファイルからバッファへデータを読み込む
	size_t readData(std::vector<char>& buffer, const size_t offset, const size_t size);
};