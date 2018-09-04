/**
*Windowの生成、管理を行うclass
*/
#pragma once
#include "OGSystem\_OGsystem.h"

class Window {
	//! アイコン情報
	GLFWimage image[1];
	//! アイコン画像のID
	GLuint id_;
	//! ウィンドウのアイコン化状況
	bool isIcon;
	//! 可視化状況
	bool isVisualization;
	//! 幅
	int widht;
	//! 高さ
	int height;
	//! Windowの名
	char* name;
	//! フルスク設定
	bool screen;
	//! Windowの位置
	Vec2 position;
	//! Window情報
	GLFWwindow *window;
public:
	/**
	*@brief	:constructor
	*/
	Window();
	/**
	*@brief	:constructor
	*@param	:int x windowXサイズ
	*@param :int y windowYサイズ
	*@param	:char* name window名
	*@param :bool flag フルスク設定
	*@param	:Vec2 pos window位置
	*/
	Window(
		const int x,
		const int y,
		char* name,
		const bool flag,
		const Vec2& pos);
	/**
	*@brief	:destructor
	*/
	~Window();
	/**
	*@brief	:constructor
	*@param	:int x windowXサイズ
	*@param :int y windowYサイズ
	*@param	:char* name window名
	*@param :bool flag フルスク設定
	*@param	:Vec2 pos window位置
	*@return:bool 生成に成功でtrue
	*/
	bool createWindow(
		const int x,
		const int y,
		char* name,
		const bool flag,
		const Vec2& pos);
	/**
	*@brief	:アイコンを設定する
	*@param	:string path ファイルパス
	*/
	void setIcon(const std::string& path);
	/**
	*@brief	:Windowのサイズとアスペクト比を固定する
	*/
	void LimitsWindow();
	/**
	*@brief	:Windowをアイコン化、アイコン化から解除する
	*/
	void WindowIcon();
	/**
	*@brief	:Windowを可視化、可視化から解除する
	*/
	void Visualization();
	/**
	*@brief	:マウスを表示させるかを決める
	*@param	:bool flag 表示設定
	*/
	void InMouseMode(const bool flag);
	/**
	*@brief	:Windowのサイズを返す
	*@return:Vec2 Windowのサイズ
	*/
	Vec2 GetSize() const;
	/**
	*@brief	:Windowの位置を返す
	*@return:Vec2 Windowの位置
	*/
	Vec2 GetPos() const;
	/**
	*@brief	:生成するWindowの位置を設定する
	*@param	:Vec2 pos Windowの位置
	*/
	void SetWindowPos(const Vec2& pos);
	/**
	*@brief	:Window情報を返す
	*@return:GLFWWinfow* Window情報
	*/
	GLFWwindow* GetWindow() const;
};