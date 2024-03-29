// RayTracer1.1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include "TGAFormat.h"
#include "Vector3d.h"
#include "Ray_new.h"
#include "hitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include <float.h>
#include <fstream>

//This uses the rejection method which is simply picks a random point within the unit cube and reject the point if its outside the sphere.
vector3d random_pt_on_sphere()
{
	vector3d p;
	do 
	{
		//Chooses a no between [-1, 1]
		float randomFloat = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;
		float randomFloat2 = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;
		float randomFloat3 = ((static_cast <float> (rand()) * 2) / static_cast <float> (RAND_MAX)) - 1.0f;
		
		//I think the minus 1 vect is just so the point p is in the scene.
		vector3d val = vector3d(randomFloat, randomFloat2, randomFloat3) - vector3d(1, 1, 1);

		p = 2.0 * (val);
	} while (p.squared_length() >= 1.0f);

	return p;

}

vector3d colour2(const ray& r, hitable_object *world, int& depth)
{
	hit_record recorded_hit;

	float min = 0.001f;
	float max = FLT_MAX;

	if (world->hit(r, min, max, recorded_hit))
	{

		//This is a formula used to calculate the point R on the unit sphere
		vector3d target = recorded_hit.p + recorded_hit.normal + random_pt_on_sphere();
		
		//The multiplyer is the light buoncing rate
		ray ray1 = ray(recorded_hit.p, target - recorded_hit.p);
		return 0.8f * colour2(ray1, world, depth);

		//This is returning the normal vector, calculated from the center of the circle to the point p where the sphere is hit.
		//return 0.5f * vector3d(recorded_hit.normal.x() + 1, recorded_hit.normal.y() + 1, recorded_hit.normal.z() + 1);
	}
	else
	{
		vector3d unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vector3d(1.0f, 1.0f, 1.0f) + (t * vector3d(0.5f, 0.7f, 1.0f));
	}

}

int main()
{
	//char filename[] = "FirstSphereRender.tga";
	//unsigned char Colour[5];
	//
	//const char *FileName = filename;
	int Width = 200;
	int Height = 100;
	int Depth = 100;
	
	//Colour[0] = 225;
	//Colour[1] = 0;
	//Colour[2] = 20;
	//Colour[3] = 255;
	//Colour[4] = '\0';
	//
	//int channels = 4;
	//
	////WriteTGA(FileName, Colour, Width, Height, channels);

	ofstream img("picture.ppm");

	img << "P3\n" << endl;
	img << Width << " " << Height << endl;
	img << "\n255" << endl;

	vector3d lower_left_corner(-2.0f, -1.0f, -1.0f);
	vector3d horizontal(4.0f, 0.0f, 0.0f);
	vector3d vertical(0.0f, 2.0f, 0.0f);
	vector3d origin(0.0f, 0.0f, 0.0f);

	hitable_object *objects[4];

	vector3d center1(0, 0.0, -1.0f);
	vector3d center2(-1.0f, -0.1, -1.0f);
	vector3d center3(1.0f, 0.3, -1.0f);
	vector3d center4(0.0f, -100.5f, -1.0f);

	objects[0] = new sphere(center1, 0.4f);
	objects[1] = new sphere(center2, 0.3f);
	objects[2] = new sphere(center3, 0.2f);
	objects[3] = new sphere(center4, 100.0f);

	hitable_object *world = new hitable_list(objects, 4);
	camera camera;

	for (int j = Height - 1; j >= 0; j--)
	{
		for(int i = 0; i < Width; i++)
		{
			vector3d colour_new(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < Depth; s++)
			{

				float randomFloat = static_cast <float>(rand() * 2.0f) / (static_cast <float>(RAND_MAX));
				float randomFloat2 = static_cast <float>(rand() * 2.0f) / (static_cast <float>(RAND_MAX));
				//The rand() here creates a blur effect if rand is taken as an int over 1
				float u = float(i + randomFloat) / float(Width);
				float v = float(j + randomFloat2) / float(Height);

				//Ray traverses through the scene to colour every pixel
				ray r = camera.getRay(u, v);

				//0.2 along r
				//No idea why this is being set here
				vector3d p = r.point_at_parameter(2.0f);
				
				//Changing the colour of each pixel depending on whether the ray hit anything in the scene
				//What is happening with each object... How are they being tested as an iterative process.
				colour_new = colour_new + colour2(r, world, Depth);

			}

			colour_new = colour_new / float(Depth);

			//Square rooting because we needed to raise the colour to the power 0.5 to gamma correct. This makes the image a little less dark and intense.
			colour_new = vector3d(sqrt(colour_new[0]), sqrt(colour_new[1]), sqrt(colour_new[2]));
			
			int ir = int(255.99 * colour_new[0]);
			int ig = int(255.99 * colour_new[1]);
			int ib = int(255.99 * colour_new[2]);

			img << ir << " " << ig << " " << ib << "\n";
			
		}
	}

	return 0;
}
