#include "Map.h"
Map::Map()
{
	
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
	//各値をテキストから格納
	while (std::getline(ifs, _s))
	{
		if (_s.substr(0, 2) == "X ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapSize.x;
		}
		if (_s.substr(0, 2) == "Y ")
		{
			std::istringstream _is(_s.substr(2));
			_is >> this->mapSize.y;
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
		if (_s.substr(0, 3) == "XS ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->DrawSize.x;
		}
		if (_s.substr(0, 3) == "YS ")
		{
			std::istringstream _is(_s.substr(3));
			_is >> this->DrawSize.y;
		}
	}
	//使用するマップチップの数
	this->chip.resize(_csize);
	//マップ配列の生成
	this->_arr.resize(this->mapSize.y);
	this->hitBase.resize(this->mapSize.y);
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->_arr[i].resize(this->mapSize.x);
		this->hitBase[i].resize(this->mapSize.x);
	}
	ifs.close();
	//画像読み込み
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
			for (int i = 0; i < this->mapSize.x; ++i)
			{
				//マップ番号を格納
				_is >> this->_arr[j][i];
			}
			++j;
		}
	}
	for (int i = 0; i < _csize; ++i)
	{
		//元画像チップの描画範囲の指定
		int x = (i % 20);
		int y = (i / 20);
		this->chip[i] = Box2D(x*32.f, y * 32.f, 32.f, 32.f);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//オブジェクトの生成
			this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
			/*if (this->_arr[y][x] != 0)
				this->hitBase[y][x].objectTag = "Floor";*/

			switch (this->_arr[y][x])
			{
			case 1:
				//床
				this->hitBase[y][x].objectTag = "Floor";
				break;
			case 2:
				this->hitBase[y][x].objectTag = "Net";
				break;
			case 3:
				this->hitBase[y][x].objectTag = "Net";
				break;
			case 4:
				this->hitBase[y][x].objectTag = "Net";
				break;
			case 6:
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 7:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
			case 8:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
			case 9:
				this->hitBase[y][x].objectTag = "Switch";
				break;
			default:
				break;
			}
		}

	}
	ifs2.close();
	return true;
}

void Map::MapRender()
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			Box2D draw(this->hitBase[y][x].position, this->DrawSize);
			draw.OffsetSize();
			mapimg.Draw(draw, this->chip[this->_arr[y][x]]);
		}
	}
}

void Map::Finalize()
{
	while (!this->_arr.empty())
		this->_arr.pop_back();
	mapimg.Finalize();
}

bool Map::MapHitCheck(Object &p)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//マップ番号０以外に当たったらTRUEを返す
			if (this->_arr[y][x] != 0) {
				if (this->hitBase[y][x].hit(p))
				{
					return true;
				}
			}
		}
	}
	return false;
}