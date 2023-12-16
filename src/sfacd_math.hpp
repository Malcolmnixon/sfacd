#pragma once

#include <cmath>
#include <limits>


namespace sfacd
{
    /// Test if a float is approximately zero
    /// @param p_value              Value to test
    /// @return                     True if zero
    bool is_zero_approx(float p_value);

    /// Test if two floats are approximately equal
    /// @param p_value1             First value to test
    /// @param p_value2             Second value to test
    /// @return                     True if equal
    bool is_equal_approx(float p_value1, float p_value2);

    /// Get sign of a float
    /// @param p_value              Value to get sign of
    /// @return                     -1 if negative, 0 if zero, 1 if positive
    int get_sign(float p_value);

    /// Linear interpolation
    /// @param p_value1             First value
    /// @param p_value2             Second value
    /// @param p_t                  Interpolation factor
    /// @return                     Interpolated value
    float lerp(float p_value1, float p_value2, float p_t);

    /// 3D vector
    struct vector3
    {
        float x; ///< X component
        float y; ///< Y component
        float z; ///< Z component

        /// Constructor
        /// @param p_x                  X component
        /// @param p_y                  Y component
        /// @param p_z                  Z component
        explicit vector3(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f);

        /// Calculate vector length squared
        /// @return                     Length squared
        inline float length2() const;

        /// Calculate vector length
        /// @return                     Length
        inline float length() const;

        /// Calculate vector dot product
        /// @param p_v                  Vector to dot with
        /// @return                     Dot product
        inline float dot(const vector3& p_v) const;

        /// Calculate vector cross product
        /// @param p_v                  Vector to cross with
        /// @return                     Cross product
        inline vector3 cross(const vector3& p_v) const;

        /// Calculate normalized vector
        /// @return                     Normalized vector
        inline vector3 normalized() const;

        /// Calculate linear interpolation
        /// @param p_v                  Vector to lerp to
        /// @param p_t                  Interpolation factor
        /// @return                     Interpolated vector
        inline vector3 lerp(const vector3& p_v, float p_t) const;

        /// Check if vector is zero
        /// @return                     True if zero
        inline bool is_zero_approx() const;

        /// Check if vector is approximately equal to another vector
        /// @param p_v                  Vector to compare with
        /// @return                     True if equal
        inline bool is_equal_approx(const vector3& p_v) const;

        /// Vector equality operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if equal
        inline bool operator==(const vector3& p_v) const;

        /// Vector inequality operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if not equal
        inline bool operator!=(const vector3& p_v) const;

        /// Vector less than operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if less than
        inline bool operator<(const vector3& p_v) const;

        /// Vector greater than operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if greater than
        inline bool operator>(const vector3& p_v) const;

        /// Vector less than or equal operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if less than or equal
        inline bool operator<=(const vector3& p_v) const;

        /// Vector greater than or equal operator
        /// @param p_v                  Vector to compare with
        /// @return                     True if greater than or equal
        inline bool operator>=(const vector3& p_v) const;

        /// Vector negation operator
        /// @return                     Negated vector
        inline vector3 operator-() const;

        /// Vector addition operator
        /// @param p_v                  Vector to add
        /// @return                     Vector sum
        inline vector3 operator+(const vector3& p_v) const;

        /// Vector subtraction operator
        /// @param p_v                  Vector to subtract
        /// @return                     Vector difference
        inline vector3 operator-(const vector3& p_v) const;

        /// Vector multiplication operator
        /// @param p_v                  Vector to multiply
        /// @return                     Vector product
        inline vector3 operator*(const vector3& p_v) const;

        /// Vector division operator
        /// @param p_v                  Vector to divide
        /// @return                     Vector quotient
        inline vector3 operator/(const vector3& p_v) const;

        /// Vector multiplication operator
        /// @param p_f                  Scalar to multiply
        /// @return                     Vector product
        inline vector3 operator*(float p_f) const;

        /// Vector division operator
        /// @param p_f                  Scalar to divide
        /// @return                     Vector quotient
        inline vector3 operator/(float p_f) const;

        /// Vector addition assignment operator
        /// @param p_v                  Vector to add
        /// @return                     Reference to self
        inline vector3& operator+=(const vector3& p_v);

        /// Vector subtraction assignment operator
        /// @param p_v                  Vector to subtract
        /// @return                     Reference to self
        inline vector3& operator-=(const vector3& p_v);

        /// Vector multiplication assignment operator
        /// @param p_v                  Vector to multiply
        /// @return                     Reference to self
        inline vector3& operator*=(const vector3& p_v);

        /// Vector division assignment operator
        /// @param p_v                  Vector to divide
        /// @return                     Reference to self
        inline vector3& operator/=(const vector3& p_v);

        /// Vector multiplication assignment operator
        /// @param p_f                  Scalar to multiply
        /// @return                     Reference to self
        inline vector3& operator*=(float p_f);

