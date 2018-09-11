#pragma once
#include "OGSystem\OGsystem.h"
enum Event
{
	RESOURCE_LOAD,
};
class EventTask
{
	//! ファイル情報
	std::ifstream ifs;
public:
	/**
	*@brief	:constructor
	*@param	:Event eventType 生成するEventの種類
	*@param	:string path 読み込むEventファイルのパス
	*/
	explicit EventTask();
	/**
	*@brief	:destructor
	*/
	virtual ~EventTask();
	/**
	*@brief	:イベントを読み込む
	*@param	:Event eventType 生成するEventの種類
	*@param	:string path 読み込むEventファイルのパス
	*@return:bool 成功true
	*/
	bool Load(const Event& eventType, const std::string& path);
};