#pragma once
//______________________________//
//|マップシステム               |//
//|履歴：2018/03/24金子翔       |//
//|____________________________|//
#include "Object\Object.h"
#include "OGSystem\Texture\Texture.h"
#include "OGSystem\OGsystem.h"
#include <cctype>
#include <algorithm>
/**
*enum Format
*ファイル形式
*/
enum Format
{
	//!	csv
	csv,
};
/**
*@brief	:ゲームに使用するマップclass
*/
class Map : public TaskObject
{
	class Base : public GameObject
	{
		//!	マップ番号
		int arr;
		//!	判定用ID
		int* ID;
	public:
		/**
		*@brief	:constructor
		*/
		Base();
		/**
		*@brief	:destructor
		*/
		virtual ~Base();
		/**
		*@brief	:登録IDが指定番号以下か調べる
		*@param	:int id 指定番号
		*@return:以下であればtrue
		*/
		bool IDCheck(const int id);
		/**
		*@brief	:登録番号が指定値と等しいか調べる
		*@param	:int chip 指定値
		*@return:同じならtrue
		*/
		bool ChipCheck(const int chip);
		/**
		*@brief	:IDを登録する
		*@param	:int id IDの値
		*/
		void SetID(const int id);
		/**
		*@brief	:マップ番号を指定する
		*@param	:int arr 指定値
		*/
		void Setarr(const int arr);
		/**
		*@brief	:登録されているマップ番号を返す
		*@return:int マップ番号の値
		*/
		int Getarr() const;
		/**
		*@brief	:登録されているIDを返す
		*@return:int* 未登録ならばnullptr
		*/
		int* GetID() const;
	};
private:
	//! ファイルパス
	const std::string _FilePath;
	//! 画像のファイル名
	std::string chipimgname;
	//!	描画マップ配列
	std::vector<Box2D> chip;
	//!	使用画像情報
	Texture mapimg;
	//!	元画像の縦横サイズ
	Vec2 chipsize;
	//!	スマートポインタ
	typedef std::shared_ptr<Map> SP;
public:
	//!	描画するマップチップの数
	Vec2 mapSize;
	//!	オブジェクト情報
	std::vector<std::vector<Base>> hitBase;
	//!	描画の縦横サイズ
	Vec2 DrawSize;
	/**
	*@brief	:constructor
	*/
	Map();
	/**
	*@brief	:更新処理
	*/
	void UpDate() override;
	/**
	*@brief	:描画処理
	*/
	void Render2D() override;
	/**
	*@brief	:解放処理
	*/
	bool Finalize();
	/**
	*@brief	:マップを外部ファイルから読み込む
	*@param	:string _path ファイル名
	*@param	:Format	format ファイル形式
	*@return:読み込みに成功すればtrue
	*/
	bool LoadMap(const std::string& _path, const Format& format);
public:
	/**
	*@brief	:destructor
	*/
	virtual ~Map();
	/**
	*@brief	:タスク生成
	*@param	:string path ファイル名
	*@param	:Format format ファイルフォーマット
	*/
	static SP Create(const std::string& path, const Format& format = csv);
	/**
	*@brief	:マップとの当たり判定
	*@param	:GameObject p 判定したいオブジェクト
	*@param	:int id 指定ID以下のもののみ判定を行う
	*@return:当たっていればtrue
	*/
	bool HitCheck(GameObject &p, const int id);
	/**
	*@brief	:マップとの当たり判定
	*@param	:GameObject p 判定したいオブジェクト
	*@param	:string name 指定名のみ判定を行う
	*@return:当たっていればtrue
	*/
	bool HitCheck(GameObject &p, const std::string& name);
private:
	/**
	*@brief	:読み込みに応じたオブジェクトの生成を行う
	*@param	:string name 読み込み名
	*@param	:int x 生成X座標
	*@param	:int y 生成Y座標
	*/
	void ObjectCreateCheck(const std::string& name,int x,int y);
	
	Vec2 waterPos;		//水の生成位置保存用
public:
	Vec2 getWaterPos(); //水の生成位置を返す
};