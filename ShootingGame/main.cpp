#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <vector>
#include "../freeglut/glut.h"
#include "QUAD.h"
#include "Bullet.h"
#include "EnemyPlane.h"
#include "BulletManager.h"
#include "MainPlane.h"
#include "EnemyManager.h"
#include "Data.h"
#include "ConstData.h"
#include "GameTimer.h"
#include "MainPlaneFunc.h"
#include "LoadTextureFunc.h"
using namespace std;
void Reshape(int,int);            //負責視窗及繪圖內容的比例 
void Keyboard(unsigned char,int,int);   //獲取鍵盤輸入
void KeyboardUp(unsigned char,int,int) ;
void SpecialKeyboardUp(int,int,int);   //獲取鍵盤輸入
void SpecialKeyboard(int,int,int);//獲取特殊鍵盤輸入
void Display(void);                     //描繪 
void Init();//初始化子彈人物敵機資訊
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(winWidth,winHeight);	//< Dual view
	glutInitWindowPosition(0,0);
	glutCreateWindow(argv[0]);
	//--------------------------------------------------
	gameTimer.tick();
	Init();
	//--------------------------------------------------
	glutReshapeFunc(Reshape); 
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(Display);
	//---Timer
	//glutTimerFunc(100,MainAnime,0);
	//glutTimerFunc(10,MainShootTimerFunc,0);
	//---Timer
	glutMainLoop(); 
	return 0; 
}
void Display(void) 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//用黑色0 0 0塗背景
	//glClearColor(1.0, 1.0, 1.0, 1.0);//用白色1 1 1塗背景
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0,0,400,0,0,0,0,1,0);   //視線的座標及方向
	//---------caculate time----------------------------
	gameTimer.tick();
	deltaTime = gameTimer.getDeltaTime();
	//---------update-----------------------------------
	mainPlane->Update(deltaTime);
	mainPlane->m_BM->isCollide(enemyM);
	enemyM->Update(deltaTime);
	//--------------------------------------------------
	glutPostRedisplay(); 
	glutSwapBuffers();
}
void Keyboard(unsigned char key, int x, int y) 
{
	switch (key)
	{
		case 'x':
			boss = new EnemyPlane(BossPlaneTex,0,300,56,63);
			for(int i=0;i<3;i++)
				boss->m_deadAnime[i] = testAnime[i];
			boss->SetImageWH(256,128);
			boss->SetTexCoord(35,90,36,98);
			enemyM->Push(*boss);
			break;
		case 'v':
			mainPlane->ChangeWeapon(wSINGLE);
			break;
		case 'c':
			mainPlane->ChangeWeapon(wDOUBLE);
			break;
		case 'a':
			mainPlane->ChangeWeapon(wTRIPLE);
			break;
		case 'Z':
			mainTrackPtr = Track_Sin;
			mainPlane->m_isShooting = true;
			break;
		case 'z':
			mainTrackPtr = Track_Line1;
			mainPlane->m_isShooting = true;
			break;
	}
	glutPostRedisplay(); 
}
void KeyboardUp(unsigned char key, int x, int y) 
{
	switch (key)
	{
		case 'Z':
		case 'z':
			mainPlane->m_isShooting = false;
			break;
	}
	glutPostRedisplay(); 
}
void SpecialKeyboard(int key, int x, int y) 
{
	switch (key)
	{
		case GLUT_KEY_UP:
			/*if( !(mainPlane->m_keyState[0] || mainPlane->m_keyState[1] || mainPlane->m_keyState[2] || mainPlane->m_keyState[3]) )
				glutTimerFunc(10, MainMoveTimer, 3);*/
			mainPlane->m_keyState[2] = true;
			break;
		case GLUT_KEY_DOWN:
			/*if( !(mainPlane->m_keyState[0] || mainPlane->m_keyState[1] || mainPlane->m_keyState[2] || mainPlane->m_keyState[3]) )
				glutTimerFunc(10, MainMoveTimer, 4);*/
			mainPlane->m_keyState[3] = true;
			break;
		case GLUT_KEY_LEFT:
			/*if( !(mainPlane->m_keyState[0] || mainPlane->m_keyState[1] || mainPlane->m_keyState[2] || mainPlane->m_keyState[3]) )
				glutTimerFunc(10, MainMoveTimer, 1);*/
			mainPlane->SetTexCoord(131,156,51,94);
			mainPlane->m_keyState[0] = true;
			mainPlane->m_state = LEFT;
			break;
		case GLUT_KEY_RIGHT:
			/*if( !(mainPlane->m_keyState[0] || mainPlane->m_keyState[1] || mainPlane->m_keyState[2] || mainPlane->m_keyState[3]) )
				glutTimerFunc(10, MainMoveTimer, 2);*/
			mainPlane->SetTexCoord(131,156,99,142);
			mainPlane->m_keyState[1] = true;
			mainPlane->m_state = RIGHT;
			break;
	}
	glutPostRedisplay(); 
}
void SpecialKeyboardUp(int key, int x, int y) 
{
	
	switch (key)
	{
		case GLUT_KEY_UP:
			mainPlane->m_keyState[2] = false;
			break;
		case GLUT_KEY_DOWN:
			mainPlane->m_keyState[3] = false;
			break;
		case GLUT_KEY_LEFT:
			mainPlane->SetTexCoord(3,28,3,46);
			mainPlane->m_keyState[0] = false;
			mainPlane->m_state = NONE;
			break;
		case GLUT_KEY_RIGHT:
			mainPlane->SetTexCoord(3,28,3,46);
			mainPlane->m_keyState[1] = false;
			mainPlane->m_state = NONE;
			break;
	}
	glutPostRedisplay(); 
}
void Reshape(int w, int h) 
{
	winWidth = w;
	winHeight = h;
	glViewport(0,0,w,h);
	/*GLfloat aspect;
	aspect=(GLfloat)w / (GLfloat)h;
	if(aspect > 1.0f)
		glViewport((w-h)/2.0f,0,(GLsizei)h,(GLsizei)h);
	else
		glViewport(0,(h-w)/2.0f,(GLsizei)w,(GLsizei)w);*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}
void Init()
{

	LoadTexture("../Data/002.bmp","../Data/002alpha.bmp",MainPlaneTex);
	LoadTexture("../Data/002.bmp","../Data/002alpha.bmp",MainPlaneTex);
	LoadTexture("../Data/aaa.bmp","../Data/aaaalpha.bmp",BossPlaneTex);
	LoadTexture("../Data/bullet1.bmp","../Data/bullet1alpha.bmp",Bullet1Tex);

	GLuint temp;
	LoadTexture("../Data/aaa.bmp","../Data/aaaalpha.bmp",temp);
	testAnime.push_back(temp);
	LoadTexture("../Data/test1.bmp","../Data/aaaalpha.bmp",temp);
	testAnime.push_back(temp);
	LoadTexture("../Data/test2.bmp","../Data/aaaalpha.bmp",temp);
	testAnime.push_back(temp);
	LoadTexture("../Data/test3.bmp","../Data/aaaalpha.bmp",temp);
	testAnime.push_back(temp);
	//tb = new Bullet(Bullet1Tex,30,30,100,100,0);

	//mainBM = new BulletManager();
	enemyM = new EnemyManager();


	//Init QUAD need to set ImageWH and TexCoord
	mainPlane = new MainPlane(MainPlaneTex,0,0,26,44);
	mainPlane->SetImageWH(256,256);
	mainPlane->SetTexCoord(3,28,3,46);
	mainPlane->SetAnimeTexCoord(selfTexCoord,0,16);
	mainPlane->SetBullet(Bullet1Tex,16,16,0);
	//mainPlane->SetBullet(MainPlaneTex,31,15,90,0,30,241,255);

	boss = new EnemyPlane(BossPlaneTex,0,300,56,63);
	boss->m_deadAnime = testAnime;
	boss->SetImageWH(256,128);
	boss->SetTexCoord(35,90,36,98);

	

	enemyM->Push(*boss);

}
