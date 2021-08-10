#include "Vector2.h"

#include <cmath>

namespace HookLibrary {
    namespace DataStructures {

        Vector2::Vector2()
            : x(0), y(0)
        {}

        Vector2::Vector2(float x, float y)
            : x(x), y(y)
        {}

        inline float Vector2::Magnitude() const {
            return sqrt(x * x + y * y);
        }

        inline float Vector2::SqrMagnitude() const {
            return (x * x + y * y);
        }

        float Vector2::Distance(const Vector2& a, const Vector2& b) {
            float x = a.x - b.x;
            float y = a.y - b.y;
            return sqrt(x * x + y * y);
        }

        inline Vector2 Vector2::operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }

        inline Vector2 Vector2::operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }

        inline Vector2 Vector2::operator*(const Vector2& other) const {
            return Vector2(x * other.x, y * other.y);
        }

        inline Vector2 Vector2::operator/(const Vector2& other) const {
            return Vector2(x / other.x, y / other.y);
        }


        inline Vector2& Vector2::operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        inline Vector2& Vector2::operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        inline Vector2& Vector2::operator*=(const Vector2& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        inline Vector2& Vector2::operator/=(const Vector2& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        inline bool Vector2::operator==(const Vector2& other) const {
            return x == other.x && y == other.y;
        }

        inline bool Vector2::operator!=(const Vector2& other) const {
            return x != other.x || y != other.y;
        }

        inline float& Vector2::operator[](size_t index) noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
            _STL_VERIFY(index < 4, "vector2 subscript out of range");
#endif
            return *((float*)(this) + index);
        }

        constexpr const float& Vector2::operator[](size_t index) const noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
            _STL_VERIFY(index < 4, "vector2 subscript out of range");
#endif
            return *((float*)(this) + index);
        }

    } // namespace DataStructures
} // namespace HookLibrary