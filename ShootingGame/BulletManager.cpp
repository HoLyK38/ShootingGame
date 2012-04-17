#include "BulletManager.h"
BulletManager::BulletManager()
{
}

void BulletManager::Push(Bullet& b)
{
	m_bullet.push_back(b);
}
void BulletManager::Update(float deltaTime)
{
	for(int i=0;i<m_bullet.size();i++){
		m_bullet[i].Update(deltaTime);
		//Ãä¬É§P©w
		if( m_bullet[i].m_y > 450 || m_bullet[i].m_y < -450 ||
			m_bullet[i].m_x > 450 || m_bullet[i].m_x < -450 )
			m_bullet.erase(m_bullet.begin()+i);
	}
}
void BulletManager::isCollide(EnemyManager* enemyM)
{
	for(int i=0;i<m_bullet.size();i++){
		for(int j=0;j<enemyM->m_enemyPlane.size();j++){
			if( m_bullet[i].isCollide(& enemyM->m_enemyPlane[j] ) ){
				enemyM->m_enemyPlane[j].m_hp -= m_bullet[i].m_atk;
				enemyM->m_enemyPlane[j].m_hurting = true;
				m_bullet.erase(m_bullet.begin()+i);
				break;
			}
		}
	}
}