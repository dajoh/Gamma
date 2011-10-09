#ifndef GAMMA_MATH_MATRIX3_H
#define GAMMA_MATH_MATRIX3_H

#include <cstring>
#include "Vector3.h"

namespace Gamma
{
	namespace Math
	{
		class Matrix3
		{
		public:
			Matrix3(bool initialize = true);
			Matrix3(float s);
			Matrix3(float *data);
			Matrix3(const Vector3 &column0, const Vector3 &column1, const Vector3 &column2);
			Matrix3(const Matrix3 &other);

			Vector3 &operator[](int index);
			const Vector3 &operator[](int index) const;

			bool operator==(const Matrix3 &other) const;
			bool operator!=(const Matrix3 &other) const;

			Matrix3 operator*(const Matrix3 &other) const;
			Matrix3 operator/(float scalar) const;
			const Matrix3 &operator*=(const Matrix3 &other);
			const Matrix3 &operator/=(float scalar);
		private:
			Vector3 m_data[3];
		};

		Matrix3::Matrix3(bool initialize)
		{
			if(initialize)
			{
				m_data[0].x = 1.0f; m_data[0].y = 0.0f; m_data[0].z = 0.0f;
				m_data[1].x = 0.0f; m_data[1].y = 1.0f; m_data[1].z = 0.0f;
				m_data[2].x = 0.0f; m_data[2].y = 0.0f; m_data[2].z = 1.0f;
			}
		}

		Matrix3::Matrix3(float s)
		{
			m_data[0].x = s; m_data[0].y = 0.0f; m_data[0].z = 0.0f;
			m_data[1].x = 0.0f; m_data[1].y = s; m_data[1].z = 0.0f;
			m_data[2].x = 0.0f; m_data[2].y = 0.0f; m_data[2].z = s;
		}

		Matrix3::Matrix3(float *data)
		{
			m_data[0].x = data[0];  m_data[0].y = data[1];  m_data[0].z = data[2];
			m_data[1].x = data[3];  m_data[1].y = data[4];  m_data[1].z = data[5];
			m_data[2].x = data[6];  m_data[2].y = data[7];  m_data[2].z = data[8];
		}

		Matrix3::Matrix3(const Vector3 &column0, const Vector3 &column1, const Vector3 &column2)
		{
			m_data[0] = column0;
			m_data[1] = column1;
			m_data[2] = column2;
		}

		Matrix3::Matrix3(const Matrix3 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
		}

		Vector3 &Matrix3::operator[](int index)
		{
			return m_data[index];
		}

		const Vector3 &Matrix3::operator[](int index) const
		{
			return m_data[index];
		}

		bool Matrix3::operator==(const Matrix3 &other) const
		{
			return ((m_data[0] == other.m_data[0]) && (m_data[1] == other.m_data[1]) && (m_data[2] == other.m_data[2]));
		}

		bool Matrix3::operator!=(const Matrix3 &other) const
		{
			return ((m_data[0] != other.m_data[0]) || (m_data[1] != other.m_data[1]) || (m_data[2] != other.m_data[2]));
		}

		Matrix3 Matrix3::operator*(const Matrix3 &other) const
		{
			Matrix3 result(false);
			result[0].x = m_data[0].x * other.m_data[0].x + m_data[1].x * other.m_data[0].y + m_data[2].x * other.m_data[0].z;
			result[0].y = m_data[0].y * other.m_data[0].x + m_data[1].y * other.m_data[0].y + m_data[2].y * other.m_data[0].z;
			result[0].z = m_data[0].z * other.m_data[0].x + m_data[1].z * other.m_data[0].y + m_data[2].z * other.m_data[0].z;
			result[1].x = m_data[0].x * other.m_data[1].x + m_data[1].x * other.m_data[1].y + m_data[2].x * other.m_data[1].z;
			result[1].y = m_data[0].y * other.m_data[1].x + m_data[1].y * other.m_data[1].y + m_data[2].y * other.m_data[1].z;
			result[1].z = m_data[0].z * other.m_data[1].x + m_data[1].z * other.m_data[1].y + m_data[2].z * other.m_data[1].z;
			result[2].x = m_data[0].x * other.m_data[2].x + m_data[1].x * other.m_data[2].y + m_data[2].x * other.m_data[2].z;
			result[2].y = m_data[0].y * other.m_data[2].x + m_data[1].y * other.m_data[2].y + m_data[2].y * other.m_data[2].z;
			result[2].z = m_data[0].z * other.m_data[2].x + m_data[1].z * other.m_data[2].y + m_data[2].z * other.m_data[2].z;
			return result;
		}

