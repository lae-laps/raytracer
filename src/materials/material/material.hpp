#pragma once

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../../ray/ray.hpp"
#include "../../objects/collection/collection.hpp"

class material {
	public:

		color albedo;

		virtual bool scatter(const ray &r, hit_record &rec, color &c, ray &scattered) const = 0;
};

#endif

