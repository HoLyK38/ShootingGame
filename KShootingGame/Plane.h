#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include <vector>
#include "Ball.h"
#include "ConstData.h"
class BulletManager;
class Bullet;
class Plane : public Ball
{
public:
	//data
	bool m_isAuto;//true = 敵人 false = 自己控制
	bool m_isShooting;
	bool m_isHurting;
	bool m_isDead;
	bool m_keyState[4];//MainPlane才需要
	int m_hp,m_hpMax;
	float m_unit;//移動單位
	float m_BAngle;//子彈角度
	std::vector<GLuint> m_deadAnime;//死亡播放動畫的Texture
	std::vector<float> m_animeTexCoord;//靜止時人物動畫貼圖座標
	Bullet* m_bullet;
	BulletManager* m_BM;
	WEAPON m_weapon;
	PlaneState m_state;
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
