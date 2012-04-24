#include "EnemyManager.h"
#include "BulletManager.h"
EnemyManager::EnemyManager(){}
void EnemyManager::Push(Plane* b)
{
	m_enemyPlane.push_back(b);
}
void EnemyManager::Update(float deltaTime)
{
	for(int i=0;i<m_enemyPlane.size();i++){
		m_enemyPlane[i]->Update(deltaTime);
		if( m_enemyPlane[i]->m_isDead ){
			delete m_enemyPlane[i];
			m_enemyPlane.erase(m_enemyPlane.begin()+i);
		}
	}
}
void EnemyManager::hitMainPlane(Plane* mainPlane)
{
	for(int i=0;i<m_enemyPlane.size();i++){
		m_enemyPlane[i]->m_BM->isCollide(mainPlane);
	}
}