		Matrix3 Matrix3::operator/(float scalar) const
		{
			Matrix3 result(false);
			result[0] = m_data[0] / scalar;
			result[1] = m_data[1] / scalar;
			result[2] = m_data[2] / scalar;
			return result;
		}

		const Matrix3 &Matrix3::operator*=(const Matrix3 &other)
		{
			*this = *this * other;
			return *this;
		}

		const Matrix3 &Matrix3::operator/=(float scalar)
		{
			m_data[0] /= scalar;
			m_data[1] /= scalar;
			m_data[2] /= scalar;
			return *this;
		}

		Vector3 operator*(const Matrix3 &matrix, const Vector3 &vector)
		{
			return Vector3(	matrix[0].x * vector.x + matrix[1].x * vector.y + matrix[2].x * vector.z,
							matrix[0].y * vector.x + matrix[1].y * vector.y + matrix[2].y * vector.z,
							matrix[0].z * vector.x + matrix[1].z * vector.y + matrix[2].z * vector.z);
		}

		Vector3 operator*(const Vector3 &vector, const Matrix3 &matrix)
		{
			return Vector3(	matrix[0].x * vector.x + matrix[0].y * vector.y + matrix[0].z * vector.z,
							matrix[1].x * vector.x + matrix[1].y * vector.y + matrix[1].z * vector.z,
							matrix[2].x * vector.x + matrix[2].y * vector.y + matrix[2].z * vector.z);
		}

		Matrix3 transposeMatrix(const Matrix3 &matrix)
		{
			Matrix3 result(false);
			result[0].x = matrix[0].x;
			result[0].y = matrix[1].x;
			result[0].z = matrix[2].x;
			result[1].x = matrix[0].y;
			result[1].y = matrix[1].y;
			result[1].z = matrix[2].y;
			result[2].x = matrix[0].z;
			result[2].y = matrix[1].z;
			result[2].z = matrix[2].z;
			return result;
		}

		Matrix3 invertMatrix(const Matrix3 &matrix)
		{
			Matrix3 inverse(false);
			inverse[0].x = + (matrix[1].y * matrix[2].z - matrix[2].y * matrix[1].z);
			inverse[1].x = - (matrix[1].x * matrix[2].z - matrix[2].x * matrix[1].z);
			inverse[2].x = + (matrix[1].x * matrix[2].y - matrix[2].x * matrix[1].y);
			inverse[0].y = - (matrix[0].y * matrix[2].z - matrix[2].y * matrix[0].z);
			inverse[1].y = + (matrix[0].x * matrix[2].z - matrix[2].x * matrix[0].z);
			inverse[2].y = - (matrix[0].x * matrix[2].y - matrix[2].x * matrix[0].y);
			inverse[0].z = + (matrix[0].y * matrix[1].z - matrix[1].y * matrix[0].z);
			inverse[1].z = - (matrix[0].x * matrix[1].z - matrix[1].x * matrix[0].z);
			inverse[2].z = + (matrix[0].x * matrix[1].y - matrix[1].x * matrix[0].y);

			float determinant = +matrix[0].x * (matrix[1].y * matrix[2].z - matrix[2].y * matrix[1].z)
								-matrix[1].x * (matrix[0].y * matrix[2].z - matrix[2].y * matrix[0].z)
								+matrix[2].x * (matrix[0].y * matrix[1].z - matrix[1].y * matrix[0].z);
			inverse /= determinant;
			return inverse;
		}
	}
}

#endif