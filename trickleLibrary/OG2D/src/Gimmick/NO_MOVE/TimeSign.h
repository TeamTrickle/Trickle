#pragma once
#include <map>
#include <array>
#include "OGSystem\OGsystem.h"

/**
 @brief		マップ上で現在時間を見せてくれる札
 @author	Heewon Kim (nabicore@icloud.com)
 @date		2018-06-11
 */

class TimeSign : public TaskObject {
private:
	bool Initialize(const Vec2&);
	virtual void UpDate() override;
	virtual void Render2D() override;
	void Finalize();

	void ClearNumberAtlas();
	void setAtlasAngle(const float&);

public:
	explicit TimeSign() {}
	virtual ~TimeSign();

	/**
	 @brief		数字画像ファイルたちが入ってるフォルダパスを再指定します
	 @param		画像パス
	 @param		ファイル拡張子 (「.」までつけて）
	 @note		フォルダの中で数字画像ファイルたちの名前は必ずその数字と同じく設定してください　（例えば１を表す画像なら1.png)
	 @note		すべての画像は同じサイズになるように制作してください
	 @note		タイムを区切る「：」も数字たちと同じサイズで「space.png」的な名前で入れて下さい
	 */
	void setAtlasPath(const std::string&, const std::string&);

	void setPosition(const Vec2&);
	Vec2& getPosition() const;

	typedef std::shared_ptr<TimeSign> SP;
	static SP Create(const Vec2&, bool);

private:
	std::array<Box2D, 4>			timeNumberDraw;
	Box2D							originPos;
	
	Texture							spacer;
	std::map<int, Texture>			numberAtlas;
	std::string						atlasPath = "numbers/";
	std::string						extension = ".png";
};