        /// Vector division assignment operator
        /// @param p_f                  Scalar to divide
        /// @return                     Reference to self
        inline vector3& operator/=(float p_f);
    };

    /// 3D Plane
    struct plane3
    {
        /// Plane normal vector
        vector3 normal;

        /// Plane distance from origin
        float distance = 0.0f;

        /// Default constructor
        plane3() = default;

        /// Construct a plane from a normal and a distance from origin
        /// @param p_normal             Plane normal vector
        /// @param p_distance           Plane distance from origin
        explicit plane3(const vector3& p_normal, float p_distance);

        /// Construct a plane from a normal and a point on the plane
        /// @param p_normal             Plane normal vector
        /// @param p_point              Point on the plane
        explicit plane3(const vector3& p_normal, const vector3& p_point);

        /// Construct a plane from three points
        /// @param p_point1             First point
        /// @param p_point2             Second point
        /// @param p_point3             Third point
        explicit plane3(const vector3& p_point1, const vector3& p_point2, const vector3& p_point3);

        /// Check if plane is approximately equal to another plane
        /// @param p_p                  Plane to compare with
        /// @return                     True if equal
        bool is_equal_approx(const plane3& p_p) const;

        /// Calculate distance from plane to point
        /// @param p_point              Point to calculate distance to
        /// @return                     Distance to point
        float distance_to(const vector3& p_point) const;

        /// Calculate which side of the plane a point is on
        /// @param p_point              Point to test
        /// @return                     -1 if behind, 0 if on, 1 if in front
        int side(const vector3& p_point) const;

        /// Project a point onto the plane
        /// @param p_point              Point to project
        /// @return                     Projected point
        vector3 project(const vector3& p_point) const;

        /// Intersect ray with plane
        /// @param p_origin             Ray origin
        /// @param p_direction          Ray direction
        /// @param p_point              Intersection point
        /// @return                     True if intersection
        bool intersect_ray(const vector3& p_origin, const vector3& p_direction, vector3* p_point) const;

        /// Intersect segment with plane
        /// @param p_point1             Segment start point
        /// @param p_point2             Segment end point
        /// @param p_point              Intersection point
        /// @return                     True if intersection
        bool intersect_segment(const vector3& p_point1, const vector3& p_point2, vector3* p_point) const;

        /// Plane equality operator
        /// @param p_p                  Plane to compare with
        /// @return                     True if equal
        bool operator==(const plane3& p_p) const;

        /// Plane inequality operator
        /// @param p_p                  Plane to compare with
        /// @return                     True if not equal
        bool operator!=(const plane3& p_p) const;
    };

    /// 3D Face
    struct face3
    {
        /// Vector of vertices
        vector3 vertex[3];

        /// Default constructor
        face3() = default;

        /// Construct a face from three vertices
        /// @param p_vertex1            First vertex
        /// @param p_vertex2            Second vertex
        /// @param p_vertex3            Third vertex
        face3(const vector3& p_vertex1, const vector3& p_vertex2, const vector3& p_vertex3);

        /// Check if face is degenerate
        /// @return                     True if degenerate
        bool is_degenerate() const;

        /// Calculate face plane
        /// @return                     Face plane
        plane3 plane() const;

        /// Slice face with plane
        /// @param p_plane              Plane to slice with
        /// @param p_above_faces        Faces above plane
        /// @param p_above_count        Number of faces above plane
        /// @param p_below_faces        Faces below plane
        /// @param p_below_count        Number of faces below plane
        void slice(const plane3& p_plane, face3* p_above_faces, int& p_above_count, face3* p_below_faces,
                   int& p_below_count) const;
    };

    inline bool is_zero_approx(const float p_value)
    {
        return std::abs(p_value) < std::numeric_limits<float>::epsilon();
    }

    inline bool is_equal_approx(const float p_value1, const float p_value2)
    {
        // Handle exact equality and infinity
        if (p_value1 == p_value2)
        {
            return true;
        }

        // Calculate comparison tolerance
        float tolerance = std::numeric_limits<float>::epsilon() * std::abs(p_value1);
        if (tolerance < std::numeric_limits<float>::min())
        {
            tolerance = std::numeric_limits<float>::min();
        }

        // Test if difference is within tolerance
        return std::abs(p_value1 - p_value2) < tolerance;
    }

    inline int get_sign(const float p_value)
    {
        if (p_value < -std::numeric_limits<float>::epsilon())
        {
            return -1;
        }
        if (p_value > std::numeric_limits<float>::epsilon())
        {
            return 1;
        }
        return 0;
    }

    inline float lerp(const float p_value1, const float p_value2, const float p_t)
    {
        return p_value1 + (p_value2 - p_value1) * p_t;
    }

