#pragma once
#include <iostream>
#include "OGSystem\Input\Input.h"

/**
 *	@brief	セーブファイル関連データタイプ定義
 *	@author	Heewon Kim (nabicore@icloud.com)
 */

namespace RecDef {
	enum KeyState {
		Idle,
		PRESS,
		RELEASE
	};
	typedef std::pair<Input::in, KeyState> WatchKey;
	typedef std::pair<In::AXIS, KeyState> WatchStick;
}