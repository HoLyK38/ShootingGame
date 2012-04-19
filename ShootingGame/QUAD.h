#ifndef QUAD_H
#define QUAD_H
#include <windows.h>
#include <stdio.h>
#include "../freeglut/glut.h"
class QUAD{
public:
	float m_vertexX[2],m_vertexY[2];//給畫圖時的點 0左 1右 0下 1上
	float m_x,m_y,m_w,m_h,m_angle;//w,h想呈現的寬高
	float m_imageW , m_imageH;//圖片原本實際寬高
	float m_top,m_down,m_right,m_left;//貼圖座標
	static const int Z=-20;
	GLuint m_textureID;
	QUAD(GLuint id,float x,float y,float w,float h,float angle);
	QUAD(GLuint id,float x,float y,float w,float h);
	QUAD(GLuint id,float x,float y,float angle);//初始化沒給width height就使用圖片的原寬高
	QUAD(GLuint id,float x,float y);//初始化沒給width height就使用圖片的原寬高
	void SetVertex();//設定畫圖時的點
	void SetImageWH(int w,int h);//設定圖片原始寬高
	void SetPoint(float x,float y);//設定圖片座標
	void SetPoint(float x,float y,float angle);//設定圖片座標
	void SetPoint(float x,float y,float w,float h,float angle);//設定圖片座標
	void SetTexCoord(float left,float right,float top,float down);//設定貼圖材質座標 //LD 0 0 RU 1 1 他所除的是圖片實際寬高
	void SetTexCoord(float left,float right);
	void Draw();//render
};
#endif