    inline vector3::vector3(const float p_x, const float p_y, const float p_z)
        : x(p_x), y(p_y), z(p_z)
    {
    }

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
        return vector3{
            y * p_v.z - z * p_v.y,
            z * p_v.x - x * p_v.z,
            x * p_v.y - y * p_v.x
        };
    }

    inline vector3 vector3::normalized() const
    {
        const float l = length();
        if (l == 0.0f)
        {
            return vector3{0.0f, 0.0f, 0.0f};
        }
        return vector3{x / l, y / l, z / l};
    }

    inline vector3 vector3::lerp(const vector3& p_v, const float p_t) const
    {
        return vector3{
           sfacd::lerp(x, p_v.x, p_t),
           sfacd::lerp(y, p_v.y, p_t),
           sfacd::lerp(z, p_v.z, p_t)
        };
    }


    inline bool vector3::is_zero_approx() const
    {
        return sfacd::is_zero_approx(x) &&
            sfacd::is_zero_approx(y) &&
            sfacd::is_zero_approx(z);
    }

    inline bool vector3::is_equal_approx(const vector3& p_v) const
    {
        return sfacd::is_equal_approx(x, p_v.x) &&
            sfacd::is_equal_approx(y, p_v.y) &&
            sfacd::is_equal_approx(z, p_v.z);
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
        if (x == p_v.x)
        {
            if (y == p_v.y)
            {
                return z < p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }

    inline bool vector3::operator>(const vector3& p_v) const
    {
        if (x == p_v.x)
        {
            if (y == p_v.y)
            {
                return z > p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }

    inline bool vector3::operator<=(const vector3& p_v) const
    {
        if (x == p_v.x)
        {
            if (y == p_v.y)
            {
                return z <= p_v.z;
            }
            return y < p_v.y;
        }
        return x < p_v.x;
    }

    inline bool vector3::operator>=(const vector3& p_v) const
    {
        if (x == p_v.x)
        {
            if (y == p_v.y)
            {
                return z >= p_v.z;
            }
            return y > p_v.y;
        }
        return x > p_v.x;
    }

    inline vector3 vector3::operator-() const
    {
        return vector3{-x, -y, -z};
    }

    inline vector3 vector3::operator+(const vector3& p_v) const
    {
        return vector3{x + p_v.x, y + p_v.y, z + p_v.z};
    }

    inline vector3 vector3::operator-(const vector3& p_v) const
    {
        return vector3{x - p_v.x, y - p_v.y, z - p_v.z};
    }

    inline vector3 vector3::operator*(const vector3& p_v) const
    {
        return vector3{x * p_v.x, y * p_v.y, z * p_v.z};
    }

    inline vector3 vector3::operator/(const vector3& p_v) const
    {
        return vector3{x / p_v.x, y / p_v.y, z / p_v.z};
    }

    inline vector3 vector3::operator*(const float p_f) const
    {
        return vector3{x * p_f, y * p_f, z * p_f};
    }

    inline vector3 vector3::operator/(const float p_f) const
    {
        return vector3{x / p_f, y / p_f, z / p_f};
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

    inline plane3::plane3(const vector3& p_normal, const float p_distance)
        : normal(p_normal)
          , distance(p_distance)
    {
    }

    inline plane3::plane3(const vector3& p_normal, const vector3& p_point)
        : normal(p_normal)
          , distance(p_normal.dot(p_point))
    {
    }

    inline plane3::plane3(const vector3& p_point1, const vector3& p_point2, const vector3& p_point3)
    {
        normal = (p_point2 - p_point1).cross(p_point3 - p_point1).normalized();
        distance = normal.dot(p_point1);
    }

    inline bool plane3::is_equal_approx(const plane3& p_p) const
    {
        return normal.is_equal_approx(p_p.normal) &&
            sfacd::is_equal_approx(distance, p_p.distance);
    }

    inline float plane3::distance_to(const vector3& p_point) const
    {
        return normal.dot(p_point) - distance;
    }

    inline int plane3::side(const vector3& p_point) const
    {
        return get_sign(distance_to(p_point));
    }

    inline vector3 plane3::project(const vector3& p_point) const
    {
        return p_point - normal * distance_to(p_point);
    }

    inline bool plane3::operator==(const plane3& p_p) const
    {
        return normal == p_p.normal && distance == p_p.distance;
    }

    inline bool plane3::operator!=(const plane3& p_p) const
    {
        return normal != p_p.normal || distance != p_p.distance;
    }

    inline face3::face3(const vector3& p_vertex1, const vector3& p_vertex2, const vector3& p_vertex3)
    {
        vertex[0] = p_vertex1;
        vertex[1] = p_vertex2;
        vertex[2] = p_vertex3;
    }

    inline bool face3::is_degenerate() const
    {
        const auto normal = (vertex[1] - vertex[0]).cross(vertex[2] - vertex[0]);
        return is_zero_approx(normal.length2());
    }

    inline plane3 face3::plane() const
    {
        return plane3(vertex[0], vertex[1], vertex[2]);
    }
}
