#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include <math.h>
#include "Ball.h"
#include "ConstData.h"
#include "Plane.h"
class Bullet : public Ball
{
public:
	//data
	typedef void (*TrackPtr)(Bullet*);
	TrackPtr m_trackPtr;//�x�s�l�u�y�D��Func
	float m_startX , m_startY; //�l�u�_�l�y��
	float m_unit;//���ʳ��
	float m_shotAngle;
	BulletState m_state;
	float m_speed;
	int m_atk;
	//function
	Bullet(GLuint a , float x,float y,float w,float h,float angle);
	Bullet(GLuint a , float w,float h,float angle);
	~Bullet();
	void SetTrack(double,TrackPtr);
	void SetTrack(TrackPtr);
	void SetStart(float, float);
	void Move();//�l�u�y�D
	void Track();//�l�u�y�D
	void Update(float);
	bool isCollide(Plane *Q);//�I������
	Bullet* Copy();
};
#endif