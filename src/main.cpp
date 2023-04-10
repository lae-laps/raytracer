// Raytracer

#include <chrono>
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
#include "materials/dielectric/dielectric.hpp"
#include "materials/lambertian/lambertian.hpp"

using std::make_shared;

collection random_scene() {
	collection world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_val();
			point3 center(a + 0.9 * random_val(), 0.2, b + 0.9 * random_val());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.7) {
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else if (choose_mat < 0.85) {
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_val(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					sphere_material = make_shared<dielectric>(color(1.0, 1.0, 1.0), 1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(color(1.0, 1.0, 1.0), 1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

int main() {

	// seed the random number generator
	
	srand(time(NULL));

	// create objects

	
	//collection world;

	collection world = random_scene();
	
	// set camera
	
	//Camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 2.0, aspect_ratio, true, 0.5);
	Camera cam(point3(13,2,3), point3(0,0,0), vec3(0,1,0), 4.5, aspect_ratio, true, 0.08);
	//Camera cam(point3(0,0,0), point3(0,0,-1), vec3(0,1,0), 4.5, aspect_ratio, false, 2.0);

	// set filewriter handler to render image

	Filewriter image(WIDTH, HEIGHT, COLOR_DEPTH);

	// render
	
	auto render_start_time = std::chrono::high_resolution_clock::now();

	for (unsigned int j = 0; j < HEIGHT; ++j) {

		update_progress_bar("+ Rendering", (val)(j) / HEIGHT);

		for (unsigned int i = 0; i < WIDTH; ++i) {

			//std::cout << "i: " << i << " | j: " << j << std::endl;

			color pixel(0, 0, 0);
			for (unsigned int s = 0; s < samples_per_pixel; ++s) {
				val u = (i + random_val()) / (WIDTH - 1);
				val v = (j + random_val()) / (HEIGHT - 1);
				ray r = cam.get_ray(u, v);
				pixel += render_color(r, world, cycles);
			}
			pixel = even_color(pixel);
			val rgb[] = {pixel.x, pixel.y, pixel.z};
			image.set_pos(i, j, rgb);
		}
	}

	update_progress_bar("* Rendered", 1.0);
	std::cout << std::endl;

	auto render_end_time = std::chrono::high_resolution_clock::now();
	auto render_duration = std::chrono::duration_cast<std::chrono::milliseconds>(render_end_time - render_start_time);

	auto t = render_duration.count();

	std::cout << " * Rendered after " << t << " milliseconds";

	if (t > 10000  ) std::cout << " ( " << (val)t / 1000	<< " seconds ) ";
	if (t > 60000  ) std::cout << " ( " << (val)t / 60000	<< " minutes ) ";
	if (t > 3600000) std::cout << " ( " << (val)t / 3600000 << " hours ) ";

	std::cout << std::endl;

	//image.debug_matrix(); 

	int err = image.write_to_file("images/render.ppm");
	if (err != 0) {
		std::cout << "write to file with exit code : " << err << std::endl;
	}

	return 0;
}

