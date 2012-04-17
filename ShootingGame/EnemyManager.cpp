#include "EnemyManager.h"
EnemyManager::EnemyManager(){}
void EnemyManager::Push(Plane* b)
{
	m_enemyPlane.push_back(b);
}
void EnemyManager::Update(float deltaTime)
{
	for(int i=0;i<m_enemyPlane.size();i++){
		if (!m_enemyPlane[i])
			m_enemyPlane.erase(m_enemyPlane.begin()+i);
		else if( m_enemyPlane[i]->m_state == DEAD ){
			delete m_enemyPlane[i];
			m_enemyPlane[i]->m_state = DEAD;
			std::cout<<"DEAD"<<std::endl;
			m_enemyPlane.erase(m_enemyPlane.begin()+i);
		}
		else
			m_enemyPlane[i]->Update(deltaTime);
	}
}