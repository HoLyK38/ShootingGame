#ifndef DATA_H
#define DATA_H
#include "GameTimer.h"
static int winWidth = 1200,winHeight = 800;//螢幕寬高
GameTimer gameTimer;
float gameTime;
float deltaTime;
float clock_x = 460,clock_y = 340;
//int HP;//自己血量
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

QUAD* BackGround;//背景
QUAD* StageTile;//背景
QUAD* Gameover;
QUAD* number[4];//右上角的Clock
QUAD* mainHP[9];//右上角的HP 1234 / 6789
QUAD* bossHP;//右上角的Boss HP條
QUAD* bossHPt;//右上角的Boss HP條外框
QUAD* Win;

Plane* mainPlane;//自機
Plane* mainPlaneQ;//自機判定點
Plane* boss;//敵機

EnemyManager *enemyM;

bool isGameover = false;
bool isWin = false;
bool clockReset = false;

float selfTexCoord[]={3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252};//靜止時人物動畫貼圖座標
float numberTexCoord[] = {576,0,60,126,190,256,320,386,440,506};//數字的TexCoord
float number2TexCoord[] = {6,56,101,153,205,256,310,360,413,467,516};//數字的TexCoord

#endif