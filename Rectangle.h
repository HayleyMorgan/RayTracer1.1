#pragma once

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "hitable_object.h"

class rectangle : hitable_object
{

public:
	rectangle() {};

	rectangle(int w, int h) : width(w), height(h) {}

	virtual bool hit(const ray& r, float& tmin, float& tmax, hit_record& rec) const;

private:

	int width, height;

};

#endif