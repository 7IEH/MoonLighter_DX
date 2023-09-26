#pragma once

namespace EH::Math
{
	struct Vector2
	{
		float x;
		float y;

		Vector2 operator-(Vector2 other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}
	};

	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3 operator+(Vector3 other)
		{
			Vector3 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			temp.z = z + other.z;
			return temp;
		}

		Vector3 operator-(Vector3 other)
		{
			Vector3 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			temp.z = z - other.z;
			return temp;
		}

		Vector3 operator/(float num)
		{
			Vector3 temp;
			temp.x = x / num;
			temp.y = y / num;
			temp.z = z / num;
			return temp;
		}

		Vector3 operator*(float num)
		{
			Vector3 temp;
			temp.x = x * num;
			temp.y = y * num;
			temp.z = z * num;
			return temp;
		}

		Vector3& operator+=(Vector3 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& operator-=(Vector3 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& Normalized()
		{
			x /= sqrt(x * x + y * y + z * z);
			y /= sqrt(x * x + y * y + z * z);
			z /= sqrt(x * x + y * y + z * z);
			return *this;
		}

		float Length()
		{
			return sqrt(x * x + y * y + z * z);
		}

		bool operator==(Vector3 other)
		{
			return ((x == other.x) && (y == other.y) && (z == other.z));
		}

		Vector3 operator-()
		{
			Vector3 temp;
			temp.x = x * -1;
			temp.y = y * -1;
			temp.z = z * -1;
			return temp;
		}
	};

	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;
	};

	inline float Dot(Vector3& vec1, Vector3& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y +vec1.z * vec2.z;
	}
}

