#include "EnemyManager.h"
EnemyManager::EnemyManager(){}

void EnemyManager::Push(EnemyPlane& b)
{
	m_enemyPlane.push_back(b);
}
void EnemyManager::Update(float deltaTime)
{
	for(int i=0;i<m_enemyPlane.size();i++){
		if( m_enemyPlane[i].m_state == DEAD )
			m_enemyPlane.erase(m_enemyPlane.begin()+i);
		else
			m_enemyPlane[i].Update(deltaTime);
	}
}