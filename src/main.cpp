// Raytracer

#include <iostream>

#include "io/io.hpp"
#include "global.hpp"
#include "ray/ray.hpp"
#include "math/math.hpp"
#include "vec3/vec3.hpp"
#include "render/render.hpp"
#include "filewriter/filewriter.hpp"
#include "objects/sphere/sphere.hpp"
#include "objects/collection/collection.hpp"

int main() {

	// create objects

	collection world;
	world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, 0, -0.4), 0.1));
	world.add(make_shared<sphere>(point3(-0.7, 0, -1), 0.2));
	world.add(make_shared<sphere>(point3(0.7, 0, -1), 0.2));

	// set camera and viewport

	Filewriter filewriter(WIDTH, HEIGHT, COLOR_DEPTH);

	val viewport_height = 2.0;
	val viewport_width = static_cast<val>(viewport_height) * aspect_ratio;
	val focal_length = 1.0;

	point3 origin(0, 0, 0);
	vec3 horizontal(viewport_width, 0, 0);
	vec3 vertical(0, viewport_height, 0);
	vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

	// render

	for (unsigned int j = 0; j < HEIGHT; ++j) {
		for (unsigned int i = 0; i < WIDTH; ++i) {
			val u = (val)(i) / (WIDTH - 1);
			val v = (val)(j) / (HEIGHT - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel = render_color(r, world);
			val rgb[] = {pixel.x, pixel.y, pixel.z};
			filewriter.set_pos(i, j, rgb);
		}
	}

	//image.debug_matrix(); 

	int err = filewriter.write_to_file("images/render3.ppm");
	if (err != 0) {
		std::cout << "write to file with exit code : " << err << std::endl;
	}

	return 0;
}

