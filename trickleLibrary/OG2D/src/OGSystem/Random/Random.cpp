#include "Random.h"

void random::Init()
{
	//乱数生成エンジンの生成
	std::random_device device;
	//シード値設定
	engine.seed(device());
}

int random::GetRand(int min_,int max_)
{
	std::uniform_int_distribution<int> range(min_,max_);
	return range(engine);
}

float random::GetRand(float min_,float max_)
{
	std::uniform_real_distribution<float> range(min_,max_);
	return range(engine);
}

std::string random::GetRand(const std::string& text, std::size_t size)
{
	if (text.empty())
	{
		std::cout << "生成に使用する文字列データが存在しません" << std::endl;
		return "";
	}
	//textデータの0番目から最後の１つ手前(\0の前まで)で乱数を生成
	std::uniform_int_distribution<std::size_t> range(0, text.size() - 1);
	std::string ReturnText;
	for (std::size_t i = 0; i < size; ++i)
	{
		std::size_t index = range(engine);
		char random_char = text[index];
		ReturnText += random_char;
	}
	return ReturnText;
}