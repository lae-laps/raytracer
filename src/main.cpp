// Raytracer

#include <iostream>

#include "io/io.hpp"
#include "ray/ray.hpp"
#include "vec3/vec3.hpp"
#include "color/color.hpp"
#include "point/point.hpp"
#include "render/render.hpp"

color ray_color(const ray &r) {

}

int main() {

	int width = 1600;
	int height = 900;

	Render render(width, height);

	for (int j = height - 1; j >= 0; --j) {
		for (int i = 0; i < width; i++) {
			double val[3];
			val[0] = double(double(i) / width);
			val[1] = double(double(j) / height);
			//val[2] = (double(i) * double(j)) / double(width * height);
			val[2] = 0.25;
			render.set_pos(i, j, val);
		}
	}

	//image.debug_matrix(); 

	int err = render.write_to_file("images/render3.ppm");
	if (err != 0) {
		std::cout << "write to file with exit code : " << err << std::endl;
	}

	return 0;
}

