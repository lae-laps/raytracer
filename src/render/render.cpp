// NetPBM

#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "render.hpp"
#include "../io/io.hpp"
#include "../global.hpp"

Render::Render(int a, int b) {
	width = a;
	height = b;

	matrix = new unsigned int[3 * width * height]();			// () after expr zeroe's the data

	/*for (unsigned int i = 0; i < 3 * width * height; i++) {	// Therefore this is unneeded
		matrix[i] = 0;
	}*/

}

Render::~Render() {
	delete [] matrix;
}

int Render::write_to_file(std::string path) {

	// return values
	// 0 -> all good
	// 1 -> error in writin

	// check if the file already exists
	struct stat buf;
	if (stat(path.c_str(), &buf) != -1) {
		throw_warning("file [" + path + "] already exists");
		std::cout << "overwrite? [y/n]> ";
		std::string check = input();
		if (check != "y" and check != "Y") {
			return 0;	
		}
		// overwrite contents in file
		check.clear();
		std::ofstream ofs;
		ofs.open(path, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}

	std::ofstream file(path);

	file << generate_headers();		// write headers
								
	for (unsigned int i = 0; i < 3 * width * height; i++) {
		/*if (i % 20 == 0) {
			std::cerr << "\rprogress: " << i << ' ' << std::flush;
		}*/
		if (i  % (width * 3) == 0) {
			if (i != 0) {
				file << std::endl;
			}
		}
		file << matrix[i] << " ";
		// this speeds down rendering but improves file readability
		/*std::string n = std::to_string(matrix[i]);
		for (long unsigned int m = 0; m < 3 - n.length(); m++) {
			file << " ";
		}*/
	}

	file << std::endl;

	file.close();

	return 0;
}

std::string Render::generate_headers() {
	std::string headers;
	headers += "P3\n";														// set magic numbers ; TODO: make this scalable
	headers += std::to_string(width) + " " + std::to_string(height) + "\n";	// set width and height
	headers += std::to_string(COLOR_DEPTH) + "\n";							// set color depth
	return headers;
}

void Render::set_pos(int x, int y, unsigned int val[]) {
	int n = offset(x, y);

	for (int i = 0; i < 3; i ++) {
		if (val[i] > COLOR_DEPTH) {
			throw_encoding_error("value " + std::to_string(val[i]) + " too large at position (" + std::to_string(x) + ", " + std::to_string(y) + ")");
		}
		matrix[n + i] = val[i];
	}
}

void Render::set_pos(int x, int y, double val[]) {

	for (int h = 0; h < 3; h++) {
		if (val[h] > 1.0) {
			throw_encoding_error("decimal value " + std::to_string(val[h]) + " exceeds 1.0 (" + std::to_string(x) + ", " + std::to_string(y) + ")");
		}
	}
	
	double f = double(COLOR_DEPTH) + 0.999;

	unsigned int rgb[] = {
		static_cast<unsigned int>(f * val[0]),
		static_cast<unsigned int>(f * val[1]),
		static_cast<unsigned int>(f * val[2]),
	};

	int n = offset(x, y);

	for (int i = 0; i < 3; i ++) {
		matrix[n + i] = rgb[i];
	}
}

void Render::set_pos(int x, int y, int z, unsigned int val) {
	if (val > COLOR_DEPTH) {
		throw_encoding_error("value " + std::to_string(val) + " too large at position (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}
	matrix[offset(x, y, z)] = val;
}

void Render::set_pos(int x, int y, int z, double val) {
	if (val > 1.0) {
		throw_encoding_error("decimal value " + std::to_string(val) + " exceeds 1.0 (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}
	matrix[offset(x, y, z)] = static_cast<unsigned int>((COLOR_DEPTH + 0.999) * val);
}

int Render::offset(int x, int y) {
	return ((y * width) - 1 + (x + 1)) * 3;
}

int Render::offset(int x,  int y, int z) {
	return ((y * width) - 1 + (x + 1)) * 3 + z;
}

void Render::debug_matrix() {

	for (unsigned int i = 0; i < width * height; i++) {
		if (i % width == 0) {
			if (i != 0) {
				std::cout << std::endl;
			}
		}
		std::cout << " (" << matrix[3 * i] << " " << matrix[3 * i + 1] << " " << matrix[3 * i + 2] << ")";
	}
	std::cout << std::endl;
}

