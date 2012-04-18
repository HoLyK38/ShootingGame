#include "Bullet.h"
float t[]={0,32,64,96};
Bullet::~Bullet(){}
Bullet::Bullet(GLuint a , float x,float y,float w,float h,float angle):QUAD(a ,x, y, w, h, angle)
{
	this->m_atk = 10;
	this->m_unit = 10;
	this->m_speed = 10;
	this->m_startX = x;
	this->m_startY = y;
	this->m_state = STOP;
	this->SetPoint(x,y);
	this->m_angle = 0;
}
Bullet::Bullet(GLuint a , float w,float h,float angle):QUAD(a ,0, 0, w, h, angle)
{
	this->m_atk = 10;
	this->m_unit = 10;
	this->m_speed = 10;
	this->m_startX = 0;
	this->m_startY = 0;
	this->m_state = STOP;
	this->SetPoint(0,0);
	this->m_angle = 0;
}

void Bullet::SetStart(float a, float b)
{
	this->m_startX = a;
	this->m_startY = b;
	this->SetPoint(a,b);

}
void Bullet::Track()
{
	if( m_trackPtr!=NULL )
		m_trackPtr(this);
}
void Bullet::SetTrack(double angle,TrackPtr t)
{
	this->m_angle = angle;
	this->m_trackPtr = t;
}
void Bullet::SetTrack(TrackPtr t)
{
	this->m_trackPtr = t;
}


void Bullet::Update(float deltaTime)
{
	this->Draw();
	this->Track();
}
bool Bullet::isCollide(const Plane *Q)
{
	if (Q!=NULL){
		bool xIsCollided = false,yIsCollided = false;
		if ( (m_x + m_w/2) > (Q->m_x - Q->m_w/2) && (m_x + m_w/2) < (Q->m_x + Q->m_w/2) ) xIsCollided = true;
		else if ( (m_x - m_w/2) > (Q->m_x - Q->m_w/2) && (m_x + m_w/2) < (Q->m_x + Q->m_w/2) ) xIsCollided = true;
		else if ( m_x > (Q->m_x - Q->m_w/2) && m_x < (Q->m_x + Q->m_w/2) ) xIsCollided = true;

		if ( (m_y + m_h/2) > (Q->m_y - Q->m_h/2) && (m_y + m_h/2) < (Q->m_y + Q->m_h/2) ) yIsCollided = true;
		else if ( (m_y - m_h/2) > (Q->m_y - Q->m_h/2) && (m_y + m_h/2) < (Q->m_y + Q->m_h/2) ) yIsCollided = true;
		else if ( m_y > (Q->m_y - Q->m_h/2) && m_y < (Q->m_y + Q->m_h/2) ) yIsCollided = true;

		if ( xIsCollided==true && yIsCollided==true ) return true;
		else return false;
	}else return false;
}