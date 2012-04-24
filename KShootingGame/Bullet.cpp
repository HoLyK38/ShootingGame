#include "Bullet.h"
Bullet::~Bullet(){}
Bullet::Bullet(GLuint a , float x,float y,float w,float h,float angle):Ball(a ,x, y, w, h, angle)
{
	this->m_atk = 10;
	this->m_unit = 10;
	this->m_speed = 0.015;
	this->m_startX = x;
	this->m_startY = y;
	this->m_state = STOP;
	this->SetPoint(x,y);
	this->m_shotAngle = 0;
}
Bullet::Bullet(GLuint a , float w,float h,float angle):Ball(a ,0, 0, w, h, angle)
{
	this->m_atk = 10;
	this->m_unit = 10;
	this->m_speed = 0.015;
	this->m_startX = 0;
	this->m_startY = 0;
	this->m_state = STOP;
	this->SetPoint(0,0);
	this->m_shotAngle = 0;
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
void Bullet::SetTrack(TrackPtr t)
{
	this->SetTrack(0,t);
}
void Bullet::SetTrack(double shotAngle,TrackPtr t)
{
	this->m_shotAngle = shotAngle;
	this->m_trackPtr = t;
}
void Bullet::Update(float deltaTime)
{
	this->Render();
	this->Track();
}
bool Bullet::isCollide(Plane *Q)
{
	Vector2 tpos = Q->GetPos();
	float tw = Q->GetWidth();
	float th = Q->GetHeight();

	if (Q!=NULL){
		bool xIsCollided = false,yIsCollided = false;
		if ( (m_pos.x + m_width/2) > (tpos.x - tw/2) && (m_pos.x + m_width/2) < (tpos.x + tw/2) ) xIsCollided = true;
		else if ( (m_pos.x - m_width/2) > (tpos.x - tw/2) && (m_pos.x + m_width/2) < (tpos.x + tw/2) ) xIsCollided = true;
		else if ( m_pos.x > (tpos.x - tw/2) && m_pos.x < (tpos.x + tw/2) ) xIsCollided = true;

		if ( (m_pos.y + m_height/2) > (tpos.y - th/2) && (m_pos.y + m_height/2) < (tpos.y + th/2) ) yIsCollided = true;
		else if ( (m_pos.y - m_height/2) > (tpos.y - th/2) && (m_pos.y + m_height/2) < (tpos.y + th/2) ) yIsCollided = true;
		else if ( m_pos.y > (tpos.y - th/2) && m_pos.y < (tpos.y + th/2) ) yIsCollided = true;

		if ( xIsCollided==true && yIsCollided==true ) return true;
		else return false;
	}else return false;
}
Bullet* Bullet::Copy()
{
	return new Bullet(m_textureID , m_pos.x , m_pos.y ,
					  m_width , m_height , m_angle );
}