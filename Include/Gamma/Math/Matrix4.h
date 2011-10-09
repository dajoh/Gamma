#ifndef GAMMA_MATH_MATRIX4_H
#define GAMMA_MATH_MATRIX4_H

#include <cstring>
#include "Vector4.h"
#include "Vector3.h"

namespace Gamma
{
	namespace Math
	{
		class Matrix4
		{
		public:
			Matrix4(bool initialize = true);
			Matrix4(float s);
			Matrix4(float *data);
			Matrix4(const Vector4 &column0, const Vector4 &column1, const Vector4 &column2, const Vector4 &column3);
			Matrix4(const Matrix4 &other);

			Vector4 &operator[](int index);
			const Vector4 &operator[](int index) const;

			bool operator==(const Matrix4 &other) const;
			bool operator!=(const Matrix4 &other) const;

			Matrix4 operator*(const Matrix4 &other) const;
			Matrix4 operator/(float scalar) const;
			const Matrix4 &operator*=(const Matrix4 &other);
			const Matrix4 &operator/=(float scalar);
		private:
			Vector4 m_data[4];
		};

		inline Matrix4::Matrix4(bool initialize)
		{
			if(initialize)
			{
				m_data[0].x = 1.0f; m_data[0].y = 0.0f; m_data[0].z = 0.0f; m_data[0].w = 0.0f;
				m_data[1].x = 0.0f; m_data[1].y = 1.0f; m_data[1].z = 0.0f; m_data[1].w = 0.0f;
				m_data[2].x = 0.0f; m_data[2].y = 0.0f; m_data[2].z = 1.0f; m_data[2].w = 0.0f;
				m_data[3].x = 0.0f; m_data[3].y = 0.0f; m_data[3].z = 0.0f; m_data[3].w = 1.0f;
			}
		}

		inline Matrix4::Matrix4(float s)
		{
			m_data[0].x = s; m_data[0].y = 0.0f; m_data[0].z = 0.0f; m_data[0].w = 0.0f;
			m_data[1].x = 0.0f; m_data[1].y = s; m_data[1].z = 0.0f; m_data[1].w = 0.0f;
			m_data[2].x = 0.0f; m_data[2].y = 0.0f; m_data[2].z = s; m_data[2].w = 0.0f;
			m_data[3].x = 0.0f; m_data[3].y = 0.0f; m_data[3].z = 0.0f; m_data[3].w = s;
		}

		inline Matrix4::Matrix4(float *data)
		{
			m_data[0].x = data[0];  m_data[0].y = data[1];  m_data[0].z = data[2];  m_data[0].w = data[3];
			m_data[1].x = data[4];  m_data[1].y = data[5];  m_data[1].z = data[6];  m_data[1].w = data[7];
			m_data[2].x = data[8];  m_data[2].y = data[9];  m_data[2].z = data[10]; m_data[2].w = data[11];
			m_data[3].x = data[12]; m_data[3].y = data[13]; m_data[3].z = data[14]; m_data[3].w = data[15];
		}

		inline Matrix4::Matrix4(const Vector4 &column0, const Vector4 &column1, const Vector4 &column2, const Vector4 &column3)
		{
			m_data[0] = column0;
			m_data[1] = column1;
			m_data[2] = column2;
			m_data[3] = column3;
		}

		inline Matrix4::Matrix4(const Matrix4 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
			m_data[3] = other.m_data[3];
		}

		inline Vector4 &Matrix4::operator[](int index)
		{
			return m_data[index];
		}

		inline const Vector4 &Matrix4::operator[](int index) const
		{
			return m_data[index];
		}

		inline bool Matrix4::operator==(const Matrix4 &other) const
		{
			return ((m_data[0] == other.m_data[0]) && (m_data[1] == other.m_data[1]) && (m_data[2] == other.m_data[2]) && (m_data[3] == other.m_data[3]));
		}

