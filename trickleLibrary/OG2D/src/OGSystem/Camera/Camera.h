#pragma once
#include "OGSystem\_OGsystem.h"
class Camera2D
{
public:
	Camera2D()
	{}
	Camera2D(Box2D pos);
	~Camera2D();
	void Initialize(Box2D pos);
	void CameraUpdate() const;
	void MovePos(Vec2 est);
	void SetPos(Vec2 est);
	void SetSize(Vec2 size_);
	void MoveSize(Vec2 size_);
	Vec2 GetPos() const;
	Vec2 GetSize() const;
	typedef std::shared_ptr<Camera2D> SP;
	static SP Create(Box2D pos);
private:
	Box2D cameraPos;
	Vec2 position;
	Vec2 Scale;
};