#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include "RecDef.h"
#include "OGSystem\Timer\glTimer.h"

/**
 *	@brief	Recorderで取ったデータを再生する
 *	@author Heewon Kim (nabicore@icloud.com)
 */

class RecPlayer {
private:

	typedef RecDef::WatchKey KeyState;
	typedef std::pair<float, RecDef::WatchKey> KeyEventTimeline;

	explicit RecPlayer() {}
	virtual ~RecPlayer() {}
	inline void printLog(const std::string&);
	bool Initialize(const std::string&);
	std::vector<std::string> Split(const std::string&, const char&);

public:
	/**
	 *	@brief	生成関数
	 *	@param	ファイル名
	 *	@param	デバッグモードフラグ（基本値：Off）
	 *	@return	オブジェクト
	 *	@return nullptr オブジェクト生成失敗（多分パス指定問題）
	 */
	static RecPlayer* Create(const std::string&, const bool&);

	/**
	 *	@brief	クラス解除
	 */
	void Destroy();

	/**
	 *	@brief	タスクのUpdateで呼ぶと読み込んだセーブデータの通り動く
	 */
	void Play();

	/**
	 *	@brief	キーを押せばやる行動を指定します
	 *	@param	キー
	 *	@param	キーを押したのか離したのか
	 *	@param	このキーを押したとき行わっれる動作を記述したvoid型関数
	 */
	void AddKeyEvent(const Input::in&, const RecDef::KeyState& state, const std::function<void()>&);

	/**
	 *	@brief	まだプレイする記録が残っているか
	 *	@return true 残っている
	 */
	bool isEnded() const;

private:
	bool											isDbgMode = false;
	Time											timer;
	std::string										fileName;
	std::queue<KeyEventTimeline>					recData;
	std::map<KeyState, std::function<void()>>		events;
};