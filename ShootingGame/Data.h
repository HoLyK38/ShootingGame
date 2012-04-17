#ifndef DATA_H
#define DATA_H
#include "GameTimer.h"
static int winWidth = 800,winHeight = 800;//�ù��e��
float gameTime;
GLuint MainPlaneTex=0;
GLuint BossPlaneTex=0;
GLuint Bullet1Tex=0;
//--
std::vector<GLuint>testAnime;
//--
Plane* mainPlane;
Plane* boss;

EnemyManager *enemyM;//enemyPlaneBulletManager
//BulletManager* mainBM;//mainPlaneBulletManager

//float selfTexCoord[]={227,195,35,3};//�R��ɤH���ʵe�K�Ϯy��

//float selfTexCoord[]={3,35,67,99,131,195,227};//�R��ɤH���ʵe
float bulletFrame[]={32,64,96};
float selfTexCoord[]={3,28,35,60,67,92,99,124,131,156,163,188,195,220,227,252};//�R��ɤH���ʵe�K�Ϯy��
//----test
float aTexCoord[]={3,35,67,99,131,163,195,227};//�R��ɤH���ʵe�K�Ϯy��
Bullet* tb;
//----
GameTimer gameTimer;
float deltaTime;
typedef void (*TrackPtr)(Bullet*);
TrackPtr mainTrackPtr;
#endif