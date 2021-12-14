/*
 * minCircle.h
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */


#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

float distanceFromCenter(const Point& a, const Point& b);
// you can add here additional methods

#endif /* MINCIRCLE_H_ */