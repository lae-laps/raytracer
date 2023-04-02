// Raytracer

#include <memory>
#include <iostream>

#include "io/io.hpp"
#include "global.hpp"
#include "ray/ray.hpp"
#include "math/math.hpp"
#include "vec3/vec3.hpp"
#include "camera/camera.hpp"
#include "render/render.hpp"
#include "materials/metal/metal.hpp"
#include "filewriter/filewriter.hpp"
#include "objects/sphere/sphere.hpp"
#include "materials/material/material.hpp"
#include "objects/collection/collection.hpp"
#include "materials/lambertian/lambertian.hpp"

using std::make_shared;

int main() {

	std::cout << "Rendering" << std::endl;

	// seed the random number generator
	
	srand(time(NULL));

	// create objects

	collection world;


	auto material_ground = lambertian(color(0.8, 0.8, 0.0));
	auto material_center = lambertian(color(0.7, 0.3, 0.3));
	auto material_left   = metal(color(0.8, 0.8, 0.8));
	auto material_right  = metal(color(0.8, 0.6, 0.2));

	world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
	world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

	/*for (int m = 0; m < 150; m++) {
		world.add(make_shared<sphere>(point3(random_val(-10, 10), random_val(-10, 10), random_val(-8, -60)), random_val(0.2, 4)));
	}*/

	// set camera
	
	Camera cam;

	// set filewriter handler to render image

	Filewriter image(WIDTH, HEIGHT, COLOR_DEPTH);

	// render

	std::cout << "got to 1" << std::endl;

	for (unsigned int j = 0; j < HEIGHT; ++j) {
		for (unsigned int i = 0; i < WIDTH; ++i) {
			std::cout << "i: " << i << " | j: " << j << std::endl;
			color pixel(0, 0, 0);
			for (unsigned int s = 0; s < samples_per_pixel; ++s) {
				val u = (i + random_val()) / (WIDTH - 1);
				val v = (j + random_val()) / (HEIGHT - 1);
				ray r = cam.get_ray(u, v);
				pixel += render_color(r, world, cycles, NULL);
			}
			pixel = even_color(pixel);
			val rgb[] = {pixel.x, pixel.y, pixel.z};
			image.set_pos(i, j, rgb);
		}
	}

	//image.debug_matrix(); 

	int err = image.write_to_file("images/render.ppm");
	if (err != 0) {
		std::cout << "write to file with exit code : " << err << std::endl;
	}

	return 0;
}

