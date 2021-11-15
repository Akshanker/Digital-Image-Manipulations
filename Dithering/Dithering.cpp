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



int clamp(float x)
{
	if (x < 0) { x = 0; }
	if (x > 255) { x = fmod(x, 255); }
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
	int thresh[4][4];

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			int ran = rand() % (255 + 1);
			thresh[x][y] = ran;
		}
	}



	int width1, height1, channels1, width2, height2, channels2;

	int deschannels = 4;
	unsigned char* img1 = stbi_load("city.jpg", &width1, &height1, &channels1, 0);
	float* img3;// = stbi_load("city.jpg", &width2, &height2, &channels2, 0);
	unsigned char* img2 = stbi_load("neb.jpg", &width2, &height2, &channels2, 0);
	cout << "image loaded" << endl;
	unsigned char* pixmap1;
	unsigned char* pixmap2;
	unsigned char* pixmap3;
	unsigned char* pixmap;
	unsigned char* hsv1;
	unsigned char* hsv2;
	pixmap1 = new unsigned char[height1 * width1 * 3];
	pixmap2 = new unsigned char[height1 * width1 * 3];
	pixmap3 = new unsigned char[height1 * width1 * 3];
	pixmap = new unsigned char[height1 * width1 * 3];
	img3 = new float[height1 * width1 * 3];
	int ch;
	cout << "Random dithering BW  --- 1" << endl;
	cout << "Random Dithering Color --- 2" << endl;
	cout << "Floyd Steinberg Error     --- 3" << endl;
	cout << "Ordered Dithering BW        --- 4" << endl;
	cout << "Ordered Dithering Color       --- 5" << endl;
	

	cin >> ch;

	for (int j = 0; j < height1; j++)
	{
		for (int i = 0; i < width1; i++)
		{
			int rps = (j * width1 + i) * 3;
			int gps = rps + 1;
			int bps = rps + 2;

			img3[rps] = (float)img1[rps] / 255.0;
			img3[gps] = (float)img1[gps] / 255.0;
			img3[bps] = (float)img1[bps] / 255.0;
		}
	}



	for (int j = 1; j < height1-1 ; j++)
	{
		for (int i = 1; i < width1 ; i++)
		{
			int  R = 0, G = 0, B = 0;
			float Rval = 0, Gval = 0, Bval = 0;
			float Alpha = 0.0;
			


			//cout << x << endl;

			int rps = (j * width1 + i) * 3;
			int gps = rps + 1;
			int bps = rps + 2;

			int rp = ((j+0.5) * width1 + (i+0.5)) * 3;
			int gp = rp + 1;
			int bp = rp + 2;

			
			//img1[rps1] = img1[rps1];

			//cout << (float)img1[rps1] <<"\n"<<"dfsf"<< endl;
			int rps1 = ((j)*width1 + (i + 1)) * 3;
			int gps1 = rps1 + 1;
			int bps1 = rps1 + 2;

			//img1[rps1] = img1[rps1];

			//cout << (float)img1[rps1] <<"\n"<<"dfsf"<< endl;


			int rps2 = ((j + 1) * width1 + (i - 1)) * 3;
			int gps2 = rps2 + 1;
			int bps2 = rps2 + 2;

			int rps3 = ((j + 1) * width1 + i) * 3;
			int gps3 = rps3 + 1;
			int bps3 = rps3 + 2;

			int rps4 = ((j + 1) * width1 + (i + 1)) * 3;
			int gps4 = rps4 + 1;
			int bps4 = rps4 + 2;



			if (ch == 1)
			{
				
				float m = -0.5, n = 0.5;
				int M = m + fmod(rand(), (n - m + 1));

				int rp = ((j + M) * width1 + (i + M)) * 3;
				int gp = rp + 1;
				int bp = rp + 2;
				int randm = rand() % 256;
				
				if ((img1[rp] + img1[gp] + img1[bp]) / 2 < randm) { Rval = 0; Gval = 0; Bval = 0; }
				else { Rval = 255; Gval = 255; Bval = 255; }
			}
			if (ch == 2)
			{

				float m = -0.5, n = 0.5;
				int M = m + fmod(rand(), (n - m + 1));

				int rp = ((j + M) * width1 + (i + M)) * 3;
				int gp = rp + 1;
				int bp = rp + 2;
				int randm = rand() % 255;

				if ((img1[rps] + img1[gps] + img1[bps]) / 3 < randm) 
				{ Rval = 0; Gval = 0; Bval = 0; }
				else 
				{
					Rval = img1[rps];
					Gval = img1[gps];
					Bval = img1[bps];
				}
			}
			if (ch == 3)
			{
				int factor = 1;
				//cout << (float)img1[rps1] << endl;
				int tmpr = (img3[rps] + 0.5);// round(factor * img1[rps] / 255)* factor * 255;
				int tmpg = (img3[gps]+0.5);//round(factor * img1[gps] / 255) * factor * 255;
				int tmpb = (img3[bps]+0.5);//round(factor * img1[bps] / 255) * factor * 255;
				
				float eR = img3[rps] - tmpr;
				float eG = img3[gps] - tmpg;
				float eB = img3[bps] - tmpb;
				//cout << eR << endl;
				//cout << (float)img1[rps] << endl;
				//cout << tmpr << endl;
				
				//img1[rps] = tmpr;
				//img1[gps] = tmpg;
				//img1[bps] = tmpb;
				//cout << (float)img1[rps4] << endl;
				img3[rps1] = (img3[rps1] + (eR * (7.0 / 16)));
				img3[gps1] = (img3[gps1] + (eG * (7.0 / 16)));
				img3[bps1] = (img3[bps1] + (eB * (7.0 / 16)));

				img3[rps2] = (img3[rps2] + (eR * (3.0 / 16)));
				img3[gps2] = (img3[gps2] + (eG * (3.0 / 16)));
				img3[bps2] = (img3[bps2] + (eB * (3.0 / 16)));

				img3[rps3] = (img3[rps3] + (eR * (5.0 / 16)));
				img3[gps3] = (img3[gps3] + (eG * (5.0 / 16)));
				img3[bps3] = (img3[bps3] + (eB * (5.0 / 16)));

				img3[rps4] = (img3[rps4] + (eR * (1.0 / 16)));
				img3[gps4] = (img3[gps4] + (eG * (1.0 / 16)));
				img3[bps4] = (img3[bps4] + (eB * (1.0 / 16)));
				
				
				//cout << eR * (1.0 / 16) << endl;
				//cout << (float)img1[rps4] << endl;

			}
			if (ch == 4)
			{
				if ((img1[rps]+img1[gps]+img1[bps])/3 < thresh[i%4][j%4])// && img1[gps] < thresh[i % 4][j % 4] && img1[bps] < thresh[i % 4][j % 4])
				{
					Rval = 0;
					Gval = 0;
					Bval = 0;
				}
				else
				{
					Rval = 255;
					Gval = 255;
					Bval = 255;
				}





			}

			if (ch == 5)
			{
				if ((img1[rps] + img1[gps] + img1[bps]) / 3 < thresh[i % 4][j % 4])// && img1[gps] < thresh[i % 4][j % 4] && img1[bps] < thresh[i % 4][j % 4])
				{
					Rval = 0;
					Gval = 0;
					Bval = 0;
				}
				else
				{
					Rval = img1[rps];
					Gval = img1[gps];
					Bval = img1[bps];
				}





			}





			pixmap2[rps] = Rval;
			pixmap2[gps] = Gval;
			pixmap2[bps] = Bval;

			pixmap3[rps] = (img3[rps]);
			pixmap3[gps] = (img3[gps]);
			pixmap3[bps] = (img3[bps]);

			


		}

	}


	for (int j = 0; j < height1; j++)
	{
		for (int i = 0; i < width1; i++)
		{
			int rps = (j * width1 + i) * 3;
			int gps = rps + 1;
			int bps = rps + 2;

			pixmap1[rps] = img3[rps] * 255;
			pixmap1[gps] = img3[gps] * 255;
			pixmap1[bps] = img3[bps] * 255;
		}
	}




	cout << "checking" << endl;
	if (ch == 1||ch==2||ch==4||ch==5)
	{
		stbi_write_jpg("result.jpg", width1, height1, 3, pixmap2, 100);
	}
	if (ch == 3) 
	{
		stbi_write_jpg("result2.jpg", width1, height1, 3, pixmap1, 100);
	}

}