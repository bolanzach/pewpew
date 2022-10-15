#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

void print_vector3(Vector3 point);
void print_vector2(Vector2 point);

// Lock an axis and rotate around it
Vector3 rotate_vector3_x(Vector3 v, float angle);
Vector3 rotate_vector3_y(Vector3 v, float angle);
Vector3 rotate_vector3_z(Vector3 v, float angle);

#endif