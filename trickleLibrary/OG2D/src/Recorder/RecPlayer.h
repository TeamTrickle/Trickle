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
	typedef std::pair<In::AXIS, float> StickState;
	typedef std::pair<float, StickState> StickEventTimeline;

	explicit RecPlayer() {}
	virtual ~RecPlayer() {}
	inline void printLog(const std::string&);
	bool Initialize(const std::string&);
	bool isPlayable() const;
	bool isEventExist(const KeyState&);
	void Reset();
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

	/**
	 *	@brief	まだプレイするスティック記録が残っているか
	 *	@return	true 残っている
	 */
	bool isAxisEnded() const;

	/**
	 *	@brief	リプレイを反復するかを選択
	 *	@param	bool値
	 */
	void SetRepeat(const bool&);

	/**
	 @brief		再生が１回終わると関数を呼ぶ
	 @param		呼ばれるbool型を返す関数、trueが呼ばれる前まで繰り返す
	 */
	void SetEndCallback(const std::function<bool()>&);

	/**
	 @return	スティックの傾き(データがない場合には0を返す)
	 */
	float GetCurrentStickTilt(const In::AXIS&);

	void SetPause();
	void SetPlay();

private:
	bool											isDbgMode = false;
	bool											isRepeat = false;
	bool											isPlaying = true;
	Time											timer;
	std::string										fileName;
	std::queue<KeyEventTimeline>					recData;
	std::queue<KeyEventTimeline>					backupData;
	std::queue<StickEventTimeline>					recStick;
	std::queue<StickEventTimeline>					backupStick;
	std::map<KeyState, std::function<void()>>		events;
	std::map<Input::in, RecDef::KeyState>			playerKeyState;
	std::function<bool()>							endCallback;
};