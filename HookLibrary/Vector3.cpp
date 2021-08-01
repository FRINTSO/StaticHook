#include "Vector3.h"
#include <cmath>

HookLibrary::DataStructures::Vector3::Vector3()
	:x(0), y(0), z(0)
{}

HookLibrary::DataStructures::Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{}

float HookLibrary::DataStructures::Vector3::Magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

float HookLibrary::DataStructures::Vector3::SqrMagnitude() const {
	return (x * x + y * y + z * z);
}

float HookLibrary::DataStructures::Vector3::Distance(const Vector3& a, const Vector3& b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - b.z;
	return sqrt(x * x + y * y + z * z);
}

HookLibrary::DataStructures::Vector3 HookLibrary::DataStructures::Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

HookLibrary::DataStructures::Vector3 HookLibrary::DataStructures::Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

HookLibrary::DataStructures::Vector3 HookLibrary::DataStructures::Vector3::operator*(const Vector3& other) const {
	return Vector3(x * other.x, y * other.y, z * other.z);
}

HookLibrary::DataStructures::Vector3 HookLibrary::DataStructures::Vector3::operator/(const Vector3& other) const {
	return Vector3(x / other.x, y / other.y, z / other.z);
}

HookLibrary::DataStructures::Vector3& HookLibrary::DataStructures::Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

HookLibrary::DataStructures::Vector3& HookLibrary::DataStructures::Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

HookLibrary::DataStructures::Vector3& HookLibrary::DataStructures::Vector3::operator*=(const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

HookLibrary::DataStructures::Vector3& HookLibrary::DataStructures::Vector3::operator/=(const Vector3& other) {
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

bool HookLibrary::DataStructures::Vector3::operator==(const Vector3& other) const {
	return x == other.x && y == other.y && z == other.z;
}

bool HookLibrary::DataStructures::Vector3::operator!=(const Vector3& other) const {
	return x != other.x || y != other.y || z != other.z;
}