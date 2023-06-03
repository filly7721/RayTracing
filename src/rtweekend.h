#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include<cstdlib>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385; // way too many digits, pi = 3

// utility functions
inline double random_double() {
	//retuan double [0,1)
	return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max) {

	return (max - min) * random_double() + min;
}
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}
inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// common headers
#include "ray.h"
#include "vec3.h"
