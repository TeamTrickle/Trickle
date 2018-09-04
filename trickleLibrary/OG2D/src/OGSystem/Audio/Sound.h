/**
*サウンドを読み込み、再生を行うclass
*一括読み込みをしている
*/
#pragma once
#include "Audio.h"
class Sound
{
private:
	//! bufferData
	std::shared_ptr<Buffer> buffer;
	//! sourceData
	std::shared_ptr<Source> source;
	//! ループ再生
	bool isloop_;
	//! ファイルパス
	const std::string filepath_;
	//! 音量
	float volume_;
public:
	/**
	*@brief	:constructor
	*/
	explicit Sound();
	/**
	*@brief	:constructor
	*@param	:string path_ ファイルのパス
	*@param	:bool loop ループ再生
	*/
	explicit Sound(const std::string& path_, const bool loop = false);
	/**
	*brief	:destructor
	*/
	~Sound();
	/**
	*@brief	:サウンドの読み込み
	*@param	:string path_ ファイル名
	*@param	:bool loop ループ再生
	*@return:bool 読み込み成功true
	*/
	bool create(const std::string& path_, const bool loop = false);
	/**
	*@brief	:サウンドの再生
	*/
	void play() const;
	/**
	*@brief	:サウンドの停止
	*/
	void stop() const;
	/**
	*@brief	:サウンドの一時停止
	*/
	void pause() const;
	/**
	*@brief	:サウンドの音量変更
	*@param	:float value_ 音量
	*/
	void volume(const float value_) const;
	/**
	*@brief	:サウンドのピッチ変更
	*@param	:floar value_ ピッチ
	*/
	void pitch(const float value_) const;
	/**
	*@brief	:サウンドのループ再生
	*@param	:bool loop_ ループの設定
	*/
	void looping(const bool loop_) const;
	/**
	*@brief	:サウンドが再生中か調べる
	*@return:再生中true
	*/
	bool isplay() const;
	/**
	*@brief	:現在の再生時間を返す
	*@return:現在の再生時間
	*/
	float currenttime() const;
	/**
	*@brief	:サウンドの時間を返す
	*@return:サウンドの時間
	*/
	float duration() const;
	/**
	*@brief	:最大音量を指定する
	*@param	:float maxVolume_ 最大音量
	*/
	void setVolume(float maxVolume_);
	/**
	*@brief	:設定されている最大音量を返す
	*@return:float 最大音量
	*/
	float getVolume() const;
};