		inline bool Matrix4::operator!=(const Matrix4 &other) const
		{
			return ((m_data[0] != other.m_data[0]) || (m_data[1] != other.m_data[1]) || (m_data[2] != other.m_data[2]) || (m_data[3] != other.m_data[3]));
		}

		inline Matrix4 Matrix4::operator*(const Matrix4 &other) const
		{
			Matrix4 result(false);
			result[0] = m_data[0] * other.m_data[0].x + m_data[1] * other.m_data[0].y + m_data[2] * other.m_data[0].z + m_data[3] * other.m_data[0].w;
			result[1] = m_data[0] * other.m_data[1].x + m_data[1] * other.m_data[1].y + m_data[2] * other.m_data[1].z + m_data[3] * other.m_data[1].w;
			result[2] = m_data[0] * other.m_data[2].x + m_data[1] * other.m_data[2].y + m_data[2] * other.m_data[2].z + m_data[3] * other.m_data[2].w;
			result[3] = m_data[0] * other.m_data[3].x + m_data[1] * other.m_data[3].y + m_data[2] * other.m_data[3].z + m_data[3] * other.m_data[3].w;
			return result;
		}

		inline Matrix4 Matrix4::operator/(float scalar) const
		{
			Matrix4 result(false);
			result[0] = m_data[0] / scalar;
			result[1] = m_data[1] / scalar;
			result[2] = m_data[2] / scalar;
			result[3] = m_data[3] / scalar;
			return result;
		}

		inline const Matrix4 &Matrix4::operator*=(const Matrix4 &other)
		{
			*this = *this * other;
			return *this;
		}

		inline const Matrix4 &Matrix4::operator/=(float scalar)
		{
			m_data[0] /= scalar;
			m_data[1] /= scalar;
			m_data[2] /= scalar;
			m_data[3] /= scalar;
			return *this;
		}

		inline Vector4 operator*(const Matrix4 &matrix, const Vector4 &vector)
		{
			return Vector4(	matrix[0].x * vector.x + matrix[1].x * vector.y + matrix[2].x * vector.z + matrix[3].x * vector.w,
							matrix[0].y * vector.x + matrix[1].y * vector.y + matrix[2].y * vector.z + matrix[3].y * vector.w,
							matrix[0].z * vector.x + matrix[1].z * vector.y + matrix[2].z * vector.z + matrix[3].z * vector.w,
							matrix[0].w * vector.x + matrix[1].w * vector.y + matrix[2].w * vector.z + matrix[3].w * vector.w);
		}

		inline Vector4 operator*(const Vector4 &vector, const Matrix4 &matrix)
		{
			return Vector4(	matrix[0].x * vector.x + matrix[0].y * vector.y + matrix[0].z * vector.z + matrix[0].w * vector.w,
							matrix[1].x * vector.x + matrix[1].y * vector.y + matrix[1].z * vector.z + matrix[1].w * vector.w,
							matrix[2].x * vector.x + matrix[2].y * vector.y + matrix[2].z * vector.z + matrix[2].w * vector.w,
							matrix[3].x * vector.x + matrix[3].y * vector.y + matrix[3].z * vector.z + matrix[3].w * vector.w);
		}

		inline Matrix4 translateMatrix(const Matrix4 &matrix, const Vector3 &vector)
		{
			Matrix4 result(matrix);
			result[3] = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z + matrix[3];
			return result;
		}

