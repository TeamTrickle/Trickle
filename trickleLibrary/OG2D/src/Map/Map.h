#pragma once
//______________________________//
//|マップシステム               |//
//|履歴：2018/03/24金子翔       |//
//|____________________________|//
#include "Object\Object.h"

enum Format
{
	csv,
};

class Map
{
public:
	//描画するマップチップの数
	Vec2 mapSize;
	//描画マップ配列
	std::vector<std::vector<int>> _arr;
	//元画像の画像位置
	std::vector<Box2D> chip;
	//オブジェクト情報
	std::vector<std::vector<Object>> hitBase;
	//使用画像情報
	Texture mapimg;
	//元画像の縦横サイズ
	Vec2 chipsize;
	//描画の縦横サイズ
	Vec2 DrawSize;
public:
	Map();
	bool LoadMap(std::string _path);
	bool LoadMap(std::string _path, Format format);
	void MapRender();
	//void MapUpdate();
	void Finalize();
	//マップとの当たり判定
	bool MapHitCheck(Object &p);
private:
	//ファイルパス
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
};