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
enum Format
{
	csv,
};

class Map : public TaskObject
{
	class Base : public GameObject
	{
		int arr;
		int* ID;
	public:
		Base();
		virtual ~Base();
		bool IDCheck(const int);
		bool ChipCheck(const int);
		void SetID(const int);
		void Setarr(const int);
		int Getarr() const;
		int* GetID() const;
	};
public:
	//描画するマップチップの数
	Vec2 mapSize;
	//描画マップ配列
	//元画像の画像位置
	std::vector<Box2D> chip;
	//オブジェクト情報
	std::vector<std::vector<Base>> hitBase;
	//使用画像情報
	Texture mapimg;
	//元画像の縦横サイズ
	Vec2 chipsize;
	//描画の縦横サイズ
	Vec2 DrawSize;
public:
	Map();
	virtual ~Map();
	typedef std::shared_ptr<Map> SP;
	static SP Create(std::string&, Format = csv, bool = true);
	bool LoadMap(std::string& _path, Format format);
	void UpDate();
	void Render2D();
	bool Finalize();
	//マップとの当たり判定
	bool HitCheck(GameObject &p, const int id);
	bool HitCheck(GameObject &p, const std::string name);
private:
	//ファイルパス
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
private:
	void ObjectCreateCheck(std::string&,int,int);
	
	Vec2 waterPos;		//水の生成位置保存用
public:
	Vec2 getWaterPos(); //水の生成位置を返す
};