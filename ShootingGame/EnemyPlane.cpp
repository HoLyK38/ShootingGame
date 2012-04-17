#include "EnemyPlane.h"
#include "BulletManager.h"
EnemyPlane::~EnemyPlane(){}
EnemyPlane::EnemyPlane(GLuint id , float x,float y,float w,float h):Plane(id ,x, y, w, h)
{
}
void EnemyPlane::Update(float deltaTime)
{
	if( this->m_hp < 0 )
		this->deadAnime(deltaTime);
	else if ( this->m_hurting )
		this->HurtAnime(deltaTime);

	this->Draw();
	this->m_BM->Update(deltaTime);
}