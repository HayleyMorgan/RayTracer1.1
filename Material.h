#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray_new.h"
#include "hitable_object.h"

class material
{
public:
	//Creating an abstract class for various materials we want to render.
	virtual bool scatter(const ray& ray_in, ray& scatter, const hit_record& recordedHit, vector3d& attenuation) const = 0;
};

//-------------------------------------------------------------------------------------------------------------------

//This uses the rejection method which is simply picks a random point within the unit cube and reject the point if its outside the sphere.
vector3d random_pt_on_sphere()
{
	vector3d p;
	do
	{
		//Chooses a no. between [-1, 1]
		float randomFloat = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;
		float randomFloat2 = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;
		float randomFloat3 = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;

		//I think the minus 1 vect is just so the point p is in the scene.
		vector3d val = vector3d(randomFloat, randomFloat2, randomFloat3) - vector3d(1, 1, 1);

		p = 2.0 * (val);
	} while (p.squared_length() >= 1.0f);

	return p;
}


class lambertian : public material
{
public: 
	lambertian(const vector3d& a) : albedo(a) {};
	virtual bool scatter(const ray& ray_in, ray& scattered, const hit_record& recordedHit, vector3d& attenuation) const
	{
		vector3d target = recordedHit.p + recordedHit.normal + random_pt_on_sphere();
		scattered = ray(recordedHit.p, target - recordedHit.p);
		attenuation = albedo;
		return true;
	}

private:
	vector3d albedo;

};

//-----------------------------------------------------------------------------------------------------------

class metal : public material
{
public:
	//Albedo is a measure of how much light that hits a surface is reflected
	//Whereas attenuation is the reduction of force/effect of signal which in this case is light

	metal(const vector3d& a) : albedo(a) {}
	virtual bool scatter(const ray& ray_in, ray& scattered, const hit_record& recordedHit, vector3d& attenuation) const
	{
		vector3d reflected = reflect(unit_vector(ray_in.direction), recordedHit.normal);
		scattered = ray(recordedHit.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), recordedHit.normal) > 0);
	}

private:
	vector3d albedo;
};

vector3d reflect(const vector3d& v, const vector3d& n)
{
	//The equation used to find the reflective ray off a surface with the init direction v
	return v - (2 * dot(v, n) * n);
}


//----------------------------------------------------------------------------------------------------------

#endif