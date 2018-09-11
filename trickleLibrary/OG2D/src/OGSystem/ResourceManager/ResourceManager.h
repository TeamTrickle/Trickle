/**
*リソースを生成、解放、管理を行うclass
*既存GameEngineを使用している場合は自動で生成される
*ここに登録しているものは自動でdeleteされるので自分でdeleteしないこと
*/
#pragma once
#include "OGSystem\Audio\Sound.h"
#include "OGSystem\Texture\Texture.h"

class ResourceManager
{
	//std::vector<S_Data> soundData;
	//! サウンドデータ
	std::vector<std::pair<std::string, Sound*>> soundData;
	//std::vector<T_Data> textureData;
	//! テクスチャデータ
	std::vector<std::pair<std::string, Texture*>> textureData;
public:
	/**
	*@brief	:存在するサウンドデータのポインタを登録する
	*@param :string name 登録名
	*@param	:Sound* sound サウンドデータのポインタ
	*/
	void SetSoundData(const std::string& name, Sound* sound);
	/**
	*@brief	:新しくサウンドを生成しデータに登録する
	*@param :string name 登録名
	*@param	:string path ファイルのパス
	*@return:bool 生成に成功でtrueを返す
	*/
	bool CreateSound(const std::string& name, const std::string& path);
	/**
	*@brief	:登録されているサウンドデータを返す
	*@param :string name　登録名
	*@return:Sound* 登録されているサウンドを返す
	*/
	Sound* GetSoundData(const std::string& name);
	/**
	*@brief	:存在するテクスチャデータのポインタを登録する
	*@param	:string 登録名
	*@param	:Texture* tex テクスチャデータのポインタ
	*/
	void SetTextureData(const std::string& name, Texture* tex);
	/**
	*@brief	:新しくテクスチャを生成しデータを登録する
	*@param	:string name 登録名
	*@param	:string path ファイルのパス
	*@return:bool 生成に成功でtrueを返す
	*/
	bool CreateTexture(const std::string& name, const std::string& path);
	/**
	*@brief	:登録されているテクスチャデータを返す
	*@param :string name 登録名
	*@return:Sound* 登録されているテクスチャを返す
	*/
	Texture* GetTextureData(const std::string& name);
	/**
	*@brief	:登録されているテクスチャデータを破棄,deleteする
	*@param	:string name 登録名
	*@return:bool 削除に成功でtrue
	*/
	bool DeleteTexture(const std::string& name);
	/**
	*@brief	:登録されているサウンドデータを破棄,deleteする
	*@param	:string name 登録名
	*@return:bool 削除に成功でtrue
	*/
	bool DeleteSound(const std::string& name);
	/**
	*@brief	:destructor 全データを破棄,deleteする
	*/
	virtual ~ResourceManager();
};