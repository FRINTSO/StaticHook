#ifndef STATICHOOK_VECTOR4_H_
#define STATICHOOK_VECTOR4_H_

namespace HookLibrary {
	namespace DataStructures {
		class Vector4
		{
		public:
			float x, y, z, w;
		public:
			explicit Vector4();
			explicit Vector4(float x, float y, float z, float w);

			inline float Magnitude() const;
			inline float SqrMagnitude() const;

			inline static float Distance(const Vector4& a, const Vector4& b);

			inline Vector4 operator+(const Vector4& other) const;
			inline Vector4 operator-(const Vector4& other) const;
			inline Vector4 operator*(const Vector4& other) const;
			inline Vector4 operator/(const Vector4& other) const;

			inline Vector4& operator+=(const Vector4& other);
			inline Vector4& operator-=(const Vector4& other);
			inline Vector4& operator*=(const Vector4& other);
			inline Vector4& operator/=(const Vector4& other);

			inline bool operator==(const Vector4& other) const;
			inline bool operator!=(const Vector4& other) const;
		};
	}
}
#endif // !STATICHOOK_VECTOR4_H_