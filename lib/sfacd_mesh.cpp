#include "cb_mesh.hpp"
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <cstdint>
#include <set>

namespace
{
	/// Regular expression for matching OBJ vertex lines
	const std::regex obj_vertex_regex(R"(^v\s+([-\d\.]+)\s+([-\d\.]+)\s+([-\d\.]+)$)");

	/// Regular expression for matching OBJ vertex texture lines
	const std::regex obj_face_vertex_regex(R"(^f\s+([\d]+)\s+([\d]+)\s+([\d]+)$)");

	/// Regular expression for matching OBJ vertex texture lines
	const std::regex obj_face_vertex_texture_regex(R"(^f\s+([\d]+)\/([\d]+)\s+([\d]+)\/([\d]+)\s+([\d]+)\/([\d]+)$)");

	/// Regular expression for matching OBJ vertex texture normal lines
	const std::regex obj_face_vertex_texture_normal_regex(R"(^f\s+([\d]+)\/([\d]+)\/([\d]+)\s+([\d]+)\/([\d]+)\/([\d]+)\s+([\d]+)\/([\d]+)\/([\d]+)$)");

	/// Calculate the edge code for a pair of vertices
	///	@param v1						First vertex
	///	@param v2						Second vertex
	///	@return							Edge code
	int64_t edge_code(const int v1, const int v2)
	{
		const int va = std::min(v1, v2);
		const int vb = std::max(v1, v2);
		return (static_cast<int64_t>(va) << 32) | static_cast<int64_t>(vb);
	}

	/// Check if a face is valid
	///	@param mesh						Mesh
	///	@param face						Face
	///	@return							True if valid
	bool is_face_valid(const cb::mesh &mesh, const cb::mesh::face& face)
	{
		// Fail if the indices are invalid
		if (face.v0 < 0 || face.v0 >= static_cast<int>(mesh.vertices.size()) ||
			face.v1 < 0 || face.v1 >= static_cast<int>(mesh.vertices.size()) ||
			face.v2 < 0 || face.v2 >= static_cast<int>(mesh.vertices.size())) {
			return false;
		}

		// Fail if the vertices are not unique
		if (face.v0 == face.v1 || face.v0 == face.v2 || face.v1 == face.v2) {
			return false;
		}

		// Fail if the the area is zero
		const auto edge1 = mesh.vertices[face.v1] - mesh.vertices[face.v0];
		const auto edge2 = mesh.vertices[face.v2] - mesh.vertices[face.v0];
		if (edge1.cross(edge2).is_zero_approx()) {
			return false;
		}

		// Face is valid
		return true;
	}
}

cb::mesh_error cb::mesh::load_obj(const char* p_path)
{
	// Clear the current contents
	vertices.clear();
	faces.clear();

	// Open the file for reading
	std::ifstream in(p_path);
	if (!in.is_open()) {
		return mesh_error::file_not_found;
	}

	// Load the raw obj vertices and faces
	std::vector<vector3> obj_vertices;
	std::vector<face> obj_faces;
	std::string line;
	while (std::getline(in, line))
	{
		// Skip empty lines
		if (line.empty()) {
			continue;
		}

		// Handle lines
		if (line[0] == 'v')
		{
			// Vertex line
			std::smatch match;
			if (std::regex_match(line, match, obj_vertex_regex))
			{
				// Add vertex
				obj_vertices.push_back({
					std::stof(match[1]),
					std::stof(match[2]),
					std::stof(match[3])
				});
			}
		}
		else if (line[0] == 'f')
		{
			// Face line
			std::smatch match;
			if (std::regex_match(line, match, obj_face_vertex_regex))
			{
				obj_faces.push_back({
					std::stoi(match[1]) - 1,
					std::stoi(match[2]) - 1,
					std::stoi(match[3]) - 1
				});
			}
			else if (std::regex_match(line, match, obj_face_vertex_texture_regex))
			{
				obj_faces.push_back({
					std::stoi(match[1]) - 1,
					std::stoi(match[3]) - 1,
					std::stoi(match[5]) - 1
				});
			}
			else if (std::regex_match(line, match, obj_face_vertex_texture_normal_regex))
			{
				obj_faces.push_back({
					std::stoi(match[1]) - 1,
					std::stoi(match[4]) - 1,
					std::stoi(match[7]) - 1
				});
			}
		}
	}

	// Close the file
	in.close();

	// Detect empty mesh
	if (obj_vertices.empty() || obj_faces.empty()) {
		return mesh_error::empty;
	}

	// Deduplicate the vertices
	std::map<vector3, int> vertex_map;
	std::map<int, int> vertex_translation;
	for (int i = 0; i < static_cast<int>(obj_vertices.size()); ++i)
	{
		// Get the vertex
		const vector3& v = obj_vertices[i];

		// Check if the vertex already exists
		auto it = vertex_map.find(v);
		if (it != vertex_map.end())
		{
			// Vertex already exists, use the existing index
			vertex_translation[i] = it->second;
		}
		else
		{
			// Vertex does not exist, add it to the map
			int index = static_cast<int>(vertices.size());
			vertex_translation[i] = index;
			vertex_map[v] = index;
			vertices.push_back(v);
		}
	}

	// Populate the faces
	for (const face& f : obj_faces)
	{
		// Add the face
		faces.push_back({
			vertex_translation[f.v0],
			vertex_translation[f.v1],
			vertex_translation[f.v2]
		});
	}

	// Sanity check the faces
	if (!std::all_of(
		faces.begin(),
		faces.end(),
		[this](const face& f) { return is_face_valid(*this, f); })) {
			return mesh_error::degenerate_face;
	}

	// Valid mesh loaded
	return mesh_error::success;
}