		inline Matrix4 rotateMatrix(const Matrix4 &matrix, float angle, const Vector3 &vector)
		{
			float r = angle * (3.1415926535897932384626433832795f / 180.0f);
			float c = cosf(r);
			float s = sinf(r);

			Vector3 axis = normalize(vector);
			Vector3 temp = axis * (1.0f - c);

			Matrix4 rotate(0.0f);
			rotate[0].x = c + temp.x * axis.x;
			rotate[0].y = 0 + temp.x * axis.y + s * axis.z;
			rotate[0].z = 0 + temp.x * axis.z - s * axis.y;
			rotate[1].x = 0 + temp.y * axis.x - s * axis.z;
			rotate[1].y = c + temp.y * axis.y;
			rotate[1].z = 0 + temp.y * axis.z + s * axis.x;
			rotate[2].x = 0 + temp.z * axis.x + s * axis.y;
			rotate[2].y = 0 + temp.z * axis.y - s * axis.x;
			rotate[2].z = c + temp.z * axis.z;

			Matrix4 result(0.0f);
			result[0] = matrix[0] * rotate[0].x + matrix[1] * rotate[0].y + matrix[2] * rotate[0].z;
			result[1] = matrix[0] * rotate[1].x + matrix[1] * rotate[1].y + matrix[2] * rotate[1].z;
			result[2] = matrix[0] * rotate[2].x + matrix[1] * rotate[2].y + matrix[2] * rotate[2].z;
			result[3] = matrix[3];
			return result;
		}

		inline Matrix4 scaleMatrix(const Matrix4 &matrix, const Vector3 &vector)
		{
			Matrix4 result(0.0f);
			result[0] = matrix[0] * vector.x;
			result[1] = matrix[1] * vector.y;
			result[2] = matrix[2] * vector.z;
			result[3] = matrix[3];
			return result;
		}

		inline Matrix4 makeFrustumMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			Matrix4 result(0.0f);
			result[0].x = (2.0f * zNear) / (right - left);
			result[1].y = (2.0f * zNear) / (top - bottom);
			result[2].x = (right + left) / (right - left);
			result[2].y = (top + bottom) / (top - bottom);
			result[2].z = -(zFar + zNear) / (zFar - zNear);
			result[2].w = -(1.0f);
			result[3].z = -(2.0f * zFar * zNear) / (zFar - zNear);
			return result;
		}

		inline Matrix4 makeOrthogonalMatrix(float left, float right, float bottom, float top)
		{
			Matrix4 result(1.0f);
			result[0].x = 2.0f / (right - left);
			result[1].y = 2.0f / (top - bottom);
			result[2].z = -(1.0f);
			result[3].x = -(right + left) / (right - left);
			result[3].y = -(top + bottom) / (top - bottom);
			return result;
		}

