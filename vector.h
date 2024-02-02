#ifndef VECTOR_H
#define VECTOR_H

#define PI 3.141592

typedef struct vector {
    double x, y;
} vector_t;

/**
 * Convert degree to radian
 * @param angle in degree
 * @return angle in radian
*/
double deg_to_rad(double angle);

/**
 * Add two vectors
 * @param v1
 * @param v2
 * @return vector_t result
*/
vector_t v_add(vector_t v1, vector_t v2);

/**
 * Subtract two vectors
 * @param v1
 * @param v2
 * @return vector_t result
*/
vector_t v_sub(vector_t v1, vector_t v2);

/**
 * Multiply vector with scalar
 * @param v 
 * @param scalar
 * @return vector_t result
*/
vector_t v_mult(vector_t v, double scalar);

/**
 * Calculate length of vector using pythagoras theorem
 * @param v Vector to calculate length of
 * @return length of vector
*/
double v_length(vector_t v);

/**
 * Calculate distance of two vectors
 * @param v1
 * @param v2
 * @return distance between the vectors
*/
double v_dist(vector_t v1, vector_t v2);

#endif