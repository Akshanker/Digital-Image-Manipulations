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

using namespace std;


int main()
{
	//establishing height and width 
	int height = 600;
	int width = 600;

	unsigned char* pixmap;

	//int i = 0;
	//int j = 0;

	pixmap = new unsigned char[height * width * 3]; //height,width,3

	for (int i = 0; i < height; i++) {

		int resultR, resultG, resultB;

		for (int j = 0; j < width; j++) {

			int rpos = (i * width + j) * 3;
			int gpos = rpos + 1;
			int bpos = rpos + 2;

			int bgR = 104, bgG = 110, bgB = 206;
			int inR = 243, inG = 92, inB =110;
			int Rval = 0, Gval = 0, Bval = 0;

			//establishing point x,y 
			int sides = 5;
			int P1 = 300;
			int P2 = 300;

			//establishing theta 
			int theta = 2 * M_PI / sides;
			//int theta = 30;


			//setting factors for antialiasing algorithm 
			int M = 16;
			int N = 16;

			for (int m = 0; m < M; m++)
			{
				for (int n = 0; n < N; n++)
				{

					int Ri = rand() % ((1 / M) + 1);
					int Rj = rand() % ((1 / N) + 1);
					int r1 = 100;
					int number = 0;
					int newmax = 0;

					for (int k = 0; k <= sides; k++)
					{
						//if(cos(k*theta)*((i-Px-r*cos(k*theta))+ sin(k*theta)*((j-Py-r*sin(theta*k))))< 0)
						if (cos(k * theta) * ((i + (m + 0.5) / M + Ri / M) - P1 - r1 * cos(k * theta)) + sin(k * theta) * ((j + (n + 0.5) / N + Rj / M) - P2 - r1 * sin(k * theta)) <= 0)
							number = number + 1;


					}
					newmax = 1;


					if (number <= sides)
						newmax = -1;



					if (newmax <= 0)
					{
						Rval += bgR;
						Gval += bgG;
						Bval += bgB;


					}

					else
					{
						Rval += inR;
						Gval += inG;
						Bval += inB;

					}


					pixmap[rpos] = Rval / (M * N);
					pixmap[gpos] = Gval / (M * N);
					pixmap[bpos] = Bval / (M * N);


				}

			}

		}
		stbi_write_jpg("AApoly.jpg", height, width, 3, pixmap, 100); //name, widt
	}
}