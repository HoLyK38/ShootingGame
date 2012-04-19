Plane *target;

bool Script();
inline bool TimeDiff(float n,float firstTime,float lastTime);
void MoveTo(float x,float y);
using namespace std;

bool Script()
{
	if(target->m_state<-1 || target->m_state>8)
		return false;

	if ( TimeDiff(gameTime,0,1) ){
		static float temp=30;
		target->ShootOn(temp,wSINGLE);
		temp += 15;
	}
	else if ( TimeDiff(gameTime,1,2.5) ){
		target->ShootOFF();
		MoveTo(300,300);
	}
	else if ( TimeDiff(gameTime,2.5,3.5) ){
		boss->SetBullet(BulletTex[1],16,16,0);
		target->SetBulletSpeed(4);
		target->ShootOn(0,wAllAngle);
	}
	else if ( TimeDiff(gameTime,3.5,5) ){
		target->ShootOFF();
		MoveTo(0,0);
	}
	else if ( TimeDiff(gameTime,5,6.5) ){
		boss->SetBullet(BulletTex[2],16,16,0);
		target->SetBulletSpeed(10);
		target->ShootOn(0,wAllAngle);
	}
	else if ( TimeDiff(gameTime,6.5,8) ){
		target->ShootOFF();
		MoveTo(-300,300);
	}
	else if ( TimeDiff(gameTime,8,9.5) ){
		boss->SetBullet(BulletTex[1],16,16,0);
		target->SetBulletSpeed(4);
		target->ShootOn(0,wAllAngle);
	}
	else if ( TimeDiff(gameTime,0,999) ){
		target->SetBulletSpeed(10);
		target->m_state = NONE;
		target->ShootOFF();
	}
}
inline bool TimeDiff(float n,float firstTime,float lastTime)
{
	if( n>firstTime && n<lastTime ) return true;
	else return false;
}
void MoveTo(float x,float y)
{
	if( (target->m_x>=x && target->m_x<x+5) && 
		(target->m_y>=y && target->m_y<y+5) )
	{
		target->m_state = NONE;
	}else{
		float temp_x,temp_y;
		temp_x = x - target->m_x;
		temp_y = y - target->m_y;
		if (temp_x > 0 && (temp_y>=0 && temp_y<5) )
			target->m_state = RIGHT;
		else if (temp_x < 0 && (temp_y>=0 && temp_y<5) )
			target->m_state = LEFT;
		else if ( (temp_x>=0 && temp_x<5) && temp_y > 0)
			target->m_state = UP;
		else if ( (temp_x>=0 && temp_x<5) && temp_y < 0)
			target->m_state = DOWN;
		else if (temp_x > 0 && temp_y > 0)
			target->m_state = RU;
		else if (temp_x > 0 && temp_y < 0)
			target->m_state = RD;
		else if (temp_x < 0 && temp_y > 0)
			target->m_state = LU;
		else if (temp_x < 0 && temp_y < 0)
			target->m_state = LD;
	}
}
