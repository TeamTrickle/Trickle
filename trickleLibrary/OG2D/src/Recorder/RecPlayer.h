#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "OGSystem\Timer\glTimer.h"
#include "OGSystem\Input\Input.h"

/**
 *	@brief	Recorderで取ったデータを再生する
 *	@author Heewon Kim (nabicore@icloud.com)
 */

class RecPlayer {

private:
	explicit RecPlayer() {}
	virtual ~RecPlayer() {}
	bool Initialize(const std::string&);

public:
	/**
	 *	@brief	生成関数
	 *	@param	ファイル名
	 *	@param	デバッグモードフラグ（基本値：Off）
	 *	@return	オブジェクト
	 */
	static RecPlayer* Create(const std::string&, const bool&);

	/**
	 *	@brief	クラス解除
	 */
	void Destroy();

private:
	std::string					fileName;
	std::istream				fileReader;
};