#include "Map.h"
Map::Map()
{
	this->chip.resize(30);
	this->chipimgname = "mapchip2.png";
	this->chipsize = { 256,256 };
	this->DrawSize = { 64,64 };
}

bool Map::LoadMap(std::string path_, Format format)
{
	if (Format::csv != format)
	{
		std::cout << "ファイル形式が読み込みに対応していません" << std::endl;
		return false;
	}
	//ファイルの読み込み(入力用式、バイナリデータでの読み込み)
	std::ifstream ifs(this->_FilePath + path_, std::ios::in | std::ios::binary);
	//読み込めなかった時のエラー処理
	if (!ifs) 
	{
		std::cout << "マップ読み込みエラー" << std::endl;
		return false; 
	}
	//読み込んだデータを入れておく変数
	std::string line;
	//改行か終了地点までの文字の文字列をlineにいれる
	std::getline(ifs, line);
	//文字列を操作するための入力class、直接アクセスできる
	std::istringstream _is(line);
	//一字書き込み変数
	std::string text;
	//_isに入っている文字列から','までの文字をtextにいれる
	std::getline(_is, text, ',');
	//textのデータを変数にいれる
 	(std::stringstream)text >> this->mapSize.x;
	std::getline(_is, text, ',');
	(std::stringstream)text >> this->mapSize.y;
	//_arrをmapyのサイズ分にサイズを変更する(配列化)
	this->_arr.resize(this->mapSize.y);
	this->hitBase.resize(this->mapSize.y);
	//_arr[]をmapxのサイズ分にサイズを変更する(二次配列化)
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->_arr[i].resize(this->mapSize.x);
		this->hitBase[i].resize(this->mapSize.x);
	}
	for (int y = 0; y < this->mapSize.y; ++y) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int x = 0; x < this->mapSize.x; ++x) {
			std::string  text;
			std::getline(ss_lt, text, ',');
			(std::stringstream)text >> this->_arr[y][x];
		}
	}
	ifs.close();
	//画像読み込み
	this->mapimg.TextureCreate(chipimgname);
	for (int i = 0; i < chip.size(); ++i)
	{
		//元画像チップの描画範囲の指定
		int x = (i % 20);
		int y = (i / 20);
		this->chip[i] = Box2D(x*chipsize.x, y * chipsize.y, chipsize.x, chipsize.y);
		this->chip[i].OffsetSize();
	}
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			//オブジェクトの生成
			this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), DrawSize, 0.f);
			switch (this->_arr[y][x])
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				//床
				this->hitBase[y][x].objectTag = "Floor";
				break;
			case 14:
			case 15:
			case 16:
			case 17:
				this->hitBase[y][x].objectTag = "Net";
				break;
				//case 3:
				//	this->hitBase[y][x].objectTag = "Net";
				//	break;
				//case 4:
				//	this->hitBase[y][x].objectTag = "Net";
				//	break;
			case 18:
			case 19:
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 21:
			case 22:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
				//case 8:
				//	this->hitBase[y][x].objectTag = "Ladder";
				//	break;
				//case 9:
				//this->hitBase[y][x].objectTag = "Switch";
				//break;
			default:
				break;
			}
		}
	}
	return true;
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
			switch (this->_arr[y][x])
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				//床
				this->hitBase[y][x].objectTag = "Floor";
				break;
			case 14:
			case 15:
			case 16:
			case 17:
				this->hitBase[y][x].objectTag = "Net";
				break;
			//case 3:
			//	this->hitBase[y][x].objectTag = "Net";
			//	break;
			//case 4:
			//	this->hitBase[y][x].objectTag = "Net";
			//	break;
			case 18:
			case 19:
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 21:
			case 22:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
			//case 8:
			//	this->hitBase[y][x].objectTag = "Ladder";
			//	break;
			//case 9:
				//this->hitBase[y][x].objectTag = "Switch";
				//break;
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
 	for  (int y = 0; y < this->mapSize.y; ++y)
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
	this->_arr.clear();
	this->hitBase.clear();
	this->chip.clear();
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