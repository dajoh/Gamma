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
			Matrix4(const Matrix4 &other);

			Vector4 &operator[](int index);
			const Vector4 &operator[](int index) const;

			bool operator==(const Matrix4 &other) const;
			bool operator!=(const Matrix4 &other) const;

			Matrix4 operator*(const Matrix4 &other) const;
			const Matrix4 &operator*=(const Matrix4 &other);
		private:
			Vector4 m_data[4];
		};

		Matrix4::Matrix4(bool initialize)
		{
			if(initialize)
			{
				m_data[0][0] = 1.0f; m_data[0][1] = 0.0f; m_data[0][2] = 0.0f; m_data[0][3] = 0.0f;
				m_data[1][0] = 0.0f; m_data[1][1] = 1.0f; m_data[1][2] = 0.0f; m_data[1][3] = 0.0f;
				m_data[2][0] = 0.0f; m_data[2][1] = 0.0f; m_data[2][2] = 1.0f; m_data[2][3] = 0.0f;
				m_data[3][0] = 0.0f; m_data[3][1] = 0.0f; m_data[3][2] = 0.0f; m_data[3][3] = 1.0f;
			}
		}

		Matrix4::Matrix4(float s)
		{
			m_data[0][0] = s; m_data[0][1] = 0.0f; m_data[0][2] = 0.0f; m_data[0][3] = 0.0f;
			m_data[1][0] = 0.0f; m_data[1][1] = s; m_data[1][2] = 0.0f; m_data[1][3] = 0.0f;
			m_data[2][0] = 0.0f; m_data[2][1] = 0.0f; m_data[2][2] = s; m_data[2][3] = 0.0f;
			m_data[3][0] = 0.0f; m_data[3][1] = 0.0f; m_data[3][2] = 0.0f; m_data[3][3] = s;
		}

		Matrix4::Matrix4(float *data)
		{
			m_data[0][0] = data[0];  m_data[0][1] = data[1];  m_data[0][2] = data[2];  m_data[0][3] = data[3];
			m_data[1][0] = data[4];  m_data[1][1] = data[5];  m_data[1][2] = data[6];  m_data[1][3] = data[7];
			m_data[2][0] = data[8];  m_data[2][1] = data[9];  m_data[2][2] = data[10]; m_data[2][3] = data[11];
			m_data[3][0] = data[12]; m_data[3][1] = data[13]; m_data[3][2] = data[14]; m_data[3][3] = data[15];
		}

		Matrix4::Matrix4(const Matrix4 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
			m_data[3] = other.m_data[3];
		}

		Vector4 &Matrix4::operator[](int index)
		{
			return m_data[index];
		}

		const Vector4 &Matrix4::operator[](int index) const
		{
			return m_data[index];
		}

		bool Matrix4::operator==(const Matrix4 &other) const
		{
			return ((m_data[0] == other.m_data[0]) && (m_data[1] == other.m_data[1]) && (m_data[2] == other.m_data[2]) && (m_data[3] == other.m_data[3]));
		}

		bool Matrix4::operator!=(const Matrix4 &other) const
		{
			return ((m_data[0] != other.m_data[0]) || (m_data[1] != other.m_data[1]) || (m_data[2] != other.m_data[2]) || (m_data[3] != other.m_data[3]));
		}

		Matrix4 Matrix4::operator*(const Matrix4 &other) const
		{
			Matrix4 result(false);
			result[0] = m_data[0] * other.m_data[0][0] + m_data[1] * other.m_data[0][1] + m_data[2] * other.m_data[0][2] + m_data[3] * other.m_data[0][3];
			result[1] = m_data[0] * other.m_data[1][0] + m_data[1] * other.m_data[1][1] + m_data[2] * other.m_data[1][2] + m_data[3] * other.m_data[1][3];
			result[2] = m_data[0] * other.m_data[2][0] + m_data[1] * other.m_data[2][1] + m_data[2] * other.m_data[2][2] + m_data[3] * other.m_data[2][3];
			result[3] = m_data[0] * other.m_data[3][0] + m_data[1] * other.m_data[3][1] + m_data[2] * other.m_data[3][2] + m_data[3] * other.m_data[3][3];
			return result;
		}

		const Matrix4 &Matrix4::operator*=(const Matrix4 &other)
		{
			*this = *this * other;
			return *this;
		}

		Vector4 operator*(const Matrix4 &matrix, const Vector4 &vector)
		{
			return Vector4(	matrix[0][0] * vector[0] + matrix[1][0] * vector[1] + matrix[2][0] * vector[2] + matrix[3][0] * vector[3],
							matrix[0][1] * vector[0] + matrix[1][1] * vector[1] + matrix[2][1] * vector[2] + matrix[3][1] * vector[3],
							matrix[0][2] * vector[0] + matrix[1][2] * vector[1] + matrix[2][2] * vector[2] + matrix[3][2] * vector[3],
							matrix[0][3] * vector[0] + matrix[1][3] * vector[1] + matrix[2][3] * vector[2] + matrix[3][3] * vector[3]);
		}

		Vector4 operator*(const Vector4 &vector, const Matrix4 &matrix)
		{
			return Vector4(	matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2] + matrix[0][3] * vector[3],
							matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2] + matrix[1][3] * vector[3],
							matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2] + matrix[2][3] * vector[3],
							matrix[3][0] * vector[0] + matrix[3][1] * vector[1] + matrix[3][2] * vector[2] + matrix[3][3] * vector[3]);
		}

		Matrix4 translateMatrix(const Matrix4 &matrix, const Vector3 &vector)
		{
			Matrix4 result(matrix);
			result[3] = matrix[0] * vector[0] + matrix[1] * vector[1] + matrix[2] * vector[2] + matrix[3];
			return result;
		}

		Matrix4 rotateMatrix(const Matrix4 &matrix, float angle, const Vector3 &vector)
		{
			float r = angle * (3.1415926535897932384626433832795f / 180.0f);
			float c = cosf(r);
			float s = sinf(r);

			Vector3 axis = normalize(vector);
			Vector3 temp = axis * (1.0f - c);

			Matrix4 rotate(0.0f);
			rotate[0][0] = c + temp[0] * axis[0];
			rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
			rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
			rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
			rotate[1][1] = c + temp[1] * axis[1];
			rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
			rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
			rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
			rotate[2][2] = c + temp[2] * axis[2];

			Matrix4 result(0.0f);
			result[0] = matrix[0] * rotate[0][0] + matrix[1] * rotate[0][1] + matrix[2] * rotate[0][2];
			result[1] = matrix[0] * rotate[1][0] + matrix[1] * rotate[1][1] + matrix[2] * rotate[1][2];
			result[2] = matrix[0] * rotate[2][0] + matrix[1] * rotate[2][1] + matrix[2] * rotate[2][2];
			result[3] = matrix[3];
			return result;
		}

		Matrix4 scaleMatrix(const Matrix4 &matrix, const Vector3 &vector)
		{
			Matrix4 result(0.0f);
			result[0] = matrix[0] * vector[0];
			result[1] = matrix[1] * vector[1];
			result[2] = matrix[2] * vector[2];
			result[3] = matrix[3];
			return result;
		}

		Matrix4 makeFrustumMatrix(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4 result(0.0f);
			result[0][0] = (2.0f * near) / (right - left);
			result[1][1] = (2.0f * near) / (top - bottom);
			result[2][0] = (right + left) / (right - left);
			result[2][1] = (top + bottom) / (top - bottom);
			result[2][2] = -(far + near) / (far - near);
			result[2][3] = -(1.0f);
			result[3][2] = -(2.0f * far * near) / (far - near);
			return result;
		}

		Matrix4 makeOrthogonalMatrix(float left, float right, float bottom, float top)
		{
			Matrix4 result(1.0f);
			result[0][0] = 2.0f / (right - left);
			result[1][1] = 2.0f / (top - bottom);
			result[2][2] = -(1.0f);
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			return result;
		}

		Matrix4 makeOrthogonalMatrix(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4 result(1.0f);
			result[0][0] = 2.0f / (right - left);
			result[1][1] = 2.0f / (top - bottom);
			result[2][2] = -(2.0f) / (far - near);
			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			result[3][2] = -(far + near) / (far - near);
			return result;
		}

		Matrix4 makePerspectiveMatrix(float fov, float width, float height, float near, float far)
		{
			float radians = fov * (3.1415926535897932384626433832795f / 180.0f);
			float h = cosf(0.5f * radians) / sinf(0.5f * radians);
			float w = h * height / width;

			Matrix4 result(0.0f);
			result[0][0] = w;
			result[1][1] = h;
			result[2][2] = (far + near) / (far - near);
			result[2][3] = 1.0f;
			result[3][2] = -(2.0f * far * near) / (far - near);
			return result;
		}

		Matrix4 makeLookAtMatrix(const Vector3 &eye, const Vector3 &center, const Vector3 &up)
		{
			Vector3 f = normalize(center - eye);
			Vector3 u = normalize(up);
			Vector3 s = normalize(cross(f, u));
			u = cross(s, f);

			Matrix4 result(1.0f);
			result[0][0] = s[0];
			result[1][0] = s[1];
			result[2][0] = s[2];
			result[0][1] = u[0];
			result[1][1] = u[1];
			result[2][1] = u[2];
			result[0][2] = -f[0];
			result[1][2] = -f[1];
			result[2][2] = -f[2];
			return translateMatrix(result, -eye);
		}

		Matrix4 transposeMatrix(const Matrix4 &matrix)
		{
			Matrix4 result(false);
			result[0][0] = matrix[0][0];
			result[0][1] = matrix[1][0];
			result[0][2] = matrix[2][0];
			result[0][3] = matrix[3][0];
			result[1][0] = matrix[0][1];
			result[1][1] = matrix[1][1];
			result[1][2] = matrix[2][1];
			result[1][3] = matrix[3][1];
			result[2][0] = matrix[0][2];
			result[2][1] = matrix[1][2];
			result[2][2] = matrix[2][2];
			result[2][3] = matrix[3][2];
			result[3][0] = matrix[0][3];
			result[3][1] = matrix[1][3];
			result[3][2] = matrix[2][3];
			result[3][3] = matrix[3][3];
			return result;
		}
	}
}

#endif