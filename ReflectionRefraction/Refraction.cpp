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

int height1, width1, channels1,height2,width2,channels2,height3,width3,channels3,height4,width4,channels4,width5,height5,channels5, height6, width6, channels6;
unsigned char* normals= stbi_load("normw.png", &width1, &height1, &channels1, 0);
unsigned char* mask = stbi_load("normwmask.jpg", &width6, &height6, &channels6, 0);
unsigned char* spec = stbi_load("specc.jpg", &width2, &height2, &channels2, 0);
unsigned char* lite = stbi_load("dark.jpg", &width3, &height3, &channels3, 0);
//unsigned char* dark = stbi_load("lite.jpg", &width4, &height4, &channels4, 0);
unsigned char* env2 = stbi_load("stars.jpg", &width5, &height5, &channels5, 0);
unsigned char* env = stbi_load("merc.jpg", &width4, &height4, &channels4, 0);
unsigned char* pixmap;
unsigned char* pixmapr;
unsigned char* pixmapt;
unsigned char* normalVF;

float clamp(float x)
{
	
	if (x < 0)x = 0;
	if (x > 1)x = 1;

	return x;

}
float clamprgb(float x)
{

	if (x < 0)x = 0;
	if (x > 255)x = (int)x%255;

	return x;

}

float smoothstep(float min, float max, float x)
{
	x = (x - min) / (max - min);

	return x;
}

Vector vecfield = Vector(0, 0, 0); Vector refl;
Vector light = Vector(sin(1), cos(4), 1).unitv();
Vector eye = Vector(10, 3, -3);


