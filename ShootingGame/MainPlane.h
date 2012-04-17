#ifndef MAINPLANE_H
#define MAINPLANE_H
#include <iostream>
#include <vector>
#include "Plane.h"
class MainPlane : public Plane
{
public:
	//data
	bool m_keyState[4];
	//function
	MainPlane(GLuint id , float x,float y,float w,float h);
	~MainPlane();
	void Move();
	void Update(float);
	void Shoot();
};

#endif