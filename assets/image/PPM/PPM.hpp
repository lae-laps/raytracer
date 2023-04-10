#pragma once

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <iostream>

#include "../Image.hpp"
#include "../../global.hpp"

class PPM : public Image {
	public:
		unsigned int *matrix;  // 3D array for rows, columns & RGB is compressed down into a 1D array
							
		std::string generate_headers() const;

		int offset(const int, const int) const;
		int offset(const int, const int, const int) const;

		unsigned int width;
		unsigned int height;
		unsigned int color_depth;
		unsigned int n;

		PPM(const int width, const int height, const int color_depth);	
		~PPM();

		int write(const std::string) const;

		void set_pos(const int, const int, const val n[]) const;
		void set_pos(const int, const int, const unsigned int n[]) const;
		void set_pos(const int, const int, const int, const val) const;
		void set_pos(const int, const int, const int, const unsigned int) const;

		void debug_matrix() const;
};

#endif

