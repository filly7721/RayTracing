#pragma once

#include "ray.h"

//necessary hit information
struct hit_record {

	point3 p; // hit point
	vec3 normal; 
	double t; // hit distance
	bool front_face; //whether the ray intersects the outside or the inside

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

//abstract class for all hittable objects
class hittable {

public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};