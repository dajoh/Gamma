#ifndef GAMMA_MATH_VECTOR4_H
#define GAMMA_MATH_VECTOR4_H

#include <cmath>

namespace Gamma
{
	namespace Math
	{
		class Vector4
		{
		public:
			Vector4();
			Vector4(float s);
			Vector4(float x, float y, float z, float w);
			Vector4(const Vector4 &other);

			float &operator[](int index);
			const float &operator[](int index) const;

			bool operator==(const Vector4 &other) const;
			bool operator!=(const Vector4 &other) const;

			Vector4 operator+() const;
			Vector4 operator-() const;

			Vector4 operator+(float scalar) const;
			Vector4 operator-(float scalar) const;
			Vector4 operator*(float scalar) const;
			Vector4 operator/(float scalar) const;
			Vector4 operator+(const Vector4 &other) const;
			Vector4 operator-(const Vector4 &other) const;
			Vector4 operator*(const Vector4 &other) const;
			Vector4 operator/(const Vector4 &other) const;

			const Vector4 &operator=(const Vector4 &other);
			const Vector4 &operator+=(float scalar);
			const Vector4 &operator-=(float scalar);
			const Vector4 &operator*=(float scalar);
			const Vector4 &operator/=(float scalar);
			const Vector4 &operator+=(const Vector4 &other);
			const Vector4 &operator-=(const Vector4 &other);
			const Vector4 &operator*=(const Vector4 &other);
			const Vector4 &operator/=(const Vector4 &other);
		private:
			float m_data[4];
		};

		inline Vector4::Vector4()
		{

		}

		inline Vector4::Vector4(float s)
		{
			m_data[0] = s;
			m_data[1] = s;
			m_data[2] = s;
			m_data[3] = s;
		}

		inline Vector4::Vector4(float x, float y, float z, float w)
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
			m_data[3] = w;
		}

		inline Vector4::Vector4(const Vector4 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
			m_data[3] = other.m_data[3];
		}

		inline float &Vector4::operator[](int index)
		{
			return m_data[index];
		}

		inline const float &Vector4::operator[](int index) const
		{
			return m_data[index];
		}

		bool Vector4::operator==(const Vector4 &other) const
		{
			return ((m_data[0] == other.m_data[0]) && (m_data[1] == other.m_data[1]) && (m_data[2] == other.m_data[2]) && (m_data[3] == other.m_data[3]));
		}

		bool Vector4::operator!=(const Vector4 &other) const
		{
			return ((m_data[0] != other.m_data[0]) || (m_data[1] != other.m_data[1]) || (m_data[2] != other.m_data[2]) || (m_data[3] != other.m_data[3]));
		}

		Vector4 Vector4::operator+() const
		{
			return Vector4(+m_data[0], +m_data[1], +m_data[2], +m_data[3]);
		}

		Vector4 Vector4::operator-() const
		{
			return Vector4(-m_data[0], -m_data[1], -m_data[2], -m_data[3]);
		}

		Vector4 Vector4::operator+(float scalar) const
		{
			return Vector4(m_data[0] + scalar, m_data[1] + scalar, m_data[2] + scalar, m_data[3] + scalar);
		}

		Vector4 Vector4::operator-(float scalar) const
		{
			return Vector4(m_data[0] - scalar, m_data[1] - scalar, m_data[2] - scalar, m_data[3] - scalar);
		}

		Vector4 Vector4::operator*(float scalar) const
		{
			return Vector4(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar, m_data[3] * scalar);
		}

		Vector4 Vector4::operator/(float scalar) const
		{
			return Vector4(m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar, m_data[3] / scalar);
		}

		Vector4 Vector4::operator+(const Vector4 &other) const
		{
			return Vector4(m_data[0] + other.m_data[0], m_data[1] + other.m_data[1], m_data[2] + other.m_data[2], m_data[3] + other.m_data[3]);
		}

		Vector4 Vector4::operator-(const Vector4 &other) const
		{
			return Vector4(m_data[0] - other.m_data[0], m_data[1] - other.m_data[1], m_data[2] - other.m_data[2], m_data[3] - other.m_data[3]);
		}

		Vector4 Vector4::operator*(const Vector4 &other) const
		{
			return Vector4(m_data[0] * other.m_data[0], m_data[1] * other.m_data[1], m_data[2] * other.m_data[2], m_data[3] * other.m_data[3]);
		}

		Vector4 Vector4::operator/(const Vector4 &other) const
		{
			return Vector4(m_data[0] / other.m_data[0], m_data[1] / other.m_data[1], m_data[2] / other.m_data[2], m_data[3] / other.m_data[3]);
		}

		const Vector4 &Vector4::operator=(const Vector4 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
			m_data[3] = other.m_data[3];
			return *this;
		}

		const Vector4 &Vector4::operator+=(float scalar)
		{
			m_data[0] += scalar;
			m_data[1] += scalar;
			m_data[2] += scalar;
			m_data[3] += scalar;
			return *this;
		}

		const Vector4 &Vector4::operator-=(float scalar)
		{
			m_data[0] -= scalar;
			m_data[1] -= scalar;
			m_data[2] -= scalar;
			m_data[3] -= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator*=(float scalar)
		{
			m_data[0] *= scalar;
			m_data[1] *= scalar;
			m_data[2] *= scalar;
			m_data[3] *= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator/=(float scalar)
		{
			m_data[0] /= scalar;
			m_data[1] /= scalar;
			m_data[2] /= scalar;
			m_data[3] /= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator+=(const Vector4 &other)
		{
			m_data[0] += other.m_data[0];
			m_data[1] += other.m_data[1];
			m_data[2] += other.m_data[2];
			m_data[3] += other.m_data[3];
			return *this;
		}

		const Vector4 &Vector4::operator-=(const Vector4 &other)
		{
			m_data[0] -= other.m_data[0];
			m_data[1] -= other.m_data[1];
			m_data[2] -= other.m_data[2];
			m_data[3] -= other.m_data[3];
			return *this;
		}

		const Vector4 &Vector4::operator*=(const Vector4 &other)
		{
			m_data[0] *= other.m_data[0];
			m_data[1] *= other.m_data[1];
			m_data[2] *= other.m_data[2];
			m_data[3] *= other.m_data[3];
			return *this;
		}

		const Vector4 &Vector4::operator/=(const Vector4 &other)
		{
			m_data[0] /= other.m_data[0];
			m_data[1] /= other.m_data[1];
			m_data[2] /= other.m_data[2];
			m_data[3] /= other.m_data[3];
			return *this;
		}

		inline float dot(const Vector4 &a, const Vector4 &b)
		{
			return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
		}

		inline float length(const Vector4 &a)
		{
			return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]));
		}

		inline float distance(const Vector4 &a, const Vector4 &b)
		{
			return length(b - a);
		}

		inline Vector4 normalize(const Vector4 &a)
		{
			return a / length(a);
		}
	}
}

#endif