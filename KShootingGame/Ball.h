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
	float m_top,m_down,m_right,m_left;//�K�Ϯy��
	float m_width,m_height;//�Q�e�{���e��
	float m_imageW , m_imageH;//�Ϥ��쥻��ڼe��
	float m_angle;
	GLuint m_textureID;//�Q�e�{��texture
	//fuction
	Ball(GLuint id,float x,float y,float w,float h,float angle);
	Ball(GLuint id,float x,float y,float w,float h);
	Ball(GLuint id,float x,float y,float angle);//��l�ƨS��width height�N�ϥιϤ�����e��
	Ball(GLuint id,float x,float y);//��l�ƨS��width height�N�ϥιϤ�����e��
	void SetVertex();//�]�w�e�Ϯɪ��I
	void SetImageWH(int w,int h);//�]�w�Ϥ���l�e��
	void SetPoint(Vector2 v);//�]�w�Ϥ��y��
	void SetPoint(Vector2 v,float angle);//�]�w�Ϥ��y��
	void SetPoint(Vector2 v,float w,float h,float angle);//�]�w�Ϥ��y��
	void SetPoint(float x,float y);//�]�w�Ϥ��y��
	void SetPoint(float x,float y,float angle);//�]�w�Ϥ��y��
	void SetPoint(float x,float y,float w,float h,float angle);//�]�w�Ϥ��y��
	void SetTexCoord(float left,float right,float top,float down);//�]�w�K�ϧ���y�� //LD 0 0 RU 1 1 �L�Ұ����O�Ϥ���ڼe��
	void SetTexCoord(float left,float right);
	float GetWidth();
	float GetHeight();
	Vector2 GetPos();
	void Render();//render
};
#endif