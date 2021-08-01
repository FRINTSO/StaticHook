#include "Vector2.h"
#include <cmath>

HookLibrary::DataStructures::Vector2::Vector2()
	: x(0), y(0)
{}

HookLibrary::DataStructures::Vector2::Vector2(float x, float y)
	: x(x), y(y)
{}

inline float HookLibrary::DataStructures::Vector2::Magnitude() const {
	return sqrt(x * x + y * y);
}

inline float HookLibrary::DataStructures::Vector2::SqrMagnitude() const {
	return (x * x + y * y);
}

float HookLibrary::DataStructures::Vector2::Distance(const Vector2& a, const Vector2& b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrt(x * x + y * y);
}

inline HookLibrary::DataStructures::Vector2 HookLibrary::DataStructures::Vector2::operator+(const Vector2& other) const {
	return Vector2(x + other.x, y + other.y);
}

inline HookLibrary::DataStructures::Vector2 HookLibrary::DataStructures::Vector2::operator-(const Vector2& other) const {
	return Vector2(x - other.x, y - other.y);
}

inline HookLibrary::DataStructures::Vector2 HookLibrary::DataStructures::Vector2::operator*(const Vector2& other) const {
	return Vector2(x * other.x, y * other.y);
}

inline HookLibrary::DataStructures::Vector2 HookLibrary::DataStructures::Vector2::operator/(const Vector2& other) const {
	return Vector2(x / other.x, y / other.y);
}


inline HookLibrary::DataStructures::Vector2& HookLibrary::DataStructures::Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

inline HookLibrary::DataStructures::Vector2& HookLibrary::DataStructures::Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

inline HookLibrary::DataStructures::Vector2& HookLibrary::DataStructures::Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

inline HookLibrary::DataStructures::Vector2& HookLibrary::DataStructures::Vector2::operator/=(const Vector2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

inline bool HookLibrary::DataStructures::Vector2::operator==(const Vector2& other) const {
	return x == other.x && y == other.y;
}

inline bool HookLibrary::DataStructures::Vector2::operator!=(const Vector2& other) const {
	return x != other.x || y != other.y;
}