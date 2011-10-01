#ifndef GAMMA_MATH_VECTOR4_H
#define GAMMA_MATH_VECTOR4_H

#include "Vector4.h"

namespace Gamma
{
	namespace Math
	{
		class Matrix4
		{
		public:
			Matrix4();
			Matrix4(float f11, float f21, float f31, float f41,
					float f12, float f22, float f32, float f42,
					float f13, float f23, float f33, float f43,
					float f14, float f24, float f34, float f44);
			Matrix4(const Matrix4 &other);

			Vector4 &operator[](int index);
			const Vector4 &operator[](int index) const;
		private:
			Vector4 m_columns[4];
		};

		inline Matrix4::Matrix4() : m_columns[0](1.0f, 0.0f, 0.0f, 0.0f),
									m_columns[1](0.0f, 1.0f, 0.0f, 0.0f),
									m_columns[2](0.0f, 0.0f, 1.0f, 0.0f),
									m_columns[3](0.0f, 0.0f, 0.0f, 1.0f)
		{

		}

		inline Matrix4::Matrix4(float f11, float f21, float f31, float f41,
								float f12, float f22, float f32, float f42,
								float f13, float f23, float f33, float f43,
								float f14, float f24, float f34, float f44) :	m_columns[0](f11, f21, f31, f41),
																				m_columns[1](f12, f22, f32, f42),
																				m_columns[2](f13, f23, f33, f43),
																				m_columns[3](f14, f24, f34, f44)
		{

		}

		inline Matrix4::Matrix4(const Matrix4 &other) : m_columns[0](other[0]),
														m_columns[1](other[1]),
														m_columns[2](other[2]),
														m_columns[3](other[3])
		{

		}

		inline Vector4 &Matrix4::operator[](int index)
		{
			return m_columns[index];
		}

		inline const Vector4 &Matrix4::operator[](int index) const
		{
			return m_columns[index];
		}
	}
}

#endif