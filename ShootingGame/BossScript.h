using namespace std;
Plane *target;
bool Script();
inline void Action_Move(float x,float y);
inline void Action_Shoot(GLuint bTex,int speed,WEAPON w,double angle);
inline bool TimeDiff(float n,float firstTime,float lastTime);
void MoveTo(float x,float y);
void AtkTimer(int);
void TitleTimer(int);
void bossAction(int n);
void BossHpDraw();
void InitBoss();
float atkTexCoord[][4] ={   {4,51,171,241} ,
{69,115,171,241} ,
{141,191,171,241} ,
{205,253,171,241} , 
{13,51,11,81} };
float timeScript[][2] = {
	{2,3} ,//shoot1
	{3,5} ,//move2
	{5,6} ,//shoot3
	{6,8} ,//move4
	{8,9} ,//shoot5
	{10,11.5} ,//move6
	{11.5,13.5} ,//shoot7
	{13.5,15} ,//move8
	{15.1,15.2} ,//shoot9
	{15.2,15.4} ,//shoot10
	{15.4,15.6} ,//shoot11
	{15.6,15.8} ,//shoot12
	{18,22} ,//shoot13
	{20,22} ,//shoot14
	{1,2} ,//shoot15
	{22,24} ,//shoot 16
	{24,27} ,//shoot 17
	{16,18} ,//move18
	{27,28} ,//shoot 19
	{28,30} ,//move 20
	{30,30.2} ,//shootall 21
	{30.2,30.4} ,//shootall 22
	{30.4,30.6} ,//shootall 23
	{30.6,31} ,//shootall 24
	{31,32} ,//move 25
	{32,33} ,//shoot 26
	{33,34} ,//shoot 26
};
float endTime=34.5;
int scriptSize = 27;//^
bool playTitle=false;;
bool Script()
{
	
	static int n = 0;
	if(target->m_state<0 || target->m_state>8 || target->m_isDead)
		return false;
	if ( gameTime >= endTime || isGameover ){
		n = 0;
		gameTime = 0;
		//playTitle = false;
		target->SetBulletSpeed(10);
		target->m_state = NONE;
		target->ShootOFF();
	}
	if (!playTitle){
		glutTimerFunc(10,TitleTimer,0);
	}

	BossHpDraw();
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
	//cout<<n<<endl;
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
	static float temp2=0;
	switch ( n ){
	case 0:
		temp += 15;
		temp =float ( int(temp) % 360);
		Action_Shoot(BulletTex[0],10,wDOUBLE,temp);
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
		Action_Shoot(BulletTex[2],10,wAllAngle,75);
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
		Action_Shoot(BulletTex[0],6,wAllAngle,rand()% 360);
		break;
	case 9:
		Action_Shoot(BulletTex[1],2.5,wAllAngle,rand()% 360);
		break;
	case 10:
		Action_Shoot(BulletTex[0],6,wAllAngle,rand()% 360);
		break;
	case 11:
		Action_Shoot(BulletTex[1],2.5,wAllAngle,rand()% 360);
		break;
	case 12:
		if ( temp2 >0.1 ){
			temp += 15;
			temp =float ( int(temp) % 360);
			Action_Shoot(BulletTex[2],10,wSINGLE,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 13:
		if ( temp2 >0.05 ){
			/*temp += 30;
			temp =float ( int(temp) % 360);*/
			
			temp = rand()% 360;
			Action_Shoot(BulletTex[0],6,wAllAngleT,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 14:
		if ( temp2 >0.05 ){
			temp = rand()% 360;
			Action_Shoot(BulletTex[1],6,wAllAngleT,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 15:
		if ( temp2 >0.1 ){
			temp += 10;
			temp =float ( int(temp) % 360);
			Action_Shoot(BulletTex[2],5,wCross,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 16:
		if ( temp2 >0.04 ){
			temp =temp + 20 + rand()% 360;
			temp =float ( int(temp) % 360) ;
			Action_Shoot(BulletTex[1],8,wCross,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 17:
		Action_Move(0,300);
		break;
	case 18:
		Action_Move(0,0);
	case 19:
		if ( temp2 >0.03 ){
			temp =temp + 20 + rand()% 360;
			temp =float ( int(temp) % 360) ;
			Action_Shoot(BulletTex[1],8,wCross,temp);
			temp2 = deltaTime;
		}
		break;
	case 20:
		Action_Move(0,-200);
		break;
	case 21:
		Action_Shoot(BulletTex[0],8,wAllAngle,rand()% 360);
		break;
	case 22:
		Action_Shoot(BulletTex[1],3,wAllAngle,rand()% 360);
		break;
	case 23:
		Action_Shoot(BulletTex[2],8,wAllAngle,rand()% 360);
		break;
	case 24:
		Action_Shoot(BulletTex[0],3,wAllAngle,rand()% 360);
		break;
	case 25:
		Action_Move(0,0);
		break;
	case 26:
		if ( temp2 >0.1 ){
			temp += 10;
			temp =float ( int(temp) % 360);
			Action_Shoot(BulletTex[2],5,wAllAngle,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case 27:
		if ( temp2 >0.05 ){
			/*temp += 30;
			temp =float ( int(temp) % 360);*/
			
			temp = rand()% 360;
			Action_Shoot(BulletTex[0],6,wAllAngleT,temp);
			temp2 = deltaTime;
		}else
			temp2 += deltaTime;
		break;
	case -1:
		target->SetBulletSpeed(10);
		target->m_state = NONE;
		target->ShootOFF();
		break;
	}
}
void BossHpDraw()
{
	if(	target->m_hp>0	){
		float p = float (target->m_hp) / float(target->m_hpMax);
		float a = 300 * p;
		float b = 300 * (1-p)/2;
		bossHP->SetPoint( 480-b , bossHP->m_y  , a , bossHP->m_h,0);
		bossHP->Draw();
	}
	bossHPt->Draw();
}
void TitleTimer(int value)
{
	static bool isPlay = false;
	if( value==0 && isPlay==false ){
		isPlay = true;
		glutTimerFunc(200,TitleTimer,value+1);
	}
	else if( value < 7 && isPlay ==true ){
		StageTile->SetPoint(StageTile->m_x,StageTile->m_y + 1);
		glutTimerFunc(200,TitleTimer,value+1);
		clockReset = true;
		gameTime = 0;
	}else{
		isPlay = false;
		playTitle = true;
	}
}

void InitBoss()
{
	GLuint temp;
	//--
	LoadTexture("../Data/system/hp.bmp","../Data/system/hpalpha.bmp",temp);
	bossHP = new QUAD(temp,480,0,300,20);
	bossHP->SetImageWH(100,10);
	LoadTexture("../Data/system/ttt.bmp","../Data/system/tttalpha.bmp",temp);
	bossHPt = new QUAD(temp,480,0,300,20);
	bossHPt->SetImageWH(100,10);


	LoadTexture("../Data/character/boss.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime1.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime2.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime3.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);


	LoadTexture("../Data/system/stagetitle.bmp","../Data/system/stagetitlealpha.bmp",StageTileTex);
	StageTile = new QUAD(StageTileTex,0,0,184*2,26*2);
	StageTile->SetImageWH(184,26);



	LoadTexture("../Data/character/boss.bmp","../Data/character/bossalpha.bmp",BossPlaneTex);
	boss = new Plane(BossPlaneTex,0,0,39,71);
	boss->m_deadAnime = bossHurtTex;
	boss->SetImageWH(256,256);
	//boss->SetTexCoord(35,90,36,98);
	boss->SetTexCoord(13,51,11,81);
	boss->SetBullet(BulletTex[0],16,16,0);
	boss->m_hp = 5000;
	boss->m_hpMax = 5000;

	enemyM->Push(boss);
	//Script target
	target = boss;
}