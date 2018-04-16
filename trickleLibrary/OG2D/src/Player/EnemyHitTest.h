#pragma once
#include "Object\Object.h"
#include "Win\WinMain.h"
#include "Task\Task_GIMMICK_Control.h"

class GIMMICK_Control;

enum State
{
	Normal,//水
	Hot,   //水蒸気
	Frieze,//氷
};
class EnemyHitTest : public Object
{
public:
	State state;
	void Initialize();
	void Finalize();
	void UpDate();
	void Render();

	EnemyHitTest();
	~EnemyHitTest();
private:
	void Move();
	Texture image;						//画像イメージ
	std::string	 _filePath;				//画像パス
};