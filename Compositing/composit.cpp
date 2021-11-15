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



int clamp(int x)
{
	if (x < 0) { x = 0; }
	if (x > 255) { x = x % 255; }
	return x;
}

int clamp2(int x)
{
	if (x < 0) { x = 0; }
	if (x >= 1) { x = x % 255; }
	return x;
}



int clamp1(int x)
{
	if (x >= 1) { x = 1; }

	return x;
}

int main()
{
	int width1, height1, channels1, width2, height2, channels2;

	int deschannels = 4;
	unsigned char* img1 = stbi_load("bby.jpg", &width1, &height1, &channels1, 0);
	unsigned char* img3 = stbi_load("alph.jpg", &width2, &height2, &channels2, 0);
	unsigned char* img2 = stbi_load("neb.jpg", &width2, &height2, &channels2, 0);
	unsigned char* img = stbi_load("bby2.jpg", &width1, &height1, &channels1, 0);
	cout << "image loaded" << endl;
	unsigned char* pixmap1;
	unsigned char* pixmap2;
	unsigned char* pixmap3;
	unsigned char* pixmap;
	unsigned char* hsv1;
	unsigned char* hsv2;
	pixmap1 = new unsigned char[height1 * width1 * 4];
	pixmap2 = new unsigned char[height1 * width1 * 4];
	pixmap3 = new unsigned char[height1 * width1 * 3];
	pixmap = new unsigned char[height1 * width1 * 3];

	int ch;
	cout << "Difference  --- 1" << endl;
	cout << "Light color --- 2" << endl;
	cout << "Darken      --- 3" << endl;
	cout << "Subtract    --- 4" << endl;
	cout << "Linear Burn --- 5" << endl;
	cout << "Normal(over)--- 6" << endl;
	cout << "Multiply    --- 7" << endl;
	cout << "Exclusion   --- 8" << endl;
	cout << "Hard Mix    --- 9" << endl;
	cout << "Screen      --- 10" << endl;
	cout << "Greenscreen --- 11" << endl;

	cin >> ch;





	for (int i = 0; i < height1; i++)
	{
		for (int j = 0; j < width1; j++)
		{
			int  R = 0, G = 0, B = 0;
			float Rval = 0, Gval = 0, Bval = 0;
			float Alpha = 0.0;
			int rp = (i * width1 + j) * 4;
			int gp = rp + 1;
			int bp = rp + 2;
			int ap = rp + 3;

			int rps = (i * width1 + j) * 3;
			int gps = rps + 1;
			int bps = rps + 2;

			if (ch == 1)
			{

				Rval = 0.54 * abs((img2[rps] - img1[rps])) + (1 - 0.54) * img1[rps];
				Gval = 0.54 * abs((img2[gps] - img1[gps])) + (1 - 0.54) * img1[gps];
				Bval = 0.54 * abs((img2[bps] - img1[bps])) + (1 - 0.54) * img1[bps];
				Alpha = 0.54 + (1 - 0.54) * 1;
			}

			if (ch == 2)
			{

				Rval = 0.6 * max(img2[rps], img1[rps]) + (1 - 0.6) * img1[rps];
				Gval = 0.6 * max(img2[gps], img1[gps]) + (1 - 0.6) * img1[gps];
				Bval = 0.6 * max(img2[bps], img1[bps]) + (1 - 0.6) * img1[bps];
				Alpha = 0.6 + (1 - 0.6) * 1;
			}

			if (ch == 3)
			{

				Rval = 0.7 * min(img2[rps], img1[rps]) + (1 - 0.7) * img1[rps];
				Gval = 0.7 * min(img2[gps], img1[gps]) + (1 - 0.7) * img1[gps];
				Bval = 0.7 * min(img2[bps], img1[bps]) + (1 - 0.7) * img1[bps];
				Alpha = 0.7 + (1 - 0.7) * 1;
			}

			if (ch == 4)
			{

				Rval = 0.5 * ((img1[rps] - img2[rps])) + (1 - 0.5) * img1[rps];
				Gval = 0.5 * ((img1[gps] - img2[gps])) + (1 - 0.5) * img1[gps];
				Bval = 0.5 * ((img1[bps] - img2[bps])) + (1 - 0.5) * img1[bps];
				Alpha = 0.5 + (1 - 0.5) * 1;
			}

			if (ch == 5)
			{

				Rval = 0.6 * ((img1[rps] + img2[rps]) - 255) + (1 - 0.6) * img1[rps];
				Gval = 0.6 * ((img1[gps] + img2[gps]) - 255) + (1 - 0.6) * img1[gps];
				Bval = 0.6 * ((img1[bps] + img2[bps]) - 255) + (1 - 0.6) * img1[bps];
				Alpha = 0.6 + (1 - 0.6) * 1;
			}



			if (ch == 6)
			{

				Rval = 0.4 * ((img2[rps])) + (1 - 0.4) * img1[rps];
				Gval = 0.4 * ((img2[gps])) + (1 - 0.4) * img1[gps];
				Bval = 0.4 * ((img2[bps])) + (1 - 0.4) * img1[bps];
				Alpha = 0.4 + (1 - 0.4) * 1;
			}

			if (ch == 7)
			{

				Rval = 0.7 * ((float)img1[rps] / 255 * (float)img2[rps]) + (1 - 0.7) * img1[rps];
				Gval = 0.7 * ((float)img1[gps] / 255 * (float)img2[gps]) + (1 - 0.7) * img1[gps];
				Bval = 0.7 * ((float)img1[bps] / 255 * (float)img2[bps]) + (1 - 0.7) * img1[bps];
				Alpha = 0.7 + (1 - 0.7) * 1;
			}

			if (ch == 8)
			{

				Rval = 0.7 * (img1[rps] + img2[rps] - 2 * (float)img1[rps] / 255 * (float)img2[rps]) + (1 - 0.7) * img1[rps];
				Gval = 0.7 * (img1[gps] + img2[gps] - 2 * (float)img1[gps] / 255 * (float)img2[gps]) + (1 - 0.7) * img1[gps];
				Bval = 0.7 * (img1[bps] + img2[bps] - 2 * (float)img1[bps] / 255 * (float)img2[bps]) + (1 - 0.7) * img1[bps];
				Alpha = 0.7 + (1 - 0.7) * 1;
			}

			if (ch == 9)
			{
				if (img2[rps] < 255 - img1[rps] && img2[gps] < 255 - img1[gps] && img2[bps] < 255 - img1[bps])
				{
					Rval = 0; //0.7 * (img1[rps] + 2 * (float)img2[rps] / 255 - 1) + (1 - 0.7) * img1[rps];
					Gval = 0;// 0.7 * (img1[gps] + 2 * (float)img2[gps] / 255 - 1) + (1 - 0.7) * img1[gps];
					Bval = 0;// 0.7 * (img1[bps] + 2 * (float)img2[bps] / 255 - 1) + (1 - 0.7) * img1[bps];
					Alpha = 0.7 + (1 - 0.7) * 1;
				}
				if (img2[rps] > 255 - img1[rps] && img2[gps] > 255 - img1[gps] && img2[bps] > 255 - img1[bps])
				{
					Rval = 255; //0.7 * (img1[rps] + 2 * (float)img2[rps] / 255 - 1) + (1 - 0.7) * img1[rps];
					Gval = 255;// 0.7 * (img1[gps] + 2 * (float)img2[gps] / 255 - 1) + (1 - 0.7) * img1[gps];
					Bval = 255;// 0.7 * (img1[bps] + 2 * (float)img2[bps] / 255 - 1) + (1 - 0.7) * img1[bps];
					Alpha = 0.7 + (1 - 0.7) * 1;
				}
			}
			if (ch == 10)
			{

				Rval = 0.7 * (255-(255-img2[rps]) * (255-img1[rps])/255 ) + (1 - 0.7) * img1[rps];
				Gval = 0.7 * (255-(255-img2[gps]) * (255-img1[gps])/255 ) + (1 - 0.7) * img1[gps];
				Bval = 0.7 * (255-(255-img2[bps]) * (255-img1[bps])/255  )+ (1 - 0.7) * img1[bps];
				Alpha = 0.7 + (1 - 0.7) * 1;
			}
			
			

			if (ch == 11)
			{
				int tmpr1 = img3[rps] / 255;
				int tmpg1 = img3[gps] / 255;
				int tmpb1 = img3[bps] / 255;
				//if (tmpr1 == 255) { tmpr1 = 1; }
				//if (tmpg1 == 255) { tmpg1 = 1; }
				//if (tmpb1 == 255) { tmpb1 = 1; }

				if (tmpr1 == 0 && tmpg1 == 0 && tmpb1 == 0)
				{
					Rval = img2[rps];
					Gval = img2[gps];
					Bval = img2[bps];
				}

				else
				{
					if (tmpr1 == 1 && tmpg1 == 1 && tmpb1 == 1)
					{
						Rval = img[rps];
						Gval = img[gps];
						Bval = img[bps];
					}
					else
					{

						float tmpr = 1 * ((img[rps])) + (1 - 1) * img2[rps];
						float tmpg = 1 * ((img[gps])) + (1 - 1) * img2[gps];
						float tmpb = 1 * ((img[bps])) + (1 - 1) * img2[bps];

						Alpha = (Gval - img2[gps]) / (img[gps] - img2[gps]);

						Rval = tmpr / Alpha;
						Gval = tmpg / Alpha;
						Bval = tmpb / Alpha;
					}
				}

				/*else
				{
					Rval = img1[rps]*img2[rps]/2;
					Gval = img1[gps]*img2[gps]/2;
					Bval = img1[bps]*img2[bps]/2;
				}*/
				//Rval = 0.4 * ((img2[rps])) + (1 - 0.4) * img1[rps];
				//Gval = 0.4 * ((img2[gps])) + (1 - 0.4) * img1[gps];
				//Bval = 0.4 * ((img2[bps])) + (1 - 0.4) * img1[bps];
				//Alpha = 0.4 + (1 - 0.4) * 1;
				//cout << tmpr1 << endl;
			}
			

			R = (int)Rval;
			G = (int)Gval;
			B = (int)Bval;




			pixmap3[rps] = clamp(R);
			pixmap3[gps] = clamp(G);
			pixmap3[bps] = clamp(B);

			//pixmap3[ap] = Alpha;


		}

	}







	cout << "checking" << endl;


	stbi_write_png("result.png", width1, height1, 3, pixmap3, width1 * 3);


}