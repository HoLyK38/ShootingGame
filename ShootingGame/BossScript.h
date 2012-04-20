using namespace std;
Plane *target;
bool Script();
inline void Action_Move(float x,float y);
inline void Action_Shoot(GLuint bTex,int speed,WEAPON w,double angle);
inline bool TimeDiff(float n,float firstTime,float lastTime);
void MoveTo(float x,float y);
void AtkTimer(int);
void bossAction(int n);
float atkTexCoord[][4] ={   {4,51,171,241} ,
{69,115,171,241} ,
{141,191,171,241} ,
{205,253,171,241} , 
{13,51,11,81} };
float timeScript[][2] = {
	{2,3} ,//shoot
	{3,5} ,//move
	{5,6} ,//shoot
	{6,8} ,//move
	{8,9} ,//shoot
	{10,11.5} ,//move
	{11.5,13.5} ,//shoot
	{13.5,15} ,//move
	{15.1,15.2} ,//shoot
	{15.2,15.4} ,//shoot
	{15.4,15.6} ,//shoot
	{15.6,15.8} ,//shoot
};
int scriptSize = 12;//^
bool Script()
{
	static int n=0;
	if(target->m_state<0 || target->m_state>8 || target->m_isDead)
		return false;
	if ( gameTime >= timeScript[scriptSize-1][1] ){
		n = 0;
		gameTime = 0;
		target->SetBulletSpeed(10);
		target->m_state = NONE;
		target->ShootOFF();
	}
	//搜尋目前時間 要做何種腳本
	int i;
	for(i=0;i<scriptSize;i++){
		if( TimeDiff(gameTime,timeScript[i][0],timeScript[i][1] ) ){
			n = i;
			break;
		}
	}
	if ( i == scriptSize )
		n = -1;
	cout<<n<<endl;
	bossAction(n);
}

inline void Action_Move(float x,float y){
	target->ShootOFF();
	MoveTo(x,y);
}
inline void Action_Shoot(GLuint bTex,int speed,WEAPON w,double angle){
	glutTimerFunc(10,AtkTimer,0);
	target->SetBullet(bTex,16,16,0);
	target->SetBulletSpeed(speed);
	target->ShootOn(angle,w);
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
void AtkTimer(int value)
{
	static bool isPlay = false;
	if( value==0 && isPlay==false ){
		isPlay = true;
		target->SetTexCoord(atkTexCoord[value][0],atkTexCoord[value][1],atkTexCoord[value][2],atkTexCoord[value][3]);
		target->SetPoint(target->m_x,target->m_y,atkTexCoord[value][1]-atkTexCoord[value][0],target->m_h,0);
		glutTimerFunc(100,AtkTimer,value+1);
	}else if( value == 0 && isPlay==true )
		isPlay = true;
	else if( value < 5 && isPlay ==true && value!=0 ){
		target->SetTexCoord(atkTexCoord[value][0],atkTexCoord[value][1],atkTexCoord[value][2],atkTexCoord[value][3]);
		target->SetPoint(target->m_x,target->m_y,atkTexCoord[value][1]-atkTexCoord[value][0],target->m_h,0);
		glutTimerFunc(200,AtkTimer,value+1);
	}else{
		isPlay = false;
	}

}
void bossAction(int n)
{
	static float temp=30;
	switch ( n ){
	case 0:
		Action_Shoot(BulletTex[0],10,wDOUBLE,temp);
		temp += 15;
		break;
	case 1:
		Action_Move(280,320);
		break;
	case 2:
		Action_Shoot(BulletTex[1],4,wAllAngle,0);
		break;
	case 3:
		Action_Move(0,0);
		break;
	case 4:
		Action_Shoot(BulletTex[2],10,wAllAngle,0);
		break;
	case 5:
		Action_Move(-280,320);
		break;
	case 6:
		Action_Shoot(BulletTex[1],4,wAllAngle,0);
		break;
	case 7:
		Action_Move(0,0);
		break;
	case 8:
		Action_Shoot(BulletTex[0],10,wAllAngle,0);
		break;
	case 9:
		Action_Shoot(BulletTex[1],4,wAllAngle,0);
		break;
	case 10:
		Action_Shoot(BulletTex[0],10,wAllAngle,0);
		break;
	case 11:
		Action_Shoot(BulletTex[1],4,wAllAngle,0);
		break;
	case -1:
		target->SetBulletSpeed(10);
		target->m_state = NONE;
		target->ShootOFF();
		break;
	}
}