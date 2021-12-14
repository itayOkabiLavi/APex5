/*
 * minCircle.cpp
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */
#include "minCircle.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

float distanceFromCenter(const Point& a, const Point& b){
    return (float)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Circle threePointCicle(const Point& a, const Point& b, const Point& c){
    float X = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    float Y = (c.x - a.x) * (c.x - a.x) + (c.y - a.y) * (c.y - a.y);
    float Z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    Point p = { ((c.y - a.y) * X - (b.y - a.y) * Y) / (2 * Z), ((b.x - a.x) * Y - (c.x - a.x) * X) / (2 * Z) };  
    p.x += a.x;
    p.y += a.y;
    return { p, distanceFromCenter(p, a) };
}

bool validCircle(const Circle& c, const vector<Point>& P){
    for (const Point& p : P)
        if (!(distanceFromCenter(c.center, p) <= c.radius))
            return false;
    return true;
}

Circle minimumCircle(vector<Point>& p){
    if (p.empty()) {
        return { { 0, 0 }, 0 };
    }
    else if (p.size() == 1) {
        return {p[0], 0};
    }
    else if (p.size() == 2) {
        float x = (p[0].x + p[1].x) / 2.0;
        float y = (p[0].y + p[1].y) / 2.0;
        Point r = {x, y};
        return {r, distanceFromCenter(r, p[0])};
    }
    else{
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                float x = (p[i].x + p[j].x) / 2.0;
                float y = (p[i].y + p[j].y) / 2.0;
                Point r = {x, y};
                Circle c = {r, distanceFromCenter(r, p[i])};
                if (validCircle(c, p))
                    return c;
            }
        }
        return threePointCicle(p[0], p[1], p[2]);///###
    }
}

Circle recorsiveAlg(Point** points, int size, std::vector<Point> boundaryPoints){
    if (size == 0 || boundaryPoints.size() == 3){
        return minimumCircle(boundaryPoints);
    }
    Point* p = points[size - 1];
    Circle c = recorsiveAlg(points, size - 1, boundaryPoints);
    if(distanceFromCenter(c.center, *p) <= c.radius){
        return c;
    }
    boundaryPoints.push_back(*p);
    return recorsiveAlg(points, size - 1, boundaryPoints);
}

Circle findMinCircle(Point** points,size_t size){
    Circle c = recorsiveAlg(points, size, {});
    return c;
}