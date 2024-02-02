#include <stdio.h>
#include <math.h>
#include "vector.h"

double deg_to_rad(double angle) {
    return angle * PI / 180.0;
}

vector_t v_add(vector_t v1, vector_t v2) {
    return (vector_t){ v1.x + v2.x, v1.y + v2.y };
}

vector_t v_sub(vector_t v1, vector_t v2) {
    return (vector_t){ v1.x - v2.x, v1.y - v2.y };
}

vector_t v_mult(vector_t v, double scalar) {
    return (vector_t){ v.x * scalar, v.y * scalar };
}

double v_length(vector_t v) {
    return sqrt(v.x*v.x + v.y*v.y);
}

double v_dist(vector_t v1, vector_t v2) {
    return v_length(v_sub(v2, v1));
}