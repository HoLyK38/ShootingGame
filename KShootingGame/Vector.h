#ifndef VECTOR_H
#define VECTOR_H

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float _x, float _y);
	Vector2* copy() { return (new Vector2(x, y)); }
};

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3* copy() { return (new Vector3(x, y, z)); }
};

#endif