void main()
{
	cout << "refract ---1" << endl;
	cout << "fresnel ----2" << endl;
	cout << "masked fresnel refr-------3" << endl;
	//cout << "reflection with mask diffuse---------4" << endl;

	int ch; 
	cin >> ch;
	//cin >> fresnel;
	eye = eye.unitv();
	pixmap = new unsigned char[height1 * width1 * 3];
	pixmapt = new unsigned char[height1 * width1 * 3];
	pixmapr = new unsigned char[height1 * width1 * 3];
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

			refl = -light + 2 * intensity * vecfield;
			refl = refl.unitv();
			/*refl.x = -light.x + 2 * intensity * vecfield.x;
			refl.y = -light.y + 2 * intensity * vecfield.y;
			refl.z = -light.x + 2 * intensity * vecfield.z;*/

			float s = dot(refl, eye);

			s = clamp(s);

			Vector dv = Vector(0, 0, 1);
			float border = 1 - dot(vecfield, dv);
			border=clamp(border);


			float dist = 10;
			Vector refl_eye = -eye + 2.0 * dot(vecfield, eye) * vecfield;

			refl_eye = refl_eye.unitv();

			float refX = abs(dist * refl.x / refl.z);
			float refY = abs(dist * refl.y / refl.z);
			refX = refX + i;
			refY = refY + j;
			refX = (int)refX % 512;
			refY = (int)refY % 512;

			int ind = (refY * width1 + refX) * 3;


			float kr = 1.1;

			float ior1 = 0.2;
			float ior2 = 1.216;
			float ior = ior1 / ior2;
			float alpha = log2(ior);

			Vector refr;
			Vector f;

			if (alpha > 0.0)
			{
				refr = alpha * (-1.0 * eye) + (1.0 - alpha) * (-1.0 * vecfield);
			}
			else
			{
				alpha = 1.0+alpha;
				f = -1.0 * eye + dot(eye, vecfield) * vecfield;
				f = f.unitv();

				refr = alpha * (-1.0 * eye) + (1, 0 - alpha) * s;

			}

			refr = refr.unitv();

			float rdist = 0.8;
			refr = rdist * (refr / refr.z);

			float RefrX = refr.x + i;
			float RefrY = refr.y + j;

			RefrX = (int)RefrX % 512;
			RefrY = (int)RefrY % 512;

			float rf = 1.3;

			float f1 = dot(eye, vecfield);
			float f2 = 1 - f1;// sqrt(1.0 - pow(f1, 2.0));
			float fresnel = 0.9;
			float rr;

			if (f2 < fresnel)
			{
				rr = 0.01 * (1 - (f2 / fresnel));
				//cout << rr << endl;
			}
			else
			{
				rr = (f2 - 0.3) / (0.9 - 0.3);// smoothstep(0.3, 0.9, f2)* (1.0 / fresnel);//
				clamp(rr);
				
				
			}



			

			 if (ch == 6)
			{
				//intensity = smoothstep(0, 1, intensity);

				pixmap[rps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				pixmap[gps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				pixmap[bps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				//NormVF.push_back(vecfield);

				/*pixmap[rps] = pixmap[rps] * (1 - s) + 255 * s;
				pixmap[gps] = pixmap[gps] * (1 - s) + 255 * s;
				pixmap[bps] = pixmap[bps] * (1 - s) + 255 * s;*/
			}

			/*if (ch == 2)
			{
				pixmap[rps] =  (intensity * dark[rps] + (1 - intensity) * lite[rps]);
				pixmap[gps] =  (intensity * dark[gps] + (1 - intensity) * lite[gps]);
				pixmap[bps] =  (intensity * dark[bps] + (1 - intensity) * lite[bps]);

				pixmap[rps] = pixmap[rps] * (1 - s) + spec[rps] * s;
				pixmap[gps] = pixmap[gps] * (1 - s) + spec[gps] * s;
				pixmap[bps] = pixmap[bps] * (1 - s) + spec[bps] * s; 

			}

			if (ch == 3)
			{
				

				pixmap[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmap[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmap[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmap[rps] = pixmap[rps] * (1 - s) + 1 * s;
				pixmap[gps] = pixmap[gps] * (1 - s) + 1 * s;
				pixmap[bps] = pixmap[bps] * (1 - s) + 1 * s;

				pixmap[rps] = pixmap[rps] * (1 - kr) + env[ind] * kr;
				pixmap[gps] = pixmap[gps] * (1 - kr) + env[ind+1] * kr;
				pixmap[bps] = pixmap[bps] * (1 - kr) + env[ind+2] * kr;


				pixmap[rps] = clamprgb(pixmap[rps]);
				pixmap[gps] = clamprgb(pixmap[gps]);
				pixmap[bps] = clamprgb(pixmap[bps]);

				if ((normals[rps] == 255 && normals[gps] == 255 && normals[bps] == 255))
				{
					pixmap[rps] = 0;
					pixmap[gps] = 0;
					pixmap[bps] = 0;
				}

				/*if ((mask[rps] == 0 && mask[gps] == 0 && mask[bps] == 0))
				{
					pixmap[rps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[gps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[bps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				}
				
			}*/
			if (ch == 1)
			{
				
				pixmap[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmap[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmap[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmap[rps] = pixmap[rps] * (1 - rf) + env2[ind] * rf;
				pixmap[gps] = pixmap[gps] * (1 - rf) + env2[ind + 1] * rf;
				pixmap[bps] = pixmap[bps] * (1 - rf) + env2[ind + 2] * rf;


				pixmap[rps] = clamprgb(pixmap[rps]);
				pixmap[gps] = clamprgb(pixmap[gps]);
				pixmap[bps] = clamprgb(pixmap[bps]);
			}

			if (ch == 2)
			{
				pixmapt[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapt[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapt[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmapt[rps] = pixmapt[rps] * (1 - s) + 1 * s;
				pixmapt[gps] = pixmapt[gps] * (1 - s) + 0 * s;
				pixmapt[bps] = pixmapt[bps] * (1 - s) + 0 * s;

				pixmapt[rps] = pixmapt[rps] * (1 - kr) + env2[ind] * kr;
				pixmapt[gps] = pixmapt[gps] * (1 - kr) + env2[ind + 1] * kr;
				pixmapt[bps] = pixmapt[bps] * (1 - kr) + env2[ind + 2] * kr;


				pixmapr[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapr[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapr[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmapr[rps] = pixmapr[rps] * (1 - rf) + env[ind] * rf;
				pixmapr[gps] = pixmapr[gps] * (1 - rf) + env[ind + 1] * rf;
				pixmapr[bps] = pixmapr[bps] * (1 - rf) + env[ind + 2] * rf;

				pixmap[rps] = rr * pixmapr[rps] + (1 - rr) * pixmapt[rps];
				pixmap[gps] = rr * pixmapr[gps] + (1 - rr) * pixmapt[gps];
				pixmap[bps] = rr * pixmapr[bps] + (1 - rr) * pixmapt[bps];


				/*if ((normals[rps] == 255 && normals[gps] == 255 && normals[bps] == 255))
				{
					pixmap[rps] = 0;
					pixmap[gps] = 0;
					pixmap[bps] = 0;
				}*/

				/*pixmap[rps] = rr * env2[rps] + (1 - rr) * env[rps];
				pixmap[gps] = rr * env2[gps] + (1 - rr) * env[gps];
				pixmap[bps] = rr * env2[bps] + (1 - rr) * env[bps];*/

				/*if ((mask[rps] == 0 && mask[gps] == 0 && mask[bps] == 0))
				{
					pixmap[rps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[gps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[bps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				}*/

				pixmap[rps] = clamprgb(pixmap[rps]);
				pixmap[gps] = clamprgb(pixmap[gps]);
				pixmap[bps] = clamprgb(pixmap[bps]);





			}
			if (ch == 3)
			{
				pixmapt[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapt[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapt[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmapt[rps] = pixmapt[rps] * (1 - s) + 1 * s;
				pixmapt[gps] = pixmapt[gps] * (1 - s) + 0 * s;
				pixmapt[bps] = pixmapt[bps] * (1 - s) + 0 * s;

				pixmapt[rps] = pixmapt[rps] * (1 - kr) + env2[ind] * kr;
				pixmapt[gps] = pixmapt[gps] * (1 - kr) + env2[ind + 1] * kr;
				pixmapt[bps] = pixmapt[bps] * (1 - kr) + env2[ind + 2] * kr;


				pixmapr[rps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapr[gps] = (intensity * 0 + (1 - intensity) * 1);
				pixmapr[bps] = (intensity * 0 + (1 - intensity) * 1);

				pixmapr[rps] = pixmapr[rps] * (1 - rf) + env[ind] * rf;
				pixmapr[gps] = pixmapr[gps] * (1 - rf) + env[ind + 1] * rf;
				pixmapr[bps] = pixmapr[bps] * (1 - rf) + env[ind + 2] * rf;

				pixmap[rps] = rr * pixmapr[rps] + (1 - rr) * pixmapt[rps];
				pixmap[gps] = rr * pixmapr[gps] + (1 - rr) * pixmapt[gps];
				pixmap[bps] = rr * pixmapr[bps] + (1 - rr) * pixmapt[bps];


				if ((normals[rps] == 255 && normals[gps] == 255 && normals[bps] == 255))
				{
					pixmap[rps] = 0;
					pixmap[gps] = 0;
					pixmap[bps] = 0;
				}

				/*pixmap[rps] = rr * env2[rps] + (1 - rr) * env[rps];
				pixmap[gps] = rr * env2[gps] + (1 - rr) * env[gps];
				pixmap[bps] = rr * env2[bps] + (1 - rr) * env[bps];*/

				if ((mask[rps] == 0 && mask[gps] == 0 && mask[bps] == 0))
				{
					pixmap[rps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[gps] = 255 * (intensity * 0 + (1 - intensity) * 1);
					pixmap[bps] = 255 * (intensity * 0 + (1 - intensity) * 1);
				}

				pixmap[rps] = clamprgb(pixmap[rps]);
				pixmap[gps] = clamprgb(pixmap[gps]);
				pixmap[bps] = clamprgb(pixmap[bps]);
			}
			

		}

	}






	stbi_write_jpg("diffuse1.jpg", width1, height1, 3, pixmap, 100);
	cout << "twar";
	

}
