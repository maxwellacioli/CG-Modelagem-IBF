#include <cstdlib>
#include <iostream>
#ifndef POINT_H
#define POINT_H

using namespace std;

class Point 
{
	private:
        double xval, yval;
	public:
        // Constructor uses default arguments to allow calling with zero, one,
        // or two values.
        Point(double x, double y) 
        {
            xval = x;
            yval = y;
        }

        // Extractors.
        double x() { return xval; }
        double y() { return yval; }
}

#endif