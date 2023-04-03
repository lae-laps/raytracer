#pragma once

#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <memory>
#include <vector>

#include "../hittable/hittable.hpp"

using std::shared_ptr;

class collection : public hittable {
	public:

		std::vector<shared_ptr<hittable>> objects;

		collection() {}
        collection(shared_ptr<hittable> object);

		void clear();
        void add(shared_ptr<hittable>);

		virtual bool hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const override;

};

#endif

