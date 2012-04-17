#include "Plane.h"
#include "BulletManager.h"
Plane::~Plane(){}
Plane::Plane(GLuint id , float x,float y,float w,float h):QUAD(id ,x, y, w, h,0)
{
	this->m_isShooting = false;
	this->m_hurting = false;
	this->m_BM = new BulletManager();
	this->m_state = NONE;
	this->m_weapon = wSINGLE;
	this->m_hp = 100;
	this->m_unit = 5;
}

void Plane::Update(float deltaTime)
{
	if( this->m_hp < 0 )
		this->deadAnime(deltaTime);

	static float sumTime=0;
	if( sumTime > 0.1 ){
		this->Shoot();
		this->StayAnime();
		sumTime = deltaTime;
	}
	else
		sumTime+=deltaTime;

	this->Draw();
	this->m_BM->Update(deltaTime);
	this->CheckState();
}
void Plane::ChangeWeapon(WEAPON weapon)
{
	this->m_weapon = weapon;
}
void Plane::CheckState()
{
	switch (m_state){
		case LEFT:
			this->m_x -= m_unit;
			break;
		case RIGHT:
			this->m_x += m_unit;
			break;
		case UP:
			this->m_y += m_unit;
			break;
		case DOWN:
			this->m_y -= m_unit;	
			break;
		case LU:
			this->m_x -= m_unit;
			this->m_y += m_unit;
			break;
		case LD:
			this->m_x -= m_unit;
			this->m_y -= m_unit;
			break;
		case RU:
			this->m_x += m_unit;
			this->m_y += m_unit;
			break;
		case RD:
			this->m_x += m_unit;
			this->m_y -= m_unit;
			break;
	}
}
void Plane::Shoot()
{
	if(this->m_isShooting){
		Bullet b_temp = Bullet(m_bullet->m_textureID,this->m_x,this->m_y+36
								,m_bullet->m_w,m_bullet->m_h,m_bullet->m_angle);
		b_temp.m_left = m_bullet->m_left;
		b_temp.m_right = m_bullet->m_right;
		b_temp.m_top = m_bullet->m_top;
		b_temp.m_down = m_bullet->m_down;
		switch ( this->m_weapon ){
		case wSINGLE :
			break;
		case wDOUBLE :
			break;
		case wTRIPLE :
			break;
		default:
			break;
		}
	}
	//glutPostRedisplay();
}
void Plane::StayAnime()
{
	static int value = 0;
	if ( this->m_state==LEFT || this->m_state==RIGHT )
		value = 0;
	else if ( value < this->m_animeTexCoord.size() )
		this->SetTexCoord( this->m_animeTexCoord[value] , this->m_animeTexCoord[value+1]);
	else
		this->SetTexCoord( this->m_animeTexCoord[value=0] , this->m_animeTexCoord[value+1]);
	value +=2;
}
void Plane::HurtAnime(float deltaTime)
{
	static float sumTime =0;
	static int n =0;
	if ( n >= m_deadAnime.size()-1 ){
		sumTime = 0;
		n = 0;
		this->m_hurting = false;
		this->m_textureID = m_deadAnime[0];
	}
	else if( sumTime > 0.02){
		this->m_textureID = m_deadAnime[n];
		n++;
		sumTime = deltaTime;
	}else{
		sumTime += deltaTime;
	}
}
void Plane::deadAnime(float deltaTime)
{
	static float sumTime =0;
	static int n =0;
	if ( n >= m_deadAnime.size() ){
		sumTime = 0;
		n = 0;
		this->m_state = DEAD;
	}
	else if( sumTime > 0.02){
		this->m_textureID = m_deadAnime[n];
		n++;
		sumTime = deltaTime;
	}else{
		sumTime += deltaTime;
	}
}
void Plane::SetAnimeTexCoord(float *t,int first,int last)
{
	this->m_animeTexCoord.insert(this->m_animeTexCoord.begin(),t+first,t+last);
}
void Plane::SetBullet(GLuint texID,float w,float h,float angle)
{
	m_bullet = new Bullet(texID,0,0,w,h,angle);
}
void Plane::SetBullet(GLuint texID,float w,float h,float angle,
	float left,float right,float top,float down)
{
	m_bullet = new Bullet(texID,0,0,w,h,angle);
	m_bullet->SetTexCoord(left,right,top,down);
}