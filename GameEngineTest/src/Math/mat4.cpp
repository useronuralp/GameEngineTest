#include "pch.h"
#include "mat4.h"

namespace GameEngineTest {
	namespace Math {


		mat4::mat4()
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}
		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity()
		{
			
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other) {
			
			float data[16];

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{	
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}

			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		mat4 operator * (mat4 left, const mat4& right)
		{

			return left.multiply(right);
		}
		mat4& mat4::operator *= (const mat4& other)
		{
			return multiply(other);
		}

		vec4 mat4::multiply(const vec4& other) const
		{
			return vec4
			{
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			};
		}
		vec4 operator * (mat4& left, const vec4& right)
		{
			return left.multiply(right);
		}


		vec3 mat4::multiply(const vec3& other) const
		{
			return vec3
			{
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z 			
			};
		}
		vec3 operator * (mat4& left, const vec3& right)
		{
			return left.multiply(right);
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom); // check this later there could be problems
			result.elements[2 + 2 * 4] = 2 / (nearPlane - farPlane); //with ordering
			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (farPlane + nearPlane) / (farPlane - nearPlane);
			
			return result;
		}
		mat4 mat4::perspective(float fov, float aspectRatio, float nearPlane, float farPlane)
		{	
			mat4 result = result.identity();

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (nearPlane + farPlane) / (nearPlane - farPlane);
			float c = (2.0f * nearPlane * farPlane / (nearPlane - farPlane));

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 0 * 4] = c;

			return result;
		}


		mat4 mat4::translation(const vec3& translation)
		{
			mat4 result = result.identity();

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;
			
			return result;
		}
		mat4 mat4::scale(const vec3& scale)
		{
			mat4 result = result.identity();

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}
		mat4 mat4::rotation(float angle, const vec3& axis)
		{
			mat4 result = result.identity();

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;
			
			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc - y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		}
	}
}