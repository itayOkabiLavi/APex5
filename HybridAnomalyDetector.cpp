/*
 * HybridAnomalyDetector.h
 *
 * Author:	Itay Okabi Lavi 208390559
 * Partner:	Haim Kelif 313377103
 */
#include "HybridAnomalyDetector.h"

const float CORRELATION_THRESHOLD = 0.9;


HybridAnomalyDetector::HybridAnomalyDetector() { }

HybridAnomalyDetector::~HybridAnomalyDetector() { }

Circle HybridAnomalyDetector::createCircleFromFloatList(float **pointsValues, int listSize) {
    Point** points = new Point*[listSize];
    for (int i = 0; i < listSize; ++i) {
        points[i] = new Point(pointsValues[0][i], pointsValues[1][i]);
    }
    Circle circle = findMinCircle(points, listSize);
    return circle;
}

void HybridAnomalyDetector::learnNormal(const TimeSeries &ts) {
    TimeSeries ts1 = ts;
    vector<correlatedFeatures> cf = this->getNormalModel();
    const float threshold = 0.8;
    for (int f1 = 0; f1 < ts1.getCCount(); ++f1) {
        float m = 0;
        int f2 = 0;
        for (int j = f1 + 1; j < ts1.getCCount(); ++j) {
            float **points = getPontsFromTs(ts1, f1, j);
            float corelation = pearson(points[0], points[1], ts1.getRCount());
            if (corelation > m) {
                m = corelation;
                f2 = j;
            }
        }
        float **points = getPontsFromTs(ts1, f1, f2);
        if (m >= threshold) {
            //printf("~linear anomaly\n");
            float maxDev = 0;
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
        } else {
            //printf("~circle anomaly? ");
            if (m > 0.5) {
                //printf("yes\n");
                Circle circle = this->createCircleFromFloatList(points,
                                                                ts1.getRCount());
                cf.push_back({ts1.getLabelByIndex(f1),
                              ts1.getLabelByIndex(f2),
                              m,
                              {0, 0},
                              0,
                              circle,
                              false});
            } //else printf("no\n");
        }
    }
    this->setNormalModel(cf);
}

vector<AnomalyReport> HybridAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> ar;
    TimeSeries ts1 = ts;
    vector<correlatedFeatures> cf = this->getNormalModel();
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
            if (correlated.fromLinear) {
                for (int j = 0; j < ts1.getRCount(); j++) {
                    Point p = Point(points[0][j], points[1][j]);
                    if (2.5 * correlated.threshold < dev(p, correlated.lin_reg)) {
                        ar.push_back(AnomalyReport(correlated.feature1 + "-" + correlated.feature2, j + 1));
                    }
                }
            } else {
                for (int j = 0; j < ts1.getRCount(); j++) {
                    Point p = Point(points[0][j], points[1][j]);
                    if (1.1 * correlated.circle.radius < distanceFromCenter(p,correlated.circle.center)) {
                        ar.push_back(AnomalyReport(correlated.feature1 + "-" + correlated.feature2, j + 1));
                    }
                }
            }
        }
    }
    return ar;
}