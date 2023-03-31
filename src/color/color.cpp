#include <iostream>

#include "color.hpp"

void color::display() const {
	std::cout << static_cast<unsigned int>((COLOR_DEPTH + 0.999) * x) << " "
			  << static_cast<unsigned int>((COLOR_DEPTH + 0.999) * y) << " "
			  << static_cast<unsigned int>((COLOR_DEPTH + 0.999) * z) << std::endl;
}


