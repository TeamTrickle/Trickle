#pragma once
#include "OGSystem/OGSystem.h"

class Credit : public TaskObject
{
	class Animation
	{
		Easing easing_x;
		Easing easing_y;
		Vec2 StartPos;
		Vec2 EndPos;
	public:
		Vec2 Move();
		Vec2 Move(const float time);
		Vec2 Move(const Easing::Name = Easing::Name::Linear, const Easing::Mode = Easing::Mode::InOut, const float = 10.f);
		Animation();
		void Set(Vec2&, Vec2&);
		bool isPlay() const;
	};
	Animation camera_anim;

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

	void Next();		//次のモードに移る
	bool LoadSize();	//テキストファイルに書いているサイズを読み込む
	void SetSize();		//読み込んだサイズを指定する
	void CreditJump(int start, int time);	//
	bool CheckTime(int);					//

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
	const int MODE9 = 9;
	int nowMode;


	Texture LadderTex;

	struct IMAGE {
		const int DRAW_X = 0;
		const int DRAW_Y = 1;
		const int DRAW_W = 2;
		const int DRAW_H = 3;
		int imageSize[4];

		Box2D draw;
		Box2D src;
		Texture tex;
	};

	int FRAME_NUM = 8;
	IMAGE frame[9];

	int timeCnt;
	int jumpTimeCnt;
	int WAITTIME;

	//エフェクトのカウント
	int effCounter;
	//花びらのエフェクト
	Texture petalTex1;
	Texture petalTex2;
	Texture petalTex3;
	Texture petalTex4;
	Texture petalTex5;
};