#include "Matrix4x4.h"
#include <xmemory>

namespace HookLibrary {
	namespace DataStructures {
		/*
		inline Matrix4x4::Matrix4x4()
			: rows()
		{}

		inline Matrix4x4::Matrix4x4(const Vector4 (&initializer)[4]) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] = initializer[i];
			}
		}

		inline Matrix4x4::Matrix4x4(const float (&initializer)[4][4]) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] = Vector4(initializer[i][0], initializer[i][1], initializer[i][2], initializer[i][3]);
			}
		}

		inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] += rhs[i];
			}
			return *this;
		}

		inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] -= rhs[i];
			}
			return *this;
		}

		inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] *= rhs[i];
			}
			return *this;
		}

		inline Matrix4x4& Matrix4x4::operator/=(const Matrix4x4& rhs) {
			for (size_t i = 0; i < 4; i++) {
				rows[i] /= rhs[i];
			}
			return *this;
		}


		Matrix4x4 operator+(Matrix4x4 lhs, const Matrix4x4& rhs) {
			lhs += rhs;
			return lhs;
		}

		Matrix4x4 operator-(Matrix4x4 lhs, const Matrix4x4& rhs) {
			lhs -= rhs;
			return lhs;
		}

		Matrix4x4 operator*(Matrix4x4 lhs, const Matrix4x4& rhs) {
			lhs *= rhs;
			return lhs;
		}

		Matrix4x4 operator/(Matrix4x4 lhs, const Matrix4x4& rhs) {
			lhs /= rhs;
			return lhs;
		}


		inline bool Matrix4x4::operator==(const Matrix4x4& rhs) const noexcept {
			return rows[0][0] == rhs.rows[0][0] && rows[1][1] == rhs.rows[1][1] && rows[2][2] == rhs.rows[2][2] && rows[3][3] == rhs.rows[3][3] &&
				rows[0][1] == rhs.rows[0][1] && rows[0][2] == rhs.rows[0][2] && rows[0][3] == rhs.rows[0][3] &&
				rows[1][0] == rhs.rows[1][0] && rows[1][2] == rhs.rows[1][2] && rows[1][3] == rhs.rows[1][3] &&
				rows[2][0] == rhs.rows[2][0] && rows[2][1] == rhs.rows[2][1] && rows[2][3] == rhs.rows[2][3] &&
				rows[3][0] == rhs.rows[3][0] && rows[3][1] == rhs.rows[3][1] && rows[3][2] == rhs.rows[3][2];
		}

		inline bool Matrix4x4::operator!=(const Matrix4x4& rhs) const noexcept {
			return (rows[0][0] != rhs.rows[0][0] || rows[0][1] != rhs.rows[0][1] || rows[0][2] != rhs.rows[0][2] || rows[0][3] != rhs.rows[0][3] ||
				rows[1][0] != rhs.rows[1][0] || rows[1][1] != rhs.rows[1][1] || rows[1][2] != rhs.rows[1][2] || rows[1][3] != rhs.rows[1][3] ||
				rows[2][0] != rhs.rows[2][0] || rows[2][1] != rhs.rows[2][1] || rows[2][2] != rhs.rows[2][2] || rows[2][3] != rhs.rows[2][3] ||
				rows[3][0] != rhs.rows[3][0] || rows[3][1] != rhs.rows[3][1] || rows[3][2] != rhs.rows[3][2] || rows[3][3] != rhs.rows[3][3]);
		}

		inline Vector4& Matrix4x4::operator[](_In_range_(0, 3) size_t index) noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
			_STL_VERIFY(index < 4, "matrix4x4 subscript out of range");
#endif // !_CONTAINER_DEBUG_LEVEL > 0
			return rows[index];
		}

		constexpr const Vector4& Matrix4x4::operator[](_In_range_(0, 3) size_t index) const noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
			_STL_VERIFY(index < 4, "matrix4x4 subscript out of range");
#endif // !_CONTAINER_DEBUG_LEVEL > 0
			return rows[index];
		}

		inline float& Matrix4x4::operator()(_In_range_(0, 3) size_t row, _In_range_(0, 3) size_t column) noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
			_STL_VERIFY(row < 4 && column < 4, "matrix4x4 subscript out of range");
#endif // !_CONTAINER_DEBUG_LEVEL > 0
			return rows[row][column];
		}

		constexpr const float& Matrix4x4::operator()(_In_range_(0, 3) size_t row, _In_range_(0, 3) size_t column) const noexcept {
#if _CONTAINER_DEBUG_LEVEL > 0
			_STL_VERIFY(row < 4 && column < 4, "matrix4x4 subscript out of range");
#endif // !_CONTAINER_DEBUG_LEVEL > 0
			return rows[row][column];
		}
		*/

	} // namespace DataStructures
} // namespace HookLibrary