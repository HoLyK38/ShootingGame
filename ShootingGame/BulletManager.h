#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include <vector>
#include "EnemyManager.h"
#include "Bullet.h"
class BulletManager
{
public:
	//data
	std::vector<Bullet> m_bullet;
	//function
	BulletManager();
	void Push(Bullet&);
	void Update(float);
	void isCollide(EnemyManager* enemyM);
};
#endif