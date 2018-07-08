///Game中用のswitchに連動した開閉を行うclass
///constructor	pos = 位置,size = 大きさ,isOpen = 開いているか(true = 開いている,false = 閉じている)
///ToOpenで開(成功true,失敗false)、ToCloseで閉(成功true,失敗false)、IsOpen(開true,閉false)で開いているかを返す
///GetIDでDoorに設定されているIDを返す、IDは生成時に決定される
///
#pragma once
#include "OGSystem\OGsystem.h"
#include "Object\Object.h"
class Door :public GameObject, public TaskObject
{
	unsigned __int8 id;
	bool isOpen;
	bool isMove;
	bool preIsOpen;
	float timeCnt;
	Vec2 originPos;
	Texture* image;
	Box2D draw;
	Box2D src;
public:
	Door(const Vec2& pos,const Vec2& size,const bool isOpen);
	virtual ~Door();
	typedef std::shared_ptr<Door> SP;
	static SP Create(const Vec2& pos,const Vec2& size,const bool isOpen);
	void UpDate() override;
	void Render2D() override;
	bool ToOpen();	
	bool ToClose();
	bool IsOpen() const;
	bool IsMove() const;
	void SetTexture(Texture*);
	unsigned __int8 GetID() const;
};