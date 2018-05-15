#pragma once
#include <random>
#include <iostream>
//ランダム生成名前空間
namespace random
{
	static std::mt19937_64 engine;				//メルセンヌツイスター64bit
	void Init();								//初期化
	int GetRand(int min_,int max_);				//整数のランダム
	float GetRand(float min_,float max_);		//浮動小数点のランダム
	std::string GetRand(						//文字列のランダム
		const std::string& text, 
		std::size_t size
	);											
}
