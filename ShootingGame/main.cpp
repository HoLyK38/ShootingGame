#include "INCLUDE.h"
using namespace std;
void Reshape(int,int);            //負責視窗及繪圖內容的比例 
void Keyboard(unsigned char,int,int);   //獲取鍵盤輸入
void KeyboardUp(unsigned char,int,int) ;
void SpecialKeyboardUp(int,int,int);   //獲取鍵盤輸入
void SpecialKeyboard(int,int,int);//獲取特殊鍵盤輸入
void Display(void);                     //描繪 
void Clock();//右上角的時間
void ClockDraw(int,int);//右上角的時間
void Init();//初始化子彈人物敵機資訊
void Frame(int)
{
	glutPostRedisplay();
	glutTimerFunc(15,Frame,0);
}//FPS
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
	glutTimerFunc(15,Frame,0);
	//---Timer
	glutMainLoop(); 
	return 0; 
}
void Display(void) 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//用黑色0 0 0塗背景
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0,0,200,0,0,0,0,1,0);   //視線的座標及方向
	//---------BackGround----------------------------
	BackGround->Draw();
	//---------caculate time----------------------------
	gameTimer.tick();
	deltaTime = gameTimer.getDeltaTime();
	Clock();
	gameTime += deltaTime;
	//---------update-----------------------------------
	if (mainPlane->m_hp <= 0) isGameover = true;
	mainPlane->Update(deltaTime);
	mainPlane->m_BM->isCollide(enemyM);
	enemyM->Update(deltaTime);
	enemyM->hitMainPlane(mainPlane);
	//---------Script-----------------------------------
	Script();
	//--------------------------------------------------
	glutSwapBuffers();
}
void Clock()
{
	static float sT = 0;
	static int m = 0,s = 0;
	static float temp=1;
	if( sT>=temp )	temp = temp + 1;
	sT += deltaTime;
	if( sT>=60 ){
		sT = 0;
		s = 0;
		m++;
	}
	else s = int(sT);
	if ( m>10 )	m = 0;
	ClockDraw(m,s);
}
void ClockDraw(int m,int s)
{
	number[0]->SetTexCoord( numberTexCoord[m] , numberTexCoord[m]+60);
	if( s<10 ){
		number[2]->SetTexCoord( numberTexCoord[0] , numberTexCoord[0]+60);
		number[3]->SetTexCoord( numberTexCoord[s] , numberTexCoord[s]+60);
	}else{
		int k,t;
		k = int(s / 10);
		t = s % 10;
		number[2]->SetTexCoord( numberTexCoord[k] , numberTexCoord[k]+60);
		number[3]->SetTexCoord( numberTexCoord[t] , numberTexCoord[t]+60);
	}
	for(int i=0;i<4;i++)
		number[i]->Draw();
}
void Keyboard(unsigned char key, int x, int y) 
{
	switch (key)
	{
		case 'q':
			gameTime = 13.5;
			break;
		case 'x':
			mainPlane->m_hp = 100;
			mainPlane->m_textureID = MainPlaneTex;
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
			mainPlane->m_isShooting = true;
			break;
		case 'z':
			mainPlane->m_isShooting = true;
			break;
	}
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
}
void SpecialKeyboard(int key, int x, int y) 
{
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		mainPlane->m_unit = 2.5;
	else
		mainPlane->m_unit = 5;
	switch (key)
	{
		case GLUT_KEY_UP:
			mainPlane->m_keyState[2] = true;
			break;
		case GLUT_KEY_DOWN:
			mainPlane->m_keyState[3] = true;
			break;
		case GLUT_KEY_LEFT:
			mainPlane->SetTexCoord(131,156,51,94);
			mainPlane->m_keyState[0] = true;
			mainPlane->m_state = LEFT;
			break;
		case GLUT_KEY_RIGHT:
			mainPlane->SetTexCoord(131,156,99,142);
			mainPlane->m_keyState[1] = true;
			mainPlane->m_state = RIGHT;
			break;
	}
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
}
void Reshape(int w, int h) 
{
	winWidth = w;
	winHeight = h;
	glViewport(-620,-380,1000*2,800*2);
	/*GLfloat aspect;
	aspect=(GLfloat)w / (GLfloat)h;
	if(aspect > 1.0f)
		glViewport((w-h)/2.0f,0,(GLsizei)h,(GLsizei)h);
	else
		glViewport(0,(h-w)/2.0f,(GLsizei)w,(GLsizei)w);*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.0f, 1.0f, 1.0f, 1000.0f);
	glOrtho(-800,800,-800,800,-800,800);
	glMatrixMode(GL_MODELVIEW);
}
void Init()
{
	GLuint temp;
	gameTime = 0;
	LoadTexture("../Data/character/main.bmp","../Data/character/mainalpha.bmp",MainPlaneTex);
	LoadTexture("../Data/character/boss.bmp","../Data/character/bossalpha.bmp",BossPlaneTex);
	LoadTexture("../Data/bullet/bullet1.bmp","../Data/bullet/bullet1alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/bullet/bullet2.bmp","../Data/bullet/bullet2alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/bullet/bullet3.bmp","../Data/bullet/bullet3alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/character/boss.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime1.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime2.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	LoadTexture("../Data/character/bossdeadanime3.bmp","../Data/character/bossalpha.bmp",temp);
	bossHurtTex.push_back(temp);
	//--
	LoadTexture("../Data/character/main.bmp","../Data/character/mainalpha.bmp",temp);
	mainHurtTex.push_back(temp);
	LoadTexture("../Data/character/maindeadanime1.bmp","../Data/character/mainalpha.bmp",temp);
	mainHurtTex.push_back(temp);
	LoadTexture("../Data/character/maindeadanime2.bmp","../Data/character/mainalpha.bmp",temp);
	mainHurtTex.push_back(temp);
	LoadTexture("../Data/character/maindeadanime3.bmp","../Data/character/mainalpha.bmp",temp);
	mainHurtTex.push_back(temp);
	//---
	//--Init Clock
	LoadTexture("../Data/system/number.bmp","../Data/system/numberalpha.bmp",numberTex);
	number[0] = new QUAD(numberTex,clock_x,clock_y,60,88);
	number[1] = new QUAD(numberTex,clock_x+60,clock_y,40,88);
	number[2] = new QUAD(numberTex,clock_x+100,clock_y,60,88);
	number[3] = new QUAD(numberTex,clock_x+160,clock_y,60,88);
	for(int i=0;i<4;i++)
		number[i]->SetImageWH(676,88);
	number[1]->SetTexCoord(636,676);
	//--Init BackGround and Gameover
	LoadTexture("../Data/system/background.bmp","../Data/system/backgroundalpha.bmp",BackGroundTex,0.45);
	BackGround = new QUAD(BackGroundTex,0,0,800,800);
	BackGround->SetImageWH(800,800);

	LoadTexture("../Data/system/gameover.bmp","../Data/system/gameoveralpha.bmp",GameoverTex,1);
	Gameover = new QUAD(GameoverTex,0,0,1200,1200);
	Gameover->SetImageWH(800,600);
	//--Init EnemyManager
	enemyM = new EnemyManager();
	//Init QUAD need to set ImageWH and TexCoord
	mainPlane = new Plane(MainPlaneTex,0,-350,26,44);
	mainPlane->m_deadAnime = mainHurtTex;
	mainPlane->m_isAuto = false;
	mainPlane->SetImageWH(256,256);
	mainPlane->SetTexCoord(3,28,3,46);
	mainPlane->SetAnimeTexCoord(selfTexCoord,0,16);
	mainPlane->SetBullet(BulletTex[0],16,16,0);
	//--
	boss = new Plane(BossPlaneTex,0,0,39,71);
	boss->m_deadAnime = bossHurtTex;
	boss->SetImageWH(256,256);
	//boss->SetTexCoord(35,90,36,98);
	boss->SetTexCoord(13,51,11,81);
	boss->SetBullet(BulletTex[0],16,16,0);
	
	enemyM->Push(boss);
	//Script target
	target = boss;
}
