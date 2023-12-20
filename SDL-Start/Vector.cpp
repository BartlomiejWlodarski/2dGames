#include "Vector.h"
#include <cmath>
#include <iostream>

using namespace std;

Vector::Vector(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

std::string Vector::printVector()
{
	string msg;
	msg = "(" + to_string(this->getX()) + ", " + to_string(this->getY()) + ", " + to_string(this->getZ()) + ")";
	return msg;
}

float Vector::getX()
{
	return x;
}

float Vector::getY()
{
	return y;
}

float Vector::getZ()
{
	return z;
}

void Vector::setX(float value)
{
	x = value;
}

void Vector::setY(float value)
{
	y = value;
}

void Vector::setZ(float value)
{
	z = value;
}

void Vector::add(Vector vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

void Vector::subtract(Vector vector)
{
	this->x -= vector.x;
	this->y -= vector.y;
	this->z -= vector.z;
}

void Vector::multiplyByScalar(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
}

void Vector::divideByScalar(float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
}

Vector Vector::crossProduct(Vector vector)
{
	Vector result{ this->y * vector.getZ() - this->z * vector.getY(), this->z * vector.getX() - this->x * vector.getZ(), this->x * vector.getY() - this->y * vector.getX() };
	return result;
}

float Vector::dotProduct(Vector vector)
{
	Vector result{ this->x * vector.getX(), this->y * vector.getY(), this->z * vector.getZ() };
	return result.getX() + result.getY() + result.getZ();
}

float Vector::angleBetweenVectors(Vector vector)
{
	float resultCosinus = this->dotProduct(vector) / (this->getLength() * vector.getLength());
	return acos(resultCosinus);
}

Vector Vector::get90DegreesVector(Vector vector)
{
	return this->crossProduct(vector);
}

float Vector::getLength()
{
	return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vector::normalize()
{
	float length = this->getLength();
	if (length != 0)
	{
		this->divideByScalar(length);
	}
	else
	{
		std::cout << "Cannot divide by 0 : called by [normalize]" << std::endl;
	}
}
