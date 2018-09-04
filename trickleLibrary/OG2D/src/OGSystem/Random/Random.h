/**ランダムの数値、文字列を取得するためのclass
*既存GameEngineを使用している場合は自動で生成、初期化される
*/
#pragma once
#include <random>
#include <iostream>
/**
*namespace random
*ランダム生成名前空間
*/
namespace random
{
	//! メルセンヌツイスター64bit
	static std::mt19937_64 engine;
	//! 初期化
	void Init();
	/**
	*@brief	:整数のランダム
	*@param	:int min_ 最低値
	*@param	:int max_ 最大値
	*@return:int ランダム値
	*/
	int GetRand(const int min_, const int max_);
	/**
	*@brief	:浮動小数点のランダム
	*@param	:float min_ 最低値
	*@param	:float max_ 最大値
	*@return:float ランダム値
	*/
	float GetRand(const float min_, const float max_);
	/**
	*@brief	:文字列のランダム
	*@param	:string text 使用する文字たち
	*@param	:size_t size 返す文字のサイズ
	*@return:string ランダム文字列
	*/
	std::string GetRand(
		const std::string& text,
		const std::size_t size
	);
}
