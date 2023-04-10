#pragma once

#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "../material/material.hpp"

class lambertian : public material {
	public:
        color albedo;

		lambertian(const color &a) : albedo(a) {}

        virtual bool scatter(const ray &r, hit_record &rec, color &attenuation, ray &scattered) const override;

};

#endif

