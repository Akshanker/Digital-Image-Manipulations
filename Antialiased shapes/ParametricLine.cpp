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

			int bgR = 14, bgG = 33, bgB = 0;
			int inR = 255, inG = 179, inB = 0;
			int in2R = 255, in2G = 96, in2B = 0;
			int Rval = 0, Gval = 0, Bval = 0;

			//establishing point x,y 
			int sides = 5;
			int P1 = 300;
			int P2 = 300;

			//establishing theta 
			int theta = 2 * M_PI / sides;
			//int theta = 30;





			int x0 = 50, y0 = 50;////LINE
			int x1 = 500, y1 = 500;

			int dx = x1 - x0;
			int dy = y1 - y0;
			int d = max(dx, dy);
			int xl = i, yl = j;


			int x2 = 300, y2 = 200;
			int x3 = 400, y3 = 350;

			int dx1 = x3 - x2;
			int dy1 = y3 - y2;
			int d1 = max(dx1, dy1);
			int xl1 = i, yl1 = j;

			Rval = bgR;
			Gval = bgG;
			Bval = bgB;

			for (int k = 0; k <= d; k++)
			{
				xl = x0 + k * dx / d;
				yl = y0 + k * dy / d;




				if (i == xl && j == yl)
				{
					Rval = inR;
					Gval = inG;
					Bval = inB;
				}








			}

			for (int k = 0; k <= d - 1; k++)
			{
				xl1 = x2 + k * dx1 / d1;
				yl1 = y2 + k * dy1 / d1;




				if (i == xl1 && j == yl1)
				{
					Rval = in2R;
					Gval = in2G;
					Bval = in2B;
				}








			}

			pixmap[rpos] = Rval;
			pixmap[gpos] = Gval;
			pixmap[bpos] = Bval;

			
		}
	}
	stbi_write_jpg("Lineparam.jpg", height, width, 3, pixmap, 100); //name, widt

}
