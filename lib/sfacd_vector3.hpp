#pragma once

#include <cmath>
#include <limits>

namespace cb
{
	/// 3D vector
	struct vector3
	{
		float x = 0.0f;	///< X component
		float y = 0.0f;	///< Y component
		float z = 0.0f;	///< Z component

		/// Calculate vector length squared
		///	@return						Length squared
		inline float length2() const;

		/// Calculate vector length
		///	@return						Length
		inline float length() const;

		/// Calculate vector dot product
		///	@param p_v					Vector to dot with
		///	@return						Dot product
		inline float dot(const vector3& p_v) const;

		/// Calculate vector cross product
		///	@param p_v					Vector to cross with
		///	@return						Cross product
		inline vector3 cross(const vector3& p_v) const;

		/// Calculate normalized vector
		///	@return						Normalized vector
		inline vector3 normalized() const;

		/// Check if vector is zero
		///	@return						True if zero
		inline bool is_zero_approx() const;

		/// Vector equality operator
		/// @param p_v					Vector to compare with
		///	@return						True if equal
		inline bool operator==(const vector3& p_v) const;

		/// Vector inequality operator
		///	@param p_v					Vector to compare with
		///	@return						True if not equal
		inline bool operator!=(const vector3& p_v) const;

		/// Vector less than operator
		///	@param p_v					Vector to compare with
		///	@return						True if less than
		inline bool operator<(const vector3& p_v) const;

		/// Vector greater than operator
		///	@param p_v					Vector to compare with
		///	@return						True if greater than
		inline bool operator>(const vector3& p_v) const;

		/// Vector less than or equal operator
		///	@param p_v					Vector to compare with
		///	@return						True if less than or equal
		inline bool operator<=(const vector3& p_v) const;

		/// Vector greater than or equal operator
		///	@param p_v					Vector to compare with
		///	@return						True if greater than or equal
		inline bool operator>=(const vector3& p_v) const;

		/// Vector negation operator
		///	@return						Negated vector
		inline vector3 operator-() const;

		/// Vector addition operator
		///	@param p_v					Vector to add
		///	@return						Vector sum
		inline vector3 operator+(const vector3& p_v) const;

		/// Vector subtraction operator
		///	@param p_v					Vector to subtract
		///	@return						Vector difference
		inline vector3 operator-(const vector3& p_v) const;

		/// Vector multiplication operator
		///	@param p_v					Vector to multiply
		///	@return						Vector product
		inline vector3 operator*(const vector3& p_v) const;

		/// Vector division operator
		///	@param p_v					Vector to divide
		///	@return						Vector quotient
		inline vector3 operator/(const vector3& p_v) const;

		/// Vector multiplication operator
		///	@param p_f					Scalar to multiply
		///	@return						Vector product
		inline vector3 operator*(float p_f) const;

		/// Vector division operator
		///	@param p_f					Scalar to divide
		///	@return						Vector quotient
		inline vector3 operator/(float p_f) const;

		/// Vector addition assignment operator
		///	@param p_v					Vector to add
		///	@return						Reference to self
		inline vector3& operator+=(const vector3& p_v);

		/// Vector subtraction assignment operator
		///	@param p_v					Vector to subtract
		///	@return						Reference to self
		inline vector3& operator-=(const vector3& p_v);

		/// Vector multiplication assignment operator
		///	@param p_v					Vector to multiply
		///	@return						Reference to self
		inline vector3& operator*=(const vector3& p_v);

		/// Vector division assignment operator
		///	@param p_v					Vector to divide
		///	@return						Reference to self
		inline vector3& operator/=(const vector3& p_v);

		/// Vector multiplication assignment operator
		///	@param p_f					Scalar to multiply
		///	@return						Reference to self
		inline vector3& operator*=(float p_f);

		/// Vector division assignment operator
		///	@param p_f					Scalar to divide
		///	@return						Reference to self
		inline vector3& operator/=(float p_f);
	};

	inline float vector3::length2() const
	{
		return x * x + y * y + z * z;
	}

