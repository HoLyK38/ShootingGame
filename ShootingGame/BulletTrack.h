#ifndef TRACK_H
#define TRACK_H

const float PI=3.14159265;
void Track_Angle(Bullet* b);
void Track_Line(Bullet* b);
void Track_Line1(Bullet* b);
void Track_Line2(Bullet* b);
void Track_Sin(Bullet* b);


void Track_Angle(Bullet* b)
{
	b->m_y +=  b->m_unit * cos(b->m_angle*PI/180);
	b->m_x +=  b->m_unit * sin(b->m_angle*PI/180);
}
void Track_Line(Bullet* b)
{
	b->m_y += b->m_unit;
}
void Track_Line1(Bullet* b)
{
	b->m_x += b->m_unit * 0.5;
	b->m_y += b->m_unit;
}
void Track_Line2(Bullet* b)
{
	b->m_x += b->m_unit * (-0.5);
	b->m_y += b->m_unit;
}
void Track_Sin(Bullet* b)
{
	b->SetPoint( b->m_startX + sin( (b->m_y-b->m_startY) / 50 )*50 , b->m_y + b->m_unit );
}
#endif