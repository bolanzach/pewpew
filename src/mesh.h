#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

// Number of vetrices in a cube
#define NUMBER_CUBE_VERTICES 8
extern Vector3 cube_vertices[NUMBER_CUBE_VERTICES];

// 6 cube faces, 2 triangles per face
#define NUMBER_CUBE_FACES (6 * 2)
extern Face cube_faces[NUMBER_CUBE_FACES];

void load_obj_file_data(char* file_name);

void load_cube_mesh_data(void);

typedef struct {
  /// Dynamic array of vertices
  Vector3* vertices;

  /// Dynamic array of faces
  Face* faces;

  /// The mesh's rotation
  Vector3 rotation;
} Mesh;

extern Mesh global_mesh;

#endif