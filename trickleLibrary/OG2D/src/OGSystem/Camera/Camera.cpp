#include "Camera.h"
//--------------------------------------------------
//@:Camera2Dclass									
//--------------------------------------------------
Camera2D::Camera2D()
{

}
Camera2D::Camera2D(Box2D& pos)
{
	//各値をセットする
	this->cameraPos = pos;
	this->position = { 0,0 };
	this->Scale = { pos.w,pos.h };
}
Camera2D::~Camera2D()
{

}
void Camera2D::Initialize(Box2D& pos)
{
	//各値をセットする
	this->cameraPos = pos;
	this->position = {0,0 };
	this->Scale = { pos.w,pos.h };
}
void Camera2D::CameraUpdate() const
{
	//行列をプロジェクションモードに変更
	glMatrixMode(GL_PROJECTION);
	//行列の初期化
	glLoadIdentity();
	//元データが書き換わらないよう値の代入
	Box2D _camera(cameraPos);
	//初期設定値からの変更値
	_camera.x += this->position.x;
	_camera.y += this->position.y;
	_camera.w = this->Scale.x;
	_camera.h = this->Scale.y;
	_camera.OffsetSize();
	//描画縦横サイズの指定
	glOrtho(_camera.x, _camera.w, _camera.h, _camera.y, -1.0f, 1.0f);
}
void Camera2D::MovePos(Vec2& est)
{
	//位置を加算する
	this->position += est;
}
void Camera2D::SetPos(Vec2& est)
{
	//位置を上書きする
	this->position = est;
}
void Camera2D::SetSize(Vec2& size_)
{
	//サイズを上書きする
	this->Scale = size_;
}
void Camera2D::MoveSize(Vec2& size_)
{
	//サイズを加算する
	this->Scale += size_;
}
Vec2 Camera2D::GetPos() const
{
	//位置を返す
	return this->position;
}
Vec2 Camera2D::GetSize() const
{
	//サイズを返す
	return this->Scale;
}