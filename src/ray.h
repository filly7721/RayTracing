#pragma once

#include "vec3.h"

class ray {

public:

	ray() : orig(0, 0, 0), dir(0, 0, 0) {}
	ray(const point3& orig, const point3& dir) : orig(orig), dir(dir) {}

	point3 origin() const {return orig;}
	point3 direction() const {return dir;}

	point3 at(double t) const {
		return point3(orig + t * dir);
	}

public:
	point3 orig;
	point3 dir;
};