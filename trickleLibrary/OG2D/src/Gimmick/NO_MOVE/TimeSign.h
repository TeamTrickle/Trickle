#pragma once
#include <map>
#include <array>
#include "OGSystem\OGsystem.h"

/**
 @brief		マップ上で現在時間を見せてくれる札
 @author	Heewon Kim (nabicore@icloud.com)
 @note		GameManagerタスクが動いていないと実行されません
 @date		2018-06-11
 */

class TimeSign : public TaskObject {
private:
	bool Initialize(const std::string&, const Box2D&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	void ClearNumberAtlas();

public:
	explicit TimeSign() {}
	virtual ~TimeSign();

	/**
	 @brief		数字画像ファイルたちが入ってるフォルダパスを再指定します
	 @param		画像パス
	 @param		1文字当たりのサイズ
	 @param		背景位置からどのくらい離れとくか
	 */
	void setAtlas(const std::string&, const Box2D&, const Box2D&);

	/**
	 @brief		時計の中、数字の位置を指定します
	 @param		位置値
	 */
	void setDialogPos(const Vec2&);

	/**
	 @brief		時間を表示する数字の角度を設定します
	 @param		度角度
	 */
	void setAtlasAngle(const float&);

	void setPosition(const Vec2&);
	Vec2& getPosition() const;

	typedef std::shared_ptr<TimeSign> SP;
	static SP Create(const std::string&, const Box2D&, bool);

private:
	bool							activate = true;
	std::array<Box2D, 4>			timeNumberDraw;
	Box2D							originPos;
	
	Texture							base;
	Texture							numberAtlas;
	std::map<int, Box2D>			numberSrcs;
	std::array<Box2D, 4>			timerDraws;
	std::array<int, 4>				currentTime;
	float							rotateAngle = 0.f;
};
