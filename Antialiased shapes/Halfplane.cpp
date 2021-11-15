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

////ASSIGNMENT 2- Half plane- DIGITAL IMAGE - ANUSHA SHANKER///////////

using namespace std;




int main()
{
	int height = 500, width = 500;
	unsigned char* pixmap;
	pixmap = new unsigned char[height * width * 3];


	for (int i = 0; i < height; i++)
	{

		int resultR, resultG, resultB;


		for (int j = 0; j < width; j++)
		{



			int rpos = (i * width + j) * 3;
			int gpos = rpos + 1;
			int bpos = rpos + 2;

			int circolR = 247, circolG = 200, circolB = 108;
			int bgR = 245, bgG = 161, bgB = 184;
			int Rval = 0, Gval = 0, Bval = 0;

			int r = 100;
			int r2 = 200;
			int centre = 250;

			int P1 = 250, P2 = 250;
			int theta = 45;

			int M = 50, N = 50;

			for (int m = 0; m < M; m++)
			{
				for (int n = 0; n < N; n++)
				{


					int Ri = rand() % ((1 / M) + 1);
					int Rj = rand() % ((1 / N) + 1);




					//HALFSPACE//

					int p = cos(theta) * ((i + (m + 0.5) / M + Ri / M) - P1) + sin(theta) * ((j + (n + 0.5) / N + Rj / M) - P2);



					if (p <= 0)
					{
						Rval += circolR;
						Gval += circolG;
						Bval += circolB;



					}


					else
					{
						Rval += bgR;
						Gval += bgG;
						Bval += bgB;
					}

					pixmap[rpos] = Rval / (M * N);
					pixmap[gpos] = Gval / (M * N);
					pixmap[bpos] = Bval / (M * N);

				}
			}


		}
	}

	stbi_write_jpg("halfplane.jpg", height, width, 3, pixmap, 100);


	}