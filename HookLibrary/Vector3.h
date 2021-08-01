#ifndef STATICHOOK_VECTOR3_H_
#define STATICHOOK_VECTOR3_H_

namespace HookLibrary {
	namespace DataStructures {
		class Vector3
		{
		public:
			float x, y, z;
		public:
			Vector3();
			Vector3(float x, float y, float z);

			float Magnitude() const;
			float SqrMagnitude() const;

			static float Distance(const Vector3& a, const Vector3& b);

			Vector3 operator+(const Vector3& other) const;
			Vector3 operator-(const Vector3& other) const;
			Vector3 operator*(const Vector3& other) const;
			Vector3 operator/(const Vector3& other) const;

			Vector3& operator+=(const Vector3& other);
			Vector3& operator-=(const Vector3& other);
			Vector3& operator*=(const Vector3& other);
			Vector3& operator/=(const Vector3& other);

			bool operator==(const Vector3& other) const;
			bool operator!=(const Vector3& other) const;
		};
	}
}

#endif // !STATICHOOK_VECTOR3_H_