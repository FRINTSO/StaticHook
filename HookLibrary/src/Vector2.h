#ifndef STATICHOOK_VECTOR2_H_
#define STATICHOOK_VECTOR2_H_

namespace HookLibrary {
	namespace DataStructures {
		class Vector2
		{
		public:
			float x, y;
		public:
			explicit Vector2();
			explicit Vector2(float x, float y);

			inline float Magnitude() const;
			inline float SqrMagnitude() const;

			static float Distance(const Vector2& a, const Vector2& b);

			inline Vector2 operator+(const Vector2& other) const;
			inline Vector2 operator-(const Vector2& other) const;
			inline Vector2 operator*(const Vector2& other) const;
			inline Vector2 operator/(const Vector2& other) const;

			inline Vector2& operator+=(const Vector2& other);
			inline Vector2& operator-=(const Vector2& other);
			inline Vector2& operator*=(const Vector2& other);
			inline Vector2& operator/=(const Vector2& other);

			inline bool operator==(const Vector2& other) const;
			inline bool operator!=(const Vector2& other) const;
		};
	}
}

#endif // !STATICHOOK_VECTOR2_H_