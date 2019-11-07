#pragma once

#ifndef SPHEREH
#define SPHEREH
#include "hitable_object.h"


class sphere : public hitable_object
{
public:
	sphere() {}

	sphere(vector3d Center, float r) : center(Center), radius(r) {};

	virtual bool hit(const ray& r, float& tmin, float& tmax, hit_record& rec) const;

private:

	vector3d center;

	float radius;
};



#endif // !SPHERE
