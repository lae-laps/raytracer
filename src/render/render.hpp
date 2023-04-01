#pragma once

#ifndef RENDER_HPP
#define RENDER_HPP

#include <iostream>

class Render {
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

		Render(int width, int height, int color_depth);	
		~Render();

		int write_to_file(std::string);

		void set_pos(int, int, double val[]);
		void set_pos(int, int, unsigned int val[]);
		void set_pos(int, int, int, double);
		void set_pos(int, int, int, unsigned int);

		void debug_matrix();
};

#endif

