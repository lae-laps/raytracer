#pragma once

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <iostream>

#include "../global.hpp"

class Filewriter {
	private:
		unsigned int *matrix;  // 3D array for rows, columns & RGB is compressed down into a 1D array

	protected:
		int offset(int, int);
		int offset(int, int, int);

		std::string generate_headers();

	public:
		unsigned int width;
		unsigned int height;
		unsigned int color_depth;
		unsigned int n;

		Filewriter(int width, int height, int color_depth);	
		~Filewriter();

		int write_to_file(std::string);

		void set_pos(const int, const int, const val n[]);
		void set_pos(const int, const int, const unsigned int n[]);
		void set_pos(const int, const int, const int, const val);
		void set_pos(const int, const int, const int, const unsigned int);

		void debug_matrix();
};

#endif

