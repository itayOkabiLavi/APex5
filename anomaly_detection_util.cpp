/*
 * animaly_detection_util.cpp
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
	float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + *x;
        ++x;
    }
    return sum / size;
}

// returns the mean (miu) of X
float mean(float* x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + *x;
        ++x;
    }
    return sum / size;
}

// returns the variance of X
float var(float* x, int size) {
    float sum = 0;
    float m = mean(x, size);
    float iterValue = 0;
    for (int i = 0; i < size; i++)
    {
        iterValue = (*x - m) * (*x - m);
        sum = sum + iterValue;
        ++x;
    }
    return sum / size;
}

// returns the multiplication of variables (=arrays) X and Y
float* multiplyXY(float* x, float* y, float* z, int size) {
    for (int i = 0; i < size; i++)
    {
        z[i] = (*x) * (*y);
		++x;
		++y;
    }
    return z;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float xy[size];
    float exy = mean(multiplyXY(x, y, xy, size), size);
    float ex = mean(x, size);
    float ey = mean(y, size);
    return exy - (ex * ey);
}

// returns the pearson value of X and Y
float pearson(float* x, float* y, int size) {
    float sx = sqrt(var(x, size));
    float sy = sqrt(var(y, size));
    return cov(x, y, size) / (sx * sy);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size) {
    float x[size];
    float y[size];
    for (int i = 0; i < size; i++)
    {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }

    float a = cov(x, y, size) / var(x, size);
    float b = mean(y, size) - (a * mean(x, size));
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    return dev(p, linear_reg(points, size));
}
 
// returns the deviation between point p and the line
float absolute(float val) {
    if (val < 0) return -1 * val;
    return val;
}

float dev(Point p,Line l) {
    return absolute(p.y - l.f(p.x));
}
