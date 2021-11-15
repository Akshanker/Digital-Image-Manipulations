#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include<cmath>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "Vector.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

using namespace std;

int height1, width1, channels1,height2,width2,channels2,height3,width3,channels3,height4,width4,channels4;
unsigned char* normals= stbi_load("NormalMap.jpg", &width1, &height1, &channels1, 0);
unsigned char* spec = stbi_load("specc.jpg", &width2, &height2, &channels2, 0);
unsigned char* lite = stbi_load("dark.jpg", &width3, &height3, &channels3, 0);
unsigned char* dark = stbi_load("lite.jpg", &width4, &height4, &channels4, 0);
unsigned char* pixmap;
unsigned char* normalVF;

float clamp(float x)
{
	
	if (x < 0)x = 0;
	if (x > 1)x = 1;

	return x;

}

Vector vecfield = Vector(0, 0, 0); Vector refl;
Vector light = Vector(sin(1), cos(4), 1).unitv();
Vector origin = Vector(8, -2, -3);


void main()
{
	cout << "diffuse just colors ---1" << endl;
	cout << "diffuse images ----2" << endl;

	int ch;
	cin >> ch;

	pixmap = new unsigned char[height1 * width1 * 3];
	normalVF = new unsigned char[height1 * width1 * 3];
	light =  light.unitv();

	for (int j = 0; j < height1; j++)
	{
		for (int i = 0; i < width1-1; i++)
		{
			int rps = (j * width1 + i) * 3;
			int gps = rps + 1;
			int bps = rps + 2;



			vecfield.x = normals[rps];// (2 * normals[rps] / 255) - 1;
			vecfield.y = normals[gps]; //(2 * normals[gps] / 255) - 1;
			vecfield.z = normals[bps]; //(2 * normals[bps] / 255) - 1;
			//cout << vecfield << endl;

			vecfield = vecfield.unitv();
			

			float intensity = dot(vecfield, light);
			intensity = clamp(intensity);

			refl.x = -light.x + 2 * intensity * vecfield.x;
			refl.y = -light.y + 2 * intensity * vecfield.y;
			refl.z = -light.x + 2 * intensity * vecfield.z;

			float s = dot(refl, origin);

			s = clamp(s);

			if (ch == 1)
			{
				//intensity = smoothstep(0, 1, intensity);

				pixmap[rps] = 0 * (intensity * 0 + (1 - intensity) * 1);
				pixmap[gps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				pixmap[bps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				//NormVF.push_back(vecfield);

				/*pixmap[rps] = pixmap[rps] * (1 - s) + 255 * s;
				pixmap[gps] = pixmap[gps] * (1 - s) + 255 * s;
				pixmap[bps] = pixmap[bps] * (1 - s) + 255 * s;*/
			}

			if (ch == 2)
			{
				pixmap[rps] =  (intensity * dark[rps] + (1 - intensity) * lite[rps]);
				pixmap[gps] =  (intensity * dark[gps] + (1 - intensity) * lite[gps]);
				pixmap[bps] =  (intensity * dark[bps] + (1 - intensity) * lite[bps]);

				pixmap[rps] = pixmap[rps] * (1 - s) + spec[rps] * s;
				pixmap[gps] = pixmap[gps] * (1 - s) + spec[gps] * s;
				pixmap[bps] = pixmap[bps] * (1 - s) + spec[bps] * s; 

			}

		}

	}






	stbi_write_jpg("diffuse1.jpg", width1, height1, 3, pixmap, 100);
	cout << "twar";
	

}
