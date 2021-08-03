#include "Vector3.h"

#include <cmath>

namespace HookLibrary {
	namespace DataStructures {

		Vector3::Vector3()
			:x(0), y(0), z(0)
		{}

		Vector3::Vector3(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

		float Vector3::Magnitude() const {
			return sqrt(x * x + y * y + z * z);
		}

		float Vector3::SqrMagnitude() const {
			return (x * x + y * y + z * z);
		}

		float Vector3::Distance(const Vector3& a, const Vector3& b) {
			float x = a.x - b.x;
			float y = a.y - b.y;
			float z = a.z - b.z;
			return sqrt(x * x + y * y + z * z);
		}

		Vector3 Vector3::operator+(const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 Vector3::operator-(const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 Vector3::operator*(const Vector3& other) const {
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		Vector3 Vector3::operator/(const Vector3& other) const {
			return Vector3(x / other.x, y / other.y, z / other.z);
		}

		Vector3& Vector3::operator+=(const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& Vector3::operator-=(const Vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& Vector3::operator*=(const Vector3& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vector3& Vector3::operator/=(const Vector3& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		bool Vector3::operator==(const Vector3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}

		bool Vector3::operator!=(const Vector3& other) const {
			return x != other.x || y != other.y || z != other.z;
		}

	} // namespace DataStructures
} // namespace HookLibrary