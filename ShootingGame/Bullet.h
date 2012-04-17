#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include <math.h>
#include "QUAD.h"
#include "ConstData.h"
#include "EnemyPlane.h"
#include "MainPlane.h"
class Bullet : public QUAD
{
public:
	//data
	typedef void (*TrackPtr)(Bullet*);
	TrackPtr m_trackPtr;//儲存子彈軌道的Func
	float m_startX , m_startY; //子彈起始座標
	float m_unit;//移動單位
	float m_angle;
	BulletState m_state;
	int m_speed;
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
	bool isCollide(const EnemyPlane *Q);//碰撞偵測
	bool isCollide(const MainPlane *Q);//碰撞偵測
	
};
#endif