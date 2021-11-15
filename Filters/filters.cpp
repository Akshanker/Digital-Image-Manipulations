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

////ASSIGNMENT 5- Filters- DIGITAL IMAGE - ANUSHA SHANKER///////////

using namespace std;

int mod(int a, int b) { return (a % b + b) % b; }

float vEkernel[3][3] = { {0,1,0},{0,0,0},{0,-1,0} };
float hEkernel[3][3] = { {0,0,0},{1,0,-1},{0,0,0} };

float edge[3][3] = { {1,0,-1},{0,0,0},{-1,0,1} };

float edge1[3][3] = { {0,1,0},{1,-4,1},{0,1,0} };



void genKernel(float MBkernel[5][5], int h, int w)
{
	//float MBkernel[3][3];
	float sigma = 30;
	float sum = 0;


	//random filter kernel generation
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)

		{
			float r = sqrt(i * i + j * j);
			float rad = 30;
			MBkernel[i][j] = 1;// exp(-(r * r) / (2 * sigma * sigma)) / (2 * M_PI) * sigma * sigma;
			if (MBkernel[i][j] < 0) { MBkernel[i][j] = 0; }
			sum += MBkernel[i][j];
		}
	}

	//normalizing
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			MBkernel[i][j] = MBkernel[i][j] / sum;
		}
	}

	//cout << sum << endl;
	//checking
	float sum1 = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			sum1 += MBkernel[i][j];
		}
	}
	//cout << sum1 << endl;
}






int main()
{
	int width, height, channels1, width2, height2, channels2;

	int ch;
	cout << "Gaussian blur   ---    1" << endl;
	cout << "Emboss   ---    2" << endl;
	cout << "Dilation   ---    3" << endl;
	cout << "Erosion   ---    4" << endl;
	cout << "Edgy Sketchy   ---    5" << endl;

	cin >> ch;

	const int h = 5, w = 5, m = 3, n = 3;
	int llim = -(w - 1) / 2;
	int ulim = (w - 1) / 2;
	int llim1 = -(m - 1) / 2;
	int ulim1 = (n - 1) / 2;

	int frowc = (w - 1) / 2;
	int fcolc = (h - 1) / 2;
	int frowc1 = (m - 1) / 2;
	int fcolc1 = (n - 1) / 2;
	float MBkernel[5][5];

	//unsigned char* img1 = stbi_load("cat.jpg", &width, &height, &channels1, 0);
	unsigned char* img2 = stbi_load("owllss.jpg", &width, &height, &channels2, 0);
	//cout << "image loaded" << endl;
	unsigned char* pixmap1;
	unsigned char* pixmap2;
	pixmap1 = new unsigned char[height * width * 3];
	pixmap2 = new unsigned char[height * width * 3];

	genKernel(MBkernel, h, w);










	float resultR, resultG, resultB;


	for (int i = 0; i < height; i++)
	{


		for (int j = 0; j < width; j++)
		{
			int Rval, Gval, Bval;
			if (ch == 1 || ch == 2 || ch == 5) { Rval = 0, Gval = 0, Bval = 0; }
			if (ch == 3) { Rval = -9999, Gval = -9999, Bval = -9999; }
			if (ch == 4) { Rval = 1000, Gval = 1000, Bval = 1000; }
			int rpos = (i * width + j) * 3;
			int gpos = rpos + 1;
			int bpos = rpos + 2;

			if (ch == 1)
			{
				for (int a = llim; a <= ulim; a++)
				{
					for (int b = llim; b <= ulim; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval += img2[rpos1] * MBkernel[frowc + a][frowc + b];
						Gval += img2[gpos1] * MBkernel[frowc + a][frowc + b];
						Bval += img2[bpos1] * MBkernel[frowc + a][frowc + b];


					}

				}




				pixmap2[rpos] = Rval;
				pixmap2[gpos] = Gval;
				pixmap2[bpos] = Bval;
			}







			if (ch == 2)
			{
				for (int a = llim1; a <= ulim1; a++)
				{
					for (int b = llim1; b <= ulim1; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval += img2[rpos1] * vEkernel[frowc1 + a][frowc1 + b];
						Gval += img2[gpos1] * vEkernel[frowc1 + a][frowc1 + b];
						Bval += img2[bpos1] * vEkernel[frowc1 + a][frowc1 + b];


					}

				}


				for (int a = llim1; a <= ulim1; a++)
				{
					for (int b = llim1; b <= ulim1; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval += img2[rpos1] * hEkernel[frowc1 + a][frowc1 + b];
						Gval += img2[gpos1] * hEkernel[frowc1 + a][frowc1 + b];
						Bval += img2[bpos1] * hEkernel[frowc1 + a][frowc1 + b];


					}

				}





				pixmap2[rpos] = (Rval + 255) / 2;// abs(mod(Rval, 255));
				pixmap2[gpos] = (Gval + 255) / 2;// abs(mod(Gval, 255));
				pixmap2[bpos] = (Bval + 255) / 2;// abs(mod(Bval, 255));
			}



			if (ch == 3)
			{
				for (int a = llim; a <= ulim; a++)
				{
					for (int b = llim; b <= ulim; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval = fmax(Rval, img2[rpos1]);
						Gval = fmax(Gval, img2[gpos1]);
						Bval = fmax(Bval, img2[bpos1]);


					}


				}

				pixmap2[rpos] = Rval;
				pixmap2[gpos] = Gval;
				pixmap2[bpos] = Bval;

			}


			if (ch == 4)
			{
				for (int a = llim; a <= ulim; a++)
				{
					for (int b = llim; b <= ulim; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval = fmin(Rval, img2[rpos1]);
						Gval = fmin(Gval, img2[gpos1]);
						Bval = fmin(Bval, img2[bpos1]);


					}

				}



				pixmap2[rpos] = Rval;
				pixmap2[gpos] = Gval;
				pixmap2[bpos] = Bval;

			}

			if (ch == 5)
			{

				for (int a = llim1; a <= ulim1; a++)
				{
					for (int b = llim1; b <= ulim1; b++)
					{

						int x = j + b;
						int y = i + a;


						if (x<0 || x>width)
						{
							x = width - mod(a, width) - 1;

						}


						if (y<0 || y>height)
						{
							y = height - mod(b, height) - 1;
						}

						int rpos1 = (y * width + x) * 3;
						int gpos1 = rpos1 + 1;
						int bpos1 = rpos1 + 2;


						//cout << rpos << endl;
						Rval += img2[rpos1] * edge1[frowc1 + a][frowc1 + b];
						Gval += img2[gpos1] * edge1[frowc1 + a][frowc1 + b];
						Bval += img2[bpos1] * edge1[frowc1 + a][frowc1 + b];


					}

				}

				Rval= 255 - min(max(0, Rval), 255);
				Gval = 255 - min(max(0, Gval), 255);
				Bval = 255 - min(max(0, Bval), 255);

				/*if (Rval >128) { Rval = 255; }
				if (Gval >128) { Gval = 255; }
				if (Bval >128) { Bval = 255; }*/

				pixmap2[rpos] = (Rval + Gval + Bval) / 3;// (Rval + 255) / 2;// abs(mod(Rval, 255));
				pixmap2[gpos] = (Rval + Gval + Bval) / 3;// (Gval + 255) / 2;// abs(mod(Gval, 255));
				pixmap2[bpos] = (Rval + Gval + Bval) / 3;// (Bval + 255) / 2;// abs(mod(Bval, 255));
			}




		}

	}





	stbi_write_jpg("result.jpg", width, height, 3, pixmap2, 100);


}