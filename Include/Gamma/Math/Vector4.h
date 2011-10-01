#ifndef GAMMA_MATH_VECTOR4_H
#define GAMMA_MATH_VECTOR4_H

namespace Gamma
{
	namespace Math
	{
		class Vector4
		{
		public:
			Vector4();
			Vector4(float f);
			Vector4(float x, float y, float z, float w = 1.0f);
			Vector4(const Vector4 &other);

			float &operator[](int index);
			const float &operator[](int index) const;
		private:
			float m_data[4];
		};

		inline Vector4::Vector4() : m_data[0](0.0f), m_data[1](0.0f), m_data[2](0.0f), m_data[3](1.0f)
		{

		}

		inline Vector4::Vector4(float f) : m_data[0](f), m_data[1](f), m_data[2](f), m_data[3](1.0f)
		{

		}

		inline Vector4::Vector4(float x, float y, float z, float w) : m_data[0](x), m_data[1](y), m_data[2](z), m_data[3](w)
		{

		}

		inline Vector4::Vector4(const Vector4 &other) : m_data[0](other[0]), m_data[1](other[1]), m_data[2](other[2]), m_data[3](other[3])
		{

		}

		inline float &Vector4::operator[](int index)
		{
			return m_data[index];
		}

		inline const float &Vector4::operator[](int index) const
		{
			return m_data[index];
		}
	}
}

#endif