#pragma once

#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "../sphere/sphere.hpp"

class Collection {
	public:
		sphere *spheres;
		unsigned int sphere_count;

		Collection();

		void add_sphere(sphere s);
};

#endif

