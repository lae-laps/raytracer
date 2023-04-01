// Raytracer

#include <iostream>

#include "io/io.hpp"
#include "ray/ray.hpp"
#include "vec3/vec3.hpp"
#include "render/render.hpp"
#include "global_collection.hpp"
#include "objects/collection/collection.hpp"

Collection collection;

int main() {

	int width = 1600;
	int height = 9000;

	Render render(WIDTH, HEIGHT, COLOR_DEPTH);

	val viewport_height = 2.0;
	val viewport_width = aspect_ratio * viewport_height;
	val focal_length = 1.0;

	point3 origin(0, 0, 0);
	vec3 horizontal(viewport_width, 0, 0);
	vec3 vertical(0, viewport_height, 0);
	vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

	sphere test(0.3, point3(0.0, 0.0, -1.0));
	collection.add_sphere(test);

	for (int j = height - 1; j >= 0; --j) {
		for (int i = 0; i < width; ++i) {
			val u = (val)(i) / (width - 1);
			val v = (val)(j) / (height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel = r.pixel_color();
			val rgb[] = {pixel.x, pixel.y, pixel.z};
			render.set_pos(i, j, rgb);
		}
	}

	//image.debug_matrix(); 

	int err = render.write_to_file("images/render3.ppm");
	if (err != 0) {
		std::cout << "write to file with exit code : " << err << std::endl;
	}

	return 0;
}

