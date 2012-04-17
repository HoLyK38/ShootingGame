#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H
#include <vector>
#include "Plane.h"
class EnemyManager
{
public:
	//data
	std::vector<Plane*> m_enemyPlane;
	//function
	EnemyManager();
	void Push(Plane*);
	void Update(float deltaTime);
	void test();
};

#endif