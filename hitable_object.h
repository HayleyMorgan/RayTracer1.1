#pragma once

#ifndef HITABLE_OBJECTH
#define HITABLE_OBJECTH

#include "Ray_new.h"

struct hit_record
{
	//t is a scalar for getting the amount we travel down the ray
	float t;
	//P is the point on the object that we intersect with
	vector3d p;
	//This is the normal to the object from which it is hit
	vector3d normal;

};

//abstract class for hitting various objects
class hitable_object
{
public:
	//This is a virtual function that will be used in every class that describes the world
	virtual bool hit(const ray& ray, float& t_min, float& t_max, hit_record& record_hit) const = 0;
};

#endif // !HITABLE_OBJECTH