		inline Matrix4 makeOrthogonalMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			Matrix4 result(1.0f);
			result[0].x = 2.0f / (right - left);
			result[1].y = 2.0f / (top - bottom);
			result[2].z = -(2.0f) / (zFar - zNear);
			result[3].x = -(right + left) / (right - left);
			result[3].y = -(top + bottom) / (top - bottom);
			result[3].z = -(zFar + zNear) / (zFar - zNear);
			return result;
		}

		inline Matrix4 makePerspectiveMatrix(float fov, float width, float height, float zNear, float zFar)
		{
			float radians = fov * (3.1415926535897932384626433832795f / 180.0f);
			float h = cosf(0.5f * radians) / sinf(0.5f * radians);
			float w = h * height / width;

			Matrix4 result(0.0f);
			result[0].x = w;
			result[1].y = h;
			result[2].z = (zFar + zNear) / (zFar - zNear);
			result[2].w = 1.0f;
			result[3].z = -(2.0f * zFar * zNear) / (zFar - zNear);
			return result;
		}

		inline Matrix4 makeLookAtMatrix(const Vector3 &eye, const Vector3 &center, const Vector3 &up)
		{
			Vector3 f = normalize(center - eye);
			Vector3 u = normalize(up);
			Vector3 s = normalize(cross(f, u));
			u = cross(s, f);

			Matrix4 result(1.0f);
			result[0].x = s.x;
			result[1].x = s.y;
			result[2].x = s.z;
			result[0].y = u.x;
			result[1].y = u.y;
			result[2].y = u.z;
			result[0].z = -(f.x);
			result[1].z = -(f.y);
			result[2].z = -(f.z);
			return translateMatrix(result, -eye);
		}

		inline Matrix4 transposeMatrix(const Matrix4 &matrix)
		{
			Matrix4 result(false);
			result[0].x = matrix[0].x;
			result[0].y = matrix[1].x;
			result[0].z = matrix[2].x;
			result[0].w = matrix[3].x;
			result[1].x = matrix[0].y;
			result[1].y = matrix[1].y;
			result[1].z = matrix[2].y;
			result[1].w = matrix[3].y;
			result[2].x = matrix[0].z;
			result[2].y = matrix[1].z;
			result[2].z = matrix[2].z;
			result[2].w = matrix[3].z;
			result[3].x = matrix[0].w;
			result[3].y = matrix[1].w;
			result[3].z = matrix[2].w;
			result[3].w = matrix[3].w;
			return result;
		}

		inline Matrix4 invertMatrix(const Matrix4 &matrix)
		{
			const Vector4 signA(+1, -1, +1, -1);
			const Vector4 signB(-1, +1, -1, +1);

			float c00 = matrix[2].z * matrix[3].w - matrix[3].z * matrix[2].w;
			float c02 = matrix[1].z * matrix[3].w - matrix[3].z * matrix[1].w;
			float c03 = matrix[1].z * matrix[2].w - matrix[2].z * matrix[1].w;

			float c04 = matrix[2].y * matrix[3].w - matrix[3].y * matrix[2].w;
			float c06 = matrix[1].y * matrix[3].w - matrix[3].y * matrix[1].w;
			float c07 = matrix[1].y * matrix[2].w - matrix[2].y * matrix[1].w;

			float c08 = matrix[2].y * matrix[3].z - matrix[3].y * matrix[2].z;
			float c10 = matrix[1].y * matrix[3].z - matrix[3].y * matrix[1].z;
			float c11 = matrix[1].y * matrix[2].z - matrix[2].y * matrix[1].z;

			float c12 = matrix[2].x * matrix[3].w - matrix[3].x * matrix[2].w;
			float c14 = matrix[1].x * matrix[3].w - matrix[3].x * matrix[1].w;
			float c15 = matrix[1].x * matrix[2].w - matrix[2].x * matrix[1].w;

			float c16 = matrix[2].x * matrix[3].z - matrix[3].x * matrix[2].z;
			float c18 = matrix[1].x * matrix[3].z - matrix[3].x * matrix[1].z;
			float c19 = matrix[1].x * matrix[2].z - matrix[2].x * matrix[1].z;

			float c20 = matrix[2].x * matrix[3].y - matrix[3].x * matrix[2].y;
			float c22 = matrix[1].x * matrix[3].y - matrix[3].x * matrix[1].y;
			float c23 = matrix[1].x * matrix[2].y - matrix[2].x * matrix[1].y;

			Vector4 fac0(c00, c00, c02, c03);
			Vector4 fac1(c04, c04, c06, c07);
			Vector4 fac2(c08, c08, c10, c11);
			Vector4 fac3(c12, c12, c14, c15);
			Vector4 fac4(c16, c16, c18, c19);
			Vector4 fac5(c20, c20, c22, c23);

			Vector4 vec0(matrix[1].x, matrix[0].x, matrix[0].x, matrix[0].x);
			Vector4 vec1(matrix[1].y, matrix[0].y, matrix[0].y, matrix[0].y);
			Vector4 vec2(matrix[1].z, matrix[0].z, matrix[0].z, matrix[0].z);
			Vector4 vec3(matrix[1].w, matrix[0].w, matrix[0].w, matrix[0].w);

			Vector4 inv0 = signA * (vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
			Vector4 inv1 = signB * (vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
			Vector4 inv2 = signA * (vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
			Vector4 inv3 = signB * (vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

			Matrix4 inverse(inv0, inv1, inv2, inv3);
			Vector4 row0(inverse[0].x, inverse[1].x, inverse[2].x, inverse[3].x);

			float determinant = dot(matrix[0], row0);
			inverse /= determinant;
			return inverse;
		}
	}
}

#endif