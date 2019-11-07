#pragma once

#ifndef HITABLELISTH
#define HITABLELISTH
#include "hitable_object.h"

class hitable_list : public hitable_object
{

public:
	hitable_list() {};

	hitable_list(hitable_object **l, int n) { list = l; l_size = n; };

	virtual bool hit(const ray& r, float& t_min, float& t_max, hit_record& rec) const;

private:
	hitable_object **list;
	int l_size;
};

bool hitable_list::hit(const ray& r, float& t_min, float& t_max, hit_record& record_hit) const
{
	bool hit_anything = false;

	float closest_object = t_max;

	hit_record temp_record;

	for (int i = 0; i < l_size; i++)
	{

		//Traversing through the object which can be collided with
		//If it has been hit, then log that it has been hit and find out if it the closest object in the records
		//This closest object is determined by the quadratic equation
		if (list[i]->hit(r, t_min, closest_object, temp_record))
		{
			hit_anything = true;
			closest_object = temp_record.t;
			record_hit = temp_record;
		}
	}

	return hit_anything;
}

#endif