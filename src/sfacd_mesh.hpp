#pragma once

#include "sfacd_math.hpp"
#include <vector>

namespace sfacd
{
	/// Mesh error
	enum class mesh_error
	{
		success,		///< No error
		file_not_found,	///< File not found
		empty,			///< Empty mesh
		degenerate_face,///< Degenerate face
	};

	/// Mesh structure
	struct mesh
	{
		/// Mesh face
		struct face
		{
			int v0;		///< First vertex index
			int v1;		///< Second vertex index
			int v2;		///< Third vertex index
		};

		/// Vector of vertices
		std::vector<vector3> vertices;

		/// Vector of faces
		std::vector<face> faces;

		/// Load mesh from OBJ file
		///	@param p_path				Path to OBJ file
		///	@return						Mesh error
		mesh_error load_obj(const char* p_path);

		/// Save mesh to OBJ file
		///	@param p_path				Path to OBJ file
		///	@return						True if successful
		bool save_obj(const char* p_path) const;

		/// Check if mesh is closed
		///	@return						True if closed
		bool is_closed() const;

		/// Check if mesh is convex
		///	@return						True if convex
		bool is_convex() const;

		/// Check if mesh is multiple separate meshes
		///	@return						True if multiple
		bool is_multiple() const;
	};
}