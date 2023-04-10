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
#include "ThreadPool/ThreadPool.hpp"
#include "objects/sphere/sphere.hpp"
#include "materials/material/material.hpp"
#include "objects/collection/collection.hpp"
#include "materials/lambertian/lambertian.hpp"

using std::make_shared;

int main() {

	// seed the random number generator
	
	srand(time(NULL));

	// create objects

	collection world;

	auto material_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	auto material_left   = make_shared<lambertian>(color(0.3, 0.3, 0.3));
	auto material_center = make_shared<lambertian>(color(0.2, 0.2, 0.2));
	auto material_right  = make_shared<metal>(color(0.5, 0.5, 0.5), 0.0);

	world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
	//world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
	//world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

	/*for (int m = 0; m < 50; m++) {
		
		auto a = make_shared<metal>(color(random_val(), random_val(), random_val()));
		auto b = make_shared<lambertian>(color(random_val(), random_val(), random_val()));

		world.add(make_shared<sphere>(point3(random_val(-10, 10), random_val(-10, 10), random_val(-8, -60)), random_val(0.2, 4), a));
		world.add(make_shared<sphere>(point3(random_val(-10, 10), random_val(-10, 10), random_val(-8, -60)), random_val(0.2, 4), b));
	}*/

	// set camera
	
	Camera cam;

	// set filewriter handler to render image

	Filewriter image(WIDTH, HEIGHT, COLOR_DEPTH);

	
	// render

	auto render_start_time = std::chrono::high_resolution_clock::now();

	{
		// create thread pool

		ThreadPool pool(4);

		// main loop

		unsigned int block = HEIGHT / RENDER_THREADS;

		for (unsigned int m = 0; m < RENDER_THREADS; m++) {

			pool.enqueue([m, cam, world, &image, block] {

				unsigned int l = (m + 1) * block;

				if (m + 1 == RENDER_THREADS) {
					l = HEIGHT;
				}

				for (unsigned int j = m * block; j < l; j++) {

					//update_progress_bar("+ Rendering", (val)(j) / HEIGHT);

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

			});
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

