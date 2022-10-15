#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

// Number of vetrices in a cube
#define NUMBER_MESH_VERTICES 8
extern Vector3 mesh_vertices[NUMBER_MESH_VERTICES];

// 6 cube faces, 2 triangles per face
#define NUMBER_MESH_FACES (6 * 2)
extern Face mesh_faces[NUMBER_MESH_FACES];

#endif