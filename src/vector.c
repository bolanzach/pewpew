#include <math.h>
#include "vector.h"
#include <stdio.h>
#include <stdint.h>

void print_vector3(Vector3 point) {
    printf("{ x: %.5f, y: %.5f, z: %.5f }\n", point.x, point.y, point.z);
}

void print_vector2(Vector2 point) {
    printf("{ x: %.5f, y: %.5f }\n", point.x, point.y );
}

Vector3 rotate_vector3_x(Vector3 vector, float angle) {
    Vector3 rotated_vector = {
        .x = vector.x,
        .y = vector.y * cos(angle) - vector.z * sin(angle),
        .z = vector.y * sin(angle) + vector.z * cos(angle)
    };
    return rotated_vector;
}

Vector3 rotate_vector3_y(Vector3 vector, float angle) {
    Vector3 rotated_vector = {
        .x = vector.x * cos(angle) - vector.z * sin(angle),
        .y = vector.y,
        .z = vector.x * sin(angle) + vector.z * cos(angle)
    };
    return rotated_vector;
}

Vector3 rotate_vector3_z(Vector3 vector, float angle) {
    Vector3 rotated_vector = {
        .x = vector.x * cos(angle) - vector.y * sin(angle),
        .y = vector.x * sin(angle) + vector.y * cos(angle),
        .z = vector.z
    };
    return rotated_vector;
}
