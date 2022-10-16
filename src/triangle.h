#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

// A face contains 3 fields that each are an index to a Vector3 in a mesh array
typedef struct {
  int a;
  int b;
  int c;
} Face;

// A Triangle is a collection of 3 Vector2 points.
// These are the actual (x,y) points on the screen
typedef struct {
  Vector2 points[3];
} Triangle2;

#endif