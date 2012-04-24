#ifndef DATA_H
#define DATA_H
#include "GameTimer.h"
static int winWidth = 1200,winHeight = 800;//�ù��e��
GameTimer gameTimer;
float gameTime;
float deltaTime;
float clock_x = 460,clock_y = 340;
//int HP;//�ۤv��q
GLuint MainPlaneTex=0;
GLuint MainPlaneMidTex=0;
GLuint BossPlaneTex=0;
std::vector<GLuint>BulletTex;
GLuint BackGroundTex=0;
GLuint numberTex=0;
GLuint number2Tex=0;
GLuint GameoverTex=0;
GLuint StageTileTex=0;
GLuint WinTex=0;

std::vector<GLuint>mainHurtTex;
std::vector<GLuint>bossHurtTex;

QUAD* BackGround;//�I��
QUAD* StageTile;//�I��
QUAD* Gameover;
QUAD* number[4];//�k�W����Clock
QUAD* mainHP[9];//�k�W����HP 1234 / 6789
QUAD* bossHP;//�k�W����Boss HP��
QUAD* bossHPt;//�k�W����Boss HP���~��
QUAD* Win;

Plane* mainPlane;//�۾�
Plane* mainPlaneQ;//�۾��P�w�I
Plane* boss;//�ľ�

EnemyManager *enemyM;

bool isGameover = false;
bool isWin = false;
bool clockReset = false;

float selfTexCoord[]={3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252};//�R��ɤH���ʵe�K�Ϯy��
float numberTexCoord[] = {576,0,60,126,190,256,320,386,440,506};//�Ʀr��TexCoord
float number2TexCoord[] = {6,56,101,153,205,256,310,360,413,467,516};//�Ʀr��TexCoord

#endif