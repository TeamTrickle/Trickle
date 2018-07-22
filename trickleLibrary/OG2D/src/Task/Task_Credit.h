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
	void Fade();

private:
	const int NON = 0;
	const int MODE1 = 1;
	const int MODE2 = 2;
	const int MODE3 = 3;
	const int MODE4 = 4;
	const int MODE5 = 5;
	const int MODE6 = 6;
	const int MODE7 = 7;
	const int MODE8 = 8;
	int nowMode;

	//enum Mode {
	//	Non,
	//	Mode1,
	//	Mode2,
	//	Mode3,
	//	Mode4,
	//	Mode5,
	//	Mode6,
	//	Mode7,
	//};
	//Mode nowMode;


	Texture frameTex;
	Texture nameTex;

	struct creditUI {
		Vec2 pos;
		float alpha;
	};
	creditUI frame;

	int timeCnt;
	float alpha;

};
