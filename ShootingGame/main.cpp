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
void HpDraw(int,int);
void Init();//初始化子彈人物敵機資訊
void test(int)
{
	if(go==true){
			Init();
			glutReshapeFunc(Reshape); 
			glutKeyboardFunc(Keyboard);
			glutKeyboardUpFunc(KeyboardUp);
			glutSpecialUpFunc(SpecialKeyboardUp);
			glutSpecialFunc(SpecialKeyboard);
			glutDisplayFunc(Display);
	}
	else
		glutTimerFunc(10,test,0);
}
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
	M_Init();
	//--------------------------------------------------
	glutReshapeFunc(Reshape); 
	glutKeyboardFunc(M_Keyboard);
	glutSpecialFunc(M_SpecialKeyboard);
	glutDisplayFunc(M_Display);
	/*glutReshapeFunc(Reshape); 
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(Display);*/
	//---Timer
	glutTimerFunc(10,test,0);
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
	if(!isGameover){
	//---------BackGround----------------------------
	BackGround->Draw();
	//---------caculate time----------------------------
	gameTimer.tick();
	deltaTime = gameTimer.getDeltaTime();
	Clock();
	gameTime += deltaTime;
	//---------update-----------------------------------
	if (mainPlane->m_isDead) isGameover = true;
	mainPlane->Update(deltaTime);
	mainPlane->m_BM->isCollide(enemyM);
	enemyM->Update(deltaTime);
	enemyM->hitMainPlane(mainPlane);
	//---------Script-----------------------------------
	Script();
	HpDraw(mainPlane->m_hp,mainPlane->m_hpMax);
	if (boss->m_isDead) isGameover = true;
	if(playTitle==false)StageTile->Draw();
	}
	else{
		Sleep(1500);
		if(boss->m_isDead)
			Win->Draw();
		else
			Gameover->Draw();
	}
	//---
	
	//--------------------------------------------------
	glutSwapBuffers();
}
void Clock()
{
	static float sT = 0;
	static int m = 0,s = 0;
	static float temp=1;
	if (clockReset){
		sT=0;m=0;s=0;temp=1;
		clockReset = false;
	}
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
void HpDraw(int hp,int maxHp)
{
	if ( hp<0 ) hp=0;
	int un,te,hu,th;//個位 十位 百位 千位
	int temp;
	th = hp / 1000;hp = hp % 1000;
	hu = hp / 100; hp = hp % 100;
	te = hp / 10;  hp = hp % 10;
	un = hp;
	mainHP[0]->SetTexCoord( number2TexCoord[th] , number2TexCoord[th]+40);
	mainHP[1]->SetTexCoord( number2TexCoord[hu] , number2TexCoord[hu]+40);
	mainHP[2]->SetTexCoord( number2TexCoord[te] , number2TexCoord[te]+40);
	mainHP[3]->SetTexCoord( number2TexCoord[un] , number2TexCoord[un]+40);

	mainHP[4]->SetTexCoord( number2TexCoord[10] , number2TexCoord[10]+38);
	
	th = maxHp / 1000;maxHp = maxHp % 1000;
	hu = maxHp / 100; maxHp = maxHp % 100;
	te = maxHp / 10;  maxHp = maxHp % 10;
	un = maxHp;
	mainHP[5]->SetTexCoord( number2TexCoord[th] , number2TexCoord[th]+40);
	mainHP[6]->SetTexCoord( number2TexCoord[hu] , number2TexCoord[hu]+40);
	mainHP[7]->SetTexCoord( number2TexCoord[te] , number2TexCoord[te]+40);
	mainHP[8]->SetTexCoord( number2TexCoord[un] , number2TexCoord[un]+40);
	for(int i=0;i<9;i++)
		mainHP[i]->Draw();
}
void Keyboard(unsigned char key, int x, int y) 
{
	if(isGameover) exit(0);
	switch (key)
	{
		case '1':
			mainPlane->ChangeWeapon(wSINGLE);
			break;
		case '2':
			mainPlane->ChangeWeapon(wDOUBLE);
			break;
		case '3':
			mainPlane->ChangeWeapon(wTRIPLE);
			break;
		case 'q':
			mainPlane->m_hp -= 10;
			break;
		case 'x':
			Init();
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
	if(isGameover) exit(0);
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-800,800,-800,800,-800,800);
	glMatrixMode(GL_MODELVIEW);
}
void Init()
{
	GLuint temp;
	srand((unsigned)time(NULL));//set 亂數種子 
	gameTimer.tick();
	gameTime = 0;
	clockReset = true;
	playTitle = false;
	isGameover = false;
	isWin = false;
	
	LoadTexture("../Data/bullet/bullet1.bmp","../Data/bullet/bullet1alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/bullet/bullet2.bmp","../Data/bullet/bullet2alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/bullet/bullet3.bmp","../Data/bullet/bullet3alpha.bmp",temp);
	BulletTex.push_back(temp);
	LoadTexture("../Data/bullet/bullet4.bmp","../Data/bullet/bullet4alpha.bmp",temp);
	BulletTex.push_back(temp);
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
	//--Init number(display HP)
	int tx=460,ty=-250;
	LoadTexture("../Data/system/number2.bmp","../Data/system/number2alpha.bmp",number2Tex);
	for(int i=0;i<4;i++){
		mainHP[i] = new QUAD(number2Tex,tx+50*i,ty,40,60);
		mainHP[i]->SetImageWH(556,60);
	}
	mainHP[4] = new QUAD(number2Tex,tx+70,ty-50,40,60);
	mainHP[4]->SetImageWH(556,60);
	for(int i=5;i<9;i++){
		mainHP[i] = new QUAD(number2Tex,tx+50*(i-5),ty-120,40,60);
		mainHP[i]->SetImageWH(556,60);
	}
	//--Init BackGround and Gameover
	LoadTexture("../Data/system/background.bmp","../Data/system/backgroundalpha.bmp",BackGroundTex,0.45);
	BackGround = new QUAD(BackGroundTex,0,0,800,800);
	BackGround->SetImageWH(800,800);

	LoadTexture("../Data/system/gameover.bmp","../Data/system/gameoveralpha.bmp",GameoverTex,1);
	Gameover = new QUAD(GameoverTex,170,-20,1000/2,900/2);
	Gameover->SetImageWH(800,600);

	LoadTexture("../Data/system/win.bmp","../Data/system/gameoveralpha.bmp",WinTex);
	Win = new QUAD(WinTex,170,-20,1000/2,900/2);
	Win->SetImageWH(800,600);
	//--Init EnemyManager
	enemyM = new EnemyManager();
	//Init QUAD need to set ImageWH and TexCoord
	LoadTexture("../Data/character/main.bmp","../Data/character/mainalpha.bmp",MainPlaneTex);
	mainPlane = new Plane(MainPlaneTex,0,-350,26,44);
	mainPlane->m_deadAnime = mainHurtTex;
	mainPlane->m_isAuto = false;
	mainPlane->SetImageWH(256,256);
	mainPlane->SetTexCoord(3,28,3,46);
	mainPlane->SetAnimeTexCoord(selfTexCoord,0,16);
	mainPlane->SetBullet(BulletTex[3],14,31,0);
	//mainPlane->SetBullet(MainPlaneTex,31,14,45,0,30,241,254);
	mainPlane->SetBulletSpeed(15);
	mainPlane->m_hp = 9999;
	mainPlane->m_hpMax = 9999;
	//--
	InitBoss();
}
