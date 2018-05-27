#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "OGSystem\Timer\glTimer.h"

/**
 *	@brief  プレイヤーの行動をファイルとして記録します
 *	@author	Heewon Kim (nabicore@icloud.com)
 */
class Recorder {
	explicit Recorder() {}
	virtual ~Recorder() {}
	bool Initialize(const std::string&);
	void printLog(const std::string&);
	void Recorde();

public:
	/**
	*	@brief	Recorderをメモリ上に作ります
	*	@param	記録に使うファイル名
	*	@param	デバッグ用ログを出すかどうか （デフォルト：False)
	*	@return	メモリアドレス、使い終わった後必ず削除すること！
	*/
	static Recorder* Create(const std::string&, const bool&);

	/**
	 *	@brief	クラスを削除します
	 */
	void Destroy();

private:
	bool				isLogging = false;
	Time				gameTimer;
	std::string			fileName = "save.txt";
	std::ofstream		fileWriter;
	std::thread			recThread;
};