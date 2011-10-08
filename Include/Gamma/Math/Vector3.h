#ifndef GAMMA_MATH_VECTOR3_H
#define GAMMA_MATH_VECTOR3_H

#include <cmath>

namespace Gamma
{
	namespace Math
	{
		class Vector3
		{
		public:
			Vector3();
			Vector3(float s);
			Vector3(float x, float y, float z);
			Vector3(const Vector3 &other);

			float &operator[](int index);
			const float &operator[](int index) const;

			bool operator==(const Vector3 &other) const;
			bool operator!=(const Vector3 &other) const;

			Vector3 operator+() const;
			Vector3 operator-() const;

			Vector3 operator+(float scalar) const;
			Vector3 operator-(float scalar) const;
			Vector3 operator*(float scalar) const;
			Vector3 operator/(float scalar) const;
			Vector3 operator+(const Vector3 &other) const;
			Vector3 operator-(const Vector3 &other) const;
			Vector3 operator*(const Vector3 &other) const;
			Vector3 operator/(const Vector3 &other) const;

			const Vector3 &operator=(const Vector3 &other);
			const Vector3 &operator+=(float scalar);
			const Vector3 &operator-=(float scalar);
			const Vector3 &operator*=(float scalar);
			const Vector3 &operator/=(float scalar);
			const Vector3 &operator+=(const Vector3 &other);
			const Vector3 &operator-=(const Vector3 &other);
			const Vector3 &operator*=(const Vector3 &other);
			const Vector3 &operator/=(const Vector3 &other);
		private:
			float m_data[3];
		};

		inline Vector3::Vector3()
		{

		}

		inline Vector3::Vector3(float s)
		{
			m_data[0] = s;
			m_data[1] = s;
			m_data[2] = s;
		}

		inline Vector3::Vector3(float x, float y, float z)
		{
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
		}

		inline Vector3::Vector3(const Vector3 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
		}

		inline float &Vector3::operator[](int index)
		{
			return m_data[index];
		}

		inline const float &Vector3::operator[](int index) const
		{
			return m_data[index];
		}

		bool Vector3::operator==(const Vector3 &other) const
		{
			return ((m_data[0] == other.m_data[0]) && (m_data[1] == other.m_data[1]) && (m_data[2] == other.m_data[2]));
		}

		bool Vector3::operator!=(const Vector3 &other) const
		{
			return ((m_data[0] != other.m_data[0]) || (m_data[1] != other.m_data[1]) || (m_data[2] != other.m_data[2]));
		}

		Vector3 Vector3::operator+() const
		{
			return Vector3(+m_data[0], +m_data[1], +m_data[2]);
		}

		Vector3 Vector3::operator-() const
		{
			return Vector3(-m_data[0], -m_data[1], -m_data[2]);
		}

		Vector3 Vector3::operator+(float scalar) const
		{
			return Vector3(m_data[0] + scalar, m_data[1] + scalar, m_data[2] + scalar);
		}

		Vector3 Vector3::operator-(float scalar) const
		{
			return Vector3(m_data[0] - scalar, m_data[1] - scalar, m_data[2] - scalar);
		}

		Vector3 Vector3::operator*(float scalar) const
		{
			return Vector3(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar);
		}

		Vector3 Vector3::operator/(float scalar) const
		{
			return Vector3(m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar);
		}

		Vector3 Vector3::operator+(const Vector3 &other) const
		{
			return Vector3(m_data[0] + other.m_data[0], m_data[1] + other.m_data[1], m_data[2] + other.m_data[2]);
		}

		Vector3 Vector3::operator-(const Vector3 &other) const
		{
			return Vector3(m_data[0] - other.m_data[0], m_data[1] - other.m_data[1], m_data[2] - other.m_data[2]);
		}

		Vector3 Vector3::operator*(const Vector3 &other) const
		{
			return Vector3(m_data[0] * other.m_data[0], m_data[1] * other.m_data[1], m_data[2] * other.m_data[2]);
		}

		Vector3 Vector3::operator/(const Vector3 &other) const
		{
			return Vector3(m_data[0] / other.m_data[0], m_data[1] / other.m_data[1], m_data[2] / other.m_data[2]);
		}

		const Vector3 &Vector3::operator=(const Vector3 &other)
		{
			m_data[0] = other.m_data[0];
			m_data[1] = other.m_data[1];
			m_data[2] = other.m_data[2];
			return *this;
		}

		const Vector3 &Vector3::operator+=(float scalar)
		{
			m_data[0] += scalar;
			m_data[1] += scalar;
			m_data[2] += scalar;
			return *this;
		}

		const Vector3 &Vector3::operator-=(float scalar)
		{
			m_data[0] -= scalar;
			m_data[1] -= scalar;
			m_data[2] -= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator*=(float scalar)
		{
			m_data[0] *= scalar;
			m_data[1] *= scalar;
			m_data[2] *= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator/=(float scalar)
		{
			m_data[0] /= scalar;
			m_data[1] /= scalar;
			m_data[2] /= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator+=(const Vector3 &other)
		{
			m_data[0] += other.m_data[0];
			m_data[1] += other.m_data[1];
			m_data[2] += other.m_data[2];
			return *this;
		}

		const Vector3 &Vector3::operator-=(const Vector3 &other)
		{
			m_data[0] -= other.m_data[0];
			m_data[1] -= other.m_data[1];
			m_data[2] -= other.m_data[2];
			return *this;
		}

		const Vector3 &Vector3::operator*=(const Vector3 &other)
		{
			m_data[0] *= other.m_data[0];
			m_data[1] *= other.m_data[1];
			m_data[2] *= other.m_data[2];
			return *this;
		}

		const Vector3 &Vector3::operator/=(const Vector3 &other)
		{
			m_data[0] /= other.m_data[0];
			m_data[1] /= other.m_data[1];
			m_data[2] /= other.m_data[2];
			return *this;
		}

		inline float dot(const Vector3 &a, const Vector3 &b)
		{
			return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
		}

		inline float length(const Vector3 &a)
		{
			return sqrtf((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
		}

		inline float distance(const Vector3 &a, const Vector3 &b)
		{
			return length(b - a);
		}

		inline Vector3 normalize(const Vector3 &a)
		{
			return a / length(a);
		}

		inline Vector3 cross(const Vector3 &a, const Vector3 &b)
		{
			return Vector3(a[1] * b[2] - b[1] * a[2], a[2] * b[0] - b[2] * a[0], a[0] * b[1] - b[0] * a[1]);
		}
	}
}

#endif