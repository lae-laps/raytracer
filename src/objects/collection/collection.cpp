#include <memory>

#include "collection.hpp"

using std::shared_ptr;
//using std::make_shared;

collection::collection(shared_ptr<hittable> object) {
	add(object);
}

void collection::clear() {
	objects.clear();
}

void collection::add(shared_ptr<hittable> object) {
	objects.push_back(object); 
}

bool collection::hit(const ray& r, val t_min, val t_max, hit_record &rec) const {
	hit_record tmp;
    bool hit_anything = false;
    val closest = t_max;

    for (const auto &object : objects) {

		if (object->hit(r, t_min, closest, tmp)) {
			hit_anything = true;
			closest = tmp.t;

			//m = make_shared<material>(object->mat);
			

			rec = tmp;
		}
	}
    return hit_anything;
}

