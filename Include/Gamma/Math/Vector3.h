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
			Vector3(float *data);
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
		public:
			float x, y, z;
		};

		inline Vector3::Vector3()
		{

		}

		inline Vector3::Vector3(float s) : x(s), y(s), z(s)
		{

		}

		inline Vector3::Vector3(float *data) : x(data[0]), y(data[1]), z(data[2])
		{

		}

		inline Vector3::Vector3(float nX, float nY, float nZ) : x(nX), y(nY), z(nZ)
		{

		}

		inline Vector3::Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z)
		{

		}

		inline float &Vector3::operator[](int index)
		{
			return (&x)[index];
		}

		inline const float &Vector3::operator[](int index) const
		{
			return (&x)[index];
		}

		bool Vector3::operator==(const Vector3 &other) const
		{
			return ((x == other.x) && (y == other.y) && (z == other.z));
		}

		bool Vector3::operator!=(const Vector3 &other) const
		{
			return ((x != other.x) || (y != other.y) || (z != other.z));
		}

		Vector3 Vector3::operator+() const
		{
			return Vector3(+x, +y, +z);
		}

		Vector3 Vector3::operator-() const
		{
			return Vector3(-x, -y, -z);
		}

		Vector3 Vector3::operator+(float scalar) const
		{
			return Vector3(x + scalar, y + scalar, z + scalar);
		}

		Vector3 Vector3::operator-(float scalar) const
		{
			return Vector3(x - scalar, y - scalar, z - scalar);
		}

		Vector3 Vector3::operator*(float scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3 Vector3::operator/(float scalar) const
		{
			return Vector3(x / scalar, y / scalar, z / scalar);
		}

		Vector3 Vector3::operator+(const Vector3 &other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 Vector3::operator-(const Vector3 &other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 Vector3::operator*(const Vector3 &other) const
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		Vector3 Vector3::operator/(const Vector3 &other) const
		{
			return Vector3(x / other.x, y / other.y, z / other.z);
		}

		const Vector3 &Vector3::operator=(const Vector3 &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		const Vector3 &Vector3::operator+=(float scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;
			return *this;
		}

		const Vector3 &Vector3::operator-=(float scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		const Vector3 &Vector3::operator+=(const Vector3 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		const Vector3 &Vector3::operator-=(const Vector3 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		const Vector3 &Vector3::operator*=(const Vector3 &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		const Vector3 &Vector3::operator/=(const Vector3 &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		inline float dot(const Vector3 &a, const Vector3 &b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		inline float length(const Vector3 &a)
		{
			return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
		}

		inline float distance(const Vector3 &a, const Vector3 &b)
		{
			return length(b - a);
		}

		inline Vector3 normalize(const Vector3 &a)
		{
			float square = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
			return a * (1.0f / sqrtf(square));
		}

		inline Vector3 cross(const Vector3 &a, const Vector3 &b)
		{
			return Vector3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
		}
	}
}

#endif