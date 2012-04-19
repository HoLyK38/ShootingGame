#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include <vector>
#include "QUAD.h"
#include "ConstData.h"
class BulletManager;
class Bullet;
class Plane : public QUAD
{
public:
	//data
	bool m_isAuto;//true = 敵人 false = 自己控制
	bool m_isShooting;
	bool m_hurting;
	bool m_keyState[4];
	int m_hp;
	float m_unit;
	std::vector<GLuint> m_deadAnime;//死亡播放動畫的Texture
	Bullet* m_bullet;
	double m_BAngle;//子彈角度
	BulletManager* m_BM;
	WEAPON m_weapon;
	PlaneState m_state;
	std::vector<float> m_animeTexCoord;//靜止時人物動畫貼圖座標
	//fuction
	Plane(GLuint id , float x,float y,float w,float h);
	~Plane();
	void Update(float);
	void Move();
	void Move(PlaneState);
	void Shoot();//依照現在狀態看要不要shoot
	void ShootOn(double,WEAPON);
	void ShootOFF();
	void CheckState();//檢查現在狀態
	void StayAnime();//靜止時的動畫
	void deadAnime(float);//死亡時的動畫
	void HurtAnime(float);//死亡時的動畫
	void ChangeWeapon(WEAPON weapon);
	void SetBulletSpeed(int);
	void SetBullet(GLuint texID,float w,float h,float angle);//設定子彈類型
	void SetBullet(GLuint texID,float w,float h,float angle,float left,float right,float top,float down);
	void SetAnimeTexCoord(float *t,int first,int last);//設定靜止時人物動畫TexCoord
};

#endif
