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
	TrackPtr m_trackPtr;//儲存子彈軌道的Func
	float m_startX , m_startY; //子彈起始座標
	float m_unit;//移動單位
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
	void Move();//子彈軌道
	void Track();//子彈軌道
	void Update(float);
	bool isCollide(Plane *Q);//碰撞偵測
	Bullet* Copy();
};
#endif