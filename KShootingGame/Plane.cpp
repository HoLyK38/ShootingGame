#include "Plane.h"
#include "BulletManager.h"
#include "BulletTrack.h"
Plane::~Plane(){}
Plane::Plane(GLuint id , float x,float y,float w,float h):Ball(id ,x, y, w, h,0)
{
	this->m_isShooting = false;
	this->m_isHurting = false;
	this->m_isDead = false;
	this->m_BM = new BulletManager();
	this->m_state = NONE;
	this->m_weapon = wSINGLE;
	this->m_hp = 100;
	this->m_hpMax = m_hp;
	this->m_unit = 5;
	this->m_BAngle = 0;
	this->m_isAuto = true;
	for(int i=0;i<4;i++) this->m_keyState[i] = false;
}
void Plane::Update(float deltaTime)
{
	if( this->m_hp <= 0 )
		this->deadAnime(deltaTime);
	else if ( this->m_isHurting )
		this->HurtAnime(deltaTime);

	static float sumTime=0;

	if( sumTime > 0.1 ){
		this->Shoot();
		if(this->m_animeTexCoord.size()!=0)this->StayAnime();
		sumTime = deltaTime;
	}
	else
		sumTime+=deltaTime;

	this->Render();
	this->m_BM->Update(deltaTime);
	if(m_isAuto) this->CheckState();
	else this->Move();
}
void Plane::ChangeWeapon(WEAPON weapon)
{
	this->m_weapon = weapon;
}
void Plane::CheckState()
{
	switch (m_state){
		case LEFT:
			this->m_pos.x -= m_unit;
			break;
		case RIGHT:
			this->m_pos.x += m_unit;
			break;
		case UP:
			this->m_pos.y += m_unit;
			break;
		case DOWN:
			this->m_pos.y -= m_unit;	
			break;
		case LU:
			this->m_pos.x -= m_unit;
			this->m_pos.y += m_unit;
			break;
		case LD:
			this->m_pos.x -= m_unit;
			this->m_pos.y -= m_unit;
			break;
		case RU:
			this->m_pos.x += m_unit;
			this->m_pos.y += m_unit;
			break;
		case RD:
			this->m_pos.x += m_unit;
			this->m_pos.y -= m_unit;
			break;
	}
	if(this->m_pos.x >300)
		this->m_pos.x -= m_unit;
	if(this->m_pos.x <-300)
		this->m_pos.x += m_unit;
	if(this->m_pos.y >400)
		this->m_pos.y -= m_unit;
	if(this->m_pos.y <-400)
		this->m_pos.y += m_unit;
}
void Plane::Shoot()
{
	if(this->m_isShooting){
		Bullet b_temp = *m_bullet->Copy();
		switch ( this->m_weapon ){
		case wSINGLE :
			b_temp.SetStart(this->m_pos.x+36*sin(m_BAngle*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			break;
		case wDOUBLE :
			b_temp.SetStart(this->m_pos.x+36*sin((m_BAngle+15)*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			b_temp.SetStart(this->m_pos.x+36*sin((m_BAngle-15)*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			break;
		case wTRIPLE :
			b_temp.SetStart(this->m_pos.x+36*sin((m_BAngle+15)*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle+30,Track_Angle);
			this->m_BM->Push(b_temp);
			b_temp.SetStart(this->m_pos.x+36*sin((m_BAngle)*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			b_temp.SetStart(this->m_pos.x+36*sin((m_BAngle-15)*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle-30,Track_Angle);
			this->m_BM->Push(b_temp);
			break;
		case wAllAngle:
			for(double i = 0 ; i < 360 ; i += 15)
			{
				b_temp.SetStart(this->m_pos.x+36*sin(i*PI/180) ,this->m_pos.y+36*cos(i*PI/180));
				b_temp.SetTrack(i+m_BAngle,Track_Angle);//Track Set
				this->m_BM->Push(b_temp);
			}
			break;
		case wAllAngleT:
			for(double i = 0 ; i < 360 ; i += 45)
			{
				b_temp.SetStart(this->m_pos.x+36*sin(i*PI/180) ,this->m_pos.y+36*cos(i*PI/180));
				b_temp.SetTrack(i+m_BAngle,Track_Angle);//Track Set
				this->m_BM->Push(b_temp);
			}
			break;
		case wCross:
			b_temp.SetStart(this->m_pos.x+36*sin(m_BAngle*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			m_BAngle += 90;
			b_temp.SetStart(this->m_pos.x+36*sin(m_BAngle*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			m_BAngle += 90;
			b_temp.SetStart(this->m_pos.x+36*sin(m_BAngle*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			m_BAngle += 90;
			b_temp.SetStart(this->m_pos.x+36*sin(m_BAngle*PI/180) ,this->m_pos.y+36*cos(m_BAngle*PI/180));
			b_temp.SetTrack(m_BAngle,Track_Angle);
			this->m_BM->Push(b_temp);
			m_BAngle += 90;
			m_BAngle -= 360;
			break;
		default:
			break;
		}
	}
}
void Plane::ShootOn(double a,WEAPON w)
{
	this->m_weapon = w;
	this->m_BAngle =a;
	this->m_isShooting = true;
}
void Plane::ShootOFF()
{
	this->m_isShooting = false;
}
void Plane::Move()
{
	if ( this->m_keyState[0] )
		this->m_pos.x -=m_unit;
	if ( this->m_keyState[1] )
		this->m_pos.x +=m_unit;
	if ( this->m_keyState[2] )
		this->m_pos.y +=m_unit;
	if ( this->m_keyState[3] )
		this->m_pos.y -=m_unit;
	if(this->m_pos.x >300)
		this->m_pos.x -= m_unit;
	if(this->m_pos.x <-300)
		this->m_pos.x += m_unit;
	if(this->m_pos.y >400)
		this->m_pos.y -= m_unit;
	if(this->m_pos.y <-400)
		this->m_pos.y += m_unit;
}
void Plane::Move(PlaneState s)
{
	this->m_state = s;
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
		this->m_isHurting = false;
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
		this->m_isDead = true;
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
void Plane::SetBulletSpeed(int u)
{
	m_bullet->m_unit = u;
}