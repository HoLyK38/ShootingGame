#ifndef DATA_H
#define DATA_H
#include "GameTimer.h"
static int winWidth = 800,winHeight = 800;//�ù��e��
GameTimer gameTimer;
float gameTime;
float deltaTime;
float clock_x = 230,clock_y = 380;
GLuint MainPlaneTex=0;
GLuint BossPlaneTex=0;
GLuint Bullet1Tex=0;
GLuint BackGroundTex=0;
GLuint numberTex=0;
std::vector<GLuint>bossHurtTex;

QUAD* BackGround;//�I��
QUAD *number[4];//�k�W����Clock
Plane* mainPlane;//�۾�
Plane* boss;//�ľ�

EnemyManager *enemyM;

float bulletFrame[]={32,64,96};
float selfTexCoord[]={3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252};//�R��ɤH���ʵe�K�Ϯy��
float numberTexCoord[] = {576,0,60,126,190,256,320,386,440,506};//�Ʀr��TexCoord

#endif