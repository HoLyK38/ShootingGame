Plane *target;

void Script();
inline bool TimeDiff(float n,float firstTime,float lastTime);
void MoveTo(float x,float y);


void Script()
{
	//std::cout<<"ScriptTime"<<std::endl;
	if ( TimeDiff(gameTime,2,4) ){
		MoveTo(300,300);
	}

	if ( TimeDiff(gameTime,4,8) ){
		target->m_weapon = wAllAngle;
		target->m_isShooting = true;
	}
}
inline bool TimeDiff(float n,float firstTime,float lastTime)
{
	if( n>firstTime && n<lastTime )
		return true;
	else
		return false;
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
