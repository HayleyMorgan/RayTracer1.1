#pragma once

#include "Vector3d.h"

#ifndef RAYH
#define RAYH

class ray
{
private:
	vector3d A;
	vector3d B;
public:
	ray() {}
	ray(const vector3d& a, const vector3d& b)
	{
		A = a;
		B = b;
	}

	vector3d origin() const { return A; }
	vector3d direction() const{ return B; }

	vector3d point_at_parameter(float t) const
	{
		return A + t * B;
	}

};


#endif // !RAYH
