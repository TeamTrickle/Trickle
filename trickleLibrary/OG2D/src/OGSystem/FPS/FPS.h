#pragma once
#include "OGSystem\_OGsystem.h"
#include <functional>
class FPS {
public:
	FPS();							//コンストラクタ
	~FPS();							//デストラクタ
	void Update();					//更新処理
	typedef std::shared_ptr<FPS> SP;//スマートポインタの生成
	static SP Create();				//スマートポインタを返す
private:
	float lastTime;					//前フレームタイム
	int count;						//カウント数
	GLfloat fps;					//fps値
};
