#ifndef QUAD_H
#define QUAD_H
#include <windows.h>
#include <stdio.h>
#include "../freeglut/glut.h"
class QUAD{
public:
	float m_vertexX[2],m_vertexY[2];//���e�Ϯɪ��I 0�� 1�k 0�U 1�W
	float m_x,m_y,m_w,m_h,m_angle;//w,h�Q�e�{���e��
	float m_imageW , m_imageH;//�Ϥ��쥻��ڼe��
	float m_top,m_down,m_right,m_left;//�K�Ϯy��
	static const int Z=-20;
	GLuint m_textureID;
	QUAD(GLuint id,float x,float y,float w,float h,float angle);
	QUAD(GLuint id,float x,float y,float w,float h);
	QUAD(GLuint id,float x,float y,float angle);//��l�ƨS��width height�N�ϥιϤ�����e��
	QUAD(GLuint id,float x,float y);//��l�ƨS��width height�N�ϥιϤ�����e��
	void SetVertex();//�]�w�e�Ϯɪ��I
	void SetImageWH(int w,int h);//�]�w�Ϥ���l�e��
	void SetPoint(float x,float y);//�]�w�Ϥ��y��
	void SetPoint(float x,float y,float angle);//�]�w�Ϥ��y��
	void SetPoint(float x,float y,float w,float h,float angle);//�]�w�Ϥ��y��
	void SetTexCoord(float left,float right,float top,float down);//�]�w�K�ϧ���y�� //LD 0 0 RU 1 1 �L�Ұ����O�Ϥ���ڼe��
	void SetTexCoord(float left,float right);
	void Draw();//render
};
#endif