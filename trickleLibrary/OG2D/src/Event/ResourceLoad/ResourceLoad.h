#pragma once
#include "OGSystem\OGsystem.h"


class ResourceLoad
{
	//!	ファイルの中身のデータ
	std::string textData;
	//! 生成するデータ情報
	std::string dataPath;
	//! データのファイル名
	std::string dataName;
	/**
	*@brief	:データを生成する
	*@param	:string text 生成するためのデータ
	*/
	void DataCreate(const std::string& text);
public:
	/**
	*@brief	:constructor
	*@param	:ifstream ifs ファイルデータ
	*/
	explicit ResourceLoad(std::ifstream& ifs);
	/**
	*@brief	:destructor
	*/
	virtual ~ResourceLoad();
};