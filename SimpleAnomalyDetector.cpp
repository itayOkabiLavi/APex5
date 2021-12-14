/*
 * SinpleAnomalyDetector.cpp
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */
#include "SimpleAnomalyDetector.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
using namespace std;

float THRESHOLD = 0.8;
float DISTANCE = 2.5;
SimpleAnomalyDetector::SimpleAnomalyDetector(){
    // TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}
float** SimpleAnomalyDetector:: getPontsFromTs(TimeSeries ts, int f1, int f2){
    float *x = new float[ts.getRCount()];
    float *y = new float[ts.getRCount()];
    ts.copyColumn(f1, x);
    ts.copyColumn(f2, y);
    float **points = new float*[2];
    points[0] = x;
    points[1] = y;
    return points;
}



void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    TimeSeries ts1 = ts;
    for (int f1 = 0; f1 < ts1.getCCount(); ++f1) {
        float m = 0;
        int f2 = 0;
        for (int j = f1 + 1; j < ts1.getCCount(); ++j) {
            float **points = getPontsFromTs(ts1, f1, j);
            float corelation = pearson(points[0], points[1], ts1.getRCount());
            if (corelation > m && corelation > THRESHOLD) {
                m = corelation;
                f2 = j;
            }
        }
        if  (f2 > 0) {
            float maxDev = 0;
            float **points = getPontsFromTs(ts1, f1, f2);
            Point* p[ts1.getRCount()];
            for(int j = 0; j < ts1.getRCount();j++){
                p[j] = new Point(points[0][j],points[1][j]);
            }
            Line line = linear_reg(p ,ts1.getRCount());
            for (int j = 0; j < ts1.getCCount(); j++) {
                Point p = Point(points[0][j],points[1][j]);
                if (maxDev < dev(p, line)) {
                    maxDev = dev(p, line);
                }
            }
            cf.push_back({ts1.getLabelByIndex(f1),
                          ts1.getLabelByIndex(f2),
                          m,
                          line,
                          maxDev,
                          {{0, 0}, 0},
                          true});
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> ar;
    TimeSeries ts1 = ts;
    for(int i = 0; i < cf.size(); i++){
        int f1 = -1;
        int f2 = -1;
        correlatedFeatures correlated = cf.at(i);
        for(int j = 0; j < ts1.getCCount(); j++){
            if(correlated.feature1 == ts1.getLabelByIndex(j)){
                f1 = j;
            }
            if(correlated.feature2 == ts1.getLabelByIndex(j)){
                f2 = j;
            }
        }
        if(f1 != -1 && f2 != -1){
            float **points = getPontsFromTs(ts1, f1, f2);
            for (int j = 0; j < ts1.getRCount(); j++){
                Point p =  Point(points[0][j], points[1][j]);
                if (DISTANCE * correlated.threshold <  dev(p, correlated.lin_reg)){
                    ar.push_back(AnomalyReport(correlated.feature1 + "-" + correlated.feature2,j+1));
                }
            }
        }
    }
    return ar;
}