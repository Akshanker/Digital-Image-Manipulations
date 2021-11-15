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

////ASSIGNMENT 2 - Circles- DIGITAL IMAGE - ANUSHA SHANKER///////////

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

			int circolR = 250, circolG = 203, circolB = 211;
			int bgR = 202, bgG = 157, bgB = 215;
			int bg2R = 133, bg2G = 126, bg2B = 187;
			int bg3R = 127, bg3G = 215, bg3B = 212;
			int bg4R = 233, bg4G = 122, bg4B = 122;

			int Rval = 0, Gval = 0, Bval = 0;

			int r1 = 50;
			int r2 = 100;
			int r3 = 150;
			int r4 = 200;
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


					int c1 = ((i + (m + 0.5) / M + Ri / M) - centre) * ((i + (m + 0.5) / M + Ri / M) - centre) + ((j + (n + 0.5) / N + Rj / M) - centre) * ((j + (n + 0.5) / N + Ri / M) - centre) - r1 * r1;

					int c2 = ((i + (m + 0.5) / M + Ri / M) - centre) * ((i + (m + 0.5) / M + Ri / M) - centre) + ((j + (n + 0.5) / N + Rj / M) - centre) * ((j + (n + 0.5) / N + Ri / M) - centre) - r2 * r2;

					int c3 = ((i + (m + 0.5) / M + Ri / M) - centre) * ((i + (m + 0.5) / M + Ri / M) - centre) + ((j + (n + 0.5) / N + Rj / M) - centre) * ((j + (n + 0.5) / N + Ri / M) - centre) - r3 * r3;

					int c4 = ((i + (m + 0.5) / M + Ri / M) - centre) * ((i + (m + 0.5) / M + Ri / M) - centre) + ((j + (n + 0.5) / N + Rj / M) - centre) * ((j + (n + 0.5) / N + Ri / M) - centre) - r4 * r4;


					if (c1 <= 0)
					{
						Rval += circolR;
						Gval += circolG;
						Bval += circolB;

					}

					else
					{
						if (c2 <= 0)
						{
							Rval += bgR;
							Gval += bgG;
							Bval += bgB;
						}

						else
						{
							if (c3 <= 0)
							{
								Rval += bg2R;
								Gval += bg2G;
								Bval += bg2B;
							}

							else
							{
								if (c4 <= 0)
								{
									Rval += bg3R;
									Gval += bg3G;
									Bval += bg3B;
								}
								else
								{
									Rval += bg4R;
									Gval += bg4G;
									Bval += bg4B;
								}
							}


						}
					}


					

					pixmap[rpos] = Rval / (M * N);
					pixmap[gpos] = Gval / (M * N);
					pixmap[bpos] = Bval / (M * N);

				}
			}


		}
	}

	stbi_write_jpg("circle.jpg", height, width, 3, pixmap, 100);


	}