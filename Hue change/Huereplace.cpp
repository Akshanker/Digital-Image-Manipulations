#include <cstdlib>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <fstream>

#include <sstream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

////ASSIGNMENT 4- Hue Replacement- DIGITAL IMAGE - ANUSHA SHANKER///////////

using namespace std;



void RGBtoHSV(int r, int g, int b, double& h, double& s, double& v) {

	double red, green, blue;
	double maxim, minim, delta;

	red = r / 255.0; green = g / 255.0; blue = b / 255.0;  /* r, g, b to 0 - 1 scale */

	maxim = max(max(red, green), blue);
	minim = min(min(red, green), blue);

	v = maxim;        /* value is maximum of r, g, b */

	if (maxim == 0) {    /* saturation and hue 0 if value is 0 */
		s = 0;
		h = 0;
	}
	else {
		s = (maxim - minim) / maxim;           /* saturation is color purity on scale 0 - 1 */

		delta = maxim - minim;
		if (delta == 0)                    /* hue doesn't matter if saturation is 0 */
			h = 0;
		else {
			if (red == maxim)                  /* otherwise, determine hue on scale 0 - 360 */
				h = (green - blue) / delta;
			else if (green == maxim)
				h = 2.0 + (blue - red) / delta;
			else /* (blue == max) */
				h = 4.0 + (red - green) / delta;
			h = h * 60.0;
			if (h < 0)
				h = h + 360.0;
		}
	}
}

void HSVtoRGB(double H, double S, double V, double& R, double& G, double& B)
{

	//S = S / 100;
	//V = V / 100;
	float C = S * V;

	float p = fmod(H / 60, 6);


	float X = C * (1 - fabs(fmod(p, 2) - 1));

	float m = V - C;


	float r, g, b;
	if (0 <= p && p < 1)
	{
		r = C, g = X, b = 0;
	}
	else if (1 <= p && p < 2)
	{
		r = X, g = C, b = 0;
	}
	else if (2 <= p && p < 3)
	{
		r = 0, g = C, b = X;
	}
	else if (3 <= p && p < 4)
	{
		r = 0, g = X, b = C;
	}
	else if (4 <= p && p < 5)
	{
		r = X, g = 0, b = C;
	}
	else if (5 <= p && p < 6)
	{
		r = C, g = 0, b = X;
	}
	else
	{
		r = 0, g = 0, b = 0;
	}


	R = (r + m) * 255;
	G = (g + m) * 255;
	B = (b + m) * 255;




}



int main()
{
	int width1, height1, channels1, width2, height2, channels2;

	unsigned char* img1 = stbi_load("sea.jpg", &width1, &height1, &channels1, 0);
	unsigned char* img2 = stbi_load("himalaya.jpg", &width2, &height2, &channels2, 0);
	cout << "image loaded" << endl;
	unsigned char* pixmap1;
	unsigned char* pixmap2;
	unsigned char* hsv1;
	unsigned char* hsv2;
	pixmap1 = new unsigned char[height1 * width1 * 3];
	pixmap2 = new unsigned char[height2 * width2 * 3];
	hsv1 = new unsigned char[height1 * width1 * 3];
	hsv2 = new unsigned char[height2 * width2 * 3];
	//float resultR, resultG, resultB;


	for (int i = 0; i < height1; i++)
	{


		double h1, s1, v1, h2, s2, v2, r, g, b;


		for (int j = 0; j < width1; j++)
		{




			int rpos = (i * width1 + j) * 3;
			int gpos = rpos + 1;
			int bpos = rpos + 2;

			RGBtoHSV(img1[rpos], img1[gpos], img1[bpos], h1, s1, v1);
			RGBtoHSV(img2[rpos], img2[gpos], img2[bpos], h2, s2, v2);



			hsv1[rpos] = h1;
			hsv1[gpos] = s1;
			hsv1[bpos] = v1;

			hsv2[rpos] = h2;
			hsv2[gpos] = s2;
			hsv2[bpos] = v2;


			//cout << h << endl << s << v << endl;

			HSVtoRGB(h2, s2, v1, r, g, b);
			//cout << r << endl << g << endl << b << endl;

			//cout << (int)pixmap1[rpos] << endl;
			pixmap1[rpos] = (r);
			pixmap1[gpos] = (g);
			pixmap1[bpos] = (b);
			//cout << (float)pixmap1[rpos] << endl;

			//cout << pixmap1[rpos] << endl;




		}
	}



	//double h, s, v;
	//double r, g, b;
	//RGBtoHSV(71, 208, 10, h, s, v);
	//cout << (float)h << endl << s << endl << v << endl;
	//HSVtoRGB(h,s,v,r,g,b);
	//cout << r << endl << g << endl << b << endl;


	stbi_write_jpg("Seaonfire.jpg", width1, height1, 3, pixmap1, 100);


}