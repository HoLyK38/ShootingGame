QUAD *Back1, *start , *Back2, *Quit, *Press;
vector<QUAD*> Button;
int manuState = 0;
bool TexState[10];
GLuint Back1Tex=0;
GLuint Back2Tex=0;
GLuint startTex=0;
GLuint QuitTex = 0;
GLuint PressTex = 0;
double undisplay = 0;
void M_PressTimeFunc(int value);
void M_Keyboard(unsigned char,int,int);   //獲取鍵盤輸入
void M_SpecialKeyboard(int,int,int);//獲取特殊鍵盤輸入
void M_Display(void);   //描繪 
void M_Init();
bool go = false;

void M_Display(void) 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);//用黑色0 0 0塗背景
	//glClearColor(1.0, 1.0, 1.0, 1.0);//用白色1 1 1塗背景
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	gluLookAt(0,0,400,0,0,0,0,1,0);   //視線的座標及方向
	for(int i = 0; i < Button.size(); i ++)
	{
		if(TexState[i])
			Button[i]->Draw();
	}
	glutSwapBuffers();
}
void M_SpecialKeyboard(int key,int x,int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
	case GLUT_KEY_UP:	
		manuState++;
		break;
	}
	if(manuState %2 == 0)
	{
		Quit->SetTexCoord(768,1024,0,128);
		start->SetTexCoord(0,256,0,128);
	}else{
		Quit->SetTexCoord(512,768,0,128);
		start->SetTexCoord(256,512,0,128);
	}
}
void M_Keyboard(unsigned char key, int x, int y)  
{
	switch (key)
	{
	case 13 : //enter key
		if(TexState[1] ==true){
			TexState[1] = false;
			TexState[0] = true;
			TexState[4] = true;
			TexState[3] = true;
		}else if (manuState %2 == 0 && TexState[1] == false){
			go = true;
		}else{
			exit(0);
		}
		break;

	}
}

void M_PressTimeFunc(int value)
{
	if(TexState[1])
	{
		if(value % 2 == 0)
			TexState[2] =true;
		else
			TexState[2] =false;
		glutPostRedisplay();
		glutTimerFunc(300,M_PressTimeFunc,value+1);
	}else
		TexState[2] =false;
}
void M_Init()
{
	int tx=210;
	LoadTexture("../Data/menu.bmp","../Data/backal.bmp",Back1Tex);
	Back1 = new QUAD(Back1Tex,256,256);
	Back1->SetImageWH(512,512);
	Back1->SetPoint(0+tx-100,0-30,winWidth,winHeight,0); 
	LoadTexture("../Data/back.bmp","../Data/backal.bmp",Back2Tex);
	Back2 = new QUAD(Back2Tex,512,512);
	Back2->SetImageWH(512,512);
	Back2->SetPoint(0+tx,0,winWidth+50,winHeight+50,0);
	LoadTexture("../Data/start.bmp","../Data/startal.bmp",PressTex);
	Press = new QUAD(PressTex,128,256);
	Press->SetTexCoord(0,256,0,256);
	Press->SetPoint(0+tx,-300,256,256,0);
	LoadTexture("../Data/SQ.bmp","../Data/SQA.bmp",startTex);
	start = new QUAD(startTex,128,1024);
	start->SetImageWH(1024,128);
	start->SetPoint(-250+tx,-100,256,128,0);
	start->SetTexCoord(0,256,0,128);
	Quit = new QUAD(startTex,128,1024);
	Quit->SetImageWH(1024,128);
	Quit->SetPoint(-250+tx,-200,256,128,0);
	Quit->SetTexCoord(768,1024,0,128);
	Button.push_back(Back1);
	Button.push_back(Back2);
	Button.push_back(Press);
	Button.push_back(start);
	Button.push_back(Quit);
	for(int i = 0; i<4; i++)
	{
		if(i!=1 && i != 2)
			TexState[i] = false;
		else 
			TexState[i] = true;
	}
	glutTimerFunc(100,M_PressTimeFunc,0);
}