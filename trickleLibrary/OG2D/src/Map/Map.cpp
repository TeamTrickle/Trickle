#include "Map.h"
#include "Player\Player.h"
#include "Bucket\bucket.h"
#include "Gimmick\NO_MOVE\Switch.h"
#include "Gimmick\NO_MOVE\TimeSign.h"
#include "Goal\Goal.h"
#include "Paint\Paint.h"

#include "UI/GoalDirectionUI.h"
Map::Map()
	:_FilePath("./data/map/")
{
	this->chip.resize(45);
	this->chipimgname = "mapchip2.png";
	this->chipsize = { 256,256 };
	this->DrawSize = { 64,64 };
	__super::Init((std::string)"map");
	__super::SetDrawOrder(0.1f);
}

Map::~Map()
{
	this->Finalize();
	if (this->GetNextTask() && !OGge->GetDeleteEngine())
	{

	}
}

bool Map::LoadMap(const std::string& path_, const Format& format)
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
	this->hitBase.resize((int)this->mapSize.y);
	//_arr[]をmapxのサイズ分にサイズを変更する(二次配列化)
	for (int i = 0; i < this->mapSize.y; ++i)
	{
		this->hitBase[i].resize((int)this->mapSize.x);
	}
	for (int y = 0; y < this->mapSize.y; ++y) {
		std::string lineText;
		std::getline(ifs, lineText);
		std::istringstream  ss_lt(lineText);
		for (int x = 0; x < this->mapSize.x; ++x) {
			std::string  text;
			std::getline(ss_lt, text, ',');
			if (text == "\r")
			{
				continue;
			}
			if (text.find("\r") != std::string::npos)
			{
				text.erase(text.find("\r"));
			}
			//文字列が数字のみかを検索
			if (std::all_of(text.cbegin(), text.cend(), isdigit))
			{
				//番号をそのまま格納
				int num = 0;
				(std::stringstream)text >> num;
				this->hitBase[y][x].Setarr(num);
			}
			else
			{
				//文字列に応じたオブジェクトを生成する
				this->ObjectCreateCheck(text, x, y);
				//その場所の番号は0としておく。
				this->hitBase[y][x].Setarr(0);
			}
		}
	}
	ifs.close();
	//画像読み込み
	this->mapimg.Create(chipimgname);
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
			if (this->hitBase[y][x].Getarr())
			{
				this->hitBase[y][x].CreateObject(Cube, Vec2(this->DrawSize.x * x, this->DrawSize.y * y), this->DrawSize, 0.0f);
			}
			switch (this->hitBase[y][x].Getarr())
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
				this->hitBase[y][x].SetID(0);
				break;
			case 14:
				this->hitBase[y][x].Scale.y = 12.0f;		//仮処理、上方向金網のみ当たり判定の高さを20に制限
				this->hitBase[y][x].SetID(1);
				break;
			case 15:	//bug
				//this->hitBase[y][x].position.x += 64 - 12;
				this->hitBase[y][x].Scale.x = 12.f;
				this->hitBase[y][x].SetID(1);
				break;
			case 16:	//bug
				//this->hitBase[y][x].position.y += 64 - 12;
				this->hitBase[y][x].Scale.y = 12.f;
				this->hitBase[y][x].SetID(1);
				break;
			case 17:	//bug
				this->hitBase[y][x].Scale.x = 12.f;
				this->hitBase[y][x].SetID(1);
				this->hitBase[y][x].objectTag = "Net";
				break;
			case 18:
			case 19:
			case 20:
			case 21:
				this->hitBase[y][x].SetID(0);
				this->hitBase[y][x].objectTag = "Soil";
				break;
			case 22:
				this->hitBase[y][x].objectTag = "LadderTop";
				break;
			case 23:
				this->hitBase[y][x].objectTag = "Ladder";
				break;
			case 24:
				this->hitBase[y][x].objectTag = "Ladder";
				this->hitBase[y][x].SetID(0);
				break;
			case 25:
			case 26:
			case 27:
				this->hitBase[y][x].SetID(1);
				break;
			case 28:
			case 29:
			case 30:
				this->hitBase[y][x].objectTag = "Kanetuki";
				this->hitBase[y][x].SetID(1);
				break;
			case 31:
			case 32:
			case 33:
				this->hitBase[y][x].objectTag = "Seihyouki";
				this->hitBase[y][x].SetID(1);
				break;
			case 37:
				this->hitBase[y][x].objectTag = "Kanetuki";
				this->hitBase[y][x].SetID(1);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

