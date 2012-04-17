#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <iostream>
#include <vector>
#include "Plane.h"
class EnemyPlane : public Plane
{
public:
	//data
	//fuction
	EnemyPlane(GLuint id , float x,float y,float w,float h);
	~EnemyPlane();
	void Update(float deltaTime);
};
#endif