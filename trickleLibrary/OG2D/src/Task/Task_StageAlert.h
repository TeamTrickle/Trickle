#pragma once
#include "OGSystem\OGsystem.h"
#include "MapPreviewer.h"
#include "StageInfoRes.h"
#include <queue>
#include <functional>


/**
 @brief		ステージ選択タスクで選択したステージの概要を表示する
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-05
 */

class StageAlert : public TaskObject {
private:

	bool Initialize(const Box2D&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	bool preloadResource(const std::string&);
	void changeTexture(Texture*, const std::string&, bool);
	inline Box2D GetFixedCameraCoord(const Box2D&) const;
	Box2D OptimizeForWindowSize(const Box2D&) const;

public:
	explicit StageAlert() {}
	virtual ~StageAlert();

	/**
	 @brief			ステージの詳細をファイルから読み込みます
	 @param			ファイルのパス
	 */
	void SetStageData(const std::string&);

	/**
	 @brief			ステージごとに見せる情報データを予めInitします
	 @param			関連情報が入ってるテキストファイルのパス
	 @return true	読み込み成功
	 @return false	読み込み失敗、テキストファイルの名前、パスなどが正しいかもう一度確認してみること！
	 */
	bool operator<<(const std::string&);

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool, const Box2D&);

private:
	std::map<Texture*, Box2D>								draws;
	std::map<Texture*, Box2D>								srcs;
	Box2D													windowSize;

	Texture													background;
	Texture													mission;
	Texture													clearFlag;
	std::array<Texture, StageInfoRes::MAX_ACHIEVEMENT>		starsTex;
	std::map<std::string, StageInfoRes*>					infoRes;
	StageInfoRes*											currentRes;
	MapPreviewer::SP										previewer;
};