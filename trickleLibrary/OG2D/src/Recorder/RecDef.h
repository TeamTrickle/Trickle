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
	static In::AXIS sticks[]{
		In::AXIS_LEFT_X,
		In::AXIS_LEFT_Y,
		In::AXIS_RIGHT_X,
		In::AXIS_RIGHT_Y
	};
	static std::map<In::AXIS, std::string> sticksName = {
		{ In::AXIS_LEFT_X, "LeftX" },
		{ In::AXIS_LEFT_Y, "LeftY" },
		{ In::AXIS_RIGHT_X, "RightX" },
		{ In::AXIS_RIGHT_Y, "RightY" }
	};
	typedef std::pair<Input::in, KeyState> WatchKey;

	static In::AXIS getAxisWithString(const std::string& str) {
		for (auto& s : sticksName) {
			if (s.second == str)
				return s.first;
		}
		return (In::AXIS)-1;
	}
}