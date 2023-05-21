#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {

public:
	sphere() {}
	sphere(point3 cen, double r) :center(cen), radius(r) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
	point3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

    // ray P(T) = A + b * t
    // C is circle center
    // (t^2)(b.b) + 2t b.(A-C) + (A-C).(A-C) - r^2=0

    //Solve 2nd order polynomial
    //discriminant = b^2 - 4ac
    //y = (-b +- sqrt(b^2 +- 4ac)) / 2a

    //simplifications
    //if h = b/2 then y = (-h +- sqrt(h^2-ac)) / a
    //so discriminant = h^2-ac
    //dot(x,x) = x.length_squared();

    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);
    // Find the nearest root within [tmin, tmax]
    auto root = (-h - sqrtd) / a;
    if (root < t_min || t_max < root) {
        //if first root is invalid, try the second root
        root = (-h + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}