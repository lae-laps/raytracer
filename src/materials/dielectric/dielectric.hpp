#pragma once

#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "../material/material.hpp"

/*	Dielectric materials are those such as glass, diamond or water which let some part of the incident rays
 *	inside. Snells law is applicable to them. To render them, we refract a portion of the rays which have a
 *	real solution to snells law, and randomly reflect some of them. We also reflect 100% of the ones which
 *	eta / eta', so refractive index ratio, is bigger than 1 as they dont have solutions.
 *
 *	Note: when creating an object with dielectric type, if the radius is set negative, the overal geometry 
 *	stays the same but as the normals point inwards, the effect is created that the sphere is hollow.
 */

class dielectric : public material {

	public:

		color albedo;	// tonality to reflect

		val ri;			// refractive index

		dielectric(const color rgb, const val refractive_index) : albedo(rgb), ri(refractive_index) {}

		virtual bool scatter(const ray& r, hit_record& rec, color &attenuation, ray& scattered) const override;

	private:

		static val reflectance(const val cosine, const val ref_index);

};

#endif

