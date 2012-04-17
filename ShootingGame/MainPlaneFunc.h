#include "BulletTrack.h"
//void MainShootTimerFunc(int);
//void MainAnime(int);//靜止時人物動畫
//void MainMoveTimer(int);

/*
void MainAnime(int value)
{
	if ( mainPlane->m_state==LEFT || mainPlane->m_state==RIGHT )
		value = 0;
	else if ( value < 8 )
		mainPlane->SetTexCoord( aTexCoord[value] , aTexCoord[value]+25);
	else{
		value = 0;
		mainPlane->SetTexCoord( aTexCoord[value] , aTexCoord[value]+25);
	}
	glutTimerFunc(100, MainAnime, value+1);
	glutPostRedisplay();
}
void MainMoveTimer(int value)
{
	if ( mainPlane->m_keyState[0] )
		mainPlane->m_x -=5;
	if ( mainPlane->m_keyState[1] )
		mainPlane->m_x +=5;
	if ( mainPlane->m_keyState[2] )
		mainPlane->m_y +=5;
	if ( mainPlane->m_keyState[3] )
		mainPlane->m_y -=5;
	if ( mainPlane->m_keyState[0] || mainPlane->m_keyState[1] || mainPlane->m_keyState[2] || mainPlane->m_keyState[3])
		glutTimerFunc(10,MainMoveTimer,value);
	glutPostRedisplay();
}*/

/*void MainShootTimerFunc(int value)
{
	if(mainPlane->m_isShooting){
		Bullet b_temp = Bullet(MainPlaneTex,mainPlane->m_x,mainPlane->m_y+36,31,14,90);;
		b_temp.SetTexCoord(0,30,241,254);
		switch ( mainPlane->m_weapon ){
		case wSINGLE :
			b_temp.SetStart(mainPlane->m_x ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			break;
		case wDOUBLE :
			b_temp.SetStart(mainPlane->m_x-10 ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			b_temp.SetStart(mainPlane->m_x+10 ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			break;
		case wTRIPLE :
			b_temp.SetStart(mainPlane->m_x ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			b_temp.SetStart(mainPlane->m_x-10 ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line2);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			b_temp.SetStart(mainPlane->m_x+10 ,mainPlane->m_y+36 );
			b_temp.SetTrack(Track_Line1);//Track Set
			//mainBM->Push(b_temp);
			mainPlane->m_BM->Push(b_temp);
			break;
		default:
			break;
		}
	}
	glutTimerFunc(10,MainShootTimerFunc,value);
	glutPostRedisplay();
}*/