bool cb::mesh::save_obj(const char* p_path) const
{
	// Open the file for writing
	std::ofstream out(p_path);
	if (!out.is_open())	{
		return false;
	}

	// Write the header
	out << "# Convex Baker" << std::endl;

	// Write the vertices
	for (const vector3& v : vertices) {
		out << "v " << v.x << " " << v.y << " " << v.z << std::endl;
	}

	// Write the faces
	for (const face& f : faces)	{
		out << "f " << f.v0 + 1 << " " << f.v1 + 1 << " " << f.v2 + 1 << std::endl;
	}

	// Close the file and return success
	out.close();
	return true;
}

bool cb::mesh::is_closed() const
{
	// Assemble the dictionary of unique edges and the count of faces that use them
	std::map<int64_t, int> edges;
	for (const face& f : faces)	{
		// Add the edges
		edges[edge_code(f.v0, f.v1)] += 1;
		edges[edge_code(f.v1, f.v2)] += 1;
		edges[edge_code(f.v2, f.v0)] += 1;
	}

	// If all edges have two faces then the mesh is closed
	return std::all_of(
		edges.begin(),
		edges.end(), 
		[](const std::pair<int64_t, int>& p) 	{ return p.second == 2; });
}

bool cb::mesh::is_convex() const
{
	// Check if the mesh is convex
	for (const face& f : faces)
	{
		// Get the face normal
		const vector3 n = (vertices[f.v1] - vertices[f.v0]).cross(vertices[f.v2] - vertices[f.v0]);

		// Check for vertices on both sides of the face
		bool found_positive = false;
		bool found_negative = false;
		for (const vector3 & v : vertices)
		{
			// Skip the face vertices
			if (v == vertices[f.v0] || v == vertices[f.v1] || v == vertices[f.v2]) {
				continue;
			}

			const float side = n.dot(v - vertices[f.v0]);
			if (side > 0.0f)
			{
				found_positive = true;
			}
			else if (side < 0.0f)
			{
				found_negative = true;
			}
		}

		// Fail if there are points on both sides of the face
		if (found_positive && found_negative) {
			return false;
		}
	}

	// Mesh is convex
	return true;
}

bool cb::mesh::is_multiple() const
{
	// Count of objects
	int objects = 0;

	// Populate a set of unassigned vertices
	std::set<int> unassigned;
	for (int i = 0; i < static_cast<int>(vertices.size()); ++i) {
		unassigned.insert(i);
	}

	// Flood fill the objects
	while (unassigned.empty() == false)
	{
		// Count this object
		++objects;

		// Seed the queue with the first unassigned vertex
		std::set<int> queue;
		queue.insert(*unassigned.begin());

		// Flood fill the object
		while (queue.empty() == false)
		{
			// Get the next vertex
			const int v = *queue.begin();
			queue.erase(queue.begin());

			// Remove the vertex from the unassigned set
			if (unassigned.erase(v) == 0) {
				continue;
			}

			// Add the adjacent vertices to the queue
			for (const face& f : faces)
			{
				if (f.v0 == v)
				{
					queue.insert(f.v1);
					queue.insert(f.v2);
				}
				else if (f.v1 == v)
				{
					queue.insert(f.v0);
					queue.insert(f.v2);
				}
				else if (f.v2 == v)
				{
					queue.insert(f.v0);
					queue.insert(f.v1);
				}
			}
		}
	}

	// Return true if there is only one object
	return objects == 1;
}
