#include "Vector.h"
Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}
Vector2::Vector2(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}
Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector3::Vector3(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}