void Map::ObjectCreateCheck(const std::string& text, int x_index, int y_index)
{
	if (text == "p")
	{
		auto player = Player::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		player->SetTexture(rm->GetTextureData((std::string)"playerTex"));
		return;
	};
	if (text == "b")
	{
		auto bucket = Bucket::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		return;
	}
	if (text == "g")
	{
		auto goal = Goal::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		goal->SetTexture(rm->GetTextureData((std::string)"goalTex"));
		auto goalDirection = GoalDirection::Create(goal);
		goalDirection->SetTextrue(rm->GetTextureData((std::string)"goalDirectionTex"), rm->GetTextureData((std::string)"arrowflowerTex"));
		return;
	}
	if (text == "gred")
	{
		auto goal = Goal::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		goal->SetTexture(rm->GetTextureData((std::string)"goalTex"));
		goal->SetColor(Paint::PaintColor::Red);
		auto goalDirection = GoalDirection::Create(goal);
		goalDirection->SetTextrue(rm->GetTextureData((std::string)"goalDirectionTex"), rm->GetTextureData((std::string)"arrowflowerTex"));
		return;
	}
	if (text == "gblue")
	{
		auto goal = Goal::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		goal->SetTexture(rm->GetTextureData((std::string)"goalTex"));
		goal->SetColor(Paint::PaintColor::Blue);
		auto goalDirection = GoalDirection::Create(goal);
		goalDirection->SetTextrue(rm->GetTextureData((std::string)"goalDirectionTex"), rm->GetTextureData((std::string)"arrowflowerTex"));
		return;
	}
	if (text == "gpurple")
	{
		auto goal = Goal::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index));
		goal->SetTexture(rm->GetTextureData((std::string)"goalTex"));
		goal->SetColor(Paint::PaintColor::Purple);
		auto goalDirection = GoalDirection::Create(goal);
		goalDirection->SetTextrue(rm->GetTextureData((std::string)"goalDirectionTex"), rm->GetTextureData((std::string)"arrowflowerTex"));
		return;
	}
	if (text == "t") 
	{
		auto inTimer = TimeSign::Create("frame.png", Box2D(this->DrawSize.x * x_index, this->DrawSize.y * y_index - 64.f, 144.f, 128.f), true);
		inTimer->setAtlas("number.png", Box2D(0, 64, 64, 64), Box2D(21.f, 40.f, 19.5f, 40.f));
		inTimer->setComma(Box2D(25, 40, 8, 14), Box2D(640, 64, 40, 64), Box2D(680, 64, 40, 64));
		inTimer->setAtlasAngle(-10.f);
		return;
	}
	if (text == "paintred")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Red);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
	if (text == "paintblue")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Blue);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
	if (text == "paintpurple")
	{
		auto paint = Paint::Create(Vec2(this->DrawSize.x * x_index, this->DrawSize.y * y_index), Vec2(64, 64), Paint::PaintColor::Purple);
		paint->SetTexture(rm->GetTextureData((std::string)"paintTex"));
		return;
	}
	if (text == "w") {
		this->waterPos = Vec2(this->DrawSize.x * x_index - 25, this->DrawSize.y * y_index);
	}
}

Vec2 Map::getWaterPos()
{
	return this->waterPos;
}

void Map::UpDate()
{

}

void Map::Render2D()
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			if (this->hitBase[y][x].Getarr() != 0)
			{
				if (this->hitBase[y][x].IsObjectDistanceCheck(OGge->camera->GetPos(), OGge->camera->GetSize()))
				{
					Box2D draw(this->hitBase[y][x].position, this->DrawSize);
					draw.OffsetSize();
					this->mapimg.Draw(draw, this->chip[this->hitBase[y][x].Getarr()]);
				}
			}
		}
	}
}

bool Map::Finalize()
{
	this->chip.clear();
	this->mapimg.Finalize();
	this->hitBase.clear();
	return true;
}

bool Map::HitCheck(GameObject &p, const int id)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			if (this->hitBase[y][x].IsObjectDistanceCheck(p.position, p.Scale))
			{
				if (this->hitBase[y][x].IDCheck(id))
				{
					if (this->hitBase[y][x].CubeHit(p))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool Map::HitCheck(GameObject &p, const std::string& name)
{
	for (int y = 0; y < this->mapSize.y; ++y)
	{
		for (int x = 0; x < this->mapSize.x; ++x)
		{
			if (this->hitBase[y][x].IsObjectDistanceCheck(p.position, p.Scale))
			{
				if (this->hitBase[y][x].objectTag == name)
				{
					if (this->hitBase[y][x].CubeHit(p))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

Map::SP Map::Create(const std::string& path, const Format& format)
{
	auto to = Map::SP(new Map());
	if (to)
	{
		to->me = to;
		OGge->SetTaskObject(to);
		if (!to->LoadMap(path, format))
		{
			to->Kill();
		}
		return to;
	}
	return nullptr;
}

Map::Base::Base()
{
	this->arr = 0;
	this->ID = nullptr;
}
Map::Base::~Base()
{
	if (this->ID)
	{
		delete this->ID;
		this->ID = nullptr;
	}
}

bool Map::Base::IDCheck(const int id)
{
	if (this->ID)
	{
		return *this->ID <= id ? true : false;
	}
	return false;
}

bool Map::Base::ChipCheck(const int chip)
{
	return this->arr == chip ? true : false;
}
void Map::Base::Setarr(const int _arr)
{
	this->arr = _arr;
}
void Map::Base::SetID(const int id)
{
	if (!this->ID)
	{
		this->ID = new int(id);
	}
	else
	{
		*this->ID = id;
	}
}
int Map::Base::Getarr() const
{
	return this->arr;
}
int* Map::Base::GetID() const
{
	return this->ID;
}