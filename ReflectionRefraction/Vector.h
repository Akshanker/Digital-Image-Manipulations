#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Vector
{
public:
	float x, y, z;
	Vector() { x = y = z = 0; }

	Vector(float a, float b, float c)
	{
		x = a; y = b; z = c;
	}
	//magnitude vector
	float length()
	{
		return sqrt(x * x + y * y + z * z);
	}
	//normalize vector
	void normalize()
	{
		x = x / length();
		y = y / length();
		z = z / length();
	}
	Vector unitv()
	{
		return Vector(x / length(),
			y / length(),
			z / length());
	}
	/*not lettting me call if i define here :/
	inline float dot(Vector v1, Vector v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}*/
	inline Vector operator +() { return *this; }
	inline Vector operator -() { return Vector(-x, -y, -z); }
	inline Vector operator += (Vector v1)
	{
		x += v1.x;
		y += v1.y;
		z += v1.z;
		return *this;
	}
	inline Vector operator -= (Vector v1)
	{
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		return *this;
	}
	inline Vector operator *= (Vector v1)
	{
		x *= v1.x;
		y *= v1.y;
		z *= v1.z;
		return *this;
	}
	inline Vector operator /= (Vector v1)
	{
		x /= v1.x;
		y /= v1.y;
		z /= v1.z;
		return *this;
	}
	inline Vector operator /= (float f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}
	inline Vector operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

};
inline float dot(Vector v1, Vector v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline Vector cross(Vector v1, Vector v2)
{

	return Vector(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);

}
inline Vector operator + (Vector v1, Vector v2)
{
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline Vector operator - (Vector v1, Vector v2)
{
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
inline Vector operator * (Vector v1, Vector v2)
{
	return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline Vector operator / (Vector v1, Vector v2)
{
	return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}
inline Vector operator / (Vector v1, float f)
{
	return Vector(v1.x / f, v1.y / f, v1.z / f);
}
inline Vector operator * (Vector v1, float f)
{
	return Vector(v1.x * f, v1.y * f, v1.z * f);
}
inline Vector operator * (float f, Vector v1)
{
	return Vector(v1.x * f, v1.y * f, v1.z * f);
}
inline Vector operator + (float f, Vector v1)
{
	return Vector(v1.x + f, v1.y + f, v1.z + f);
}
inline Vector operator + (Vector v1, float f)
{
	return Vector(v1.x + f, v1.y + f, v1.z + f);
}
inline ostream& operator<<(ostream& o, Vector v1)
{
	return o << v1.x << " " << v1.y << " " << v1.z << endl;

}