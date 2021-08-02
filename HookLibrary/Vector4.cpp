#include "Vector4.h"

#include <cmath>

namespace HookLibrary {
	namespace DataStructures {

		Vector4::Vector4()
			:x(0), y(0), z(0), w(0)
		{}

		Vector4::Vector4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{}

		inline float Vector4::Magnitude() const {
			return sqrt(x * x + y * y + z * z + w * w);
		}

		inline float Vector4::SqrMagnitude() const {
			return (x * x + y * y + z * z + w * w);
		}

		inline float Vector4::Distance(const Vector4& a, const Vector4& b) {
			float x = a.x - b.x;
			float y = a.y - b.y;
			float z = a.z - b.z;
			float w = a.w - b.w;
			return sqrt(x * x + y * y + z * z + w * w);
		}

		inline Vector4 Vector4::operator+(const Vector4& other) const {
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		inline Vector4 Vector4::operator-(const Vector4& other) const {
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		inline Vector4 Vector4::operator*(const Vector4& other) const {
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		inline Vector4 Vector4::operator/(const Vector4& other) const {
			return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		inline Vector4& Vector4::operator+=(const Vector4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		inline Vector4& Vector4::operator-=(const Vector4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		inline Vector4& Vector4::operator*=(const Vector4& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		inline Vector4& Vector4::operator/=(const Vector4& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		inline bool Vector4::operator==(const Vector4& other) const {
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		inline bool Vector4::operator!=(const Vector4& other) const {
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}

	} // namespace DataStructures
} // namespace HookLibrary