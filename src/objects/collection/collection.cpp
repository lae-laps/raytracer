#include "collection.hpp"

collection::collection(shared_ptr<hittable> object) {
	add(object);
}

void collection::clear() {
	objects.clear();
}

void collection::add(shared_ptr<hittable> object) {
	objects.push_back(object); 
}

bool collection::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record tmp;
    bool hit_anything = false;
    val closest = t_max;

    for (const auto &object : objects) {
		if (object->hit(r, t_min, closest, tmp)) {
			hit_anything = true;
			closest = tmp.t;
			rec = tmp;
		}
	}
    return hit_anything;
}

