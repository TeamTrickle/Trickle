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

	Box2D getSrcOriginal(Texture*) const;
	bool preloadResource(const std::string&);
	inline Box2D GetFixedCameraCoord(const Box2D&) const;
	Box2D OptimizeForWindowSize(const Box2D&) const;
	void positioning();

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

	/**
	 @param			ステージ名
	 @return		ステージ情報がロードされているかどうか
	 */
	bool isExist(const std::string&);

	void SelectFirstElement();

	void setActive(const bool&);
	bool isActive() const;

	void setPosition(const Vec2&);
	Vec2 getPosition() const;

	typedef std::shared_ptr<StageAlert> SP;
	static SP Create(bool, const Box2D&);

private:
	bool													active = false;

	Vec2													position;
	Box2D													titleDraw;
	std::array<Box2D, StageInfoRes::MAX_ACHIEVEMENT>		starFixedDraw;
	std::array<Box2D, StageInfoRes::MAX_ACHIEVEMENT>		achievementFixedDraw;
	std::map<Texture*, Box2D>								draws;
	std::map<Texture*, Box2D>								srcs;
	Box2D													clearFlagDraw;
	Box2D													windowSize;
	Box2D													missionDraw;
	Box2D													missionSrc;

	std::map<std::string, StageInfoRes*>					infoRes;
	StageInfoRes*											currentRes;

	Texture													background;
	Texture													clearFlag;
	Texture*												clearStarTex;
	Texture*												normalStarTex;
	MapPreviewer::SP										previewer;
};