#pragma once

#ifndef CAMERAH
#define CAMERAH

#include "Ray_new.h"

class camera
{
public:
	vector3d lower_left_corner;
	vector3d horizontal;
	vector3d vertical;
	vector3d origin;

	camera()
	{
		 lower_left_corner = vector3d(-2.0f, -1.0f, -1.0f);
		 horizontal = vector3d(4.0f, 0.0f, 0.0f);
		 vertical = vector3d(0.0f, 2.0f, 0.0f);
		 origin = vector3d(0.0f, 0.0f, 0.0f);
	}

	ray getRay(float u, float v) { return ray(origin, (lower_left_corner + (u * horizontal) + (v * vertical)) - origin); }

};



#endif
