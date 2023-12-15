#include "sfacd_math.hpp"

namespace sfacd
{
	inline bool plane3::intersect_ray(const vector3& p_origin, const vector3& p_direction, vector3* p_point) const
	{
		// Calculate the denominator
		const float den = normal.dot(p_direction);
		if (is_zero_approx(den)) {
			return false;
		}

		// Calculate the distance along the ray to the intersection point
		const float dist = (distance - normal.dot(p_origin)) / den;
		if (dist < std::numeric_limits<float>::epsilon()) {
			return false;
		}

		// Save the optional intersection point
		if (p_point) {
			*p_point = p_origin + p_direction * dist;
		}

		return true;
	}

	inline bool plane3::intersect_segment(const vector3& p_point1, const vector3& p_point2, vector3* p_point) const
	{
		// Calculate the distance from the segment points to the plane
		const float dist1 = distance_to(p_point1);
		const float dist2 = distance_to(p_point2);

		// If the points are on the same side of the plane then there is no intersection
		if (get_sign(dist1) == get_sign(dist2)) {
			return false;
		}

		// Save the optional the intersection point
		if (p_point) {
			const float t = dist1 / (dist1 - dist2);
			*p_point = p_point1 + (p_point2 - p_point1) * t;
		}

		return true;
	}

	int face3::slice(const plane3& plane, face3* faces) const
	{
		// If the face is degenerate then the slice is empty
		if (is_degenerate())
			return 0;

		// Points above or on the plane (4 for quadrilateral)
		vector3 above[4];
		int above_count = 0;

		// Points below or on the plane (4 for quadrilateral)
		vector3 below[4];
		int below_count = 0;

		// Process all vertices and edges
		for (int i = 0; i < 3; ++i) {
			// Calculate the distance from the point to the plane
			const float vertex_dist = plane.distance_to(vertex[i]);
			const int vertex_sign = get_sign(vertex_dist);

			// If the point is on the plane then add it to both lists
			if (vertex_sign == 0) {
				above[above_count++] = vertex[i];
				below[below_count++] = vertex[i];
				continue;
			}

			// Add the point to the above or below list
			if (vertex_sign > 0) {
				above[above_count++] = vertex[i];
			} else {
				below[below_count++] = vertex[i];
			}

			// Check for intersection with the next edge
			const int i2 = (i + 1) % 3;
			const float next_dist = plane.distance_to(vertex[i2]);
			const int next_sign = get_sign(next_dist);
			if (vertex_sign != next_sign)
			{
				// Calculate the intersection point
				const float t = vertex_dist / (vertex_dist - next_dist);
				const vector3 point = vertex[i] + (vertex[i2] - vertex[i]) * t;

				// Add the intersection point to both lists
				above[above_count++] = point;
				below[below_count++] = point;
			}
		}

		// Construct the face/quadrilateral above the plane
		int face_count = 0;
		if (above_count >= 3) {
			// Construct the above face
			faces[face_count++] = face3{ above[0], above[1], above[2] };

			// Construct the above face (quadrilateral)
			if (above_count == 4) {
				faces[face_count++] = face3{ above[2], above[3], above[0] };
			}
		}

		// Construct the face/quadrilateral below the plane
		if (below_count >= 3) {
			// Construct the above face
			faces[face_count++] = face3{ below[0], below[1], below[2] };

			// Construct the above face (quadrilateral)
			if (below_count == 4) {
				faces[face_count++] = face3{ below[2], below[3], below[0] };
			}
		}

		// Return the count of faces
		return face_count;
	}
}