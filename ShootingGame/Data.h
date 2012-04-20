#ifndef DATA_H
#define DATA_H
#include "GameTimer.h"
static int winWidth = 1200,winHeight = 800;//螢幕寬高
GameTimer gameTimer;
float gameTime;
float deltaTime;
float clock_x = 460,clock_y = 340;
GLuint MainPlaneTex=0;
GLuint BossPlaneTex=0;
std::vector<GLuint>BulletTex;
GLuint BackGroundTex=0;
GLuint numberTex=0;
GLuint GameoverTex=0;

std::vector<GLuint>mainHurtTex;
std::vector<GLuint>bossHurtTex;

QUAD* BackGround;//背景
QUAD* Gameover;
QUAD *number[4];//右上角的Clock
Plane* mainPlane;//自機
Plane* boss;//敵機

EnemyManager *enemyM;

bool isGameover = false;

float bulletFrame[]={32,64,96};
float selfTexCoord[]={3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252};//靜止時人物動畫貼圖座標
float numberTexCoord[] = {576,0,60,126,190,256,320,386,440,506};//數字的TexCoord

#endif