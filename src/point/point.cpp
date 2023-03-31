#include "point.hpp"

point::point(val x, val y, val z) {
	set_x(x);     
	set_y(y);     
	set_z(z);     
}

void point::set_x(val n) {x = n;}
void point::set_y(val n) {y = n;}
void point::set_z(val n) {z = n;}

