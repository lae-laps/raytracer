#pragma once

#ifndef METAL_HPP
#define	METAL_HPP

#include "../material/material.hpp"

class metal : public material {
	public:
		color albedo;
		val fuzziness;

		metal(const color& a, const val f) : albedo(a), fuzziness(f) {}

		virtual bool scatter(const ray &r_in, hit_record &rec, color &attenuation, ray &scattered) const override;
};

#endif

