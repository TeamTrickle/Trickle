#pragma once

#include "Object\Object.h"

class Map
{
public:
	Map();
	bool LoadMap(std::string _path);
	void MapRender();
	//void MapUpDate();
	void Finalize();
	int mapX, mapY;
	std::vector<std::vector<int>> _arr;
	std::vector<Box2D> chip;
	//std::vector<std::vector<Object>> hitBase;
	std::vector<std::vector<Box2D>> hitBase;
	Texture mapimg;
	Vec2 chipsize;
	bool MapHitCheck(CollisionBox &p);
private:
	const std::string _FilePath = "./data/map/";
	std::string chipimgname;
};