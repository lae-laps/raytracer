#pragma once 

#ifndef PNG_HPP
#define PNG_HPP

#include "../Image.hpp"
#include "../../global.hpp"

#include <iostream>

class PNG : public Image {
	public:

		unsigned int width;
		unsigned int height;
		unsigned int color_depth;

		PNG(unsigned int w, unsigned int h, unsigned int c);

		int write(const std::string path) const override;

		void set_pos(const int, const int, const val n[]) const;
		void set_pos(const int, const int, const unsigned int n[]) const;
		void set_pos(const int, const int, const int, const val) const;
		void set_pos(const int, const int, const int, const unsigned int) const;

};

#endif

