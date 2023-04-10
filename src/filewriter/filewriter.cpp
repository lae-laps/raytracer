// NetPBM

#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "filewriter.hpp"
#include "../io/io.hpp"
#include "../global.hpp"

Filewriter::Filewriter(int a, int b, int c) {
	width = a;
	height = b;
	color_depth = c;

	matrix = new unsigned int[3 * width * height]();			// () after expr zeroe's the data

	/*for (unsigned int i = 0; i < 3 * width * height; i++) {	// Therefore this is unneeded
		matrix[i] = 0;
	}*/

	n = width * height * 3;

}

Filewriter::~Filewriter() {
	delete [] matrix;
}

int Filewriter::write_to_file(std::string path) {

	// return values
	// 0 -> all good
	// 1 -> error in writin

	// check if the file already exists
	struct stat buf;
	if (stat(path.c_str(), &buf) != -1) {
		//throw_warning("file [" + path + "] already exists");
		if (ASK_TO_OVERWRITE) {
			std::cout << "overwrite? [y/n]> ";
			std::string check = input();
			if (check != "y" and check != "Y") {
				return 0;	
			}
			// overwrite contents in file
			check.clear();
		}
		std::ofstream ofs;
		ofs.open(path, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}

	std::ofstream file(path);

	file << generate_headers();		// write headers
								
	for (unsigned int i = 0; i < 3 * width * height; i++) {
	//for (unsigned int i = 3 * width * height; i > 0; i--) {
		/*if (i % 20 == 0) {
			std::cerr << "\rprogress: " << i << ' ' << std::flush;
		}*/
		if (i % (width * 3) == 0) {
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

std::string Filewriter::generate_headers() {
	std::string headers;
	headers += "P3\n";														// set magic numbers ; TODO: make this scalable
	headers += std::to_string(width) + " " + std::to_string(height) + "\n";	// set width and height
	headers += std::to_string(color_depth) + "\n";							// set color depth
	return headers;
}

void Filewriter::set_pos(const int x, const int y, const unsigned int r[]) {
	int n = offset(x, y);

	for (int i = 0; i < 3; i ++) {
		if (r[i] > color_depth) {
			throw_encoding_error("value " + std::to_string(r[i]) + " too large at position (" + std::to_string(x) + ", " + std::to_string(y) + ")");
		}
		matrix[n + i] = r[i];
	}
}

void Filewriter::set_pos(const int x, const int y, const val n[]) {

	for (int h = 0; h < 3; h++) {
		if (n[h] > 1.0) {
			throw_encoding_error("decimal value " + std::to_string(n[h]) + " exceeds 1.0 (" + std::to_string(x) + ", " + std::to_string(y) + ")");
		}
	}

	val f = static_cast<val>(color_depth) + 0.999;

	unsigned int rgb[] = {
		static_cast<unsigned int>(f * n[0]),
		static_cast<unsigned int>(f * n[1]),
		static_cast<unsigned int>(f * n[2]),
	};

	int r = offset(x, y);

	for (int i = 0; i < 3; i ++) {
		if (r + i < 0) throw_error("index out of bounds");
		matrix[r + i] = rgb[i];
	}
}

void Filewriter::set_pos(const int x, const int y, const int z, const unsigned int n) {
	if (n > color_depth) {
		throw_encoding_error("value " + std::to_string(n) + " too large at position (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}
	matrix[offset(x, y, z)] = n;
}

void Filewriter::set_pos(const int x, const int y, const int z, const val n) {
	if (n > 1.0) {
		throw_encoding_error("decimal value " + std::to_string(n) + " exceeds 1.0 (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}
	matrix[offset(x, y, z)] = static_cast<unsigned int>((color_depth + 0.999) * n);
}

int Filewriter::offset(int x, int y) {
	return (n) - ((y * width)  + x ) * 3;
}

int Filewriter::offset(int x,  int y, int z) {
	return (n) - ((y * width) + x) * 3 + z;
}

void Filewriter::debug_matrix() {

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

