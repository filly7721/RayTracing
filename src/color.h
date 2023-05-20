#pragma once

#include <iostream>

#include "vec3.h"

void write_color(std::ostream& out, color pixel_color) {
	//translate 0-1 to 0-255
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}