	inline float vector3::length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	inline float vector3::dot(const vector3& p_v) const
	{
		return x * p_v.x + y * p_v.y + z * p_v.z;
	}

	inline vector3 vector3::cross(const vector3& p_v) const
	{
		return {
			y * p_v.z - z * p_v.y,
			z * p_v.x - x * p_v.z,
			x * p_v.y - y * p_v.x
		};
	}

	inline vector3 vector3::normalized() const
	{
		const float l = length();
		if (l == 0.0f) {
			return { 0.0f, 0.0f, 0.0f };
		}
		return { x / l, y / l, z / l };
	}

	inline bool vector3::is_zero_approx() const
	{
		return std::abs(x) < std::numeric_limits<float>::epsilon() &&
			std::abs(y) < std::numeric_limits<float>::epsilon() &&
			std::abs(z) < std::numeric_limits<float>::epsilon();
	}

	inline bool vector3::operator==(const vector3& p_v) const
	{
		return x == p_v.x && y == p_v.y && z == p_v.z;
	}

	inline bool vector3::operator!=(const vector3& p_v) const
	{
		return x != p_v.x || y != p_v.y || z != p_v.z;
	}

	inline bool vector3::operator<(const vector3& p_v) const
	{
		if (x == p_v.x) {
			if (y == p_v.y) {
				return z < p_v.z;
			}
			return y < p_v.y;
		}
		return x < p_v.x;
	}

	inline bool vector3::operator>(const vector3& p_v) const
	{
		if (x == p_v.x) {
			if (y == p_v.y) {
				return z > p_v.z;
			}
			return y > p_v.y;
		}
		return x > p_v.x;
	}

	inline bool vector3::operator<=(const vector3& p_v) const
	{
		if (x == p_v.x) {
			if (y == p_v.y) {
				return z <= p_v.z;
			}
			return y < p_v.y;
		}
		return x < p_v.x;
	}

	inline bool vector3::operator>=(const vector3& p_v) const
	{
		if (x == p_v.x) {
			if (y == p_v.y) {
				return z >= p_v.z;
			}
			return y > p_v.y;
		}
		return x > p_v.x;
	}

	inline vector3 vector3::operator-() const
	{
		return { -x, -y, -z };
	}

	inline vector3 vector3::operator+(const vector3& p_v) const
	{
		return { x + p_v.x, y + p_v.y, z + p_v.z };
	}

	inline vector3 vector3::operator-(const vector3& p_v) const
	{
		return { x - p_v.x, y - p_v.y, z - p_v.z };
	}

	inline vector3 vector3::operator*(const vector3& p_v) const
	{
		return { x * p_v.x, y * p_v.y, z * p_v.z };
	}

	inline vector3 vector3::operator/(const vector3& p_v) const
	{
		return { x / p_v.x, y / p_v.y, z / p_v.z };
	}

	inline vector3 vector3::operator*(const float p_f) const
	{
		return { x * p_f, y * p_f, z * p_f };
	}

	inline vector3 vector3::operator/(const float p_f) const
	{
		return { x / p_f, y / p_f, z / p_f };
	}

	inline vector3& vector3::operator+=(const vector3& p_v)
	{
		x += p_v.x;
		y += p_v.y;
		z += p_v.z;
		return *this;
	}

	inline vector3& vector3::operator-=(const vector3& p_v)
	{
		x -= p_v.x;
		y -= p_v.y;
		z -= p_v.z;
		return *this;
	}

	inline vector3& vector3::operator*=(const vector3& p_v)
	{
		x *= p_v.x;
		y *= p_v.y;
		z *= p_v.z;
		return *this;
	}

	inline vector3& vector3::operator/=(const vector3& p_v)
	{
		x /= p_v.x;
		y /= p_v.y;
		z /= p_v.z;
		return *this;
	}

	inline vector3& vector3::operator*=(const float p_f)
	{
		x *= p_f;
		y *= p_f;
		z *= p_f;
		return *this;
	}

	inline vector3& vector3::operator/=(const float p_f)
	{
		x /= p_f;
		y /= p_f;
		z /= p_f;
		return *this;
	}
}
