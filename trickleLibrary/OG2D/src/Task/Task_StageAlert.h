#pragma once
#include "OGSystem\OGsystem.h"


/**
 @brief		ステージ選択タスクで選択したステージの概要を表示する
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-05
 */

class StageAlert : public TaskObject {
private:
	typedef std::pair<std::string, bool> Achievement;

	bool Initialize();
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

public:
	explicit StageAlert() {}
	virtual ~StageAlert();

	/**
	 @brief			ステージの詳細をファイルから読み込みます
	 @param			ファイルのパス
	 @return true	読み込みに成功した
	 @note			ステージをクリアしたか、どんな評価をもらったかなどが「ステージ名前_save.txt」形で保存されます
	 */
	bool SetStageData(const std::string&);

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool = true);

private:
	const static int MAX_ACHIEVEMENT = 3;

private:
	std::string					stageName;
	bool						isClear = false;
	Achievement					achievements[MAX_ACHIEVEMENT];

	Texture						background;
	Texture						star;
	Texture						mission;
	Texture						clearFlag;
};