#pragma once
#include "OGSystem\OGsystem.h"
#include <string>
#include <array>

/**
	@brief	MapAlertで使われるステージ全般を見せてくれる画面です
	@author	Heewon Kim (nabicore@icloud.com)
	@date	2018-06-10
 */

class MapPreviewer : public TaskObject {
private:
	bool Initialize(const Box2D&, const std::string&);

public:
	explicit MapPreviewer() {}
	virtual ~MapPreviewer();

	virtual void UpDate() override;
	virtual void Render2D() override;

	/**
		@brief	プレビュー用写真を差し替えます
		@param	ファイル名
	 */
	void replaceThumbnail(const std::string&);

	void setVisible(const bool&);
	bool isVisible() const;

	typedef std::shared_ptr<MapPreviewer> SP;
	static SP Create(bool, const Box2D&, const std::string&);


private:
	bool					visible = true;
	Box2D					windowSize;
	Texture					mapThumbnail;
	Vec2					thumbSize;
	Vec2					pointPos;
	float					camSpeed = 5.f;

	const static std::array<Vec2, 4> CamMoveSeq;
};