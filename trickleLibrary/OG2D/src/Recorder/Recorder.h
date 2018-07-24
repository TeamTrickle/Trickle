#pragma once
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <queue>
#include "RecDef.h"
#include "OGSystem\OGsystem.h"
#include "OGSystem\Timer\glTimer.h"

/**
 *	@brief  プレイヤーの行動をファイルとして記録します
 *	@author	Heewon Kim (nabicore@icloud.com)
 */
class Recorder {
private:

	explicit Recorder() {}
	virtual ~Recorder() {}
	bool Initialize(const std::string&);
	bool isKeyListenable() const;
	inline void printLog(const std::string&);
	bool isAlreadyRecorded(const RecDef::WatchKey&, const RecDef::KeyState&) const;
	void Recorde();
	void RecordeButton();
	void RecordeSticks();

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

	/**
	 *	@brief	行動を記録します
	 *	@param	記録されるメッセージ
	 */
	void WriteRecord(const std::string&);

	/**
	 *	@brief	キー入力記録を許可します
	 *	@param	OGge->in
	 */
	void ActivateKeyRecord(Input*);

	/**
	 *	@brief	キー入力を記録するキーをしていします。
	 *	@param	キー
	 */
	void AddKeyInputWatchList(const Input::in&);
	void operator>>(const Input::in&);

	/**
	 *	@brief	記録を開始します
	 */
	void RecordStart();

	/**
	 *	@brief	JoyStickも記録します
	 */
	void RecordJoysticks();


private:
	bool							isRecordSticks = false;
	bool							isLogging = false;
	Time*							gameTimer;
	Input*							inputListener;
	std::string						fileName = "save.txt";
	std::ofstream					fileWriter;
	std::thread						recThread;
	std::queue<std::string>			inputQueue;
	std::vector<RecDef::WatchKey>	watchKeys;
};