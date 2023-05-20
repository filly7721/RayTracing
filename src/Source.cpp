#include<iostream>

#include "vec3.h"
#include "color.h"

#include "ray.h"

double hit_Sphere(const point3 &center,double radius, const ray &r) {
    // ray P(T) = A + b * t
    // C is circle center
    //(t^2)(b.b) + 2t b.(A-C) + (A-C).(A-C) - r^2=0

    //simplifications
    //if h = b/2 then y = (-h +- sqrt(h^2-ac)) / h
    //discriminant = h^2-ac
    //dot(x,x) = x.length_squared();

    point3 oc = r.origin() - center; // = A-C

    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return -1.0;
    return (-h - sqrt(discriminant)) / h;
}

color ray_color(const ray &r){
    auto t = hit_Sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0) {
        vec3 N = unit_vector(r.at(t) - point3(0, 0, -1));
        return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    //y can be [-1, 1], though it will rarely reach the extreme ends, still we need it to be [0, 1]
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	
    // Image 
    const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);


    // Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

}