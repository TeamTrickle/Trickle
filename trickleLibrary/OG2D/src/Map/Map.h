#pragma once
//______________________________//
//|マップシステム               |//
//|履歴：2018/03/24金子翔       |//
//|____________________________|//
#include "Object\Object.h"

class Map
{
public:
	Map();
	bool LoadMap(std::string _path);
	void MapRender();
	//void MapUpdate();
	void Finalize();
	//描画するマップチップの数
	//int mapX, mapY;
	Vec2 mapSize;
	//描画マップ配列
	std::vector<std::vector<int>> _arr;
	//元画像の画像位置
	std::vector<Box2D> chip;
	//オブジェクト情報
	std::vector<std::vector<Object>> hitBase;
	//std::vector<std::vector<Box2D>> hitBase;
	//使用画像情報
	Texture mapimg;
	//元画像の縦横サイズ
	Vec2 chipsize;
	//描画の縦横サイズ
	Vec2 DrawSize;
	//マップとの当たり判定
	bool MapHitCheck(Object &p);
private:
	//ファイルパス
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
};