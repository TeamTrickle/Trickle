#pragma once
#include "Sound.h"

class SoundManager
{
public:
	explicit SoundManager();				//コンストラクタ
	~SoundManager();						//デストラクタ
	void SetMaxVolume(const float value_);	//最大音量を登録する
	float GetMaxVolume() const;				//最大音量を返す
	void SetVolume(const Sound* s,			//選択されたSoundの音量を最大音量に適応した値に変える
					const float value_);
	void SetSound(Sound* s);				//Soundデータを登録する
	bool DeleteSound(const Sound* s);	//Soundデータを破棄する
	void AllDelete();						//Soundデータを全削除する
	void Application();						//最大音量を登録されているSoundすべてに適応させる
private:
	float MaxVolume;						//最大音量を格納する
	std::vector<Sound*> sounddata;			//適応させるSoundのデータを格納する
};