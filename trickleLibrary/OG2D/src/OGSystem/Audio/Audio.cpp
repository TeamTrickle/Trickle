#include "Audio.h"
//---------------------------------
//@:Audioclass
//---------------------------------
Audio::Audio()
{
	std::cout << "Audio()" << std::endl;
	//アプリケーションをデバイスに接続させる
	//引数はデバイスの指定,NULLなら既定のデバイス
	this->device = alcOpenDevice(nullptr);
	if (!this->device)
	{
		std::cout << "デバイスの接続Error" << std::endl;
		return;
	}
	//コンテキストの生成
	this->context = alcCreateContext(this->device, nullptr);
	if (!this->context)
	{
		std::cout << "コンテキスト生成Error" << std::endl;
		return;
	}
	//操作するコンテキストの選択
	if (alcMakeContextCurrent(this->context) == ALC_FALSE)
	{
		std::cout << "操作コンテキストの選択Error" << std::endl;
		return;
	}
}
Audio::~Audio()
{
	std::cout << "~Audio()" << std::endl;
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}
Audio::SP Audio::Create()
{
	return Audio::SP(new Audio());
}
//---------------------------------
//@:Bufferclass
//---------------------------------
Audio::Buffer::Buffer()
{
	std::cout << "Buffer()" << std::endl;
	//バッファを１つ生成
	alGenBuffers(1, &this->id_);
	//現在進行時間を0にする
	this->nowTime = 0.f;
}
Audio::Buffer::Buffer(std::string& path_)
{
	std::cout << "Buffer(string)" << std::endl;
	//バッファを１つ生成
	alGenBuffers(1, &this->id_);
	//Wavファイルの読み込み
	Wav wav_data(path_);
	//経過時間を確認
	this->nowTime = wav_data.time();
	// 波形データをバッファにセット
	alBufferData(id_, wav_data.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, wav_data.data(), wav_data.size(), wav_data.sampleRate());
}
Audio::Buffer::~Buffer()
{
	std::cout << "~Buffer()" << std::endl;
	//バッファの削除
	alDeleteBuffers(1, &this->id_);
}
float Audio::Buffer::GetTime() const
{
	std::cout << "GetTime()" << std::endl;
	//進行時間を返す
	return this->nowTime;
}
ALuint Audio::Buffer::GetID() const
{
	std::cout << "GetID()" << std::endl;
	//バッファに登録してあるIDを返す
	return this->id_;
}
void Audio::Buffer::Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const
{
	std::cout << "Bint(bool,void*,u_int,u_int)" << std::endl;
	//波形データをバッファにセット
	alBufferData(this->id_, stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, rate);
}
//---------------------------------
//@:Sourceclass
//---------------------------------
Audio::Source::Source()
{
	std::cout << "Source()" << std::endl;
	//ソースを１つ生成する
	alGenSources(1, &this->id_);
}
Audio::Source::~Source()
{
	std::cout << "~Source()" << std::endl;
	//波形データを解除する
	this->UnBindBuffer();
	//ソースを削除する
	alDeleteSources(1, &this->id_);
}
void Audio::Source::BindBuffer(const Buffer& burrer_)
{
	std::cout << "BindBuffer()" << std::endl;
	//ソースにバッファを指定する
	alSourcei(this->id_, AL_BUFFER, burrer_.GetID());
}
void Audio::Source::UnBindBuffer() const
{
	std::cout << "UnBindBuffer()" << std::endl;
	//ソースのバッファを解除する
	alSourcei(this->id_, AL_BUFFER, 0);
}
ALuint Audio::Source::GetID() const
{
	std::cout << "GetID()" << std::endl;
	//ソースのIDを返す
	return this->id_;
}
void Audio::Source::Play() const
{
	std::cout << "Play()" << std::endl;
	//再生する
	alSourcePlay(this->id_);
}
void Audio::Source::Stop() const
{
	std::cout << "Stop()" << std::endl;
	//止める
	alSourceStop(this->id_);
}
void Audio::Source::Pause() const
{
	std::cout << "Pause()" << std::endl;
	//一時停止する
	alSourcePause(this->id_);
}
void Audio::Source::Volume(const float volume_) const
{
	std::cout << "Volume(float)" << std::endl;
	//音量の変更
	alSourcef(this->id_, AL_GAIN, volume_);
}
void Audio::Source::Pitch(const float value_) const
{
	std::cout << "Pitch(float)" << std::endl;
	//ピッチの変更
	alSourcef(this->id_, AL_PITCH, value_);
}
void Audio::Source::Looping(const bool loop_) const
{
	std::cout << "Looping(bool)" << std::endl;
	//TRUEで終了時最初の位置に戻る
	alSourcei(this->id_, AL_LOOPING, loop_ ? AL_TRUE : AL_FALSE);
}
bool Audio::Source::isPlay() const
{
	std::cout << "isPlay()" << std::endl;
	//現在の状態を返す
	ALint state;
	alGetSourcei(this->id_, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
float Audio::Source::currenttime() const
{
	//現在の再生時間を返す
	ALfloat nowtime;
	alGetSourcef(this->id_, AL_SEC_OFFSET, &nowtime);
	return nowtime;
}
void Audio::Source::queueBuffer(const Buffer& buffer_) const
{
	std::cout << "queueBuffer(Buffer)" << std::endl;
	ALuint buffers = buffer_.GetID();
	//バッファネームのキューを作成
	alSourceQueueBuffers(this->id_, 1, &buffers);
}
ALuint Audio::Source::UnqueueBuffer() const
{
	std::cout << "UnqueueBuffer()" << std::endl;
	ALuint buffers;
	//キューからバッファを除去する
	alSourceUnqueueBuffers(this->id_, 1, &buffers);
	return buffers;
}
int Audio::Source::processed() const
{
	std::cout << "processed()" << std::endl;
	int pro_;
	//再生済みのバッファ数を返す
	alGetSourcei(this->id_, AL_BUFFERS_PROCESSED, &pro_);
	return pro_;
}
//---------------------------------
//@:Wavclass
//---------------------------------
Audio::Wav::Wav(const std::string& file)
{
	std::ifstream fstr(file, std::ios::binary);
	if (!fstr)
	{
		std::cout << "ファイル読み込みエラー" << std::endl;
		throw;
	}
	// ファイル情報を解析
	if (!Audio::Wav::analyzeWavFile(this->info, fstr))
	{
		std::cout << "Wavファイル読み込みエラー: " << file << std::endl;
		throw;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
		std::cout << "Wavファイルのフォーマットエラー" << std::endl;
		throw;
	}
	// 再生時間(秒)
	this->time_ = this->info.size / this->info.ch / 2.0f / this->info.sample_rate;
	// データ読み込み
	data_.resize(this->info.size);
	Audio::Wav::searchChunk(fstr, "data");
	fstr.seekg(4, fstr.cur);
	fstr.read(&data_[0], info.size);
}
u_int Audio::Wav::channel() const
{
	return this->info.ch;
}
bool Audio::Wav::isStereo() const
{
	return this->info.ch == 2;
}
u_int Audio::Wav::sampleRate() const
{
	return this->info.sample_rate;
}
u_int Audio::Wav::size() const
{
	return this->info.size;
}
float Audio::Wav::time() const
{
	return this->time_;
}
const char* Audio::Wav::data() const
{
	return &this->data_[0];
}
u_int Audio::Wav::getValue(const char* ptr, const u_int num)
{
	u_int value = 0;
	for (u_int i = 0; i < num; ++i, ++ptr)
	{
		// TIPS:int型より小さい型はint型に拡張されてから計算されるので8bit以上シフトしても問題ない
		value = value + (static_cast<u_char>(*ptr) << (i * 8));
	}
#ifdef __BIG_ENDIAN__
	value = (value << 24) | ((value << 8) & 0xff0000) | ((value >> 8) & 0xff00) | (value >> 24);
#endif
	return value;
}
bool Audio::Wav::searchChunk(std::ifstream& fstr, const char* chunk)
{
	//チャンク開始位置
	int WAV_START_SIZE = 12;
	fstr.seekg(WAV_START_SIZE, fstr.beg);
	// チャンクの並びは不定なので、常にファイルの先頭から探す
	while (1)
	{
		char tag[4];
		fstr.read(tag, 4);
		if (!std::strncmp(tag, chunk, 4))
		{
			return true;
		}
		// 次のチャンクへ
		char data[4];
		fstr.read(data, 4);
		u_int chunk_size = Audio::Wav::getValue(data, 4);
		fstr.seekg(chunk_size, fstr.cur);
		if (fstr.eof())
		{
			break;
		}
	}
	return false;
}
u_int Audio::Wav::getChunkSize(std::ifstream& fstr)
{
	char data[4];
	fstr.read(data, 4);
	return Audio::Wav::getValue(data, 4);
}
bool Audio::Wav::analyzeWavFile(Info& info, std::ifstream& fstr)
{
	// ファイルがwav形式か調べる
	enum
	{
		WAV_HEADER_SIZE = 12
	};
	char header[WAV_HEADER_SIZE];
	fstr.read(header, WAV_HEADER_SIZE);
	if (std::strncmp(&header[0], "RIFF", 4))
	{
		std::cout << "このファイルはRIFFではありません" << std::endl;
		return false;
	}
	if (std::strncmp(&header[8], "WAVE", 4))
	{
		std::cout << "このファイルはWaveではありません" << std::endl;
		return false;
	}
	enum
	{
		// fmtチャンク内のデータ位置
		WAV_ID = 0,
		WAV_CH = WAV_ID + 2,
		WAV_SAMPLE_RATE = WAV_CH + 2,
		WAV_BPS = WAV_SAMPLE_RATE + 4,
		WAV_BLOCK_SIZE = WAV_BPS + 4,
		WAV_BIT = WAV_BLOCK_SIZE + 2,
	};
	// fmtチャンクを探してデータ形式を取得
	if (!searchChunk(fstr, "fmt "))
	{
		std::cout << "fmtチャンクが存在しません" << std::endl;
		return false;
	}
	u_int chunk_size = Audio::Wav::getChunkSize(fstr);
	std::vector<char> chunk(chunk_size);
	fstr.read(&chunk[0], chunk_size);
	info.id = Audio::Wav::getValue(&chunk[WAV_ID], 2);
	info.ch = Audio::Wav::getValue(&chunk[WAV_CH], 2);
	info.sample_rate = Audio::Wav::getValue(&chunk[WAV_SAMPLE_RATE], 4);
	info.bit = Audio::Wav::getValue(&chunk[WAV_BIT], 2);
	// dataチャンクを探してデータ長を取得
	if (!searchChunk(fstr, "data"))
	{
		std::cout << "dataチャンクが存在しません" << std::endl;
		return false;
	}
	info.size = Audio::Wav::getChunkSize(fstr);
	return true;
}
//---------------------------------
//@:StreamWavclass
//---------------------------------
Audio::StreamWav::StreamWav(const std::string& file) :
	fstr_(file, std::ios::binary),
	loop_(false)
{
	if (!this->fstr_) throw "ファイルを開くことができません";
	// ファイル情報を解析
	if (!Wav::analyzeWavFile(this->info, this->fstr_))
	{
		return;
	}
	if ((this->info.id != 1) || (this->info.bit != 16))
	{
		// IDが１で量子化ビット数が16以外は扱わない
		std::cout << "Wavファイルフォーマットエラー" << std::endl;
		return;
	}
	this->last_size_ = this->info.size;
	// データの先頭位置を覚えておく
	this->top_pos_ = static_cast<size_t>(this->fstr_.tellg());
}
bool Audio::StreamWav::isStereo() const
{
	return this->info.ch == 2;
}
u_int Audio::StreamWav::sampleRate() const
{
	return this->info.sample_rate;
}
size_t Audio::StreamWav::GetlastSize() const
{
	return this->last_size_;
}
void Audio::StreamWav::loop(const bool loop)
{
	this->loop_ = loop;
}
void Audio::StreamWav::toTop()
{
	this->fstr_.seekg(this->top_pos_, this->fstr_.beg);
	this->last_size_ = this->info.size;
}
bool Audio::StreamWav::isEnd() const
{
	return last_size_ == 0;
}
size_t Audio::StreamWav::read(std::vector<char>& buffer)
{
	size_t remain_size = buffer.size();
	// ループしない場合、残りの中途半端なサイズを読み込んで終了
	if (!this->loop_ && (this->last_size_ < remain_size))
	{
		remain_size = this->last_size_;
	}
	size_t offset = 0;
	size_t total_read_size = 0;
	// ループ再生の場合はバッファを満たすまでデータを読み込む
	while (remain_size > 0) {
		size_t read_size = Audio::StreamWav::readData(buffer, offset, remain_size);

		total_read_size += read_size;
		remain_size -= read_size;
		this->last_size_ -= read_size;
		offset += read_size;
		if (this->loop_ && !this->last_size_)
		{
			Audio::StreamWav::toTop();
		}
	}
	return total_read_size;
}
size_t Audio::StreamWav::readData(std::vector<char>& buffer, const size_t offset, const size_t size)
{
	size_t read_size = (size < this->last_size_) ? size : this->last_size_;
	this->fstr_.read(&buffer[offset], read_size);
	return read_size;
}