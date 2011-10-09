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
			Vector4(float *data);
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
		public:
			float x, y, z, w;
		};

		inline Vector4::Vector4()
		{

		}

		inline Vector4::Vector4(float s) : x(s), y(s), z(s), w(s)
		{

		}

		inline Vector4::Vector4(float *data) : x(data[0]), y(data[1]), z(data[2]), w(data[3])
		{

		}

		inline Vector4::Vector4(float nX, float nY, float nZ, float nW) : x(nX), y(nY), z(nZ), w(nW)
		{

		}

		inline Vector4::Vector4(const Vector4 &other) : x(other.x), y(other.y), z(other.z), w(other.w)
		{

		}

		inline float &Vector4::operator[](int index)
		{
			return (&x)[index];
		}

		inline const float &Vector4::operator[](int index) const
		{
			return (&x)[index];
		}

		bool Vector4::operator==(const Vector4 &other) const
		{
			return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
		}

		bool Vector4::operator!=(const Vector4 &other) const
		{
			return ((x != other.x) || (y != other.y) || (z != other.z) || (w != other.w));
		}

		Vector4 Vector4::operator+() const
		{
			return Vector4(+x, +y, +z, +w);
		}

		Vector4 Vector4::operator-() const
		{
			return Vector4(-x, -y, -z, -w);
		}

		Vector4 Vector4::operator+(float scalar) const
		{
			return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
		}

		Vector4 Vector4::operator-(float scalar) const
		{
			return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
		}

		Vector4 Vector4::operator*(float scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		Vector4 Vector4::operator/(float scalar) const
		{
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		Vector4 Vector4::operator+(const Vector4 &other) const
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		Vector4 Vector4::operator-(const Vector4 &other) const
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		Vector4 Vector4::operator*(const Vector4 &other) const
		{
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		Vector4 Vector4::operator/(const Vector4 &other) const
		{
			return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		const Vector4 &Vector4::operator=(const Vector4 &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
			return *this;
		}

		const Vector4 &Vector4::operator+=(float scalar)
		{
			x += scalar;
			y += scalar;
			z += scalar;
			w += scalar;
			return *this;
		}

		const Vector4 &Vector4::operator-=(float scalar)
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;
			w -= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		const Vector4 &Vector4::operator+=(const Vector4 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		const Vector4 &Vector4::operator-=(const Vector4 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		const Vector4 &Vector4::operator*=(const Vector4 &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		const Vector4 &Vector4::operator/=(const Vector4 &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		inline float dot(const Vector4 &a, const Vector4 &b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}

		inline float length(const Vector4 &a)
		{
			return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w));
		}

		inline float distance(const Vector4 &a, const Vector4 &b)
		{
			return length(b - a);
		}

		inline Vector4 normalize(const Vector4 &a)
		{
			float square = (a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w);
			return a * (1.0f / sqrtf(square));
		}
	}
}

#endif