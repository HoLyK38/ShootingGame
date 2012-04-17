#include "MainPlane.h"
#include "BulletManager.h"
MainPlane::MainPlane(GLuint id , float x,float y,float w,float h):Plane(id ,x, y, w, h)
{
	for(int i=0;i<4;i++) this->m_keyState[i] = false;
}
void MainPlane::Update(float deltaTime)
{
	if( this->m_hp < 0 ){
		this->m_state = DEAD;
	}

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
	this->Move();
	
}
void Track_Linea(Bullet* b)
{
	b->m_y += b->m_unit;
}
void MainPlane::Shoot()
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
			b_temp.SetStart(this->m_x,this->m_y+36);
			b_temp.SetTrack(Track_Linea);
			this->m_BM->Push(b_temp);
			break;
		case wDOUBLE :
			break;
		case wTRIPLE :
			break;
		default:
			break;
		}
	}
}
void MainPlane::Move()
{
	if ( this->m_keyState[0] )
		this->m_x -=5;
	if ( this->m_keyState[1] )
		this->m_x +=5;
	if ( this->m_keyState[2] )
		this->m_y +=5;
	if ( this->m_keyState[3] ){
	    this->m_y -=5;		
	}
}