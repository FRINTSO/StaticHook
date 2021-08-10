#ifndef STATICHOOK_VECTOR3_H_
#define STATICHOOK_VECTOR3_H_

namespace HookLibrary {
	namespace DataStructures {

		class Vector3 {
		public:
			float x, y, z;
		public:
			explicit Vector3();
			explicit Vector3(float x, float y, float z);

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

			inline float& operator[](size_t index) noexcept;
			constexpr const float& operator[](size_t index) const noexcept;
		};

	} // namespace DataStructures
} // namespace HookLibrary

#endif // !STATICHOOK_VECTOR3_H_