#pragma once

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string.h>
#include <iostream>

#include "../global.hpp"

class Image {
	public:
		unsigned int width;
		unsigned int height;

		virtual int write(const std::string path) const = 0;

		void set_pixel(const int x, const int y, unsigned int rgb[]);

		void set_pos(const int, const int, const val n[]) const;
		void set_pos(const int, const int, const unsigned int n[]) const;
		void set_pos(const int, const int, const int, const val) const;
		void set_pos(const int, const int, const int, const unsigned int) const;
	
		unsigned int *matrix;

		unsigned int offset(const int, const int) const;

		void generate_image();

};

#endif

