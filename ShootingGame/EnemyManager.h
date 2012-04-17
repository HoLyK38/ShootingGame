#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H
#include <vector>
#include "EnemyPlane.h"
class EnemyManager
{
public:
	//data
	std::vector<EnemyPlane> m_enemyPlane;
	//function
	EnemyManager();
	void Push(EnemyPlane&);
	void Update(float deltaTime);
	void test();
};

#endif