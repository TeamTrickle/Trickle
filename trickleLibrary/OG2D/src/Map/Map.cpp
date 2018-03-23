#include "Map.h"
Map::Map()
{
	this->mapX = 0;
	this->mapY = 0;
}

bool Map::LoadMap(std::string _path)
{
	std::ifstream ifs(this->_FilePath + _path, std::ios::in | std::ios::binary);
	if (!ifs)
	{
		std::cout << "マップ読み込みエラー" << std::endl;
		return false;
	}
	std::string _s;
	int _csize = 0;
	while (std::getline(ifs, _s))
	{
		if (_s.substr(0, 2) == "X ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapX;
		}
		if (_s.substr(0, 2) == "Y ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapY;
		}
		if (_s.substr(0, 2) == "C ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> _csize;
		}
		if (_s.substr(0, 2) == "N ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->chipimgname;
		}
		if (_s.substr(0, 3) == "CX ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->chipsize.x;
		}
		if (_s.substr(0, 3) == "CY ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->chipsize.y;
		}
	}
	this->chip.resize(_csize);
	this->_arr.resize(this->mapY);
	this->hitBase.resize(this->mapY);
	for (int i = 0; i < this->mapY; ++i)
	{
		this->_arr[i].resize(this->mapX);
		this->hitBase[i].resize(this->mapX);
	}
	ifs.close();
	mapimg.TextureCreate(chipimgname);
	int j = 0;
	std::ifstream ifs2(this->_FilePath + _path, std::ios::in | std::ios::binary);
	if (!ifs2)
	{
		std::cout << "マップ読み込みエラー" << std::endl;
		return false;
	}
	while (std::getline(ifs2, _s))
	{
		if (_s.substr(0, 8) == "MapChip ")
		{
			std::istringstream _is(_s.substr(8));
			for (int i = 0; i < this->mapX; ++i)
			{
				_is >> this->_arr[(mapY - 1) - j][i];
			}
			++j;
		}
	}
	for (int i = 0; i < _csize; ++i)
	{
		int x = (i % 10);
		int y = (i / 10);
		this->chip[i] = Box2D(x*32.f, y * 32.f, 32.f, 32.f);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapY; ++y)
	{
		for (int x = 0; x < this->mapX; ++x)
		{
			/*this->hitBase[y][x].position = { this->chipsize.x * x,(._height - chipsize.y) - this->chipsize.y * y };
			this->hitBase[y][x].collisionCube.hitBase = { this->hitBase[y][x].position.x,this->hitBase[y][x].position.y,this->chipsize.x,this->chipsize.y };
			this->hitBase[y][x].collisionCube.hitBase.OffsetSize();
			this->hitBase[y][x].collisionCube.angle = 0.f;*/
			/*this->hitBase[y][x].position = { this->chipsize.x * x,this->chipsize.y * y };
			this->hitBase[y][x].collisionCube.hitBase = { this->hitBase[y][x].position.x,this->hitBase[y][x].position.y,this->chipsize.x,this->chipsize.y };
			this->hitBase[y][x].collisionCube.hitBase.OffsetSize();
			this->hitBase[y][x].collisionCube.angle = 0.f;*/
			this->hitBase[y][x] = { x*this->chipsize.x,(this->mapY * this->chipsize.y - this->chipsize.y) - y*this->chipsize.y ,chipsize.x,chipsize.y };
			this->hitBase[y][x].OffsetSize();
		}

	}
	ifs2.close();
	return true;
}

void Map::MapRender()
{
	for (int y = 0; y < this->mapY; ++y)
	{
		for (int x = 0; x < this->mapX; ++x)
		{
			//mapimg.Draw(this->hitBase[y][x].collisionCube.hitBase, this->chip[this->_arr[(mapY - 1) - y][x]]);
			mapimg.Draw(this->hitBase[y][x], this->chip[this->_arr[(this->mapY - 1) - y][x]]);
		}
	}
}

void Map::Finalize()
{
	mapimg.Finalize();
}

bool Map::MapHitCheck(CollisionBox &p)
{
	for (int y = 0; y < this->mapY; ++y)
	{
		for (int x = 0; x < this->mapX; ++x)
		{
			if (this->_arr[y][x] != 0) {
				/*if (this->hitBase[y][x].collisionCube.hitBox(p))
				{
					return true;
				}*/
			}
		}
	}
	return false;
}