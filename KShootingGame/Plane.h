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
	bool m_isAuto;//true = �ĤH false = �ۤv����
	bool m_isShooting;
	bool m_isHurting;
	bool m_isDead;
	bool m_keyState[4];//MainPlane�~�ݭn
	int m_hp,m_hpMax;
	float m_unit;//���ʳ��
	float m_BAngle;//�l�u����
	std::vector<GLuint> m_deadAnime;//���`����ʵe��Texture
	std::vector<float> m_animeTexCoord;//�R��ɤH���ʵe�K�Ϯy��
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
	void Shoot();//�̷Ӳ{�b���A�ݭn���nshoot
	void ShootOn(double,WEAPON);
	void ShootOFF();
	void CheckState();//�ˬd�{�b���A
	void StayAnime();//�R��ɪ��ʵe
	void deadAnime(float);//���`�ɪ��ʵe
	void HurtAnime(float);//���`�ɪ��ʵe
	void ChangeWeapon(WEAPON weapon);
	void SetBulletSpeed(int);
	void SetBullet(GLuint texID,float w,float h,float angle);//�]�w�l�u����
	void SetBullet(GLuint texID,float w,float h,float angle,float left,float right,float top,float down);
	void SetAnimeTexCoord(float *t,int first,int last);//�]�w�R��ɤH���ʵeTexCoord
};

#endif
