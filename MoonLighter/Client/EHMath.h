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

		Vector3 operator-(Vector3 other)
		{
			Vector3 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			temp.z = z - other.z;
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
}

