#ifndef BALL_H
#define BALL_H
#include <windows.h>
#include <lua.hpp>
#include <LuaCell.h>
#include "../freeglut/glut.h"
#include "Vector.h"
class Ball{
public:
	//data
	lua_State* luaState;
	Vector2 m_vertex[4];
	Vector2 m_pos;
	static const int Z=50;
	float m_top,m_down,m_right,m_left;//貼圖座標
	float m_width,m_height;//想呈現的寬高
	float m_imageW , m_imageH;//圖片原本實際寬高
	float m_angle;
	GLuint m_textureID;//想呈現的texture
	//fuction
	Ball(GLuint id,float x,float y,float w,float h,float angle);
	Ball(GLuint id,float x,float y,float w,float h);
	Ball(GLuint id,float x,float y,float angle);//初始化沒給width height就使用圖片的原寬高
	Ball(GLuint id,float x,float y);//初始化沒給width height就使用圖片的原寬高
	void SetVertex();//設定畫圖時的點
	void SetImageWH(int w,int h);//設定圖片原始寬高
	void SetPoint(Vector2 v);//設定圖片座標
	void SetPoint(Vector2 v,float angle);//設定圖片座標
	void SetPoint(Vector2 v,float w,float h,float angle);//設定圖片座標
	void SetPoint(float x,float y);//設定圖片座標
	void SetPoint(float x,float y,float angle);//設定圖片座標
	void SetPoint(float x,float y,float w,float h,float angle);//設定圖片座標
	void SetTexCoord(float left,float right,float top,float down);//設定貼圖材質座標 //LD 0 0 RU 1 1 他所除的是圖片實際寬高
	void SetTexCoord(float left,float right);
	float GetWidth();
	float GetHeight();
	Vector2 GetPos();
	void Render();//render
};
#endif