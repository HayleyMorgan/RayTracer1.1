#include "pch.h"
#include "Sphere.h"

bool sphere::hit(const ray& r, float& t_min, float& t_max, hit_record& record_hit) const
{
	vector3d oc_vector = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(oc_vector, r.direction());
	float c = dot(oc_vector, oc_vector) - (radius * radius);

	float discriminant = (b * b) - (4 * a * c);

	//Making sure we are not looking for complex roots
	if (discriminant > 0)
	{
		float temp;
		//This is the only one that is ever positive

		float sqrt_discr = sqrt(discriminant);
		temp = (-b - sqrt_discr) / (2 * a);

		//Checking that t is within the boundaries
		if (temp < t_max && temp > t_min)
		{
			record_hit.t = temp;
			record_hit.p = r.point_at_parameter(record_hit.t);
			record_hit.normal = (record_hit.p - center);
			return true;
		}

		temp = (-b + sqrt_discr) / (2 * a);
		if (temp < t_max && temp > t_min)
		{
			//Recording the values found for the collision
			//I feel like the problem is connected to looking for the nearest collision... How and when am I searching for the smallest t value on the ray and how are these compared in this arciteture
			record_hit.t = temp;
			record_hit.p = r.point_at_parameter(record_hit.t);
			record_hit.normal = (record_hit.p - center);
			return true;
		}


	}
	return false;

}


