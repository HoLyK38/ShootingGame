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
		//Ãä¬É§P©w
		if( m_bullet[i].m_y > 400 || m_bullet[i].m_y < -400 ||
			m_bullet[i].m_x > 300 || m_bullet[i].m_x < -300 )
			m_bullet.erase(m_bullet.begin()+i);
		else
			m_bullet[i].Update(deltaTime);
	}
}
void BulletManager::isCollide(EnemyManager* enemyM)
{
	for(int i=0;i<m_bullet.size();i++){
		for(int j=0;j<enemyM->m_enemyPlane.size();j++){
			//std::cout<<enemyM->m_enemyPlane.size()<<std::endl;
			if( m_bullet[i].isCollide( enemyM->m_enemyPlane[j] ) ){
				enemyM->m_enemyPlane[j]->m_hp -= m_bullet[i].m_atk;
				enemyM->m_enemyPlane[j]->m_hurting = true;
				m_bullet.erase(m_bullet.begin()+i);
				break;
			}
		}
	}
}
void BulletManager::isCollide(Plane* mainPlane)
{
	for(int i=0;i<m_bullet.size();i++){
			if( m_bullet[i].isCollide( mainPlane ) ){
				mainPlane->m_hp -= m_bullet[i].m_atk;
				mainPlane->m_hurting = true;
				m_bullet.erase(m_bullet.begin()+i);
				break;
			}
	}
}