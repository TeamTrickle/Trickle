#include "Audio.h"
//---------------------------------
//@:Audioclass
//---------------------------------
Audio::Audio()
{
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
Buffer::Buffer()
{
	//バッファを１つ生成
	alGenBuffers(1, &this->id_);
	//現在進行時間を0にする
	this->nowTime = 0.f;
}
Buffer::Buffer(const std::string& path_)
{
	//バッファを１つ生成
	alGenBuffers(1, &this->id_);
	//Wavファイルの読み込み
	Wav wav_data(path_);
	//経過時間を確認
	this->nowTime = wav_data.time();
	// 波形データをバッファにセット
	alBufferData(id_, wav_data.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, wav_data.data(), wav_data.size(), wav_data.sampleRate());
}
Buffer::~Buffer()
{
	//バッファの削除
	alDeleteBuffers(1, &this->id_);
}
float Buffer::GetTime() const
{
	//進行時間を返す
	return this->nowTime;
}
ALuint Buffer::GetID() const
{
	//バッファに登録してあるIDを返す
	return this->id_;
}
void Buffer::Bind(const bool stereo, const void* data, const u_int size, const u_int rate) const
{
	//波形データをバッファにセット
	alBufferData(this->id_, stereo ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, rate);
}
//---------------------------------
//@:Sourceclass
//---------------------------------
Source::Source()
{
	//ソースを１つ生成する
	alGenSources(1, &this->id_);
}
Source::~Source()
{
	//波形データを解除する
	this->UnBindBuffer();
	//ソースを削除する
	alDeleteSources(1, &this->id_);
}
void Source::BindBuffer(const Buffer& burrer_)
{
	//ソースにバッファを指定する
	alSourcei(this->id_, AL_BUFFER, burrer_.GetID());
}
void Source::UnBindBuffer() const
{
	//ソースのバッファを解除する
	alSourcei(this->id_, AL_BUFFER, 0);
}
ALuint Source::GetID() const
{
	//ソースのIDを返す
	return this->id_;
}
void Source::Play() const
{
	//再生する
	alSourcePlay(this->id_);
}
void Source::Stop() const
{
	//止める
	alSourceStop(this->id_);
}
void Source::Pause() const
{
	//一時停止する
	alSourcePause(this->id_);
}
void Source::Volume(const float volume_) const
{
	//音量の変更
	alSourcef(this->id_, AL_GAIN, volume_);
}
void Source::Pitch(const float value_) const
{
	//ピッチの変更
	alSourcef(this->id_, AL_PITCH, value_);
}
void Source::Looping(const bool loop_) const
{
	//TRUEで終了時最初の位置に戻る
	alSourcei(this->id_, AL_LOOPING, loop_ ? AL_TRUE : AL_FALSE);
}
bool Source::isPlay() const
{
	//現在の状態を返す
	ALint state;
	alGetSourcei(this->id_, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}
float Source::currenttime() const
{
	//現在の再生時間を返す
	ALfloat nowtime;
	alGetSourcef(this->id_, AL_SEC_OFFSET, &nowtime);
	return nowtime;
}
void Source::queueBuffer(const Buffer& buffer_) const
{
	ALuint buffers = buffer_.GetID();
	//バッファネームのキューを作成
	alSourceQueueBuffers(this->id_, 1, &buffers);
}
ALuint Source::UnqueueBuffer() const
{
	ALuint buffers;
	//キューからバッファを除去する
	alSourceUnqueueBuffers(this->id_, 1, &buffers);
	return buffers;
}
int Source::processed() const
{
	int pro_;
	//再生済みのバッファ数を返す
	alGetSourcei(this->id_, AL_BUFFERS_PROCESSED, &pro_);
	return pro_;
}
//---------------------------------
//@:Wavclass
//---------------------------------
Wav::Wav(const std::string& file)
{
	std::ifstream fstr(file, std::ios::binary);
	if (!fstr)
	{
		std::cout << "ファイル読み込みエラー" << std::endl;
		throw;
	}
	// ファイル情報を解析
	if (!Wav::analyzeWavFile(this->info, fstr))
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
	Wav::searchChunk(fstr, "data");
	fstr.seekg(4, fstr.cur);
	fstr.read(&data_[0], info.size);
}
u_int Wav::channel() const
{
	return this->info.ch;
}
bool Wav::isStereo() const
{
	return this->info.ch == 2;
}
u_int Wav::sampleRate() const
{
	return this->info.sample_rate;
}
u_int Wav::size() const
{
	return this->info.size;
}
float Wav::time() const
{
	return this->time_;
}
const char* Wav::data() const
{
	return &this->data_[0];
}
u_int Wav::getValue(const char* ptr, const u_int num)
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
bool Wav::searchChunk(std::ifstream& fstr, const char* chunk)
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
		u_int chunk_size = Wav::getValue(data, 4);
		fstr.seekg(chunk_size, fstr.cur);
		if (fstr.eof())
		{
			break;
		}
	}
	return false;
}
u_int Wav::getChunkSize(std::ifstream& fstr)
{
	char data[4];
	fstr.read(data, 4);
	return Wav::getValue(data, 4);
}
bool Wav::analyzeWavFile(Info& info, std::ifstream& fstr)
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
	u_int chunk_size = Wav::getChunkSize(fstr);
	std::vector<char> chunk(chunk_size);
	fstr.read(&chunk[0], chunk_size);
	info.id = Wav::getValue(&chunk[WAV_ID], 2);
	info.ch = Wav::getValue(&chunk[WAV_CH], 2);
	info.sample_rate = Wav::getValue(&chunk[WAV_SAMPLE_RATE], 4);
	info.bit = Wav::getValue(&chunk[WAV_BIT], 2);
	// dataチャンクを探してデータ長を取得
	if (!searchChunk(fstr, "data"))
	{
		std::cout << "dataチャンクが存在しません" << std::endl;
		return false;
	}
	info.size = Wav::getChunkSize(fstr);
	return true;
}
//---------------------------------
//@:StreamWavclass
//---------------------------------
StreamWav::StreamWav(const std::string& file) :
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
bool StreamWav::isStereo() const
{
	return this->info.ch == 2;
}
u_int StreamWav::sampleRate() const
{
	return this->info.sample_rate;
}
size_t StreamWav::GetlastSize() const
{
	return this->last_size_;
}
void StreamWav::loop(const bool loop)
{
	this->loop_ = loop;
}
void StreamWav::toTop()
{
	this->fstr_.seekg(this->top_pos_, this->fstr_.beg);
	this->last_size_ = this->info.size;
}
bool StreamWav::isEnd() const
{
	return last_size_ == 0;
}
size_t StreamWav::read(std::vector<char>& buffer)
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
		size_t read_size = StreamWav::readData(buffer, offset, remain_size);

		total_read_size += read_size;
		remain_size -= read_size;
		this->last_size_ -= read_size;
		offset += read_size;
		if (this->loop_ && !this->last_size_)
		{
			StreamWav::toTop();
		}
	}
	return total_read_size;
}
size_t StreamWav::readData(std::vector<char>& buffer, const size_t offset, const size_t size)
{
	size_t read_size = (size < this->last_size_) ? size : this->last_size_;
	this->fstr_.read(&buffer[offset], read_size);
	return read_size;
}