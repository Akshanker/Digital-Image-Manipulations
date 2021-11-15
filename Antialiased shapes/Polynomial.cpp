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

////ASSIGNMENT 2- Polynomial - DIGITAL IMAGE - ANUSHA SHANKER///////////

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

			int circolR = 138, circolG = 198, circolB = 76;
			int bgR = 236, bgG = 242, bgB = 163;
			int bg2R = 7, bg2G = 53, bg2B = 38;

			int Rval = 0, Gval = 0, Bval = 0;

			int r = 100;
			int r2 = 200;
			int centre = 250;

			int P1 = 250, P2 = 250;
			int theta = 90;

			int M = 50, N = 50;

			for (int m = 0; m < M; m++)
			{
				for (int n = 0; n < N; n++)
				{


					int Ri = rand() % ((1 / M) + 1);
					int Rj = rand() % ((1 / N) + 1);


					int p = cos(theta) * ((i + (m + 0.5) / M + Ri / M) - P1) + sin(theta) * ((j + (n + 0.5) / N + Rj / M) - P2);

					double leaf = (pow((((i + (m + 0.5) / M + Ri / M) - centre) * ((i + (m + 0.5) / M + Ri / M) - centre) + ((j + (n + 0.5) / N + Rj / M) - centre) * ((j + (n + 0.5) / N + Ri / M) - centre) - r * r), 3)) - 150 * pow(((i + (m + 0.5) / M + Ri / M) - centre), 3) * pow(((j + (n + 0.5) / N + Rj / M) - centre), 2);// +pow(((i + (m + 0.5) / M + Ri / M) - centre), 2) * 50 * pow(((j + (n + 0.5) / N + Rj / M) - centre), 3);

					

					if (leaf <= 0)
					{
						Rval += circolR;
						Gval += circolG;
						Bval += circolB;

					}

					else
					{
						if (p <= 0)
						{
							Rval += bgR;
							Gval += bgG;
							Bval += bgB;
						}

						else
						{
							Rval += bg2R;
							Gval += bg2G;
							Bval += bg2B;
						}
					}


					

					pixmap[rpos] = Rval / (M * N);
					pixmap[gpos] = Gval / (M * N);
					pixmap[bpos] = Bval / (M * N);

				}
			}


		}
	}

	stbi_write_jpg("Leafpolynomial.jpg", height, width, 3, pixmap, 100);


	}
