#pragma once
#include <string>
class Vector
{
private:
	float x;
	float y;
	float z;

public:
	Vector(float a, float b, float c);
	Vector();
	std::string printVector();
	float getX();
	float getY();
	float getZ();
	void setX(float value);
	void setY(float value);
	void setZ(float value);
	void add(Vector vector);
	void subtract(Vector vector);

	float getLength();
	void normalize();

	void multiplyByScalar(float value);
	void divideByScalar(float value);
	Vector crossProduct(Vector vector);
	float dotProduct(Vector vector);
	float angleBetweenVectors(Vector vector);
	Vector get90DegreesVector(Vector v);


};

