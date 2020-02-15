// RollingBall.h : header file
//
#include "StdAfx.h"

class RollingBall
{
public:
	byte* data;
	int patchwidth;
	int shrinkfactor;

	RollingBall(int radius);
    virtual ~RollingBall();

	/** Computes the location of each point on the rolling ball patch relative to the 
	center of the sphere containing it.  The patch is located in the top half 
	of this sphere.  The vertical axis of the sphere passes through the center of 
	the patch.  The projection of the patch in the xy-plane below is a square.
	*/
	void buildRollingBall(int ballradius, int arcTrimPer);

}

RollingBall::RollingBall(int radius)
{
	int arcTrimPer;
	if (radius<=10) {
		shrinkfactor = 1;
		arcTrimPer = 12; // trim 24% in x and y
	} else if (radius<=30) {
		shrinkfactor = 2;
		arcTrimPer = 12; // trim 24% in x and y
	} else if (radius<=100) {
		shrinkfactor = 4;
		arcTrimPer = 16; // trim 32% in x and y
	} else {
		shrinkfactor = 8;
		arcTrimPer = 20; // trim 40% in x and y
	}
	buildRollingBall(radius, arcTrimPer);
}

RollingBall::~RollingBall()
{

}

void RollingBall::buildRollingBall(int ballradius, int arcTrimPer)
{
	int rsquare;        // rolling ball radius squared
	int xtrim;          // # of pixels trimmed off each end of ball to make patch
	int xval, yval;     // x,y-values on patch relative to center of rolling ball
	int smallballradius, diam; // radius and diameter of rolling ball
	int temp;           // value must be >=0 to take square root
	int halfpatchwidth; // distance in x or y from center of patch to any edge
	int ballsize;       // size of rolling ball array

	//shrinkfactor = shrinkfactor;
	smallballradius = ballradius/shrinkfactor;
	if (smallballradius<1)
		smallballradius = 1;
	rsquare = smallballradius*smallballradius;
	diam = smallballradius*2;
	xtrim = (arcTrimPer*diam)/100; // only use a patch of the rolling ball
	patchwidth = diam - xtrim - xtrim;
	halfpatchwidth = smallballradius - xtrim;
	ballsize = (patchwidth+1)*(patchwidth+1);
	data = new byte[ballsize*sizeof(byte)];

	for (int i=0; i<ballsize; i++) {
		xval = i % (patchwidth+1) - halfpatchwidth;
		yval = i / (patchwidth+1) - halfpatchwidth;
		temp = rsquare - (xval*xval) - (yval*yval);
		if (temp >= 0)
			//data[i] = (byte)Math.round(sqrt(temp)); // Java Math.round是求四舍五入取整的意思
			data[i] = (byte)(int)(sqrt((double)temp));
		else
			data[i] = 0;
	}
}