#pragma once
#include "OGSystem\_OGsystem.h"

class FPS {
public:
	FPS();							//コンストラクタ
	~FPS();							//デストラクタ
	void Update();					//更新処理
private:
	float lastTime;					//前フレームタイム
	int count;						//カウント数
	GLfloat fps;					//fps値
};
