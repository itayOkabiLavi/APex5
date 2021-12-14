/*
 * HybridAnomalyDetector.h
 *
 * Author:	Haim Kelif 313377103
 * Partner:	Itay Okabi Lavi 208390559
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
//#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
//#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    void learnNormal(const TimeSeries &ts) override;
    vector<AnomalyReport> detect(const TimeSeries &ts) override;
    Circle createCircleFromFloatList(float** pointsValues, int listSize);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */