#pragma once
#include "OGSystem/OGSystem.h"

class Credit : public TaskObject
{
public:
	std::string taskName;
	//シェアポインタ宣言
	typedef std::shared_ptr<Credit> SP;
	static Credit::SP Create(bool flag = true);
	//コンストラクタ
	Credit();
	//デストラクタ
	virtual ~Credit();
	//生成処理
	bool Initialize();
	//更新処理
	void UpDate();
	//描画処理
	void Render2D();
	void Finalize();

private:
	enum Mode {
		Non,
		Mode1,
	};
	Mode nowMode;


	Texture backTex;
	Texture frameTex;
	Texture nameTex;

	struct creditUI {
		Vec2 pos;
		float alpha;
	};
	creditUI frame;

	int cnt;

};
